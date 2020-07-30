// CMyForm4.cpp: 구현 파일
//

#include "stdafx.h"
#include "afxdialogex.h"
#include "ExamFormSwitching.h"
#include "CMyForm4.h"
#include "Port.h"


// CMyForm4

IMPLEMENT_DYNCREATE(CMyForm4, CFormView)

CMyForm4::CMyForm4()
	: CFormView(IDD_FORM_FORM4)
{

}

CMyForm4::CMyForm4(UINT nIDTemplate)
	: CFormView(nIDTemplate)
{

}

CMyForm4::~CMyForm4()
{
}

void CMyForm4::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	/*DDX_Control(pDX, IDC_COMBO1, record_type);
	DDX_Control(pDX, IDC_COMBO2, data_num);
	DDX_Control(pDX, IDC_COMBO4, alarm_state);
	DDX_Control(pDX, IDC_EDIT10, FR_temp);
	DDX_Control(pDX, IDC_EDIT11, FR_output_volt);
	DDX_Control(pDX, IDC_EDIT12, FR_load_curr);
	DDX_Control(pDX, IDC_EDIT13, FR_batt_curr);
	DDX_Control(pDX, IDC_EDIT14, FR_rv);
	DDX_Control(pDX, IDC_EDIT16, FR_sv);
	DDX_Control(pDX, IDC_EDIT18, FR_tv);
	DDX_Control(pDX, IDC_EDIT15, FR_rc);
	DDX_Control(pDX, IDC_EDIT17, FR_sc);
	DDX_Control(pDX, IDC_EDIT19, FR_tc);
	DDX_Control(pDX, IDC_EDIT86, facility_no);
	DDX_Control(pDX, IDC_EDIT87, monitor_point);
	DDX_Control(pDX, IDC_EDIT88, alarm_data);
	DDX_Control(pDX, IDC_EDIT90, set_data);
	DDX_Control(pDX, IDC_EDIT91, alarm_date);
	DDX_Control(pDX, IDC_EDIT89, alarm_time);*/
	DDX_Control(pDX, IDC_EDIT1, send_box);
	DDX_Control(pDX, IDC_EDIT2, record_box);
}

BEGIN_MESSAGE_MAP(CMyForm4, CFormView)
	//ON_BN_CLICKED(IDC_BUTTON2, &CMyForm4::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON1, &CMyForm4::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CMyForm4::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CMyForm4::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &CMyForm4::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON5, &CMyForm4::OnBnClickedButton5)
	ON_BN_CLICKED(IDC_BUTTON6, &CMyForm4::OnBnClickedButton6)
	ON_BN_CLICKED(IDC_BUTTON7, &CMyForm4::OnBnClickedButton7)
	ON_BN_CLICKED(IDC_BUTTON8, &CMyForm4::OnBnClickedButton8)
	ON_BN_CLICKED(IDC_BUTTON9, &CMyForm4::OnBnClickedButton9)
	ON_BN_CLICKED(IDC_BUTTON10, &CMyForm4::OnBnClickedButton10)
	ON_BN_CLICKED(IDC_BUTTON11, &CMyForm4::OnBnClickedButton11)
	ON_BN_CLICKED(IDC_BUTTON12, &CMyForm4::OnBnClickedButton12)
	ON_BN_CLICKED(IDC_BUTTON13, &CMyForm4::OnBnClickedButton13)
	ON_BN_CLICKED(IDC_BUTTON14, &CMyForm4::OnBnClickedButton14)
	ON_EN_CHANGE(IDC_EDIT2, &CMyForm4::OnEnChangeEdit2)
END_MESSAGE_MAP()


BOOL CMyForm4::Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.

	return CFormView::Create(lpszClassName, lpszWindowName, dwStyle, rect, pParentWnd, nID, pContext);
}


void CMyForm4::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();
	/*this->record_type.InsertString(0, _T("정시이력 데이터"));
	this->record_type.InsertString(1, _T("교류배전부 경보이력 데이터"));
	this->record_type.InsertString(2, _T("직류배전부 경보이력 데이터"));
	this->record_type.InsertString(3, _T("정류유니트부 경보이력 데이터"));
	this->record_type.InsertString(4, _T("축전지셀 경보이력 데이터"));

	for (int i = 1; i <= 168; i++) {
		CString str;
		str.Format(_T("%d"), i);
		this->data_num.InsertString(i - 1, str);	
	}

	this->alarm_state.InsertString(0, _T("None"));
	this->alarm_state.InsertString(1, _T("Low"));
	this->alarm_state.InsertString(2, _T("High"));
	this->alarm_state.InsertString(3, _T("Fail"));*/
	
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
}


// CMyForm4 진단

#ifdef _DEBUG
void CMyForm4::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CMyForm4::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CMyForm4 메시지 처리기


/*void CMyForm4::OnBnClickedButton2()
{
	CTime cTime = CTime::GetCurrentTime();
	CString strDate, strTime; // 반환되는 날짜와 시간을 저장할 CString 변수 선언

	strDate.Format(_T("%04d-%02d-%02d"), cTime.GetYear(), cTime.GetMonth(), cTime.GetDay());
	strTime.Format(_T("%02d:%02d:%02d"), cTime.GetHour(), cTime.GetMinute(), cTime.GetSecond());
	switch (record_type.GetCurSel()) {
	case 0:
		FR_activate(1);
		AR_activate(0);

		data_num.SetCurSel(0);
		FR_temp.SetWindowTextA(_T("0.0"));
		FR_output_volt.SetWindowTextA(_T("0.0"));
		FR_load_curr.SetWindowTextA(_T("0.0"));
		FR_batt_curr.SetWindowTextA(_T("0.0"));
		FR_rv.SetWindowTextA(_T("0.0"));
		FR_sv.SetWindowTextA(_T("0.0"));
		FR_tv.SetWindowTextA(_T("0.0"));
		FR_rc.SetWindowTextA(_T("0.0"));
		FR_sc.SetWindowTextA(_T("0.0"));
		FR_tc.SetWindowTextA(_T("0.0"));
		break;

	case 1:
	case 2:
	case 3:
	case 4:
		FR_activate(0);
		AR_activate(1);

		alarm_state.SetCurSel(0);
		facility_no.SetWindowTextA(_T("1"));
		monitor_point.SetWindowTextA(_T("1"));
		alarm_data.SetWindowTextA(_T("0"));
		set_data.SetWindowTextA(_T("0"));
		alarm_date.SetWindowTextA(strDate);
		alarm_time.SetWindowTextA(strTime);
		break;
	}
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}

void CMyForm4::FR_activate(BOOL set) {
	data_num.EnableWindow(set);
	FR_temp.EnableWindow(set);
	FR_output_volt.EnableWindow(set);
	FR_load_curr.EnableWindow(set);
	FR_batt_curr.EnableWindow(set);
	FR_rv.EnableWindow(set);
	FR_sv.EnableWindow(set);
	FR_tv.EnableWindow(set);
	FR_rc.EnableWindow(set);
	FR_sc.EnableWindow(set);
	FR_tc.EnableWindow(set);

	if (!set) {
		data_num.SetCurSel(-1);
		FR_temp.SetWindowTextA(_T(""));
		FR_output_volt.SetWindowTextA(_T(""));
		FR_load_curr.SetWindowTextA(_T(""));
		FR_batt_curr.SetWindowTextA(_T(""));
		FR_rv.SetWindowTextA(_T(""));
		FR_sv.SetWindowTextA(_T(""));
		FR_tv.SetWindowTextA(_T(""));
		FR_rc.SetWindowTextA(_T(""));
		FR_sc.SetWindowTextA(_T(""));
		FR_tc.SetWindowTextA(_T(""));
	}
}

void CMyForm4::AR_activate(BOOL set) {
	alarm_state.EnableWindow(set);
	facility_no.EnableWindow(set);
	monitor_point.EnableWindow(set);
	alarm_data.EnableWindow(set);
	set_data.EnableWindow(set);
	alarm_date.EnableWindow(set);
	alarm_time.EnableWindow(set);

	if (!set) {
		alarm_state.SetCurSel(-1);
		facility_no.SetWindowTextA(_T(""));
		monitor_point.SetWindowTextA(_T(""));
		alarm_data.SetWindowTextA(_T(""));
		set_data.SetWindowTextA(_T(""));
		alarm_date.SetWindowTextA(_T(""));
		alarm_time.SetWindowTextA(_T(""));
	}
}*/


void CMyForm4::OnBnClickedButton1()
{
	CString str;
	send_box.GetWindowTextA(str);
	str += "\r\n\n";
	/*test_port = new Port(_T("\\\\.\\COM5"), _T("38400"), _T("None"), _T("8 bit"), _T("1 bit"));
	test_port->Send(str, str.GetLength());

	test_port->Close();
	test_port->HandleClose();
	test_port->Clear();
	test_port = NULL;*/
	record_box.ReplaceSel("[S] ");
	record_box.ReplaceSel(str);
	record_box.LineScroll(record_box.GetLineCount());
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}

unsigned char CMyForm4::get_crc(CString data) {
	int sum = 0;
	for (int i = 1; i < data.GetLength() - 1; i++)
		sum += data.GetAt(i);

	return (char)(sum % 256);
}


void CMyForm4::OnBnClickedButton2()
{
	CString send_data, temp;
	LPSTR write_buff;
	test_port = new Port(_T("\\\\.\\COM5"), _T("38400"), _T("None"), _T("8 bit"), _T("1 bit"));

	if (test_port->Create(GetSafeHwnd()) != 0) {
		send_data += (unsigned char)0xC5;
		send_data += _T("sMAD");

		send_data += _T("210");
		send_data += _T("120");
		send_data += _T("110");
		send_data += _T("060");

		send_data += '/';
		send_data += (unsigned char)0xCA;
		send_data += get_crc(send_data);
		send_data.Insert(1, (unsigned char)send_data.GetLength() - 3);

		write_buff = send_data.GetBuffer(0);
		test_port->Send(write_buff, send_data.GetLength());
	}

	test_port->Close();
	test_port->HandleClose();
	test_port->Clear();
	test_port = NULL;
		// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void CMyForm4::OnBnClickedButton3()
{
	CString send_data, temp;
	LPSTR write_buff;
	test_port = new Port(_T("\\\\.\\COM5"), _T("38400"), _T("None"), _T("8 bit"), _T("1 bit"));

	if (test_port->Create(GetSafeHwnd()) != 0) {
		send_data += (unsigned char)0xC5;
		send_data += "sMDC";

		send_data += _T("585");
		send_data += _T("540");
		send_data += _T("490");

		send_data += '/';
		send_data += (unsigned char)0xCA;
		send_data += get_crc(send_data);
		send_data.Insert(1, (unsigned char)send_data.GetLength() - 3);

		write_buff = send_data.GetBuffer(0);
		test_port->Send(write_buff, send_data.GetLength());

		//send_data += "\r\n";
		//record_box.ReplaceSel(send_data);
	}

	test_port->Close();
	test_port->HandleClose();
	test_port->Clear();
	test_port = NULL;
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void CMyForm4::OnBnClickedButton4()
{
	CString send_data, temp;
	LPSTR write_buff;
	test_port = new Port(_T("\\\\.\\COM5"), _T("38400"), _T("None"), _T("8 bit"), _T("1 bit"));

	if (test_port->Create(GetSafeHwnd()) != 0) {
		send_data += (char)0xC5;
		send_data += "sMRU";

		send_data += _T("585");
		send_data += _T("540");

		send_data += '/';
		send_data += (char)0xCA;
		send_data += get_crc(send_data);
		send_data.Insert(1, (char)send_data.GetLength() - 3);

		write_buff = send_data.GetBuffer(0);
		test_port->Send(write_buff, send_data.GetLength());

		//send_data += "\r\n";
		//record_box.ReplaceSel(send_data);
	}

	test_port->Close();
	test_port->HandleClose();
	test_port->Clear();
	test_port = NULL;
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void CMyForm4::OnBnClickedButton5()
{
	CString send_data, temp;
	LPSTR write_buff;
	test_port = new Port(_T("\\\\.\\COM5"), _T("38400"), _T("None"), _T("8 bit"), _T("1 bit"));

	if (test_port->Create(GetSafeHwnd()) != 0) {
		send_data += (char)0xC5;
		send_data += "sMBC";

		send_data += _T("8000");
		send_data += _T("2500");
		send_data += _T("250");
		send_data += _T("105");

		send_data += '/';
		send_data += (char)0xCA;
		send_data += get_crc(send_data);
		send_data.Insert(1, (char)send_data.GetLength() - 3);

		write_buff = send_data.GetBuffer(0);
		test_port->Send(write_buff, send_data.GetLength());

		//send_data += "\r\n";
		//record_box.ReplaceSel(send_data);
	}

	test_port->Close();
	test_port->HandleClose();
	test_port->Clear();
	test_port = NULL;
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void CMyForm4::OnBnClickedButton6()
{
	CString send_data, temp;
	LPSTR write_buff;
	test_port = new Port(_T("\\\\.\\COM5"), _T("38400"), _T("None"), _T("8 bit"), _T("1 bit"));

	if (test_port->Create(GetSafeHwnd()) != 0) {
		send_data += (char)0xC5;
		send_data += "sOTS/oT";

		send_data += _T("20190101");
		send_data += _T("070000");

		send_data += '/';
		send_data += (char)0xCA;
		send_data += get_crc(send_data);
		send_data.Insert(1, (char)send_data.GetLength() - 3);

		write_buff = send_data.GetBuffer(0);
		test_port->Send(write_buff, send_data.GetLength());

		//send_data += "\r\n";
		//record_box.ReplaceSel(send_data);
	}

	test_port->Close();
	test_port->HandleClose();
	test_port->Clear();
	test_port = NULL;
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void CMyForm4::OnBnClickedButton7()
{
	CString send_data, temp;
	LPSTR write_buff;
	test_port = new Port(_T("\\\\.\\COM5"), _T("38400"), _T("None"), _T("8 bit"), _T("1 bit"));

	if (test_port->Create(GetSafeHwnd()) != 0) {
		send_data += (char)0xC5;
		send_data += "sOUS/oU";

		send_data += _T("00X");

		send_data += '/';
		send_data += (char)0xCA;
		send_data += get_crc(send_data);
		send_data.Insert(1, (char)send_data.GetLength() - 3);

		write_buff = send_data.GetBuffer(0);
		test_port->Send(write_buff, send_data.GetLength());

		//send_data += "\r\n";
		//record_box.ReplaceSel(send_data);
	}

	test_port->Close();
	test_port->HandleClose();
	test_port->Clear();
	test_port = NULL;
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void CMyForm4::OnBnClickedButton8()
{
	CString send_data, temp;
	LPSTR write_buff;
	test_port = new Port(_T("\\\\.\\COM5"), _T("38400"), _T("None"), _T("8 bit"), _T("1 bit"));

	if (test_port->Create(GetSafeHwnd()) != 0) {
		send_data += (char)0xC5;
		send_data += "sOOR";

		send_data += _T("600");
		send_data += _T("075");

		send_data += '/';
		send_data += (char)0xCA;
		send_data += get_crc(send_data);
		send_data.Insert(1, (char)send_data.GetLength() - 3);

		write_buff = send_data.GetBuffer(0);
		test_port->Send(write_buff, send_data.GetLength());

		//send_data += "\r\n";
		//record_box.ReplaceSel(send_data);
	}

	test_port->Close();
	test_port->HandleClose();
	test_port->Clear();
	test_port = NULL;
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void CMyForm4::OnBnClickedButton9()
{
	CString send_data, temp;
	LPSTR write_buff;
	test_port = new Port(_T("\\\\.\\COM5"), _T("38400"), _T("None"), _T("8 bit"), _T("1 bit"));

	if (test_port->Create(GetSafeHwnd()) != 0) {
		send_data += (char)0xC5;
		send_data += "sOCM";

		send_data += _T("3");
		send_data += _T("150");
		send_data += _T("030");

		send_data += '/';
		send_data += (char)0xCA;
		send_data += get_crc(send_data);
		send_data.Insert(1, (char)send_data.GetLength() - 3);

		write_buff = send_data.GetBuffer(0);
		test_port->Send(write_buff, send_data.GetLength());

		//send_data += "\r\n";
		//record_box.ReplaceSel(send_data);
	}

	test_port->Close();
	test_port->HandleClose();
	test_port->Clear();
	test_port = NULL;
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void CMyForm4::OnBnClickedButton10()
{
	CString send_data, temp;
	LPSTR write_buff;
	test_port = new Port(_T("\\\\.\\COM5"), _T("38400"), _T("None"), _T("8 bit"), _T("1 bit"));

	if (test_port->Create(GetSafeHwnd()) != 0) {
		send_data += (char)0xC5;
		send_data += "sOAC";

		send_data += _T("0100");
		send_data += _T("200");
		send_data += _T("20");
		send_data += _T("100");

		send_data += '/';
		send_data += (char)0xCA;
		send_data += get_crc(send_data);
		send_data.Insert(1, (char)send_data.GetLength() - 3);

		write_buff = send_data.GetBuffer(0);
		test_port->Send(write_buff, send_data.GetLength());

		//send_data += "\r\n";
		//record_box.ReplaceSel(send_data);
	}

	test_port->Close();
	test_port->HandleClose();
	test_port->Clear();
	test_port = NULL;
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void CMyForm4::OnBnClickedButton11()
{
	CString send_data, temp;
	LPSTR write_buff;
	test_port = new Port(_T("\\\\.\\COM5"), _T("38400"), _T("None"), _T("8 bit"), _T("1 bit"));

	if (test_port->Create(GetSafeHwnd()) != 0) {
		send_data += (char)0xC5;
		send_data += "sOPT";

		send_data += (char)0x30;		
		send_data += (char)0x40;

		send_data += '/';
		send_data += (char)0xCA;
		send_data += get_crc(send_data);
		send_data.Insert(1, (char)send_data.GetLength() - 3);

		write_buff = send_data.GetBuffer(0);
		test_port->Send(write_buff, send_data.GetLength());

		//send_data += "\r\n";
		//record_box.ReplaceSel(send_data);
	}

	test_port->Close();
	test_port->HandleClose();
	test_port->Clear();
	test_port = NULL;
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void CMyForm4::OnBnClickedButton12()
{
	CString send_data, temp;
	LPSTR write_buff;
	test_port = new Port(_T("\\\\.\\COM5"), _T("38400"), _T("None"), _T("8 bit"), _T("1 bit"));

	if (test_port->Create(GetSafeHwnd()) != 0) {
		send_data += (char)0xC5;
		send_data += _T("rTTX");

		send_data += '/';
		send_data += (char)0xCA;
		send_data += get_crc(send_data);
		send_data.Insert(1, (char)(send_data.GetLength() - 3));

		write_buff = send_data.GetBuffer(0);
		test_port->Send(write_buff, send_data.GetLength());

		//AfxMessageBox(send_data);

		//send_data += "\r\n";
		//record_box.ReplaceSel(send_data);
	}

	test_port->Close();
	test_port->HandleClose();
	test_port->Clear();
	test_port = NULL;
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void CMyForm4::OnBnClickedButton13()
{
	CString send_data, temp;
	LPSTR write_buff;
	test_port = new Port(_T("\\\\.\\COM5"), _T("38400"), _T("None"), _T("8 bit"), _T("1 bit"));

	if (test_port->Create(GetSafeHwnd()) != 0) {
		send_data += (char)0xC5;
		send_data += "iMAD";

		send_data += '/';
		send_data += (char)0xCA;
		send_data += get_crc(send_data);
		send_data.Insert(1, (char)send_data.GetLength() - 3);

		write_buff = send_data.GetBuffer(0);
		test_port->Send(write_buff, send_data.GetLength());

		//send_data += "\r\n";
		//record_box.ReplaceSel(send_data);
	}

	test_port->Close();
	test_port->HandleClose();
	test_port->Clear();
	test_port = NULL;
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void CMyForm4::OnBnClickedButton14()
{
	CString send_data, temp;
	LPSTR write_buff;
	test_port = new Port(_T("\\\\.\\COM5"), _T("38400"), _T("None"), _T("8 bit"), _T("1 bit"));

	if (test_port->Create(GetSafeHwnd()) != 0) {
		send_data += (char)0xC5;
		send_data += "iOTS";

		send_data += '/';
		send_data += (char)0xCA;
		send_data += get_crc(send_data);
		send_data.Insert(1, (char)send_data.GetLength() - 3);

		write_buff = send_data.GetBuffer(0);
		test_port->Send(write_buff, send_data.GetLength());

		//send_data += "\r\n";
		//record_box.ReplaceSel(send_data);
	}

	test_port->Close();
	test_port->HandleClose();
	test_port->Clear();
	test_port = NULL;
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void CMyForm4::OnEnChangeEdit2()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CFormView::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
}
