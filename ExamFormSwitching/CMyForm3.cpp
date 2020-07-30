// CMyForm3.cpp: 구현 파일
//

#include "stdafx.h"
#include "ExamFormSwitching.h"
#include "CMyForm3.h"
#include "afxdialogex.h"
#include "Port.h"


// CMyForm3 대화 상자

IMPLEMENT_DYNAMIC(CMyForm3, CFormView)

CMyForm3::CMyForm3()
	: CFormView(IDD_FORM_FORM3)
{

}

CMyForm3::CMyForm3(UINT nIDTemplate)
	: CFormView(nIDTemplate)
{

}

CMyForm3::~CMyForm3()
{
}

void CMyForm3::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO1, select_box);
	DDX_Control(pDX, IDC_COMBO2, charge_mode);
	DDX_Control(pDX, IDC_EDIT6, section3_date);
	DDX_Control(pDX, IDC_EDIT7, section3_time);
	DDX_Control(pDX, IDC_EDIT23, RU_volt);
	DDX_Control(pDX, IDC_EDIT82, RU_curr);
	DDX_Control(pDX, IDC_EDIT84, ec_volt);
	DDX_Control(pDX, IDC_EDIT85, fc_volt);
	DDX_Control(pDX, IDC_EDIT14, ec_point);
	DDX_Control(pDX, IDC_EDIT16, ec_curr);
	DDX_Control(pDX, IDC_EDIT15, endtime);
	DDX_Control(pDX, IDC_EDIT17, ec_interval);
	DDX_Control(pDX, IDC_EDIT83, fixed_interval);
	DDX_Control(pDX, IDC_EDIT86, num_cases);
	DDX_Control(pDX, IDC_COMBO4, mod1);
	DDX_Control(pDX, IDC_COMBO36, mod2);
	DDX_Control(pDX, IDC_COMBO34, mod3);
	DDX_Control(pDX, IDC_COMBO37, mod4);
	DDX_Control(pDX, IDC_COMBO38, mod5);
	DDX_Control(pDX, IDC_COMBO39, mod6);
	DDX_Control(pDX, IDC_COMBO40, mod7);
	DDX_Control(pDX, IDC_COMBO41, mod8);
	DDX_Control(pDX, IDC_COMBO42, mod9);
	DDX_Control(pDX, IDC_COMBO43, mod10);
	DDX_Control(pDX, IDC_COMBO44, mod11);
	DDX_Control(pDX, IDC_COMBO45, mod12);
	DDX_Control(pDX, IDC_COMBO46, mod13);
	DDX_Control(pDX, IDC_COMBO47, mod14);
	DDX_Control(pDX, IDC_COMBO48, mod15);
	DDX_Control(pDX, IDC_COMBO49, mod16);
	DDX_Control(pDX, IDC_COMBO50, mod17);
	DDX_Control(pDX, IDC_COMBO51, mod18);
	DDX_Control(pDX, IDC_COMBO52, mod19);
	DDX_Control(pDX, IDC_COMBO53, mod20);
	DDX_Control(pDX, IDC_COMBO54, mod21);
	DDX_Control(pDX, IDC_COMBO55, mod22);
	DDX_Control(pDX, IDC_COMBO56, mod23);
	DDX_Control(pDX, IDC_COMBO57, mod24);
	DDX_Control(pDX, IDC_COMBO58, mod25);
	DDX_Control(pDX, IDC_COMBO59, mod26);
	DDX_Control(pDX, IDC_COMBO60, mod27);
	DDX_Control(pDX, IDC_COMBO61, mod28);
	DDX_Control(pDX, IDC_COMBO62, mod29);
	DDX_Control(pDX, IDC_COMBO63, mod30);
	//DDX_Control(pDX, IDC_COMBO64, select_module);
}


BEGIN_MESSAGE_MAP(CMyForm3, CFormView)
	ON_BN_CLICKED(IDC_BUTTON2, &CMyForm3::OnBnClickedButton2)
	ON_CBN_SELCHANGE(IDC_COMBO42, &CMyForm3::OnCbnSelchangeCombo42)
	ON_CBN_SELCHANGE(IDC_COMBO47, &CMyForm3::OnCbnSelchangeCombo47)
END_MESSAGE_MAP()


// CMyForm3 메시지 처리기


BOOL CMyForm3::Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.

	return CFormView::Create(lpszClassName, lpszWindowName, dwStyle, rect, pParentWnd, nID, pContext);
}


void CMyForm3::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();
	this->select_box.InsertString(0, _T("시간 설정"));
	this->select_box.InsertString(1, _T("정류 모듈 실장 유무"));
	this->select_box.InsertString(2, _T("정류 모듈 출력 설정"));
	this->select_box.InsertString(3, _T("충전 모드 설정"));
	this->select_box.InsertString(4, _T("자동충전 모드 설정"));
	this->select_box.InsertString(5, _T("정시이력 저장주기 및 경보이력 저장 건 수 설정"));

	this->charge_mode.InsertString(0, _T("0:자동 부동"));
	this->charge_mode.InsertString(1, _T("1:자동 균등"));
	this->charge_mode.InsertString(2, _T("2:수동 부동"));
	this->charge_mode.InsertString(3, _T("3:수동 균등"));
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	module_set[1] = &mod1;
	module_set[2] = &mod2;
	module_set[3] = &mod3;
	module_set[4] = &mod4;
	module_set[5] = &mod5;
	module_set[6] = &mod6;
	module_set[7] = &mod7;
	module_set[8] = &mod8;
	module_set[9] = &mod9;
	module_set[10] = &mod10;
	module_set[11] = &mod11;
	module_set[12] = &mod12;
	module_set[13] = &mod13;
	module_set[14] = &mod14;
	module_set[15] = &mod15;
	module_set[16] = &mod16;
	module_set[17] = &mod17;
	module_set[18] = &mod18;
	module_set[19] = &mod19;
	module_set[20] = &mod20;
	module_set[21] = &mod21;
	module_set[22] = &mod22;
	module_set[23] = &mod23;
	module_set[24] = &mod24;
	module_set[25] = &mod25;
	module_set[26] = &mod26;
	module_set[27] = &mod27;
	module_set[28] = &mod28;
	module_set[29] = &mod29;
	module_set[30] = &mod30;

	for (int i = 1; i <= 30; i++) {
		module_set[i]->InsertString(0, _T("O:실장"));
		module_set[i]->InsertString(1, _T("X:탈장"));
		module_set[i]->InsertString(2, _T("F:이상"));
		module_set[i]->InsertString(3, _T("!:설정 안됨"));
	}

	/*select_module.InsertString(0, _T("전체"));
	for (int i = 1; i <= 30; i++) {
		CString temp;
		temp.Format(_T("%d"), i);
		select_module.InsertString(i, temp);
	}*/
}


void CMyForm3::OnBnClickedButton2()
{
	CTime cTime = CTime::GetCurrentTime();
	CString strDate, strTime; // 반환되는 날짜와 시간을 저장할 CString 변수 선언

	strDate.Format(_T("%04d-%02d-%02d"), cTime.GetYear(), cTime.GetMonth(), cTime.GetDay());
	strTime.Format(_T("%02d:%02d:%02d"), cTime.GetHour(), cTime.GetMinute(), cTime.GetSecond());

	switch (select_box.GetCurSel()) {
	case 0:
		DT_activate(2);
		RUst_activate(0);
		RUout_activate(0);
		CM_activate(0);
		AC_activate(0);
		FI_activate(0); 
		
		/*section3_date.SetWindowTextA(strDate);
		section3_time.SetWindowTextA(strTime);*/
		break;

	case 1:
		DT_activate(0);
		RUst_activate(2);
		RUout_activate(0);
		CM_activate(0);
		AC_activate(0);
		FI_activate(0);

		break;

	case 2:
		DT_activate(0);
		RUst_activate(0);
		RUout_activate(2);
		CM_activate(0);
		AC_activate(0);
		FI_activate(0);

		/*RU_volt.SetWindowTextA(_T("0.0"));
		RU_curr.SetWindowTextA(_T("0.0"));*/
		break;

	case 3:
		DT_activate(0);
		RUst_activate(0);
		RUout_activate(0);
		CM_activate(2);
		AC_activate(0);
		FI_activate(0);

		/*charge_mode.SetCurSel(0);
		ec_volt.SetWindowTextA(_T("0.0"));
		fc_volt.SetWindowTextA(_T("0.0"));*/
		break;

	case 4:
		DT_activate(0);
		RUst_activate(0);
		RUout_activate(0);
		CM_activate(0);
		AC_activate(2);
		FI_activate(0);

		/*ec_point.SetWindowTextA(_T("0"));
		ec_curr.SetWindowTextA(_T("0.0"));
		endtime.SetWindowTextA(_T("0"));
		ec_interval.SetWindowTextA(_T("0.0"));*/
		break;

	case 5:
		DT_activate(0);
		RUst_activate(0);
		RUout_activate(0);
		CM_activate(0);
		AC_activate(0);
		FI_activate(2);

		/*fixed_interval.SetWindowTextA(_T("10"));
		num_cases.SetWindowTextA(_T("30"));*/
		break;
	default:
		break;
	}
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}

void CMyForm3::DT_activate(int set) {
	if (set == 0) {
		section3_date.EnableWindow(set);
		section3_time.EnableWindow(set);
	}

	else if (set == 1) {
		section3_date.EnableWindow(set);
		section3_time.EnableWindow(set);

		section3_date.SetReadOnly(set);
		section3_time.SetReadOnly(set);
	}

	else if (set == 2) {
		section3_date.EnableWindow(1);
		section3_time.EnableWindow(1);

		section3_date.SetReadOnly(0);
		section3_time.SetReadOnly(0);
	}
}

void CMyForm3::RUst_activate(int set) {
	//select_module.EnableWindow(set);

	for (int i = 1; i <= 30; i++) {
		module_set[i]->EnableWindow(set);
	}

	//select_module.SetCurSel(0);
}

void CMyForm3::RUout_activate(int set) {
	if (set == 0) {
		RU_volt.EnableWindow(set);
		RU_curr.EnableWindow(set);
	}

	else if (set == 1) {
		RU_volt.EnableWindow(set);
		RU_curr.EnableWindow(set);

		RU_volt.SetReadOnly(set);
		RU_curr.SetReadOnly(set);
	}

	else if (set == 2) {
		RU_volt.EnableWindow(1);
		RU_curr.EnableWindow(1);

		RU_volt.SetReadOnly(0);
		RU_curr.SetReadOnly(0);
	}
}

void CMyForm3::CM_activate(int set) {
	if (set == 0) {
		charge_mode.EnableWindow(set);
		ec_volt.EnableWindow(set);
		fc_volt.EnableWindow(set);
	}

	else if (set == 1) {
		charge_mode.EnableWindow(set);
		ec_volt.EnableWindow(set);
		fc_volt.EnableWindow(set);

		ec_volt.SetReadOnly(set);
		fc_volt.SetReadOnly(set);
	}

	else if (set == 2) {
		charge_mode.EnableWindow(1);
		ec_volt.EnableWindow(1);
		fc_volt.EnableWindow(1);

		ec_volt.SetReadOnly(0);
		fc_volt.SetReadOnly(0);
	}
}

void CMyForm3::AC_activate(int set) {
	if (set == 0) {
		ec_point.EnableWindow(set);
		ec_curr.EnableWindow(set);
		endtime.EnableWindow(set);
		ec_interval.EnableWindow(set);
	}

	else if (set == 1) {
		ec_point.EnableWindow(set);
		ec_curr.EnableWindow(set);
		endtime.EnableWindow(set);
		ec_interval.EnableWindow(set);

		ec_point.SetReadOnly(set);
		ec_curr.SetReadOnly(set);
		endtime.SetReadOnly(set);
		ec_interval.SetReadOnly(set);
	}

	else if (set == 2) {
		ec_point.EnableWindow(1);
		ec_curr.EnableWindow(1);
		endtime.EnableWindow(1);
		ec_interval.EnableWindow(1);

		ec_point.SetReadOnly(0);
		ec_curr.SetReadOnly(0);
		endtime.SetReadOnly(0);
		ec_interval.SetReadOnly(0);
	}
}

void CMyForm3::FI_activate(int set) {
	if (set == 0) {
		fixed_interval.EnableWindow(set);
		num_cases.EnableWindow(set);
	}

	else if (set == 1) {
		fixed_interval.EnableWindow(set);
		num_cases.EnableWindow(set);

		fixed_interval.SetReadOnly(set);
		num_cases.SetReadOnly(set);
	}

	else if (set == 2) {
		fixed_interval.EnableWindow(1);
		num_cases.EnableWindow(1);

		fixed_interval.SetReadOnly(0);
		num_cases.SetReadOnly(0);
	}
}


void CMyForm3::OnCbnSelchangeCombo42()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void CMyForm3::OnCbnSelchangeCombo47()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}
