// CMyForm1.cpp: 구현 파일
//

#include "stdafx.h"
#include "ExamFormSwitching.h"
#include "CMyForm1.h"
#include "afxdialogex.h"
#include "Port.h"


// CMyForm1 대화 상자

IMPLEMENT_DYNAMIC(CMyForm1, CFormView)

CMyForm1::CMyForm1()
	: CFormView(IDD_FORM_FORM1)
{

}

CMyForm1::CMyForm1(UINT nIDTemplate)
	: CFormView(nIDTemplate)
{

}
CMyForm1::~CMyForm1()
{
}

void CMyForm1::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	//DDX_Control(pDX, IDC_COMBO1, section1_facility);
	DDX_Control(pDX, IDC_COMBO4, mod1_state);
	DDX_Control(pDX, IDC_COMBO5, mod2_state);
	DDX_Control(pDX, IDC_COMBO6, mod3_state);
	DDX_Control(pDX, IDC_COMBO7, mod4_state);
	DDX_Control(pDX, IDC_COMBO8, mod5_state);
	DDX_Control(pDX, IDC_COMBO9, mod6_state);
	DDX_Control(pDX, IDC_COMBO10, mod7_state);
	DDX_Control(pDX, IDC_COMBO11, mod8_state);
	DDX_Control(pDX, IDC_COMBO12, mod9_state);
	DDX_Control(pDX, IDC_COMBO13, mod10_state);
	DDX_Control(pDX, IDC_COMBO14, mod11_state);
	DDX_Control(pDX, IDC_COMBO15, mod12_state);
	DDX_Control(pDX, IDC_COMBO16, mod13_state);
	DDX_Control(pDX, IDC_COMBO17, mod14_state);
	DDX_Control(pDX, IDC_COMBO18, mod15_state);
	DDX_Control(pDX, IDC_COMBO19, mod16_state);
	DDX_Control(pDX, IDC_COMBO20, mod17_state);
	DDX_Control(pDX, IDC_COMBO21, mod18_state);
	DDX_Control(pDX, IDC_COMBO22, mod19_state);
	DDX_Control(pDX, IDC_COMBO23, mod20_state);
	DDX_Control(pDX, IDC_COMBO24, mod21_state);
	DDX_Control(pDX, IDC_COMBO25, mod22_state);
	DDX_Control(pDX, IDC_COMBO26, mod23_state);
	DDX_Control(pDX, IDC_COMBO27, mod24_state);
	DDX_Control(pDX, IDC_COMBO28, mod25_state);
	DDX_Control(pDX, IDC_COMBO29, mod26_state);
	DDX_Control(pDX, IDC_COMBO30, mod27_state);
	DDX_Control(pDX, IDC_COMBO31, mod28_state);
	DDX_Control(pDX, IDC_COMBO32, mod29_state);
	DDX_Control(pDX, IDC_COMBO33, mod30_state);
	DDX_Control(pDX, IDC_COMBO2, operate_mode);
	DDX_Control(pDX, IDC_COMBO3, charge_mode);
	DDX_Control(pDX, IDC_COMBO34, monitor_state);
	DDX_Control(pDX, IDC_EDIT9, facility_no);
	DDX_Control(pDX, IDC_EDIT6, section1_date);
	DDX_Control(pDX, IDC_EDIT7, section1_time);
	DDX_Control(pDX, IDC_EDIT8, AC_state);
	DDX_Control(pDX, IDC_EDIT10, AC_temp);
	DDX_Control(pDX, IDC_EDIT11, AC_ouput_volt);
	DDX_Control(pDX, IDC_EDIT12, AC_load_curr);
	DDX_Control(pDX, IDC_EDIT13, AC_batt_curr);
	DDX_Control(pDX, IDC_EDIT14, AC_rv);
	DDX_Control(pDX, IDC_EDIT16, AC_sv);
	DDX_Control(pDX, IDC_EDIT18, AC_tv);
	DDX_Control(pDX, IDC_EDIT15, AC_rc);
	DDX_Control(pDX, IDC_EDIT17, AC_sc);
	DDX_Control(pDX, IDC_EDIT19, AC_tc);
	DDX_Control(pDX, IDC_EDIT21, extend_com);
	DDX_Control(pDX, IDC_CHECK1, load_fuse_error);
	DDX_Control(pDX, IDC_CHECK2, batt_fuse_error);
	DDX_Control(pDX, IDC_EDIT22, volt_mod1);
	DDX_Control(pDX, IDC_EDIT24, volt_mod2);
	DDX_Control(pDX, IDC_EDIT26, volt_mod3);
	DDX_Control(pDX, IDC_EDIT28, volt_mod4);
	DDX_Control(pDX, IDC_EDIT30, volt_mod5);
	DDX_Control(pDX, IDC_EDIT32, volt_mod6);
	DDX_Control(pDX, IDC_EDIT34, volt_mod7);
	DDX_Control(pDX, IDC_EDIT36, volt_mod8);
	DDX_Control(pDX, IDC_EDIT38, volt_mod9);
	DDX_Control(pDX, IDC_EDIT40, volt_mod10);
	DDX_Control(pDX, IDC_EDIT42, volt_mod11);
	DDX_Control(pDX, IDC_EDIT44, volt_mod12);
	DDX_Control(pDX, IDC_EDIT46, volt_mod13);
	DDX_Control(pDX, IDC_EDIT48, volt_mod14);
	DDX_Control(pDX, IDC_EDIT50, volt_mod15);
	DDX_Control(pDX, IDC_EDIT52, volt_mod16);
	DDX_Control(pDX, IDC_EDIT54, volt_mod17);
	DDX_Control(pDX, IDC_EDIT56, volt_mod18);
	DDX_Control(pDX, IDC_EDIT58, volt_mod19);
	DDX_Control(pDX, IDC_EDIT60, volt_mod20);
	DDX_Control(pDX, IDC_EDIT62, volt_mod21);
	DDX_Control(pDX, IDC_EDIT64, volt_mod22);
	DDX_Control(pDX, IDC_EDIT66, volt_mod23);
	DDX_Control(pDX, IDC_EDIT68, volt_mod24);
	DDX_Control(pDX, IDC_EDIT70, volt_mod25);
	DDX_Control(pDX, IDC_EDIT72, volt_mod26);
	DDX_Control(pDX, IDC_EDIT74, volt_mod27);
	DDX_Control(pDX, IDC_EDIT76, volt_mod28);
	DDX_Control(pDX, IDC_EDIT78, volt_mod29);
	DDX_Control(pDX, IDC_EDIT80, volt_mod30);
	DDX_Control(pDX, IDC_EDIT23, curr_mod1);
	DDX_Control(pDX, IDC_EDIT25, curr_mod2);
	DDX_Control(pDX, IDC_EDIT27, curr_mod3);
	DDX_Control(pDX, IDC_EDIT29, curr_mod4);
	DDX_Control(pDX, IDC_EDIT31, curr_mod5);
	DDX_Control(pDX, IDC_EDIT33, curr_mod6);
	DDX_Control(pDX, IDC_EDIT35, curr_mod7);
	DDX_Control(pDX, IDC_EDIT37, curr_mod8);
	DDX_Control(pDX, IDC_EDIT39, curr_mod9);
	DDX_Control(pDX, IDC_EDIT41, curr_mod10);
	DDX_Control(pDX, IDC_EDIT43, curr_mod11);
	DDX_Control(pDX, IDC_EDIT45, curr_mod12);
	DDX_Control(pDX, IDC_EDIT47, curr_mod13);
	DDX_Control(pDX, IDC_EDIT49, curr_mod14);
	DDX_Control(pDX, IDC_EDIT51, curr_mod15);
	DDX_Control(pDX, IDC_EDIT53, curr_mod16);
	DDX_Control(pDX, IDC_EDIT55, curr_mod17);
	DDX_Control(pDX, IDC_EDIT57, curr_mod18);
	DDX_Control(pDX, IDC_EDIT59, curr_mod19);
	DDX_Control(pDX, IDC_EDIT61, curr_mod20);
	DDX_Control(pDX, IDC_EDIT63, curr_mod21);
	DDX_Control(pDX, IDC_EDIT65, curr_mod22);
	DDX_Control(pDX, IDC_EDIT67, curr_mod23);
	DDX_Control(pDX, IDC_EDIT69, curr_mod24);
	DDX_Control(pDX, IDC_EDIT71, curr_mod25);
	DDX_Control(pDX, IDC_EDIT73, curr_mod26);
	DDX_Control(pDX, IDC_EDIT75, curr_mod27);
	DDX_Control(pDX, IDC_EDIT77, curr_mod28);
	DDX_Control(pDX, IDC_EDIT79, curr_mod29);
	DDX_Control(pDX, IDC_EDIT81, curr_mod30);
	//DDX_Control(pDX, IDC_COMBO35, alarm_target);
	DDX_Control(pDX, IDC_CHECK11, AD_alarm);
	DDX_Control(pDX, IDC_CHECK14, DC_alarm);
	DDX_Control(pDX, IDC_CHECK13, RU_alarm);
	DDX_Control(pDX, IDC_CHECK12, BU_alarm);
	DDX_Control(pDX, IDC_COMBO35, OV_box);
	DDX_Control(pDX, IDC_COMBO38, LC_box);
	DDX_Control(pDX, IDC_COMBO65, RV_box);
	DDX_Control(pDX, IDC_COMBO66, SV_box);
	DDX_Control(pDX, IDC_COMBO67, TV_box);
	DDX_Control(pDX, IDC_COMBO68, RC_box);
	DDX_Control(pDX, IDC_COMBO69, SC_box);
	DDX_Control(pDX, IDC_COMBO70, TC_box);
}


BEGIN_MESSAGE_MAP(CMyForm1, CFormView)
	ON_CBN_SELCHANGE(IDC_COMBO1, &CMyForm1::OnCbnSelchangeCombo1)
	ON_CBN_SELCHANGE(IDC_COMBO4, &CMyForm1::OnCbnSelchangeCombo4)
	ON_CBN_SELCHANGE(IDC_COMBO3, &CMyForm1::OnCbnSelchangeCombo3)
	ON_CBN_SELCHANGE(IDC_COMBO34, &CMyForm1::OnCbnSelchangeCombo34)
	//ON_BN_CLICKED(IDC_BUTTON2, &CMyForm1::OnBnClickedButton2)
	ON_CBN_SELCHANGE(IDC_COMBO15, &CMyForm1::OnCbnSelchangeCombo15)
	ON_CBN_SELCHANGE(IDC_COMBO17, &CMyForm1::OnCbnSelchangeCombo17)
	ON_BN_CLICKED(IDC_CHECK11, &CMyForm1::OnBnClickedCheck11)
	ON_BN_CLICKED(IDC_CHECK2, &CMyForm1::OnBnClickedCheck2)
END_MESSAGE_MAP()


// CMyForm1 메시지 처리기


BOOL CMyForm1::Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.

	return CFormView::Create(lpszClassName, lpszWindowName, dwStyle, rect, pParentWnd, nID, pContext);
}


void CMyForm1::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();
	/*this->section1_facility.InsertString(0, _T("전체"));
	this->section1_facility.InsertString(1, _T("교류배전부"));
	this->section1_facility.InsertString(2, _T("직류제어부"));
	this->section1_facility.InsertString(3, _T("정류유니트부"));*/

	this->operate_mode.InsertString(0, _T("자동운전"));
	this->operate_mode.InsertString(1, _T("수동운전"));

	this->charge_mode.InsertString(0, _T("자동 부동"));
	this->charge_mode.InsertString(1, _T("자동 균등"));
	this->charge_mode.InsertString(2, _T("수동 부동"));
	this->charge_mode.InsertString(3, _T("수동 균등"));

	this->monitor_state.InsertString(0, _T("정상"));
	this->monitor_state.InsertString(1, _T("이상"));

	/*this->alarm_target.InsertString(0, _T("교류배전부"));
	this->alarm_target.InsertString(1, _T("직류제어부"));
	this->alarm_target.InsertString(2, _T("정류유니트부"));
	this->alarm_target.InsertString(3, _T("축전지셀"));*/

	mod_state[1]  = &mod1_state;
	mod_state[2]  = &mod2_state;
	mod_state[3]  = &mod3_state;
	mod_state[4]  = &mod4_state;
	mod_state[5]  = &mod5_state;
	mod_state[6]  = &mod6_state;
	mod_state[7]  = &mod7_state;
	mod_state[8]  = &mod8_state;
	mod_state[9]  = &mod9_state;
	mod_state[10] = &mod10_state;
	mod_state[11] = &mod11_state;
	mod_state[12] = &mod12_state;
	mod_state[13] = &mod13_state;
	mod_state[14] = &mod14_state;
	mod_state[15] = &mod15_state;
	mod_state[16] = &mod16_state;
	mod_state[17] = &mod17_state;
	mod_state[18] = &mod18_state;
	mod_state[19] = &mod19_state;
	mod_state[20] = &mod20_state;
	mod_state[21] = &mod21_state;
	mod_state[22] = &mod22_state;
	mod_state[23] = &mod23_state;
	mod_state[24] = &mod24_state;
	mod_state[25] = &mod25_state;
	mod_state[26] = &mod26_state;
	mod_state[27] = &mod27_state;
	mod_state[28] = &mod28_state;
	mod_state[29] = &mod29_state;
	mod_state[30] = &mod30_state;
	
	volt_mod[1]  = &volt_mod1;
	volt_mod[2]  = &volt_mod2;
	volt_mod[3]  = &volt_mod3;
	volt_mod[4]  = &volt_mod4;
	volt_mod[5]  = &volt_mod5;
	volt_mod[6]  = &volt_mod6;
	volt_mod[7]  = &volt_mod7;
	volt_mod[8]  = &volt_mod8;
	volt_mod[9]  = &volt_mod9;
	volt_mod[10] = &volt_mod10;
	volt_mod[11] = &volt_mod11;
	volt_mod[12] = &volt_mod12;
	volt_mod[13] = &volt_mod13;
	volt_mod[14] = &volt_mod14;
	volt_mod[15] = &volt_mod15;
	volt_mod[16] = &volt_mod16;
	volt_mod[17] = &volt_mod17;
	volt_mod[18] = &volt_mod18;
	volt_mod[19] = &volt_mod19;
	volt_mod[20] = &volt_mod20;
	volt_mod[21] = &volt_mod21;
	volt_mod[22] = &volt_mod22;
	volt_mod[23] = &volt_mod23;
	volt_mod[24] = &volt_mod24;
	volt_mod[25] = &volt_mod25;
	volt_mod[26] = &volt_mod26;
	volt_mod[27] = &volt_mod27;
	volt_mod[28] = &volt_mod28;
	volt_mod[29] = &volt_mod29;
	volt_mod[30] = &volt_mod30;

	curr_mod[1]  = &curr_mod1;
	curr_mod[2]  = &curr_mod2;
	curr_mod[3]  = &curr_mod3;
	curr_mod[4]  = &curr_mod4;
	curr_mod[5]  = &curr_mod5;
	curr_mod[6]  = &curr_mod6;
	curr_mod[7]  = &curr_mod7;
	curr_mod[8]  = &curr_mod8;
	curr_mod[9]  = &curr_mod9;
	curr_mod[10] = &curr_mod10;
	curr_mod[11] = &curr_mod11;
	curr_mod[12] = &curr_mod12;
	curr_mod[13] = &curr_mod13;
	curr_mod[14] = &curr_mod14;
	curr_mod[15] = &curr_mod15;
	curr_mod[16] = &curr_mod16;
	curr_mod[17] = &curr_mod17;
	curr_mod[18] = &curr_mod18;
	curr_mod[19] = &curr_mod19;
	curr_mod[20] = &curr_mod20;
	curr_mod[21] = &curr_mod21;
	curr_mod[22] = &curr_mod22;
	curr_mod[23] = &curr_mod23;
	curr_mod[24] = &curr_mod24;
	curr_mod[25] = &curr_mod25;
	curr_mod[26] = &curr_mod26;
	curr_mod[27] = &curr_mod27;
	curr_mod[28] = &curr_mod28;
	curr_mod[29] = &curr_mod29;
	curr_mod[30] = &curr_mod30;

	for (int i = 1; i <= 30; i++) {
		mod_state[i]->InsertString(0, _T("정상"));
		mod_state[i]->InsertString(1, _T("탈장"));
		mod_state[i]->InsertString(2, _T("통신"));
		mod_state[i]->InsertString(3, _T("모드"));
		mod_state[i]->InsertString(4, _T("전류 limit"));
		mod_state[i]->InsertString(5, _T("저전압"));
		mod_state[i]->InsertString(6, _T("고전압"));
		mod_state[i]->InsertString(7, _T("온도"));
		mod_state[i]->InsertString(8, _T("입력"));
	}
	
	OV_box.InsertString(0, _T("정상"));
	OV_box.InsertString(1, _T("Low"));
	OV_box.InsertString(2, _T("High"));

	LC_box.InsertString(0, _T("정상"));
	LC_box.InsertString(1, _T("Low"));
	LC_box.InsertString(2, _T("High"));

	RV_box.InsertString(0, _T("정상"));
	RV_box.InsertString(1, _T("Low"));
	RV_box.InsertString(2, _T("High"));

	SV_box.InsertString(0, _T("정상"));
	SV_box.InsertString(1, _T("Low"));
	SV_box.InsertString(2, _T("High"));

	TV_box.InsertString(0, _T("정상"));
	TV_box.InsertString(1, _T("Low"));
	TV_box.InsertString(2, _T("High"));

	RC_box.InsertString(0, _T("정상"));
	RC_box.InsertString(1, _T("Low"));
	RC_box.InsertString(2, _T("High"));

	SC_box.InsertString(0, _T("정상"));
	SC_box.InsertString(1, _T("Low"));
	SC_box.InsertString(2, _T("High"));

	TC_box.InsertString(0, _T("정상"));
	TC_box.InsertString(1, _T("Low"));
	TC_box.InsertString(2, _T("High"));
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
}


void CMyForm1::OnCbnSelchangeCombo1()
{
	
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void CMyForm1::OnCbnSelchangeCombo4()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void CMyForm1::OnCbnSelchangeCombo3()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}

void CMyForm1::AC_activate(BOOL set) {		//교류배전부 활성화/비활성화
	AC_state.EnableWindow(set);
	AC_temp.EnableWindow(set);
	AC_ouput_volt.EnableWindow(set);
	AC_load_curr.EnableWindow(set);
	AC_batt_curr.EnableWindow(set);
	AC_rv.EnableWindow(set);
	AC_sv.EnableWindow(set);
	AC_tv.EnableWindow(set);
	AC_rc.EnableWindow(set);
	AC_sc.EnableWindow(set);
	AC_tc.EnableWindow(set);
	((CComboBox*)GetDlgItem(IDC_COMBO35))->EnableWindow(set);
	((CComboBox*)GetDlgItem(IDC_COMBO38))->EnableWindow(set);
	RV_box.EnableWindow(set);
	SV_box.EnableWindow(set);
	TV_box.EnableWindow(set);
	RC_box.EnableWindow(set);
	SC_box.EnableWindow(set);
	TC_box.EnableWindow(set);

	if (!set) {
		AC_state.SetWindowTextA(_T(""));
		AC_temp.SetWindowTextA(_T(""));
		AC_ouput_volt.SetWindowTextA(_T(""));
		AC_load_curr.SetWindowTextA(_T(""));
		AC_batt_curr.SetWindowTextA(_T(""));

		AC_rc.SetWindowTextA(_T(""));
		AC_rv.SetWindowTextA(_T(""));
		AC_sc.SetWindowTextA(_T(""));
		AC_sv.SetWindowTextA(_T(""));
		AC_tv.SetWindowTextA(_T(""));
		AC_tc.SetWindowTextA(_T(""));
	}
}

void CMyForm1::DC_activate(BOOL set) {			//직류제어부 활성화/비활성화
	operate_mode.EnableWindow(set);
	charge_mode.EnableWindow(set);
	monitor_state.EnableWindow(set);
	extend_com.EnableWindow(set);
	load_fuse_error.EnableWindow(set);
	batt_fuse_error.EnableWindow(set);

	if (!set) {
		operate_mode.SetCurSel(-1);
		charge_mode.SetCurSel(-1);
		monitor_state.SetCurSel(-1);
		extend_com.SetWindowTextA(_T(""));
	}
}

void CMyForm1::MOD_activate(BOOL set, int mod) {		//정류유니트부 활성화/비활성화
	for (int i = 1; i <= mod; i++) {
		volt_mod[i]->EnableWindow(set);
		curr_mod[i]->EnableWindow(set);
		mod_state[i]->EnableWindow(set);
	}

	if (!set) {
		for (int i = 1; i <= mod; i++) {
			volt_mod[i]->SetWindowTextA(_T(""));
			curr_mod[i]->SetWindowTextA(_T(""));
			mod_state[i]->SetCurSel(-1);
		}
	}
}

void CMyForm1::OnCbnSelchangeCombo34()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


/*void CMyForm1::OnBnClickedButton2()
{
	CTime cTime = CTime::GetCurrentTime();
	CString strDate, strTime; // 반환되는 날짜와 시간을 저장할 CString 변수 선언

	strDate.Format(_T("%04d-%02d-%02d"), cTime.GetYear(), cTime.GetMonth(), cTime.GetDay());
	strTime.Format(_T("%02d:%02d:%02d"), cTime.GetHour(), cTime.GetMinute(), cTime.GetSecond());

	switch (section1_facility.GetCurSel()) {
	case 0:
		facility_no.EnableWindow(false);
		section1_date.EnableWindow(true);
		section1_time.EnableWindow(true);
		//alarm_target.EnableWindow(true);
		AC_activate(true);
		DC_activate(false);
		MOD_activate(false, 30);

		section1_date.SetWindowTextA(strDate);
		section1_time.SetWindowTextA(strTime);
		alarm_target.SetCurSel(0);

		AC_state.SetWindowTextA(_T("0"));
		AC_temp.SetWindowTextA(_T("0.0"));
		AC_ouput_volt.SetWindowTextA(_T("0.0"));
		AC_load_curr.SetWindowTextA(_T("0.0"));
		AC_batt_curr.SetWindowTextA(_T("0.0"));
		
		AC_rc.SetWindowTextA(_T("0.0"));
		AC_rv.SetWindowTextA(_T("0.0"));
		AC_sc.SetWindowTextA(_T("0.0"));
		AC_sv.SetWindowTextA(_T("0.0"));
		AC_tv.SetWindowTextA(_T("0.0"));
		AC_tc.SetWindowTextA(_T("0.0"));

		section1_date.SetReadOnly(1);
		section1_time.SetReadOnly(1);
		break;
	case 1:
		facility_no.EnableWindow(true);
		section1_date.EnableWindow(false);
		section1_time.EnableWindow(false);
		alarm_target.EnableWindow(false);
		AC_activate(true);
		DC_activate(false);
		MOD_activate(false, 30);

		section1_date.SetWindowTextA(_T(""));
		section1_time.SetWindowTextA(_T(""));
		alarm_target.SetCurSel(-1);

		facility_no.SetWindowTextA(_T("1"));
		AC_state.SetWindowTextA(_T("0"));
		AC_temp.SetWindowTextA(_T("0.0"));
		AC_ouput_volt.SetWindowTextA(_T("0.0"));
		AC_load_curr.SetWindowTextA(_T("0.0"));
		AC_batt_curr.SetWindowTextA(_T("0.0"));

		AC_rc.SetWindowTextA(_T("0.0"));
		AC_rv.SetWindowTextA(_T("0.0"));
		AC_sc.SetWindowTextA(_T("0.0"));
		AC_sv.SetWindowTextA(_T("0.0"));
		AC_tv.SetWindowTextA(_T("0.0"));
		AC_tc.SetWindowTextA(_T("0.0"));
		break;
	case 2:
		facility_no.EnableWindow(true);
		section1_date.EnableWindow(false);
		section1_time.EnableWindow(false);
		alarm_target.EnableWindow(false);
		AC_activate(false);
		DC_activate(true);
		MOD_activate(false, 30);

		section1_date.SetWindowTextA(_T(""));
		section1_time.SetWindowTextA(_T(""));
		alarm_target.SetCurSel(-1);

		operate_mode.SetCurSel(0);
		charge_mode.SetCurSel(0);
		monitor_state.SetCurSel(0);
		extend_com.SetWindowTextA(_T("1"));
		break;
	case 3:
		facility_no.EnableWindow(false);
		section1_date.EnableWindow(false);
		section1_time.EnableWindow(false);
		alarm_target.EnableWindow(false);
		AC_activate(false);
		DC_activate(false);
		MOD_activate(true, 30);

		section1_date.SetWindowTextA(_T(""));
		section1_time.SetWindowTextA(_T(""));
		alarm_target.SetCurSel(-1);

		section1_date.SetWindowTextA(_T(""));
		section1_time.SetWindowTextA(_T(""));
		alarm_target.SetCurSel(-1);

		for (int i = 1; i <= 30; i++) {
			volt_mod[i]->SetWindowTextA(_T("0.0"));
			curr_mod[i]->SetWindowTextA(_T("0.0"));
			mod_state[i]->SetCurSel(0);
		}
		break;
	default:
		facility_no.EnableWindow(false);
		section1_date.EnableWindow(false);
		section1_time.EnableWindow(false);
		alarm_target.EnableWindow(false);
		AC_activate(false);
		DC_activate(false);
		MOD_activate(false, 30);
		break;

	}
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}*/


void CMyForm1::OnBnClickedRadio7()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void CMyForm1::OnCbnSelchangeCombo15()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void CMyForm1::OnCbnSelchangeCombo17()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void CMyForm1::OnBnClickedCheck11()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void CMyForm1::OnBnClickedCheck2()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}
