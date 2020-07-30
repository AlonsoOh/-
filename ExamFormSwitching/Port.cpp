/*#include "stdafx.h"
#include "Port.h"

#define MAXBLOCK        80

DWORD BAUD_RATE_TABLE[] = { CBR_38400, CBR_19200, CBR_9600, CBR_4800,CBR_2400, CBR_1200};

// Flow control flags
#define FC_DTRDSR       0x01   //데이터 단말기(DTR) 대기,데이터 세트(DSR) 대기를 위한 신호
#define FC_RTSCTS       0x02
#define FC_XONXOFF      0x04

// ascii definitions
#define ASCII_BEL       0x07
#define ASCII_BS        0x08
#define ASCII_LF        0x0A
#define ASCII_CR        0x0D
#define ASCII_XON       0x11
#define ASCII_XOFF      0x13

// Event Watch용 쓰레드 함수
DWORD CommWatchProc(LPSTR lpData);


BOOL Port::OpenPort(long port_number, long baud_rate_select)
{

	// 포트 상태 관련 변수들을 초기화 한다

	idComDev = 0;
	fConnected = FALSE;
	fLocalEcho = FALSE;
	fAutoWrap = TRUE;
	dwBaudRate = BAUD_RATE_TABLE[baud_rate_select];
	bByteSize = 8;
	bFlowCtrl = FC_XONXOFF;
	bParity = NOPARITY;
	bStopBits = ONESTOPBIT;
	fXonXoff = FALSE;
	fUseCNReceive = TRUE;
	fDisplayErrors = TRUE;
	osWrite.Offset = 0;
	osWrite.OffsetHigh = 0;
	osRead.Offset = 0;
	osRead.OffsetHigh = 0;


	// Overlapped I/O에 쓰이는 Event 객체들을 생성

	// Read를 위한 Event 객체 생성
	osRead.hEvent = CreateEvent(
		NULL,
		TRUE,
		FALSE,
		NULL);
	if (osRead.hEvent == NULL)
		return FALSE;
	

	// Write를 위한 Event 객체 생성
	osWrite.hEvent = CreateEvent(
		NULL,
		TRUE,
		FALSE,
		NULL);

	if (osWrite.hEvent == NULL) {
		CloseHandle(osRead.hEvent);
		return FALSE;
	}


	// 포트를 생성한다
	CString temp;
	//strcpy(temp, "\\\\.\\");
	temp.Format(_T("\\\\.\\"));
	//sprintf(port_name, "COM%d", port_number);
	port_name.Format(_T("COM%d"), port_number);
	//strcat(temp, port_name);
	temp = temp + port_name;
	idComDev = CreateFile(temp,
		GENERIC_READ | GENERIC_WRITE,
		0,
		NULL,
		OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL | FILE_FLAG_OVERLAPPED,	// Overlapped I/O
		NULL);

	if (idComDev == INVALID_HANDLE_VALUE) {
		CloseHandle(osRead.hEvent);
		CloseHandle(osWrite.hEvent);
		return FALSE;
	}

	SetCommMask(idComDev, EV_RXCHAR);
	SetupComm(idComDev, 4096, 4096);	// 버퍼 설정
	PurgeComm(idComDev, PURGE_TXABORT | PURGE_RXABORT |
		PURGE_TXCLEAR | PURGE_RXCLEAR);	// 버퍼의 모든 데이타를 지운다


	// Overlapped I/O를 위한 Time Out 설정
	COMMTIMEOUTS  CommTimeOuts;

	CommTimeOuts.ReadIntervalTimeout = 0xFFFFFFFF;
	CommTimeOuts.ReadTotalTimeoutMultiplier = 0;
	CommTimeOuts.ReadTotalTimeoutConstant = 1000;

	CommTimeOuts.WriteTotalTimeoutMultiplier = 2 * CBR_9600 / dwBaudRate; // CBR_9600 기준 ms당 바이트를 두배까지 설정
	CommTimeOuts.WriteTotalTimeoutConstant = 0;
	SetCommTimeouts(idComDev, &CommTimeOuts);

	// 포트를 사용가능 상태로 만들고 Event를 감시할 쓰레드를 생성한다
	if (SetupConnection() == TRUE) {
		fConnected = TRUE;

		// 쓰레드 생성
		hWatchThread = CreateThread(
			(LPSECURITY_ATTRIBUTES)NULL,
			0,
			(LPTHREAD_START_ROUTINE)CommWatchProc,
			(LPVOID)this,
			0,
			&dwThreadID);

		if (hWatchThread == NULL)	// 쓰레드 생성 실패
		{
			fConnected = FALSE;

			CloseHandle(osRead.hEvent);
			CloseHandle(osWrite.hEvent);
			CloseHandle(idComDev);
			return FALSE;
		}

		else {
			// 장치에 DTR(Data-Terminal-Ready)을 알린다
			EscapeCommFunction(idComDev, SETDTR);
		}
	}

	else {
		fConnected = FALSE;

		CloseHandle(osRead.hEvent);
		CloseHandle(osWrite.hEvent);
		CloseHandle(idComDev);
		return FALSE;
	}
	return TRUE;
}

BOOL Port::SetupConnection(void)
{
	// DCB 구조체를 이용하여 포트를 셋팅한다
	BYTE       bSet;
	DCB        dcb;

	dcb.DCBlength = sizeof(DCB);

	GetCommState(idComDev, &dcb);

	dcb.BaudRate = dwBaudRate;
	dcb.ByteSize = bByteSize;
	dcb.Parity = bParity;
	dcb.StopBits = bStopBits;

	// setup hardware flow control

	bSet = (BYTE)((bFlowCtrl & FC_DTRDSR) != 0);
	dcb.fOutxDsrFlow = bSet;
	if (bSet)
		dcb.fDtrControl = DTR_CONTROL_HANDSHAKE;
	else
		dcb.fDtrControl = DTR_CONTROL_ENABLE;

	bSet = (BYTE)((bFlowCtrl & FC_RTSCTS) != 0);
	dcb.fOutxCtsFlow = bSet;
	if (bSet)
		dcb.fRtsControl = RTS_CONTROL_HANDSHAKE;
	else
		dcb.fRtsControl = RTS_CONTROL_ENABLE;

	// setup software flow control

	bSet = (BYTE)((bFlowCtrl & FC_XONXOFF) != 0);

	dcb.fInX = dcb.fOutX = bSet;
	dcb.XonChar = ASCII_XON;
	dcb.XoffChar = ASCII_XOFF;
	dcb.XonLim = 100;
	dcb.XoffLim = 100;

	// other various settings

	dcb.fBinary = TRUE;
	dcb.fParity = TRUE;

	return SetCommState(idComDev, &dcb);
}

long Port::ReadCommBlock(LPSTR lpszBlock, long nMaxLength)
{
	BOOL       fReadStat;
	COMSTAT    ComStat;
	DWORD      dwErrorFlags;
	DWORD      dwLength;
	DWORD      dwError;
	char       szError[10];

	// 큐에서 읽어야 할 데이타 크기를 가져온다
	ClearCommError(idComDev, &dwErrorFlags, &ComStat);
	dwLength = min((DWORD)nMaxLength, ComStat.cbInQue);

	if (dwLength > 0)	// 읽어야 할 데이타가 있는 경우
	{
		// 데이타를 읽는다. Overlapped I/O임을 주의.
		fReadStat = ReadFile(idComDev, lpszBlock,
			dwLength, &dwLength, &osRead);
		if (!fReadStat)	// 읽어야 할 바이트를 다 읽지 못했다
		{
			if (GetLastError() == ERROR_IO_PENDING)	// I/O Pending에 의해 다 읽지 못한 경우
			{
				// I/O가 완료되기를 기다린다.
				while (!GetOverlappedResult(idComDev,
					&osRead, &dwLength, TRUE))
				{
					dwError = GetLastError();
					if (dwError == ERROR_IO_INCOMPLETE)	// I/O가 아직 끝나지 않았다
						continue;
					else	// 에러 발생
					{
						sprintf(szError, "<CE-%u>\n\r", dwError);
						printf(szError);
						// 에러를 클리어 하고 다른 I/O가 가능하도록 한다
						ClearCommError(idComDev, &dwErrorFlags, &ComStat);
						break;
					}

				}

			}
			else // I/O Pending이 아닌 다른 에러가 발생한 경우
			{
				dwLength = 0;
				// 에러를 클리어 하고 다른 I/O가 가능하도록 한다
				ClearCommError(idComDev, &dwErrorFlags, &ComStat);
			}
		}
	}

	return (dwLength);

}

BOOL Port::WriteCommBlock(LPSTR lpByte, DWORD dwBytesToWrite)
{

	BOOL        fWriteStat;
	DWORD       dwBytesWritten;
	DWORD       dwErrorFlags;
	DWORD   	dwError;
	DWORD       dwBytesSent = 0;
	COMSTAT     ComStat;
	CString     szError;

	fWriteStat = WriteFile(idComDev, lpByte, dwBytesToWrite,
		&dwBytesWritten, &osWrite);

	if (!fWriteStat)	// 써야할 바이트를 다 쓰지 못했다
	{
		if (GetLastError() == ERROR_IO_PENDING)	// I/O Pending에 의한 경우
		{
			// I/O가 완료되기를 기다린다
			while (!GetOverlappedResult(idComDev,
				&osWrite, &dwBytesWritten, TRUE))
			{
				dwError = GetLastError();
				if (dwError == ERROR_IO_INCOMPLETE)
				{
					// 보낸 전체 바이트 수를 체크
					dwBytesSent += dwBytesWritten;
					continue;
				}
				else
				{
					// 에러 발생
					//sprintf(szError, "<CE-%u>", dwError);
					szError.Format(_T("<CE-%u>"), dwError);
					printf("%s\r\n", szError);
					//WriteTTYBlock( hWnd, szError, lstrlen( szError ) ) ;
					ClearCommError(idComDev, &dwErrorFlags, &ComStat);
					break;
				}
			}

			dwBytesSent += dwBytesWritten;

			if (dwBytesSent != dwBytesToWrite)	// 보내야 할 바이트와 보낸 바이트가 일치하지 않는 경우
				//sprintf(szError, "\nProbable Write Timeout: Total of %ld bytes sent", dwBytesSent);
				szError.Format(_T("\nProbable Write Timeout: Total of %ld bytes sent>"), dwBytesSent);
			else	// 성공적으로 모두 보낸 경우
				//sprintf(szError, "\n%ld bytes written", dwBytesSent);
				szError.Format(_T("\n%ld bytes written"), dwBytesSent);

			OutputDebugString(szError);
		}
		else // I/O Pending 외의 다른 에러
		{
			ClearCommError(idComDev, &dwErrorFlags, &ComStat);
			return FALSE;
		}
	}


	return TRUE;

}

BOOL Port::ClosePort(void)
{
	fConnected = FALSE;

	// 이벤트 발생을 중지한다
	SetCommMask(idComDev, 0);

	// Event Watch 쓰레드가 중지되기를 기다린다
	while (dwThreadID != 0);


	// DTR(Data-Terminal-Ready) 시그널을 Clear 한다
	EscapeCommFunction(idComDev, CLRDTR);

	// 대기중인 모든 데이타를 지운다	
	PurgeComm(idComDev, PURGE_TXABORT | PURGE_RXABORT |
		PURGE_TXCLEAR | PURGE_RXCLEAR);

	// 핸들을 반환한다
	CloseHandle(osRead.hEvent);
	CloseHandle(osWrite.hEvent);
	CloseHandle(idComDev);

	return TRUE;

}

// Event Watch 쓰레드
DWORD CommWatchProc(LPSTR lpData)
{
	DWORD       dwEvtMask;
	Port* pp = (Port*)lpData;
	OVERLAPPED  os;
	long        nLength;
	BYTE       abIn[MAXBLOCK + 1];

	memset(&os, 0, sizeof(OVERLAPPED));

	// Event 객체 생성
	os.hEvent = CreateEvent(
		NULL,
		TRUE,
		FALSE,
		NULL);

	if (os.hEvent == NULL)
		return FALSE;

	if (!SetCommMask(pp->idComDev, EV_RXCHAR))
	{
		CloseHandle(os.hEvent);
		return FALSE;
	}

	while (pp->fConnected)
	{
		dwEvtMask = 0;

		// Event가 발생할 때 까지 블럭
		WaitCommEvent(pp->idComDev, &dwEvtMask, NULL);
		// MSDN 상의 설명과는 달리 WaitCommEvent의 마지막 매개 변수가 NULL이다
		// 설명에 의하면 FILE_FLAG_OVERLAPPED로 생성된 경우 반드시 NULL이 아닌 Overlapped
		// 구조체를 사용해야 한다고 되어있으나 몇몇 샘플을 검토한 결과 오히려 Code 87 에러가
		// 발생한다
		// 이런 이유로 os의 Event 객체는 별 의미가 없다
		// 또한 이런 이유로 멀티 쓰레드가 아닌 단일 쓰레드에서는 Overlapped I/O를 사용하는
		// 의미가 없을 것 같다 ( Polling 시 블럭되기 때문)

		if ((dwEvtMask & EV_RXCHAR) == EV_RXCHAR)
		{
			do
			{
				if (nLength = pp->ReadCommBlock((LPSTR)abIn, MAXBLOCK))
				{
					//작업 예외 처리
				}
			} while (nLength > 0);
		}
		else
		{
			printf("<Other Event>\r\n");
		}
	}

	CloseHandle(os.hEvent);

	pp->dwThreadID = 0;
	pp->hWatchThread = NULL;

	return TRUE;

}*/

#include "stdafx.h"
#include "Port.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//IMPLEMENT_DYNCREATE(Port, CCmdTarget)
Port::Port() {

}


Port::Port(CString port, CString baudrate, CString parity, CString databit, CString stopbit)
{
	m_sComPort = port;
	m_sBaudRate = baudrate;
	m_sParity = parity;
	m_sDataBit = databit;
	m_sStopBit = stopbit;
	m_bFlowChk = 1;
	m_bIsOpenned = FALSE;
	m_nLength = 0;
	memset(m_sInBuf, 0, MAXBUF * 2);
	m_pEvent = new CEvent(FALSE, TRUE);
}

Port::~Port()
{
	if (m_bIsOpenned)
		Close();
	delete m_pEvent;
}


BEGIN_MESSAGE_MAP(Port, CCmdTarget)
	//{{AFX_MSG_MAP(Port)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

//Port message handler
void Port::ResetSerial()
{
	DCB		dcb;
	DWORD	DErr;
	COMMTIMEOUTS	CommTimeOuts;

	if (!m_bIsOpenned)
		return;

	ClearCommError(m_hComDev, &DErr, NULL);
	SetupComm(m_hComDev, InBufSize, OutBufSize);
	PurgeComm(m_hComDev, PURGE_TXABORT | PURGE_RXABORT | PURGE_TXCLEAR | PURGE_RXCLEAR);

	// set up for overlapped I/O
	CommTimeOuts.ReadIntervalTimeout = MAXDWORD;
	CommTimeOuts.ReadTotalTimeoutMultiplier = 0;
	CommTimeOuts.ReadTotalTimeoutConstant = 0;

	// CBR_9600 is approximately 1byte/ms. For our purposes, allow
	// double the expected time per character for a fudge factor.
	CommTimeOuts.WriteTotalTimeoutMultiplier = 0;
	CommTimeOuts.WriteTotalTimeoutConstant = 1000;
	SetCommTimeouts(m_hComDev, &CommTimeOuts);


	memset(&dcb, 0, sizeof(DCB));
	dcb.DCBlength = sizeof(DCB);

	GetCommState(m_hComDev, &dcb);

	dcb.fBinary = TRUE;
	dcb.fParity = TRUE;

	if (m_sBaudRate == "300")
		dcb.BaudRate = CBR_300;
	else if (m_sBaudRate == "600")
		dcb.BaudRate = CBR_600;
	else if (m_sBaudRate == "1200")
		dcb.BaudRate = CBR_1200;
	else if (m_sBaudRate == "2400")
		dcb.BaudRate = CBR_2400;
	else if (m_sBaudRate == "4800")
		dcb.BaudRate = CBR_4800;
	else if (m_sBaudRate == "9600")
		dcb.BaudRate = CBR_9600;
	else if (m_sBaudRate == "14400")
		dcb.BaudRate = CBR_14400;
	else if (m_sBaudRate == "19200")
		dcb.BaudRate = CBR_19200;
	else if (m_sBaudRate == "28800")
		dcb.BaudRate = CBR_38400;
	else if (m_sBaudRate == "33600")
		dcb.BaudRate = CBR_38400;
	else if (m_sBaudRate == "38400")
		dcb.BaudRate = CBR_38400;
	else if (m_sBaudRate == "56000")
		dcb.BaudRate = CBR_56000;
	else if (m_sBaudRate == "57600")
		dcb.BaudRate = CBR_57600;
	else if (m_sBaudRate == "115200")
		dcb.BaudRate = CBR_115200;
	else if (m_sBaudRate == "128000")
		dcb.BaudRate = CBR_128000;
	else if (m_sBaudRate == "256000")
		dcb.BaudRate = CBR_256000;
	else if (m_sBaudRate == "PCI_9600")
		dcb.BaudRate = 1075;
	else if (m_sBaudRate == "PCI_19200")
		dcb.BaudRate = 2212;
	else if (m_sBaudRate == "PCI_38400")
		dcb.BaudRate = 4300;
	else if (m_sBaudRate == "PCI_57600")
		dcb.BaudRate = 6450;
	else if (m_sBaudRate == "PCI_500K")
		dcb.BaudRate = 56000;


	if (m_sParity == "None")
		dcb.Parity = NOPARITY;
	else if (m_sParity == "Even")
		dcb.Parity = EVENPARITY;
	else if (m_sParity == "Odd")
		dcb.Parity = ODDPARITY;

	if (m_sDataBit == "7 Bit")
		dcb.ByteSize = 7;
	else if (m_sDataBit == "8 Bit")
		dcb.ByteSize = 8;

	if (m_sStopBit == "1 Bit")
		dcb.StopBits = ONESTOPBIT;
	else if (m_sStopBit == "1.5 Bit")
		dcb.StopBits = ONE5STOPBITS;
	else if (m_sStopBit == "2 Bit")
		dcb.StopBits = TWOSTOPBITS;

	dcb.fRtsControl = RTS_CONTROL_ENABLE;
	dcb.fDtrControl = DTR_CONTROL_ENABLE;
	dcb.fOutxDsrFlow = FALSE;

	if (m_bFlowChk) {
		dcb.fOutX = FALSE;
		dcb.fInX = FALSE;
		dcb.XonLim = 2048;
		dcb.XoffLim = 1024;
	}
	else {
		dcb.fOutxCtsFlow = TRUE;
		dcb.fRtsControl = RTS_CONTROL_HANDSHAKE;
	}

	SetCommState(m_hComDev, &dcb);
	SetCommMask(m_hComDev, EV_RXCHAR);

}

void Port::Close()
{
	if (!m_bIsOpenned)
		return;

	m_bIsOpenned = FALSE;
	SetCommMask(m_hComDev, 0);
	EscapeCommFunction(m_hComDev, CLRDTR);
	PurgeComm(m_hComDev, PURGE_TXABORT | PURGE_RXABORT | PURGE_TXCLEAR | PURGE_RXCLEAR);
	Sleep(500);

}

UINT CommThread(LPVOID lpData)
{
	extern short g_nRemoteStatus;
	DWORD       ErrorFlags;
	COMSTAT     ComStat;
	DWORD	EvtMask;
	char	buf[MAXBUF];
	DWORD	Length;
	int	size;
	int	insize = 0;

	Port* Comm = (Port*)lpData;

	while (Comm->m_bIsOpenned) {
		EvtMask = 0;
		Length = 0;
		insize = 0;
		memset(buf, '\0', MAXBUF);
		WaitCommEvent(Comm->m_hComDev, &EvtMask, NULL);
		ClearCommError(Comm->m_hComDev, &ErrorFlags, &ComStat);
		if ((EvtMask & EV_RXCHAR) && ComStat.cbInQue) {
			if (ComStat.cbInQue > MAXBUF)
				size = MAXBUF;
			else
				size = ComStat.cbInQue;
			do {
				ClearCommError(Comm->m_hComDev, &ErrorFlags, &ComStat);
				if (!ReadFile(Comm->m_hComDev, buf + insize, size, &Length, &(Comm->m_OLR))) {
					// 에러
					TRACE("Error in ReadFile\n");
					if (GetLastError() == ERROR_IO_PENDING) {
						if (WaitForSingleObject(Comm->m_OLR.hEvent, 1000) != WAIT_OBJECT_0)
							Length = 0;
						else
							GetOverlappedResult(Comm->m_hComDev, &(Comm->m_OLR), &Length, FALSE);
					}
					else
						Length = 0;
				}
				insize += Length;
			} while ((Length != 0) && (insize < size));
			ClearCommError(Comm->m_hComDev, &ErrorFlags, &ComStat);

			if (Comm->m_nLength + insize > MAXBUF * 2)
				insize = (Comm->m_nLength + insize) - MAXBUF * 2;

			Comm->m_pEvent->ResetEvent();
			memcpy(Comm->m_sInBuf + Comm->m_nLength, buf, insize);
			Comm->m_nLength += insize;
			Comm->m_pEvent->SetEvent();
			LPARAM temp = (LPARAM)Comm;
			SendMessage(Comm->m_hWnd, WM_MYRECEIVE, Comm->m_nLength, temp);


		}
	}
	PurgeComm(Comm->m_hComDev, PURGE_TXABORT | PURGE_RXABORT | PURGE_TXCLEAR | PURGE_RXCLEAR);
	LPARAM temp = (LPARAM)Comm;
	SendMessage(Comm->m_hWnd, WM_MYCLOSE, 0, temp);
	return 0;
}

void Port::HandleClose()
{
	CloseHandle(m_hComDev);
	CloseHandle(m_OLR.hEvent);
	CloseHandle(m_OLW.hEvent);

}

BOOL Port::Create(HWND hWnd)
{
	m_hWnd = hWnd;

	m_hComDev = CreateFile(m_sComPort, GENERIC_READ | GENERIC_WRITE,
		0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL | FILE_FLAG_OVERLAPPED,
		NULL);

	if (m_hComDev != INVALID_HANDLE_VALUE)
		m_bIsOpenned = TRUE;
	else
		return FALSE;

	ResetSerial();

	m_OLW.Offset = 0;
	m_OLW.OffsetHigh = 0;
	m_OLR.Offset = 0;
	m_OLR.OffsetHigh = 0;

	m_OLR.hEvent = CreateEvent(NULL, TRUE, FALSE, NULL);
	if (m_OLR.hEvent == NULL) {
		CloseHandle(m_OLR.hEvent);
		return FALSE;
	}
	m_OLW.hEvent = CreateEvent(NULL, TRUE, FALSE, NULL);
	if (m_OLW.hEvent == NULL) {
		CloseHandle(m_OLW.hEvent);
		return FALSE;
	}
	AfxBeginThread(CommThread, (LPVOID)this);
	EscapeCommFunction(m_hComDev, SETDTR);
	return TRUE;

}

BOOL Port::Send(LPCTSTR outbuf, int len)
{
	BOOL	bRet = TRUE;
	DWORD       ErrorFlags;
	COMSTAT     ComStat;

	DWORD       BytesWritten;
	DWORD       BytesSent = 0;

	ClearCommError(m_hComDev, &ErrorFlags, &ComStat);
	if (!WriteFile(m_hComDev, outbuf, len, &BytesWritten, &m_OLW)) {
		if (GetLastError() == ERROR_IO_PENDING) {
			if (WaitForSingleObject(m_OLW.hEvent, 1000) != WAIT_OBJECT_0)
				bRet = FALSE;
			else
				GetOverlappedResult(m_hComDev, &m_OLW, &BytesWritten, FALSE);
		}
		else /* I/O error */
			bRet = FALSE; /* ignore error */
	}

	ClearCommError(m_hComDev, &ErrorFlags, &ComStat);

	return bRet;

}

int Port::Receive(LPSTR inbuf, int len)
{
	CSingleLock lockObj((CSyncObject*)m_pEvent, FALSE);
	// argument value is not valid
	if (len == 0)
		return -1;
	else if (len > MAXBUF)
		return -1;

	if (m_nLength == 0) {
		inbuf[0] = '\0';
		return 0;
	}
	else if (m_nLength <= len) {
		lockObj.Lock();
		memcpy(inbuf, m_sInBuf, m_nLength);
		memset(m_sInBuf, 0, MAXBUF * 2);
		int tmp = m_nLength;
		m_nLength = 0;
		lockObj.Unlock();
		return tmp;
	}
	else {
		lockObj.Lock();
		memcpy(inbuf, m_sInBuf, len);
		memmove(m_sInBuf, m_sInBuf + len, MAXBUF * 2 - len);
		m_nLength -= len;
		lockObj.Unlock();
		return len;
	}
}

void Port::Clear()
{
	PurgeComm(m_hComDev, PURGE_TXABORT | PURGE_RXABORT | PURGE_TXCLEAR | PURGE_RXCLEAR);
	memset(m_sInBuf, 0, MAXBUF * 2);
	m_nLength = 0;

}