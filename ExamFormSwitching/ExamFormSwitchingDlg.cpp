
// ExamFormSwitchingDlg.cpp: 구현 파일
//

#include <stdlib.h>
#include <math.h>
#include "stdafx.h"
#include "ExamFormSwitching.h"
#include "ExamFormSwitchingDlg.h"
#include "afxdialogex.h"
#include "Port.h"
#include "CMyForm1.h"
#include "CMyForm2.h"
#include "CMyForm3.h"
#include "CMyForm4.h"
#include "CMyForm5.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

// 구현입니다.
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CExamFormSwitchingDlg 대화 상자



CExamFormSwitchingDlg::CExamFormSwitchingDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_ExamFormSwitching_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	m_pForm1 = NULL;
	m_pForm2 = NULL;
	m_pForm3 = NULL;
	m_pForm4 = NULL;
	m_pForm5 = NULL;
}

void CExamFormSwitchingDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO3, baud_rate);
	DDX_Control(pDX, IDC_COMBO34, comport_list);
	DDX_Control(pDX, IDC_BUTTON1, connect_button);
	DDX_Control(pDX, IDC_BUTTON2, data_set);
}

BEGIN_MESSAGE_MAP(CExamFormSwitchingDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_RADIO_FORM1, &CExamFormSwitchingDlg::OnBnClickedRadioForm1)
	ON_BN_CLICKED(IDC_RADIO_FORM2, &CExamFormSwitchingDlg::OnBnClickedRadioForm2)
	ON_BN_CLICKED(IDC_RADIO_FORM3, &CExamFormSwitchingDlg::OnBnClickedRadioForm3)
	ON_BN_CLICKED(IDC_RADIO_FORM4, &CExamFormSwitchingDlg::OnBnClickedRadioForm4)
	ON_BN_CLICKED(IDC_RADIO_FORM5, &CExamFormSwitchingDlg::OnBnClickedRadioForm5)
	ON_CBN_SELCHANGE(IDC_COMBO3, &CExamFormSwitchingDlg::OnCbnSelchangeCombo3)
	ON_BN_CLICKED(IDC_BUTTON1, &CExamFormSwitchingDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CExamFormSwitchingDlg::OnBnClickedButton2)

	ON_MESSAGE(WM_MYRECEIVE, &CExamFormSwitchingDlg::OnReceive)
	ON_MESSAGE(WM_MYCLOSE, &CExamFormSwitchingDlg::OnThreadClosed)
END_MESSAGE_MAP()


// CExamFormSwitchingDlg 메시지 처리기

BOOL CExamFormSwitchingDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.

	// IDM_ABOUTBOX는 시스템 명령 범위에 있어야 합니다.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);
	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}


	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	// 프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	CheckDlgButton(IDC_RADIO_FORM1, 1);				//첫번째 파트를 띄우게 초기화시킴

	AllocForms();

	//baud_rate 선택지 삽입
	baud_rate.InsertString(0, _T("38400"));
	baud_rate.InsertString(1, _T("19200"));
	baud_rate.InsertString(2, _T("9600"));
	baud_rate.InsertString(3, _T("4800"));
	baud_rate.InsertString(4, _T("2400"));
	baud_rate.InsertString(5, _T("1200"));

	CString temp_name, input;
	int count = 0;

	for (int i = 1; i <= 99; i++) {
		temp_name.Format(_T("COM%d"), i);
		input.Format(_T("\\\\.\\"));
		input += temp_name;
		port = new Port(input, _T("38400"), _T("None"), _T("8 bit"), _T("1 bit"));
		if (port->Create(GetSafeHwnd()) != 0) {
			comport_list.InsertString(count++, temp_name);
		}

		if (port) {
			port->Close();
			port->HandleClose();
			port->Clear();
			port = NULL;
		}
	}

	strDate.Format(_T("%04d-%02d-%02d"), cTime.GetYear(), cTime.GetMonth(), cTime.GetDay());
	strTime.Format(_T("%02d:%02d:%02d"), cTime.GetHour(), cTime.GetMinute(), cTime.GetSecond());

	baud_rate.SetCurSel(0);
	comport_list.SetCurSel(0);
	Rectifier_init();

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CExamFormSwitchingDlg::Rectifier_init() {
	//Section 1 정보 초기화
	for (int i = 1; i <= MODULE_MAX; i++) {
		s1.mod[i].current = 10 + i;
		s1.mod[i].voltage = 53.5f;
		s1.mod[i].state = NM;
		//s1.mod[i].state = (1 << (8 - AF));
	}

	for (int i = 0; i < 3; i++) {
		s1.ADphase_info[i][VOLTAGE] = 220;
		s1.ADphase_info[i][CURRENT] = 100;
	}

	s1.AD_phase[0] = 0x00;
	s1.AD_phase[1] = 0x00;
	s1.AD_phase[2] = 0x00;
	s1.DC_state[0] = 0x00;
	s1.DC_state[1] = 0x00;

	s1.facility_no		= 1;
	s1.sur_temp			= 25;
	s1.output_volt		= 58;
	s1.load_cur			= 100;
	s1.batt_cur			= 200;
	s1.module_quantity	= 30;
	s1.phase			= 3;
	s1.alarm_target		= 0x30;
	s1.operate_mode		= 0;
	s1.charge_mode		= 0;
	s1.extend_comm		= 0;
	s1.monitor_comm		= 0;

	//Section2 정보 초기화
	s2.state				= 3;
	s2.AD_curr[UPPER]		= 100;
	s2.AD_curr[LOWER]		= 50;
	s2.AD_volt[UPPER]		= 220;
	s2.AD_volt[LOWER]		= 120;
	s2.DC_volt[UPPER]		= 57.5f;
	s2.DC_volt[LOWER]		= 53.0f;
	s2.RU_volt[UPPER]		= 57.5f;
	s2.RU_volt[LOWER]		= 53.0f;
	s2.BC_cell_volt[UPPER]	= 9.500f;
	s2.BC_cell_volt[LOWER]	= 3.000f;
	s2.BC_total_volt[UPPER]	= 28.5f;
	s2.BC_total_volt[LOWER] = 9.0f;
	s2.DC_curr				= 500;

	//Section3 정보 초기화
	s3.sys_time.year	= cTime.GetYear();
	s3.sys_time.month	= cTime.GetMonth();
	s3.sys_time.date	= cTime.GetDay();
	s3.sys_time.hour	= cTime.GetHour();
	s3.sys_time.minute	= cTime.GetMinute();
	s3.sys_time.second	= cTime.GetSecond();
	s3.OR_volt			= 57.5f;
	s3.OR_curr			= 70;
	s3.CM_mode			= AUTO_EQ;
	s3.EQ_volt			= 13.5f;
	s3.FL_volt			= 2.2f;
	s3.AC_point			= 500;
	s3.AC_final_curr	= 100;
	s3.AC_final_time	= 10;
	s3.AC_interval		= 200;
	s3.PT_interval		= 0x10;
	s3.PT_num			= 0x30;

	for (int i = 1; i <= 30; i++)
		s3.module_info[i] = PLUG;

	//Section5 정보 초기화
	s5.password		= (_T("000000"));
	s5.system_set	= 0x31;
	s5.bat_num		= 5;
	s5.alarm_AD		= 3;
	s5.alarm_DC		= 3;
	s5.alarm_RU		= 0;
	s5.alarm_BU		= 0;
}

void CExamFormSwitchingDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 응용 프로그램의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CExamFormSwitchingDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CExamFormSwitchingDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CExamFormSwitchingDlg::AllocForms()
{
	CCreateContext context;
	ZeroMemory(&context, sizeof(context));

	CRect rectOfPanelArea;

	GetDlgItem(IDC_STATIC_RECT)->GetWindowRect(&rectOfPanelArea);
	ScreenToClient(&rectOfPanelArea);
	
	m_pForm1 = new CMyForm1();
	m_pForm1->Create(NULL, NULL, WS_CHILD | WS_VSCROLL | WS_HSCROLL, rectOfPanelArea, this, IDD_FORM_FORM1, &context);
	m_pForm1->OnInitialUpdate();
	m_pForm1->ShowWindow(SW_SHOW);

	m_pForm2 = new CMyForm2();
	m_pForm2->Create(NULL, NULL, WS_CHILD | WS_VSCROLL | WS_HSCROLL, rectOfPanelArea, this, IDD_FORM_FORM2, &context);
	m_pForm2->OnInitialUpdate();
	m_pForm2->ShowWindow(SW_HIDE);

	m_pForm3 = new CMyForm3();
	m_pForm3->Create(NULL, NULL, WS_CHILD | WS_VSCROLL | WS_HSCROLL, rectOfPanelArea, this, IDD_FORM_FORM3, &context);
	m_pForm3->OnInitialUpdate();
	m_pForm3->ShowWindow(SW_HIDE);

	m_pForm4 = new CMyForm4();
	m_pForm4->Create(NULL, NULL, WS_CHILD | WS_VSCROLL | WS_HSCROLL, rectOfPanelArea, this, IDD_FORM_FORM3, &context);
	m_pForm4->OnInitialUpdate();
	m_pForm4->ShowWindow(SW_HIDE);

	m_pForm5 = new CMyForm5();
	m_pForm5->Create(NULL, NULL, WS_CHILD | WS_VSCROLL | WS_HSCROLL, rectOfPanelArea, this, IDD_FORM_FORM3, &context);
	m_pForm5->OnInitialUpdate();
	m_pForm5->ShowWindow(SW_HIDE);

	GetDlgItem(IDC_STATIC_RECT)->DestroyWindow();
}

void CExamFormSwitchingDlg::OnDestroy()
{
	CDialogEx::OnDestroy();

	if (m_pForm1 != NULL)
	{
		m_pForm1->DestroyWindow();
	}

	if (m_pForm2 != NULL)
	{
		m_pForm2->DestroyWindow();
	}

	if (m_pForm3 != NULL)
	{
		m_pForm3->DestroyWindow();
	}

	if (m_pForm4 != NULL)
	{
		m_pForm3->DestroyWindow();
	}

	if (m_pForm5 != NULL)
	{
		m_pForm3->DestroyWindow();
	}
}

//해당 파트 창에 출력하기
void CExamFormSwitchingDlg::ShowForm(int idx)
{
	switch (idx)
	{
	case 0:
		m_pForm1->ShowWindow(SW_SHOW);
		m_pForm2->ShowWindow(SW_HIDE);
		m_pForm3->ShowWindow(SW_HIDE);
		m_pForm4->ShowWindow(SW_HIDE);
		m_pForm5->ShowWindow(SW_HIDE);
		break;
	case 1:
		m_pForm1->ShowWindow(SW_HIDE);
		m_pForm2->ShowWindow(SW_SHOW);
		m_pForm3->ShowWindow(SW_HIDE);
		m_pForm4->ShowWindow(SW_HIDE);
		m_pForm5->ShowWindow(SW_HIDE);
		break;
	case 2:
		m_pForm1->ShowWindow(SW_HIDE);
		m_pForm2->ShowWindow(SW_HIDE);
		m_pForm3->ShowWindow(SW_SHOW);
		m_pForm4->ShowWindow(SW_HIDE);
		m_pForm5->ShowWindow(SW_HIDE);
		break;
	case 3:
		m_pForm1->ShowWindow(SW_HIDE);
		m_pForm2->ShowWindow(SW_HIDE);
		m_pForm3->ShowWindow(SW_HIDE);
		m_pForm4->ShowWindow(SW_SHOW);
		m_pForm5->ShowWindow(SW_HIDE);
		break;
	case 4:
		m_pForm1->ShowWindow(SW_HIDE);
		m_pForm2->ShowWindow(SW_HIDE);
		m_pForm3->ShowWindow(SW_HIDE);
		m_pForm4->ShowWindow(SW_HIDE);
		m_pForm5->ShowWindow(SW_SHOW);
		break;
	}
}

//실시간 데이터 파트 활성화
void CExamFormSwitchingDlg::activate_form1(BOOL flag) {
	CString str;
	//창 활성화
	m_pForm1->facility_no.EnableWindow(flag);
	m_pForm1->section1_date.EnableWindow(flag);
	m_pForm1->section1_time.EnableWindow(flag);

	m_pForm1->AD_alarm.EnableWindow(flag);
	m_pForm1->DC_alarm.EnableWindow(flag);
	m_pForm1->RU_alarm.EnableWindow(flag);
	m_pForm1->BU_alarm.EnableWindow(flag);

	//m_pForm1->GetDlgItem(IDC_CHECK10)->EnableWindow(flag);

	m_pForm1->AC_activate(flag);
	m_pForm1->DC_activate(flag);
	m_pForm1->MOD_activate(flag, 30);

	//데이터 값 출력
	str.Format(_T("%d"), s1.facility_no);				//시설번호
	m_pForm1->facility_no.SetWindowTextA(str);			//날짜, 시간
	m_pForm1->section1_date.SetWindowTextA(strDate);
	m_pForm1->section1_time.SetWindowTextA(strTime);
	
	//경보대상
	if (s1.alarm_target & (1 << 0)) m_pForm1->AD_alarm.SetCheck(1);
	if (s1.alarm_target & (1 << 1)) m_pForm1->DC_alarm.SetCheck(1);
	if (s1.alarm_target & (1 << 2)) m_pForm1->RU_alarm.SetCheck(1);
	if (s1.alarm_target & (1 << 3)) m_pForm1->BU_alarm.SetCheck(1);

	//교류배전부
	int state_check = (s1.AD_phase[2] >> 2) % 4;			//부하전류 상태 check
	m_pForm1->OV_box.SetCurSel(state_check);

	state_check = (s1.AD_phase[2] >> 4) % 4;				//출력전압 상태 check
	m_pForm1->LC_box.SetCurSel(state_check);

	state_check = (s1.AD_phase[VOLTAGE]) % 4;				//RST전압 상태 check
	m_pForm1->RV_box.SetCurSel(state_check);

	state_check = (s1.AD_phase[VOLTAGE] >> 2) % 4;
	m_pForm1->SV_box.SetCurSel(state_check);

	state_check = (s1.AD_phase[VOLTAGE] >> 4) % 4;
	m_pForm1->TV_box.SetCurSel(state_check);

	state_check = (s1.AD_phase[CURRENT]) % 4;				//RST전류 상태 check
	m_pForm1->RC_box.SetCurSel(state_check);

	state_check = (s1.AD_phase[CURRENT] >> 2) % 4;				
	m_pForm1->SC_box.SetCurSel(state_check);

	state_check = (s1.AD_phase[CURRENT] >> 4) % 4;
	m_pForm1->TC_box.SetCurSel(state_check);

	str.Format(_T("%d"), s1.phase);
	m_pForm1->AC_state.SetWindowTextA(str);
	str.Format(_T("%d"), s1.sur_temp);
	m_pForm1->AC_temp.SetWindowTextA(str);
	
	str.Format(_T("%2.1f"), s1.output_volt);				//출력전압
	//if (s1.AD_phase[2] & (1 << 5)) m_pForm1->CheckDlgButton(IDC_CHECK3, 1);
	m_pForm1->AC_ouput_volt.SetWindowTextA(str);

	str.Format(_T("%d"), s1.load_cur);						//부하 전류
	//if (s1.AD_phase[2] & (1 << 3)) m_pForm1->CheckDlgButton(IDC_CHECK4, 1);
	m_pForm1->AC_load_curr.SetWindowTextA(str);

	str.Format(_T("%d"), s1.batt_cur);						//축전지 전류
	m_pForm1->AC_batt_curr.SetWindowTextA(str);
	if(s1.batt_cur >= 0) m_pForm1->CheckDlgButton(IDC_CHECK10, 1);	//부하전류 양수일 때 충전 상태 체크, 아니면 해제
	else m_pForm1->CheckDlgButton(IDC_CHECK10, 0);
	
	str.Format(_T("%d"), s1.ADphase_info[R_PHASE][CURRENT]);		//RST 전류 전압 출력
	//if (s1.AD_phase[1] & (1 << 1))  m_pForm1->CheckDlgButton(IDC_CHECK5, 1);
	m_pForm1->AC_rc.SetWindowTextA(str);

	str.Format(_T("%d"), s1.ADphase_info[R_PHASE][VOLTAGE]);
	//if (s1.AD_phase[0] & (1 << 1))  m_pForm1->CheckDlgButton(IDC_CHECK15, 1);
	m_pForm1->AC_rv.SetWindowTextA(str);
	
	str.Format(_T("%d"), s1.ADphase_info[S_PHASE][CURRENT]);
	//if (s1.AD_phase[1] & (1 << 3))  m_pForm1->CheckDlgButton(IDC_CHECK7, 1);
	m_pForm1->AC_sc.SetWindowTextA(str);

	str.Format(_T("%d"), s1.ADphase_info[S_PHASE][VOLTAGE]);
	//if (s1.AD_phase[0] & (1 << 3))  m_pForm1->CheckDlgButton(IDC_CHECK16, 1);
	m_pForm1->AC_sv.SetWindowTextA(str);
	
	str.Format(_T("%d"), s1.ADphase_info[T_PHASE][CURRENT]);
	//if (s1.AD_phase[1] & (1 << 5))  m_pForm1->CheckDlgButton(IDC_CHECK9, 1);
	m_pForm1->AC_tc.SetWindowTextA(str);

	str.Format(_T("%d"), s1.ADphase_info[T_PHASE][VOLTAGE]);
	//if (s1.AD_phase[0] & (1 << 5))  m_pForm1->CheckDlgButton(IDC_CHECK17, 1);
	m_pForm1->AC_tv.SetWindowTextA(str);
	
	//직류제어부
	m_pForm1->operate_mode.SetCurSel(s1.operate_mode);		//운전 모드
	m_pForm1->charge_mode.SetCurSel(s1.charge_mode);		//충전모드
	m_pForm1->monitor_state.SetCurSel(s1.monitor_comm);		//감시장치간 통신

	str.Format(_T("%d"), s1.extend_comm);					//확장랙간 통신
	m_pForm1->extend_com.SetWindowTextA(str);

	if (s1.DC_state[0]) m_pForm1->load_fuse_error.SetCheck(1);		//부하 fuse 이상 여부 체크
	if (s1.DC_state[1]) m_pForm1->batt_fuse_error.SetCheck(1);		//축전지 fuse 이상 여부 체크


	//정류유니트부
	for (int i = 1; i <= 30; i++) {									//각 모듈 전압, 전류, 상태 출력
		str.Format(_T("%2.1f"), s1.mod[i].voltage);
		m_pForm1->volt_mod[i]->SetWindowTextA(str);
		str.Format(_T("%d"), s1.mod[i].current);
		m_pForm1->curr_mod[i]->SetWindowTextA(str);

		if(s1.mod[i].state == NM)									//정상일 경우
			m_pForm1->mod_state[i]->SetCurSel(s1.mod[i].state);

		else {
			for (int j = 7; j >= 0; j--) {
				if ((1 >> j) & s1.mod[i].state) {
					m_pForm1->mod_state[i]->SetCurSel(8 - j);
					break;
				}
			}
		}
	}

	m_pForm1->facility_no.SetReadOnly(1);		//시설번호, 날짜, 시간은 함부로 수정하지 못하게 Readonly로 설정
	m_pForm1->section1_date.SetReadOnly(1);
	m_pForm1->section1_time.SetReadOnly(1);
}	

//계측 상하한치 설정 파트 활성화
void CExamFormSwitchingDlg::activate_form2(BOOL flag) {
	CString str;
	m_pForm2->AC_activate(flag);
	m_pForm2->DC_activate(flag);
	m_pForm2->RU_activate(flag);
	m_pForm2->BAT_activate(flag);

	//데이터 값 출력
	//교류배전부
	str.Format(_T("%d"), s2.state);						//상
	m_pForm2->AC_state.SetWindowTextA(str);
	str.Format(_T("%d"), s2.AD_volt[UPPER]);			//입력전압 상하한치
	m_pForm2->AC_input_vmax.SetWindowTextA(str);
	str.Format(_T("%d"), s2.AD_volt[LOWER]);
	m_pForm2->AC_input_vmin.SetWindowTextA(str);
	str.Format(_T("%d"), s2.AD_curr[UPPER]);			//입력전류 상하한치
	m_pForm2->AC_input_cmax.SetWindowTextA(str);
	str.Format(_T("%d"), s2.AD_curr[LOWER]);
	m_pForm2->AC_input_cmin.SetWindowTextA(str);
	
	//축전지부
	str.Format(_T("%1.3f"), s2.BC_cell_volt[UPPER]);	//셀 전압 상하한치
	m_pForm2->batt_vmax.SetWindowTextA(str);
	str.Format(_T("%1.3f"), s2.BC_cell_volt[LOWER]);
	m_pForm2->batt_vmin.SetWindowTextA(str);
	str.Format(_T("%2.1f"), s2.BC_total_volt[UPPER]);	//셀 총전압 상하한치
	m_pForm2->batt_tvmax.SetWindowTextA(str);
	str.Format(_T("%2.1f"), s2.BC_total_volt[LOWER]);
	m_pForm2->batt_tvmin.SetWindowTextA(str);
	
	//직류제어부
	str.Format(_T("%2.1f"), s2.DC_volt[UPPER]);			//출력전압 상하한치
	m_pForm2->DC_output_vmax.SetWindowTextA(str);
	str.Format(_T("%2.1f"), s2.DC_volt[LOWER]);
	m_pForm2->DC_output_vmin.SetWindowTextA(str);
	str.Format(_T("%d"), s2.DC_curr);
	m_pForm2->DC_output_cmax.SetWindowTextA(str);		//출력전류 상한치

	//정류유니트부
	str.Format(_T("%2.1f"), s2.RU_volt[UPPER]);			//모듈 출력전압 상하한치
	m_pForm2->RU_output_vamx.SetWindowTextA(str);
	str.Format(_T("%2.1f"), s2.RU_volt[LOWER]);
	m_pForm2->RU_output_vmin.SetWindowTextA(str);
}

//시스템 운용 설정 파트 활성화
void CExamFormSwitchingDlg::activate_form3(BOOL flag) {
	CString str;

	m_pForm3->DT_activate(flag);
	m_pForm3->RUst_activate(flag);
	m_pForm3->RUout_activate(flag);
	m_pForm3->CM_activate(flag);
	m_pForm3->AC_activate(flag);
	m_pForm3->FI_activate(flag);

	//데이터 값 출력
	m_pForm3->section3_date.SetWindowTextA(strDate);
	m_pForm3->section3_time.SetWindowTextA(strTime);

	//정류모듈 출력
	str.Format(_T("%2.1f"), s3.OR_volt);
	m_pForm3->RU_volt.SetWindowTextA(str);
	str.Format(_T("%d"), s3.OR_curr);
	m_pForm3->RU_curr.SetWindowTextA(str);

	//충전모드 설정
	m_pForm3->charge_mode.SetCurSel(s3.CM_mode);
	str.Format(_T("%2.1f"), s3.EQ_volt);
	m_pForm3->ec_volt.SetWindowTextA(str);
	str.Format(_T("%2.1f"), s3.FL_volt);
	m_pForm3->fc_volt.SetWindowTextA(str);

	//자동충전 조건
	str.Format(_T("%d"), s3.AC_point);
	m_pForm3->ec_point.SetWindowTextA(str);
	str.Format(_T("%d"), s3.AC_final_curr);
	m_pForm3->ec_curr.SetWindowTextA(str);
	str.Format(_T("%d"), s3.AC_final_time);
	m_pForm3->endtime.SetWindowTextA(str);
	str.Format(_T("%d"), s3.AC_interval);
	m_pForm3->ec_interval.SetWindowTextA(str);

	//정시이력 및 경보이력
	str.Format(_T("%x"), s3.PT_interval);
	m_pForm3->fixed_interval.SetWindowTextA(str);
	str.Format(_T("%x"), s3.PT_num);
	m_pForm3->num_cases.SetWindowTextA(str);

	//정류모듈 실장유무
	for (int i = 1; i <= 30; i++)
		m_pForm3->module_set[i]->SetCurSel(s3.module_info[i]);
}

//시스템 정보 파트 활성화
void CExamFormSwitchingDlg::activate_form5(BOOL flag) {
	CString str;

	//비밀번호 및 나머지 시스템 정보 컨트롤 활성화
	m_pForm5->password.EnableWindow(flag);
	m_pForm5->SY_activate(flag);

	//m_pForm5->password.SetReadOnly(flag);
	//출력
	m_pForm5->password.SetWindowTextA(s5.password);

	//시스템 설정 set
	if (s5.system_set == 0x11)
		m_pForm5->system_set.SetWindowTextA((_T("단상 220V/25A")));

	else if (s5.system_set == 0x21)
		m_pForm5->system_set.SetWindowTextA((_T("3상 380V/50A")));

	else if (s5.system_set >= 0x31 && s5.system_set <= 0x35)
		m_pForm5->system_set.SetWindowTextA((_T("3상 220V/100A")));

	//0x41~0x45일 경우
	else if (s5.system_set >= 0x41 && s5.system_set <= 0x45)
		m_pForm5->system_set.SetWindowTextA((_T("3상 380V/100A")));

	//경보 데이터 출력
	str.Format(_T("%d"), s5.bat_num);			//축전지 조수
	m_pForm5->bat.SetWindowTextA(str);
	str.Format(_T("%d"), s5.alarm_AD);			//AD, DC, RU, BU 경보가 일어난 번호(존재하면)
	m_pForm5->ac.SetWindowTextA(str);
	str.Format(_T("%d"), s5.alarm_DC);
	m_pForm5->dc.SetWindowTextA(str);
	str.Format(_T("%d"), s5.alarm_RU);
	m_pForm5->ru.SetWindowTextA(str);
	str.Format(_T("%d"), s5.alarm_BU);
	m_pForm5->batt_part.SetWindowTextA(str);
}

void CExamFormSwitchingDlg::OnBnClickedRadioForm1()
{
	ShowForm(0);
}


void CExamFormSwitchingDlg::OnBnClickedRadioForm2()
{
	ShowForm(1);
}


void CExamFormSwitchingDlg::OnBnClickedRadioForm3()
{
	ShowForm(2);
}


void CExamFormSwitchingDlg::OnBnClickedRadioForm4()
{
	ShowForm(3);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void CExamFormSwitchingDlg::OnBnClickedRadioForm5()
{
	ShowForm(4);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}

//스레드 닫음
LRESULT CExamFormSwitchingDlg::OnThreadClosed(WPARAM length, LPARAM lpara)
{
	//overlapped i/o 핸들을 닫는다.
	((Port*)lpara)->HandleClose();
	delete ((Port*)lpara);
	
	return 0;
}

//RS232 통신을 통해 데이터를 받은 경우
LRESULT CExamFormSwitchingDlg::OnReceive(WPARAM length, LPARAM lpara) {
	CString send_data, temp;			//send_data : 보낼 데이터 만드는 CString 변수
	char *data, sys_code;					//받은 데이터 및 시스템 정보를 위한 sys_code
	LPSTR write_buff;						//보낼 데이터 버퍼
	int pos_count = 0;						//현재 데이터(받은 프로토콜)의 위치를 표시

	data = (char*)malloc(20000 * sizeof(char));
	
	//포트에 연결되있으면
	if (port) {
		port->Receive(data, length);
		data[length] = '\0';
		m_pForm4->record_box.ReplaceSel("[R] ");									//송수신 기록을 하는 파트4의 박스에 기록한다.
		
		for (int i = 0; i < (int)length; i++) {
			save_str += data[i];
			temp.Format("%02X ", (unsigned char)data[i]);							//멀티바이트 아스키코드로 기록
			m_pForm4->record_box.ReplaceSel(temp);
		}
		m_pForm4->record_box.ReplaceSel("\r\n\r\n");								//한 줄씩 띄워서 가독성을 높임
		m_pForm4->record_box.LineScroll(m_pForm4->record_box.GetLineCount());		//자동 스크롤을 위한 부분
		//int data_length = (int)data[1];

		save_data = save_str.GetBuffer(0);
		//데이터를 받는데 시작 문자가 아닌 경우 pass
		if (complete == false && data[0] != (char)0xC5) return 0;

		//데이터를 나눠서 받는데 시작 문자(CA)만 받았을 경우 
		else if (complete == false && data[0] == (char)0xC5 && length == 1) {
			complete = true;
			return 0;						//다음 내용을 받아야 하므로 패스
		}

		//길이 2이상의 데이터를 받기 시작한 경우
		else if (complete == false && data[0] == (char)0xC5 && length != 1) {
			total_length = (int)data[1];
			count = total_length + 4;
			

			//한 큐에 프로토콜을 다 받는 경우 바로 체크과정으로 넘어가면 됨
			//나눠서 프로토콜을 받는 경우
			if (count != length) {
				complete = true;				//complete flag on 후 패스
				count -= length;
				return 0;
			}
		}

		//프로토콜을 나눠서 마저 받는 경우
		else if (complete) {
			if (total_length == 0) {			//아직 length를 받지 못한 경우 즉, 시작 문자만 받았던 경우 
				total_length = (int)data[0];
				count = total_length + 3;
			}

			count -= length;					//남은 프로토콜 길이에 현재 큐의 길이를 뺀다

			if (count != 0) return 0;			//count가 0이 아니라면 아직도 다 받지 못한 경우 pass
		}

		/*int i = 0;
		m_pForm4->record_box.ReplaceSel("Check> ");
		while (save_data[i] != '\0') {
			temp.Format("%02X ", (unsigned char)save_data[i++]);							//멀티바이트 아스키코드로 기록
			m_pForm4->record_box.ReplaceSel(temp);
		}
		m_pForm4->record_box.ReplaceSel("\r\n\r\n");								//한 줄씩 띄워서 가독성을 높임
		m_pForm4->record_box.LineScroll(m_pForm4->record_box.GetLineCount());		//자동 스크롤을 위한 부분*/

		//뒤의 형식 체크(종료 문자 및 CRC 문자 체크)
		if (save_data[2 + total_length] == (char)0xCA && save_data[3 + total_length] == (char)get_crc(save_str, CRC_CHECK)) {
			switch (save_data[2]) {
				//실시간 데이터
			case 'r':
				//시스템 전체
				if (save_data[3] == 'T' && save_data[4] == 'T') {
					send_data += (char)0xC5;				//시작 문자
					send_data += "rTT";

					temp.Format(_T("%c"), s1.phase);		//상
					send_data += temp;
					temp.Format(_T("%04d%02d%02d"), cTime.GetYear(), cTime.GetMonth(), cTime.GetDay());			//날짜
					send_data += temp;
					temp.Format(_T("%02d%02d%02d"), cTime.GetHour(), cTime.GetMinute(), cTime.GetSecond());		//시간
					send_data += temp;

					//RST 전압 전류
					temp.Format(_T("%03d%03d%03d"), s1.ADphase_info[R_PHASE][VOLTAGE], s1.ADphase_info[S_PHASE][VOLTAGE], s1.ADphase_info[T_PHASE][VOLTAGE]);
					send_data += temp;
					temp.Format(_T("%03d%03d%03d"), s1.ADphase_info[R_PHASE][CURRENT], s1.ADphase_info[S_PHASE][CURRENT], s1.ADphase_info[T_PHASE][CURRENT]);
					send_data += temp;

					if (s1.sur_temp >= 0) send_data += "+";
					//else send_data += "-";
					temp.Format(_T("%02d"), s1.sur_temp);					//주위온도
					send_data += temp;

					temp.Format(_T("%03d"), (int)(s1.output_volt * 10));	//출력전압
					send_data += temp;

					temp.Format(_T("%4d"), s1.load_cur);					//부하전류
					send_data += temp;

					if (s1.batt_cur >= 0) {									//축전지 전류
						send_data += "+";									//전류값 양수 음수인 경우 분류
						temp.Format(_T("%4d"), s1.batt_cur);
					}

					else {
						send_data += "-";
						temp.Format(_T("%4d"), -s1.batt_cur);
					}

					send_data += temp;

					send_data += (unsigned char)s1.alarm_target;			//경보 대상

					send_data += "/";										//End code
					send_data += (unsigned char)0xCA;						//종료 문자

					send_data.Insert(1, (unsigned char)send_data.GetLength() - 2);		//요구한 위치에 length 삽입
					send_data += get_crc(send_data, CRC_INSERT);						//CRC 문자 넣기
				}

				//교류배전부
				else if (save_data[3] == 'T' && save_data[4] == 'A') {
					send_data += (char)0xC5;
					send_data += "rTA";

					temp.Format(_T("%d"), s1.facility_no);					//시설번호
					send_data += temp;
					temp.Format(_T("%d"), s1.phase);						//상
					send_data += temp;

					send_data += (unsigned char)s1.AD_phase[VOLTAGE];		//상태1(RST 전압 상태)
					send_data += (unsigned char)s1.AD_phase[CURRENT];		//상태2(RST 전류 상태)

					//RST 전압 전류
					temp.Format(_T("%3d%3d%3d"), s1.ADphase_info[R_PHASE][VOLTAGE], s1.ADphase_info[S_PHASE][VOLTAGE], s1.ADphase_info[T_PHASE][VOLTAGE]);
					send_data += temp;
					temp.Format(_T("%3d%3d%3d"), s1.ADphase_info[R_PHASE][CURRENT], s1.ADphase_info[S_PHASE][CURRENT], s1.ADphase_info[T_PHASE][CURRENT]);
					send_data += temp;

					if (s1.sur_temp >= 0) send_data += "+";					//주위 온도
					//else send_data += "-";
					temp.Format(_T("%2d"), s1.sur_temp);
					send_data += temp;
					temp.Format(_T("%3d"), (int)(s1.output_volt * 10));		//출력전압
					send_data += temp;

					temp.Format(_T("%4d"), s1.load_cur);					//부하 전류
					send_data += temp;

					if (s1.batt_cur >= 0) {									//축전지 전류
						send_data += "+";									//전류값 양수 음수인 경우 분류
						temp.Format(_T("%4d"), s1.batt_cur);
					}

					else {
						send_data += "-";
						temp.Format(_T("%4d"), -s1.batt_cur);
					}
					send_data += temp;

					send_data += (unsigned char)s1.AD_phase[2];				//상태3(출력전압, 부하전류 상태)

					send_data += "/";
					send_data += (char)0xCA;

					send_data.Insert(1, (unsigned char)send_data.GetLength() - 2);
					send_data += get_crc(send_data, CRC_INSERT);
				}

				//직류배전부
				else if (save_data[3] == 'T' && save_data[4] == 'D') {
					send_data += (char)0xC5;
					send_data += "rTD";

					temp.Format(_T("%d"), s1.facility_no);					//시설번호
					send_data += temp;
					send_data += (unsigned char)s1.operate_mode;			//운전모드
					send_data += (unsigned char)s1.charge_mode;				//충전모드
					send_data += (unsigned char)s1.extend_comm;				//확장랙간 통신
					send_data += (unsigned char)s1.monitor_comm;			//감시장치간 통신

					/*temp.Format(_T("%c%c"), s1.DC_state[0], s1.DC_state[1]);
					send_data += temp;*/
					send_data += (unsigned char)s1.DC_state[0];				//상태(2바이트, 0 : 부하 fuse 1 : 축전지 fuse)
					send_data += (unsigned char)s1.DC_state[1];

					send_data += "/";
					send_data += (char)0xCA;

					send_data.Insert(1, (unsigned char)send_data.GetLength() - 2);
					send_data += get_crc(send_data, CRC_INSERT);
				}

				//정류유니트부
				else if (save_data[3] == 'T' && save_data[4] == 'R') {
					//if (strncmp(data + 5, "X/", 2) != 0 || data[7] != 0xCA || data[8] != get_crc(str)) return -1;

					send_data += (char)0xC5;
					send_data += "rTR";

					temp.Format(_T("%2d"), s1.module_quantity);			//총 모듈 수
					send_data += temp;

					for (int i = 1; i <= MODULE_MAX; i++) {					//모듈 각각 전압, 전류, 상태 기록
						temp.Format(_T("%3d%3d"), (int)(s1.mod[i].voltage * 10), s1.mod[i].current);
						send_data += temp;
						send_data += (unsigned char)s1.mod[i].state;
					}

					send_data += "/";
					send_data += (char)0xCA;

					send_data.Insert(1, (unsigned char)send_data.GetLength() - 2);
					send_data += get_crc(send_data, CRC_INSERT);
				}
				write_buff = send_data.GetBuffer(0);						//send_data를 형식에 맞게 char* 로 변환
				port->Send(write_buff, send_data.GetLength());				//송신

				//send_data += "\r\n";
				m_pForm4->record_box.ReplaceSel("[S] ");					//송신한 내용 또한 파트4 상자에 기록
				for (int i = 0; i < send_data.GetLength(); i++) {
					temp.Format("%02X ", (unsigned char)send_data[i]);
					m_pForm4->record_box.ReplaceSel(temp);
				}
				m_pForm4->record_box.ReplaceSel("\r\n\r\n");
				m_pForm4->record_box.LineScroll(m_pForm4->record_box.GetLineCount());
				break;

				//계측 상하한치 or 시스템 운용
			case 'i':
				//계측 상하한치
				if (save_data[3] == 'M') {
					//교류배전부
					if (strncmp(save_data + 4, "AD", 2) == 0) {
						//if (data[6] != '/' || data[7] != 0xCA || data[8] != get_crc(str)) return -1;

						send_data += (char)0xC5;
						send_data += "iMA";

						temp.Format(_T("%c"), s2.state);			//상
						send_data += temp;
						//입력전압 전류 상하한치
						temp.Format(_T("%03d%03d%03d%03d"), s2.AD_volt[UPPER], s2.AD_volt[LOWER], s2.AD_curr[UPPER], s2.AD_curr[LOWER]);
						send_data += temp;

						send_data += "/";
						send_data += (char)0xCA;

						send_data.Insert(1, (unsigned char)send_data.GetLength() - 2);
						send_data += get_crc(send_data, CRC_INSERT);
					}

					//직류제어부
					else if (strncmp(save_data + 4, "DC", 2) == 0) {
						//if (data[6] != '/' || data[7] != 0xCA || data[8] != get_crc(str)) return -1;

						send_data += (char)0xC5;
						send_data += "iMD";

						//출력전압 상하한치, 출력전류 상한치
						temp.Format(_T("%03d%03d%04d"), (int)(s2.DC_volt[UPPER] * 10), (int)(s2.DC_volt[LOWER] * 10), s2.DC_curr);
						send_data += temp;

						send_data += "/";
						send_data += (char)0xCA;

						send_data.Insert(1, (unsigned char)send_data.GetLength() - 2);
						send_data += get_crc(send_data, CRC_INSERT);
					}

					//정류유니트부
					else if (strncmp(save_data + 4, "RU", 2) == 0) {
						//if (data[6] != '/' || data[7] != 0xCA || data[8] != get_crc(str)) return -1;

						send_data += (char)0xC5;
						send_data += "iMR";

						//모듈 출력전압 상하한치
						temp.Format(_T("%03d%03d"), (int)(s2.RU_volt[UPPER] * 10), (int)(s2.RU_volt[LOWER] * 10));
						send_data += temp;

						send_data += "/";
						send_data += (char)0xCA;

						send_data.Insert(1, (unsigned char)send_data.GetLength() - 2);
						send_data += get_crc(send_data, CRC_INSERT);
					}

					//축전지부
					else if (strncmp(save_data + 4, "BC", 2) == 0) {
						//if (data[6] != '/' || data[7] != 0xCA || data[8] != get_crc(str)) return -1;

						send_data += (char)0xC5;
						send_data += "iMB";

						//셀 전압 상하한치
						temp.Format(_T("%04d%04d"), (int)(s2.BC_cell_volt[UPPER] * 1000), (int)(s2.BC_cell_volt[LOWER] * 1000));
						send_data += temp;
						//셀 총전압 상하한치
						temp.Format(_T("%03d%03d"), (int)(s2.BC_total_volt[UPPER] * 10), (int)(s2.BC_total_volt[LOWER] * 10));
						send_data += temp;

						send_data += "/";
						send_data += (char)0xCA;

						send_data.Insert(1, (unsigned char)send_data.GetLength() - 2);
						send_data += get_crc(send_data, CRC_INSERT);
					}
				}

				//시스템 운용
				else if (save_data[3] == 'O') {
					//시간설정
					if (strncmp(save_data + 4, "TS", 2) == 0) {
						//if (data[6] != '/' || data[7] != 0xCA || data[8] != get_crc(str)) return -1;

						send_data += (char)0xC5;
						send_data += "iOT";

						//날짜 시간
						temp.Format(_T("%04d%02d%02d"), s3.sys_time.year, s3.sys_time.month, s3.sys_time.date);
						send_data += temp;
						temp.Format(_T("%02d%02d%02d"), s3.sys_time.hour, s3.sys_time.minute, s3.sys_time.second);
						send_data += temp;

						send_data += "/";
						send_data += (char)0xCA;

						send_data.Insert(1, (unsigned char)send_data.GetLength() - 2);
						send_data += get_crc(send_data, CRC_INSERT);
					}

					//정류모듈 실장 유무
					else if (strncmp(save_data + 4, "US", 2) == 0) {
						//if (data[6] != '/' || data[7] != 0xCA || data[8] != get_crc(str)) return -1;

						send_data += (char)0xC5;
						send_data += "iOU";

						//각 모듈 상태 프로토콜에 맞게 변환
						for (int i = 1; i <= MODULE_MAX; i++) {
							if (s3.module_info[i] == PLUG) send_data += "O";
							else if (s3.module_info[i] == UNPLUG) send_data += "X";
							else if (s3.module_info[i] == _FAILED) send_data += "F";
							else if (s3.module_info[i] == NOTSET) send_data += "!";
						}

						send_data += "/";
						send_data += (char)0xCA;

						send_data.Insert(1, (unsigned char)send_data.GetLength() - 2);
						send_data += get_crc(send_data, CRC_INSERT);
					}

					//정류모듈 출력 설정
					else if (strncmp(save_data + 4, "OR", 2) == 0) {
						//if (data[6] != '/' || data[7] != 0xCA || data[8] != get_crc(str)) return -1;

						send_data += (char)0xC5;
						send_data += "iOO";

						//정류모듈 출력 전압 전류
						temp.Format(_T("%03d%03d"), (int)(s3.OR_volt * 10), s3.OR_curr);
						send_data += temp;

						send_data += "/";
						send_data += (char)0xCA;

						send_data.Insert(1, (unsigned char)send_data.GetLength() - 2);
						send_data += get_crc(send_data, CRC_INSERT);
					}

					//충전모드 설정
					else if (strncmp(save_data + 4, "CM", 2) == 0) {
						//if (data[6] != '/' || data[7] != 0xCA || data[8] != get_crc(str)) return -1;

						send_data += (char)0xC5;
						send_data += "iOC";

						//충전모드, 균등충전 전압, 부동충전 전압
						temp.Format(_T("%d%03d%3d"), s3.CM_mode, (int)(s3.EQ_volt * 10), (int)(s3.FL_volt * 10));
						send_data += temp;

						send_data += "/";
						send_data += (char)0xCA;

						send_data.Insert(1, (unsigned char)send_data.GetLength() - 2);
						send_data += get_crc(send_data, CRC_INSERT);
					}

					//자동충전 조건 설정
					else if (strncmp(save_data + 4, "AC", 2) == 0) {
						//if (data[6] != '/' || data[7] != 0xCA || data[8] != get_crc(str)) return -1;

						send_data += (char)0xC5;
						send_data += "iOA";

						//균등충전 조건전류점, 종지전류
						temp.Format(_T("%04d%03d"), s3.AC_point, s3.AC_final_curr);
						send_data += temp;

						//종지시간, 균등충전주기
						temp.Format(_T("%02d%03d"), s3.AC_final_time, s3.AC_interval);
						send_data += temp;

						send_data += "/";
						send_data += (char)0xCA;

						send_data.Insert(1, (unsigned char)send_data.GetLength() - 2);
						send_data += get_crc(send_data, CRC_INSERT);
					}

					//정시이력 저장주기 및 경보이력
					else if (strncmp(save_data + 4, "PT", 2) == 0) {
						//if (data[6] != '/' || data[7] != 0xCA || data[8] != get_crc(str)) return -1;

						send_data += (char)0xC5;
						send_data += "iOP";

						//정시저장 주기, 경보 저장 건 수
						temp.Format(_T("%c%c"), s3.PT_interval, s3.PT_num);
						send_data += temp;

						send_data += "/";
						send_data += (char)0xCA;

						send_data.Insert(1, (unsigned char)send_data.GetLength() - 2);
						send_data += get_crc(send_data, CRC_INSERT);
					}
				}
				write_buff = send_data.GetBuffer(0);
				port->Send(write_buff, send_data.GetLength());					//RS통신으로 송신

				m_pForm4->record_box.ReplaceSel("[S] ");						//송신내용 파트4에 기록
				for (int i = 0; i < send_data.GetLength(); i++) {
					temp.Format("%02X ", (unsigned char)send_data[i]);
					m_pForm4->record_box.ReplaceSel(temp);
				}
				m_pForm4->record_box.ReplaceSel("\r\n\r\n");
				m_pForm4->record_box.LineScroll(m_pForm4->record_box.GetLineCount());
				break;

				//시스템 정보 확인
			case 'C':
				if (save_data[3] != (char)0xCA || save_data[4] != (char)get_crc(save_str, CRC_CHECK)) return -1;

				send_data += (unsigned char)0xC5;
				send_data += "A";								//프로토콜 요구사항 'A'

				send_data += (unsigned char)s5.system_set;		//시스템 설정
				send_data += "fO";

				sys_code = (unsigned char)s5.bat_num << 4;		//축전지 조수 세팅 후 시프트 연산으로 상위비트로 보내기

				if (s5.alarm_AD) sys_code |= 1;					//그 밑의 4비트는 각각 AD, DC, RU, BU에 문제가 있으면 해당 비트를 on한다.
				if (s5.alarm_DC) sys_code |= 2;
				if (s5.alarm_RU) sys_code |= 4;
				if (s5.alarm_BU) sys_code |= 8;

				send_data += (unsigned char)sys_code;

				if (s5.alarm_AD)								//각 파트별로 경보가 있는 경우 해당 파트의 넘버의 비트를 킨 값을 넘긴다.
					send_data += (unsigned char)(1 << (s5.alarm_AD - 1));

				else send_data += (unsigned char)0;

				if (s5.alarm_DC)
					send_data += (unsigned char)(1 << (s5.alarm_DC - 1));

				else send_data += (unsigned char)0;

				if (s5.alarm_RU)
					send_data += (unsigned char)(1 << (s5.alarm_RU - 1));

				else send_data += (unsigned char)0;

				if (s5.alarm_BU)
					send_data += (unsigned char)(1 << (s5.alarm_BU - 1));

				else send_data += (unsigned char)0;

				send_data += "/";
				send_data += (unsigned char)0xCA;

				send_data.Insert(1, (unsigned char)send_data.GetLength() - 2);
				send_data += get_crc(send_data, CRC_INSERT);

				write_buff = send_data.GetBuffer(0);
				port->Send(write_buff, send_data.GetLength());

				m_pForm4->record_box.ReplaceSel("[S] ");
				for (int i = 0; i < send_data.GetLength(); i++) {
					temp.Format("%02X ", (unsigned char)send_data[i]);
					m_pForm4->record_box.ReplaceSel(temp);
				}
				m_pForm4->record_box.ReplaceSel("\r\n\r\n");
				m_pForm4->record_box.LineScroll(m_pForm4->record_box.GetLineCount());

				break;

				//암호 확인
			case 'P':
				if (strncmp(save_data + 2, "Pass", 4) == 0) {				//Pass로 시작하면
					if (save_data[7] != (char)0xCA || save_data[8] != (char)get_crc(save_str, CRC_CHECK)) return -1;

					send_data += (char)0xC5;
					send_data += "P";
					send_data += s5.password;							//6자리 암호

					send_data += "/";
					send_data += (char)0xCA;

					send_data.Insert(1, (unsigned char)send_data.GetLength() - 2);
					send_data += get_crc(send_data, CRC_INSERT);

					write_buff = send_data.GetBuffer(0);
					port->Send(write_buff, send_data.GetLength());

					m_pForm4->record_box.ReplaceSel("[S] ");
					for (int i = 0; i < send_data.GetLength(); i++) {
						temp.Format("%02X ", (unsigned char)send_data[i]);
						m_pForm4->record_box.ReplaceSel(temp);
					}
					m_pForm4->record_box.ReplaceSel("\r\n\r\n");
					m_pForm4->record_box.LineScroll(m_pForm4->record_box.GetLineCount());
					break;
				}

				//설정
			case 's':
				//계측 상하한치
				if (save_data[3] == 'M') {
					pos_count = 4;
					temp = save_str.Mid(pos_count, 5);
					//교류배전부
					if (temp.Compare("AD/tA") == 0) {
						pos_count += 5;

						temp = save_str.Mid(pos_count, 3);
						s2.AD_volt[UPPER] = atoi(temp);					//입력전압 상하한치
						temp.Format(_T("%d"), s2.AD_volt[UPPER]);
						m_pForm2->AC_input_vmax.SetWindowTextA(temp);
						pos_count += 3;

						temp = save_str.Mid(pos_count, 3);
						s2.AD_volt[LOWER] = atoi(temp);
						temp.Format(_T("%d"), s2.AD_volt[LOWER]);
						m_pForm2->AC_input_vmin.SetWindowTextA(temp);
						pos_count += 3;

						temp = save_str.Mid(pos_count, 3);					//입력전류 상하한치
						s2.AD_curr[UPPER] = atoi(temp);
						temp.Format(_T("%d"), s2.AD_curr[UPPER]);
						m_pForm2->AC_input_cmax.SetWindowTextA(temp);
						pos_count += 3;

						temp = save_str.Mid(pos_count, 3);
						s2.AD_curr[LOWER] = atoi(temp);
						temp.Format(_T("%d"), s2.AD_curr[LOWER]);
						m_pForm2->AC_input_cmin.SetWindowTextA(temp);
					}

					//직류제어부
					else if (temp.Compare("DC/tD") == 0) {
						pos_count += 5;

						temp = save_str.Mid(pos_count, 3);						//출력전압 상하한치
						s2.DC_volt[UPPER] = (float)atoi(temp) / 10.0f;
						temp.Format(_T("%2.1f"), s2.DC_volt[UPPER]);
						m_pForm2->DC_output_vmax.SetWindowTextA(temp);
						pos_count += 3;

						//AfxMessageBox(_T("NOPROBLEM"));
						temp = save_str.Mid(pos_count, 3);
						s2.DC_volt[LOWER] = (float)atoi(temp) / 10.0f;
						temp.Format(_T("%2.1f"), s2.DC_volt[LOWER]);
						m_pForm2->DC_output_vmin.SetWindowTextA(temp);
						pos_count += 3;

						temp = save_str.Mid(pos_count, 4);						//출력전류 상한치
						s2.DC_curr = atoi(temp);
						temp.Format(_T("%d"), s2.DC_curr);
						m_pForm2->DC_output_cmax.SetWindowTextA(temp);
					}

					//정류유니트부
					else if (temp.Compare("RU/tR") == 0) {
						pos_count += 5;

						temp = save_str.Mid(pos_count, 3);						//모듈 출력전압 상하한치
						s2.RU_volt[UPPER] = (float)atoi(temp) / 10.0f;
						temp.Format(_T("%2.1f"), s2.RU_volt[UPPER]);
						m_pForm2->RU_output_vamx.SetWindowTextA(temp);
						pos_count += 3;

						temp = save_str.Mid(pos_count, 3);
						s2.RU_volt[LOWER] = (float)atoi(temp) / 10.0f;
						temp.Format(_T("%2.1f"), s2.RU_volt[LOWER]);
						m_pForm2->RU_output_vmin.SetWindowTextA(temp);
					}

					//축전지부
					else if (temp.Compare("BC/tB") == 0) {
						pos_count += 5;

						temp = save_str.Mid(pos_count, 4);							//셀 전압 상하한치
						s2.BC_cell_volt[UPPER] = (float)atoi(temp) / 1000.0f;
						temp.Format(_T("%1.3f"), s2.BC_cell_volt[UPPER]);
						m_pForm2->batt_vmax.SetWindowTextA(temp);
						pos_count += 4;

						temp = save_str.Mid(pos_count, 4);
						s2.BC_cell_volt[LOWER] = (float)atoi(temp) / 1000.0f;
						temp.Format(_T("%1.3f"), s2.BC_cell_volt[LOWER]);
						m_pForm2->batt_vmin.SetWindowTextA(temp);
						pos_count += 4;

						temp = save_str.Mid(pos_count, 3);							//셀 총전압 상하한치
						s2.BC_total_volt[UPPER] = (float)atoi(temp) / 10.0f;
						temp.Format(_T("%2.1f"), s2.BC_total_volt[UPPER]);
						m_pForm2->batt_tvmax.SetWindowTextA(temp);
						pos_count += 3;

						temp = save_str.Mid(pos_count, 3);
						s2.BC_total_volt[LOWER] = (float)atoi(temp) / 10.0f;
						temp.Format(_T("%2.1f"), s2.BC_total_volt[LOWER]);
						m_pForm2->batt_tvmin.SetWindowTextA(temp);
					}
				}

				//시스템 운용 설정
				else if (save_data[3] == 'O') {
					pos_count = 4;
					temp = save_str.Mid(pos_count, 5);
					//시간 설정
					if (temp.Compare("TS/oT") == 0) {
						pos_count += 5;

						temp = save_str.Mid(pos_count, 4);				//년월일
						s3.sys_time.year = atoi(temp);
						pos_count += 4;

						temp = save_str.Mid(pos_count, 2);
						s3.sys_time.month = atoi(temp);
						pos_count += 2;

						temp = save_str.Mid(pos_count, 2);
						s3.sys_time.date = atoi(temp);
						temp.Format(_T("%04d-%02d-%02d"), s3.sys_time.year, s3.sys_time.month, s3.sys_time.date);
						m_pForm3->section3_date.SetWindowTextA(temp);
						pos_count += 2;

						temp = save_str.Mid(pos_count, 2);				//시분초
						s3.sys_time.hour = atoi(temp);
						pos_count += 2;

						temp = save_str.Mid(pos_count, 2);
						s3.sys_time.minute = atoi(temp);
						pos_count += 2;

						temp = save_str.Mid(pos_count, 2);
						s3.sys_time.second = atoi(temp);
						temp.Format(_T("%02d:%02d:%02d"), s3.sys_time.hour, s3.sys_time.minute, s3.sys_time.second);
						m_pForm3->section3_time.SetWindowTextA(temp);
					}

					//정류모듈 실장 유무 설정
					else if (temp.Compare("US/oU") == 0) {
						pos_count += 5;
						if (save_data[pos_count] == '0' && save_data[pos_count + 1] == '0') {		// 0 : 전체일 경우
							for (int i = 1; i <= 30; i++) {
								switch (save_data[pos_count + 2]) {
								case 'O':
									s3.module_info[i] = PLUG;
									break;
								case 'X':
									s3.module_info[i] = UNPLUG;
									break;
								case 'F':
									s3.module_info[i] = _FAILED;
									break;
								}
								m_pForm3->module_set[i]->SetCurSel(s3.module_info[i]);
							}
						}

						else {															// 유닛 넘버를 정해줄 때
							temp = save_str.Mid(pos_count, 2);
							switch (save_data[pos_count + 2]) {
							case 'O':
								s3.module_info[atoi(temp)] = PLUG;
								break;
							case 'X':
								s3.module_info[atoi(temp)] = UNPLUG;
								break;
							case 'F':
								s3.module_info[atoi(temp)] = _FAILED;
								break;
							}
							m_pForm3->module_set[atoi(temp)]->SetCurSel(s3.module_info[atoi(temp)]);
						}
					}

					//정류모듈 출력 설정
					else if (temp.Compare("OR/oO") == 0) {
						pos_count += 5;

						temp = save_str.Mid(pos_count, 3);					//출력 전압
						s3.OR_volt = (float)atoi(temp) / 10.0f;
						temp.Format(_T("%2.1f"), s3.OR_volt);
						m_pForm3->RU_volt.SetWindowTextA(temp);
						pos_count += 3;

						temp = save_str.Mid(pos_count, 3);					//출력 전류
						s3.OR_curr = atoi(temp);
						temp.Format(_T("%d"), s3.OR_curr);
						m_pForm3->RU_curr.SetWindowTextA(temp);
					}

					//충전모드 설정
					else if (temp.Compare("CM/oC") == 0) {
						pos_count += 5;

						s3.CM_mode = save_data[pos_count] - '0';				//충전모드
						m_pForm3->charge_mode.SetCurSel(s3.CM_mode);
						pos_count++;

						temp = save_str.Mid(pos_count, 3);					//균등충전 전압
						s3.EQ_volt = (float)atoi(temp) / 10.0f;
						temp.Format(_T("%2.1f"), s3.EQ_volt);
						m_pForm3->ec_volt.SetWindowTextA(temp);
						pos_count += 3;

						temp = save_str.Mid(pos_count, 3);					//부동충전 전압
						s3.FL_volt = atoi(temp) / 10.0f;
						temp.Format(_T("%2.1f"), s3.FL_volt);
						m_pForm3->fc_volt.SetWindowTextA(temp);
					}

					//자동충전 조건 설정
					else if (temp.Compare("AC/oA") == 0) {
						pos_count += 5;

						temp = save_str.Mid(pos_count, 4);					//균등충전 조건전류점
						s3.AC_point = atoi(temp);
						temp.Format(_T("%d"), s3.AC_point);
						m_pForm3->ec_point.SetWindowTextA(temp);
						pos_count += 4;

						temp = save_str.Mid(pos_count, 3);					//균등충전 종지전류
						s3.AC_final_curr = atoi(temp);
						temp.Format(_T("%d"), s3.AC_final_curr);
						m_pForm3->ec_curr.SetWindowTextA(temp);
						pos_count += 3;

						temp = save_str.Mid(pos_count, 2);					//종지시간
						s3.AC_final_time = atoi(temp);
						temp.Format(_T("%d"), s3.AC_final_time);
						m_pForm3->endtime.SetWindowTextA(temp);
						pos_count += 2;

						temp = save_str.Mid(pos_count, 3);					//균등충전주기
						s3.AC_interval = atoi(temp);
						temp.Format(_T("%d"), s3.AC_interval);
						m_pForm3->ec_interval.SetWindowTextA(temp);
					}

					//정시이력 저장주기 및 경보이력 저장 건 수 설정
					else if (temp.Compare("PT/oP") == 0) {
						pos_count += 5;

						s3.PT_interval = save_data[pos_count];				//정시저장 주기
						//s3.PT_interval = data[pos_count] / 16 * 10 + data[pos_count] % 16;
						temp.Format(_T("%x"), s3.PT_interval);
						m_pForm3->fixed_interval.SetWindowTextA(temp);

						s3.PT_num = save_data[pos_count + 1];				//경보 저장 건 수
						//s3.PT_num = data[pos_count + 1] / 16 * 10 + data[pos_count + 1] % 16;
						temp.Format(_T("%x"), s3.PT_num);
						m_pForm3->num_cases.SetWindowTextA(temp);
					}
				}

			default:
				break;
			}
		}
		
		save_data = "";								//save_data 다시 새로운 프로토콜 받아야 하므로 초기화
		save_str = _T("");
		complete = false;							//complete flag도 false로 on
		total_length = 0;							//total_length 및 count도 0으로 초기화
		count = 0;
	}

	return 0;
}

void CExamFormSwitchingDlg::OnCbnSelchangeCombo3() {
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}

//연결 버튼을 눌렀을 시 실행하는 함수
void CExamFormSwitchingDlg::OnBnClickedButton1()
{
	CTime cTime = CTime::GetCurrentTime();
	CString port_no, baud_no, message, send_data, temp;			//반환되는 날짜와 시간을 저장할 CString 변수 선언
	LPSTR read_buff = "";
	long port_num = comport_list.GetCurSel() + 1;
	long speed = baud_rate.GetCurSel();
	char sys_code = (char)s5.bat_num << 4;
	
	port_no.Format(_T("\\\\.\\"));
	comport_list.GetLBText(comport_list.GetCurSel(), temp);
	port_no += temp;

	if(port_name.Find("COM") == -1)
		port_name = temp;

	baud_no.Format(_T("%d"), 38400 >> speed);

	if (!connected) {
		port = new Port(port_no, baud_no, _T("None"), _T("8 bit"), _T("1 bit"));

		if (port->Create(GetSafeHwnd()) != 0) {
			//message.Format(_T("COM%d 연결!"), port_num);
			message = port_name + " 연결!";
			AfxMessageBox(message);
			connected = true;
			connect_button.SetWindowTextA(_T("연결끊기"));
			data_set.EnableWindow(1);
			
			activate_form1(true);
			activate_form2(true);
			activate_form3(true);
			//activate_form4(true);
			activate_form5(true);
		}

		else {
			AfxMessageBox(_T("연결실패!"));
			return;
		}
	}

	else {
		if (port) {
			port->Close();
			port->HandleClose();
			port->Clear();
			port = NULL;
			
			//message.Format(_T("COM%d 연결끊기!"), port_num);
			message = port_name + " 연결끊기!";
			port_name.Format(_T(""));
			AfxMessageBox(message);
			connected = false;
			activate_form1(false);
			activate_form2(false);
			activate_form3(false);
			//activate_form4(true);
			activate_form5(false);
			m_pForm4->record_box.SetWindowTextA(_T(""));					// 프로토콜 주고받는 상자 초기화

			connect_button.SetWindowTextA(_T("연   결"));
			data_set.EnableWindow(0);
		}

		else {
			AfxMessageBox(_T("연결끊기 실패!"));
			return;
		}
	}
}		

//CRC문자를 구하는 함수
unsigned char CExamFormSwitchingDlg::get_crc(CString data, int flag) {
	CString temp, message;
	int sum = 0;
	//CRC가 맞는지의 여부를 체크할 때
	if (flag == CRC_CHECK) 
		for (int i = 2; i < data.GetLength() - 2; i++)				//CRC가 존재하므로 뒤에 2개의 문자를 제외함
			sum += (int)data.GetAt(i);

	//CRC값을 구하여서 넣을려고 할 때
	else if (flag == CRC_INSERT) 
		for (int i = 2; i < data.GetLength() - 1; i++)				//아직은 CRC가 존재하지 않으므로 1개의 문자를 제외
			sum += (int)data.GetAt(i);

	return (unsigned char)sum % 256;
}

//데이터 설정 버튼을 눌렀을 시 실행하는 함수
void CExamFormSwitchingDlg::OnBnClickedButton2() {
	CString temp, token;
	//LPSTR write_buff;
	//char length;
	int i = 0;
	//if (connect) {
		if (IsDlgButtonChecked(IDC_RADIO_FORM1)) {
			int state_flag1, state_flag2, state_flag3;							//RST상태 체크 변수
			//교류배전부 정보 변경
			m_pForm1->AC_ouput_volt.GetWindowTextA(temp);						//출력전압 변경
			s1.output_volt = (float)atof(temp);

			m_pForm1->AC_load_curr.GetWindowTextA(temp);						//부하전류 변경
			s1.load_cur = atoi(temp);

			m_pForm1->AC_batt_curr.GetWindowTextA(temp);						//축전지 전류 변경
			s1.batt_cur = atoi(temp);
			if (s1.batt_cur >= 0) m_pForm1->CheckDlgButton(IDC_CHECK10, 1);		//축전지 전류 양수이면 충전 상태 체크
			else m_pForm1->CheckDlgButton(IDC_CHECK10, 0);

			state_flag3 = m_pForm1->RV_box.GetCurSel();							//RST전압 상태 가져오고 상태1값 변경
			state_flag2 = m_pForm1->SV_box.GetCurSel();
			state_flag1 = m_pForm1->TV_box.GetCurSel();
			s1.AD_phase[VOLTAGE] = (state_flag1 << 4) | (state_flag2 << 2) | (state_flag3);

			state_flag3 = m_pForm1->RC_box.GetCurSel();							//RST전류 상태 가져오고 상태2값 변경
			state_flag2 = m_pForm1->SC_box.GetCurSel();
			state_flag1 = m_pForm1->TC_box.GetCurSel();
			s1.AD_phase[CURRENT] = (state_flag1 << 4) | (state_flag2 << 2) | (state_flag3);

			state_flag1 = m_pForm1->OV_box.GetCurSel();							//출력전압 상태
			state_flag2 = m_pForm1->LC_box.GetCurSel();							//부하전류 상태
			s1.AD_phase[2] = (state_flag1 << 4) | (state_flag2 << 2);

			if (m_pForm1->AD_alarm.GetCheck()) s1.alarm_target |= 1;			//경보대상 상태 변경
			else s1.alarm_target &= ~1;

			if (m_pForm1->DC_alarm.GetCheck()) s1.alarm_target |= (1 << 1);
			else s1.alarm_target &= ~(1 << 1);

			if (m_pForm1->RU_alarm.GetCheck()) s1.alarm_target |= (1 << 2);
			else s1.alarm_target &= ~(1 << 2);

			if (m_pForm1->BU_alarm.GetCheck()) s1.alarm_target |= (1 << 3);
			else s1.alarm_target &= ~(1 << 3);

			m_pForm1->AC_rv.GetWindowTextA(temp);								//RST상 전압 전류 변경
			s1.ADphase_info[R_PHASE][VOLTAGE] = atoi(temp);

			m_pForm1->AC_sv.GetWindowTextA(temp);
			s1.ADphase_info[S_PHASE][VOLTAGE] = atoi(temp);

			m_pForm1->AC_tv.GetWindowTextA(temp);
			s1.ADphase_info[T_PHASE][VOLTAGE] = atoi(temp);

			m_pForm1->AC_rc.GetWindowTextA(temp);								
			s1.ADphase_info[R_PHASE][CURRENT] = atoi(temp);

			m_pForm1->AC_sc.GetWindowTextA(temp);
			s1.ADphase_info[S_PHASE][CURRENT] = atoi(temp);

			m_pForm1->AC_tc.GetWindowTextA(temp);
			s1.ADphase_info[T_PHASE][CURRENT] = atoi(temp);

			//직류제어부 정보 변경
			s1.operate_mode = (char)m_pForm1->operate_mode.GetCurSel();			//운전모드
			s1.charge_mode = (char)m_pForm1->charge_mode.GetCurSel();			//충전모드
			s1.monitor_comm = (char)m_pForm1->monitor_state.GetCurSel();		//감시장치간 통신

			if (m_pForm1->load_fuse_error.GetCheck())							//부하 fuse 이상 여부 체크
				s1.DC_state[0] = 0x01;

			else s1.DC_state[0] = 0x00;

			if (m_pForm1->batt_fuse_error.GetCheck())							//축전지 fuse 이상 여부 체크
				s1.DC_state[1] = 0x04;

			else s1.DC_state[1] = 0x00;

			//정류유니트부 정보 변경
			for (int i = 1; i <= 30; i++) {
				int flag_on = m_pForm1->mod_state[i]->GetCurSel();
				if (flag_on == NM)												//정상인 경우
					s1.mod[i].state = NM;

				else s1.mod[i].state = 0 | (1 << (8 - flag_on));				//정상이 아닌 경우 해당 상태 플래그 on

				m_pForm1->curr_mod[i]->GetWindowTextA(temp);
				s1.mod[i].current = atoi(temp);

				m_pForm1->volt_mod[i]->GetWindowTextA(temp);
				s1.mod[i].voltage = atof(temp);
			}
		}

		//계측 상하한치 설정
		if (IsDlgButtonChecked(IDC_RADIO_FORM2)) {								
				switch (m_pForm2->select_measure.GetCurSel()) {
					//정류제어부
				case 0:
					m_pForm2->AC_input_vmax.GetWindowTextA(temp);				//입력전압 상하한치 변경
					s2.AD_volt[UPPER] = atoi(temp);

					m_pForm2->AC_input_vmin.GetWindowTextA(temp);			
					s2.AD_volt[LOWER] = atoi(temp);

					m_pForm2->AC_input_cmax.GetWindowTextA(temp);				//입력전류 상하한치 변경
					s2.AD_curr[UPPER] = atoi(temp);

					m_pForm2->AC_input_cmin.GetWindowTextA(temp);
					s2.AD_curr[LOWER] = atoi(temp);
					break;
					//직류제어부
				case 1:
					m_pForm2->DC_output_vmax.GetWindowTextA(temp);				//출력전압 상하한치 변경
					s2.DC_volt[UPPER] = (float)atof(temp);

					m_pForm2->DC_output_vmin.GetWindowTextA(temp);
					s2.DC_volt[LOWER] = (float)atof(temp);

					m_pForm2->DC_output_cmax.GetWindowTextA(temp);				//출력전류 상한치 변경
					s2.DC_curr = atoi(temp);
					break;
					//정류유니트부
				case 2:
					m_pForm2->RU_output_vamx.GetWindowTextA(temp);				//모듈 출력전압 상하한치 변경
					s2.RU_volt[UPPER] = (float)atof(temp);

					m_pForm2->RU_output_vmin.GetWindowTextA(temp);
					s2.RU_volt[LOWER] = (float)atof(temp);
					break;
					//축전지부
				case 3:
					m_pForm2->batt_vmax.GetWindowTextA(temp);					//셀 전압 상하한치 변경
					s2.BC_cell_volt[UPPER] = (float)atof(temp);

					m_pForm2->batt_vmin.GetWindowTextA(temp);
					s2.BC_cell_volt[LOWER] = (float)atof(temp);

					m_pForm2->batt_tvmax.GetWindowTextA(temp);					//셀 총전압 상하한치 변경
					s2.BC_total_volt[UPPER] = (float)atof(temp);

					m_pForm2->batt_tvmin.GetWindowTextA(temp);
					s2.BC_total_volt[LOWER] = (float)atof(temp);
					break;
				}
			}

		//시스템 운용설정
		else if (IsDlgButtonChecked(IDC_RADIO_FORM3)) {
				switch (m_pForm3->select_box.GetCurSel()) {
				//시간 설정
				case 0:
					m_pForm3->section3_date.GetWindowTextA(temp);			//시스템 시간 변경
					while (AfxExtractSubString(token, temp, i, '-')) {		//'-'로 연월일 구분
						switch (i) {
						case 0:
							s3.sys_time.year = atoi(token);
							break;

						case 1:
							s3.sys_time.month = atoi(token);
							break;

						case 2:
							s3.sys_time.date = atoi(token);
							break;
						}
						i++;
					}
					i = 0;
					m_pForm3->section3_time.GetWindowTextA(temp);

					while (AfxExtractSubString(token, temp, i, ':')) {		//':'로 시분초 구분
						switch (i) {
						case 0:
							s3.sys_time.hour = atoi(token);
							break;

						case 1:
							s3.sys_time.minute = atoi(token);
							break;

						case 2:
							s3.sys_time.second = atoi(token);
							break;
						}
						i++;
					}
					break;
				//정류모듈 실장 유무 설정
				case 1:
					/*int set_num;
					set_num = m_pForm3->select_module.GetCurSel();				//정류모듈 실장 유무 변경
					//temp.Format(_T("%d"), set_num);
					if (set_num == 0) 
						for (int i = 1; i <= 30; i++)
							s3.module_info[i] = m_pForm3->mod1.GetCurSel();
					
					else
						s3.module_info[set_num] = m_pForm3->module_set[set_num]->GetCurSel();*/

					for (int i = 1; i <= 30; i++)
						s3.module_info[i] = m_pForm3->module_set[i]->GetCurSel();

					break;

				case 2:															
					m_pForm3->RU_volt.GetWindowTextA(temp);						//정류 모듈 출력 전압 전류 변경
					s3.OR_volt = (float)atof(temp);

					m_pForm3->RU_curr.GetWindowTextA(temp);
					s3.OR_curr = atoi(temp);
					break;
				
				case 3:
					s3.CM_mode = m_pForm3->charge_mode.GetCurSel();				//충전모드 변경

					m_pForm3->ec_volt.GetWindowTextA(temp);						//균등충전 전압 변경
					s3.EQ_volt = (float)atof(temp);

					m_pForm3->fc_volt.GetWindowTextA(temp);						//부동충전 전압 변경
					s3.EQ_volt = (float)atof(temp);
					break;

				case 4:
					m_pForm3->ec_point.GetWindowTextA(temp);					//균등충전 조건전류점 변경
					s3.AC_point = atoi(temp);

					m_pForm3->ec_curr.GetWindowTextA(temp);						//종지전류 변경
					s3.AC_final_curr = atoi(temp);

					m_pForm3->endtime.GetWindowTextA(temp);						//종지시간 변경
					s3.AC_final_time = atoi(temp);

					m_pForm3->ec_interval.GetWindowTextA(temp);					//균등충전주기 변경
					s3.AC_interval = atoi(temp);
					break;

				case 5:
					long value;													//균등충전 종지전류 변경
			
					m_pForm3->fixed_interval.GetWindowTextA(temp);				//정시저장 주기 변경
					value = strtoul(temp, NULL, 16);
					s3.PT_interval = (int)value;

					m_pForm3->num_cases.GetWindowTextA(temp);					//경보 저장 건 수 변경
					value = strtoul(temp, NULL, 16);
					s3.PT_num = (int)value;
					break;
				}
			}

		else if (IsDlgButtonChecked(IDC_RADIO_FORM5)) {
			s5.password = _T("");
			m_pForm5->password.GetWindowTextA(temp);							//비밀번호 변경

			for (int i = 0; i < 6; i++)
				s5.password += temp.GetAt(i);
		}
		// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	//}
}



