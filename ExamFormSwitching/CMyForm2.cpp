// CMyForm2.cpp: 구현 파일
//

#include "stdafx.h"
#include "ExamFormSwitching.h"
#include "ExamFormSwitchingDlg.h"
#include "CMyForm2.h"
#include "afxdialogex.h"
#include "Port.h"


// CMyForm2 대화 상자

IMPLEMENT_DYNAMIC(CMyForm2, CFormView)

CMyForm2::CMyForm2()
	: CFormView(IDD_FORM_FORM2)
{

}

CMyForm2::CMyForm2(UINT nIDTemplate)
	: CFormView(nIDTemplate)
{

}

CMyForm2::~CMyForm2()
{
}

void CMyForm2::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO1, select_measure);
	DDX_Control(pDX, IDC_EDIT8, AC_state);
	//  DDX_Control(pDX, IDC_EDIT10, AC_input_cmax);
	DDX_Control(pDX, IDC_EDIT10, AC_input_vmax);
	DDX_Control(pDX, IDC_EDIT11, AC_input_vmin);
	DDX_Control(pDX, IDC_EDIT12, AC_input_cmax);
	DDX_Control(pDX, IDC_EDIT13, AC_input_cmin);
	//  DDX_Control(pDX, IDC_EDIT14, batt_vamx);
	DDX_Control(pDX, IDC_EDIT14, batt_vmax);
	DDX_Control(pDX, IDC_EDIT15, batt_vmin);
	DDX_Control(pDX, IDC_EDIT16, batt_tvmax);
	DDX_Control(pDX, IDC_EDIT17, batt_tvmin);
	//  DDX_Control(pDX, IDC_EDIT20, DC_ouput_vmax);
	//  DDX_Control(pDX, IDC_EDIT21, DC_total_vmin);
	//  DDX_Control(pDX, IDC_EDIT22, DC_ouput_cmax);
	//  DDX_Control(pDX, IDC_EDIT23, RU_ouput_vmax);
	DDX_Control(pDX, IDC_EDIT82, RU_output_vmin);
	//  DDX_Control(pDX, IDC_EDIT21, DC_ouput_vmin);
	DDX_Control(pDX, IDC_EDIT20, DC_output_vmax);
	DDX_Control(pDX, IDC_EDIT21, DC_output_vmin);
	DDX_Control(pDX, IDC_EDIT22, DC_output_cmax);
	DDX_Control(pDX, IDC_EDIT23, RU_output_vamx);
}


BEGIN_MESSAGE_MAP(CMyForm2, CFormView)
	ON_BN_CLICKED(IDC_BUTTON2, &CMyForm2::OnBnClickedButton2)
END_MESSAGE_MAP()


// CMyForm2 메시지 처리기


BOOL CMyForm2::Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.

	return CFormView::Create(lpszClassName, lpszWindowName, dwStyle, rect, pParentWnd, nID, pContext);
}


void CMyForm2::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();
	this->select_measure.InsertString(0, _T("교류배전부"));
	this->select_measure.InsertString(1, _T("직류제어부"));
	this->select_measure.InsertString(2, _T("정류유니트부"));
	this->select_measure.InsertString(3, _T("축전지셀"));

	this->select_measure.SetCurSel(-1);
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
}

void CMyForm2::AC_activate(int set) {			//교류배전부 활성화/비활성화
	if (set == 0) {
		AC_state.EnableWindow(set);
		AC_input_vmax.EnableWindow(set);
		AC_input_vmin.EnableWindow(set);
		AC_input_cmax.EnableWindow(set);
		AC_input_cmin.EnableWindow(set);
	}

	else if (set == 1) {
		AC_state.EnableWindow(set);
		AC_input_vmax.EnableWindow(set);
		AC_input_vmin.EnableWindow(set);
		AC_input_cmax.EnableWindow(set);
		AC_input_cmin.EnableWindow(set);

		AC_state.SetReadOnly(set);
		AC_input_vmax.SetReadOnly(set);
		AC_input_vmin.SetReadOnly(set);
		AC_input_cmax.SetReadOnly(set);
		AC_input_cmin.SetReadOnly(set);
	}

	else if(set == 2) {
		AC_state.EnableWindow(1);
		AC_input_vmax.EnableWindow(1);
		AC_input_vmin.EnableWindow(1);
		AC_input_cmax.EnableWindow(1);
		AC_input_cmin.EnableWindow(1);

		AC_state.SetReadOnly(0);
		AC_input_vmax.SetReadOnly(0);
		AC_input_vmin.SetReadOnly(0);
		AC_input_cmax.SetReadOnly(0);
		AC_input_cmin.SetReadOnly(0);
	}
}

void CMyForm2::DC_activate(int set) {			//직류제어부 활성화/비활성화
	if (set == 0) {
		DC_output_vmax.EnableWindow(set);
		DC_output_vmin.EnableWindow(set);
		DC_output_cmax.EnableWindow(set);
	}

	else if (set == 1) {
		DC_output_vmax.EnableWindow(set);
		DC_output_vmin.EnableWindow(set);
		DC_output_cmax.EnableWindow(set);

		DC_output_vmax.SetReadOnly(set);
		DC_output_vmin.SetReadOnly(set);
		DC_output_cmax.SetReadOnly(set);
	}

	else if(set == 2) {
		DC_output_vmax.EnableWindow(1);
		DC_output_vmin.EnableWindow(1);
		DC_output_cmax.EnableWindow(1);

		DC_output_vmax.SetReadOnly(0);
		DC_output_vmin.SetReadOnly(0);
		DC_output_cmax.SetReadOnly(0);
	}
}

void CMyForm2::BAT_activate(int set) {			//축전지부 활성화/비활성화
	if (set == 0) {
		batt_vmax.EnableWindow(set);
		batt_vmin.EnableWindow(set);
		batt_tvmax.EnableWindow(set);
		batt_tvmin.EnableWindow(set);
	}

	else if (set == 1) {
		batt_vmax.EnableWindow(set);
		batt_vmin.EnableWindow(set);
		batt_tvmax.EnableWindow(set);
		batt_tvmin.EnableWindow(set);

		batt_vmax.SetReadOnly(set);
		batt_vmin.SetReadOnly(set);
		batt_tvmax.SetReadOnly(set);
		batt_tvmin.SetReadOnly(set);
	}

	else if (set == 2) {
		batt_vmax.EnableWindow(1);
		batt_vmin.EnableWindow(1);
		batt_tvmax.EnableWindow(1);
		batt_tvmin.EnableWindow(1);

		batt_vmax.SetReadOnly(0);
		batt_vmin.SetReadOnly(0);
		batt_tvmax.SetReadOnly(0);
		batt_tvmin.SetReadOnly(0);
	}
}

void CMyForm2::RU_activate(int set) {			//정류유니트부 활성화/비활성화
	if (set == 0) {
		RU_output_vamx.EnableWindow(set);
		RU_output_vmin.EnableWindow(set);
	}

	else if (set == 1) {
		RU_output_vamx.EnableWindow(set);
		RU_output_vmin.EnableWindow(set);

		RU_output_vamx.SetReadOnly(set);
		RU_output_vmin.SetReadOnly(set);
	}

	if (set == 2) {
		RU_output_vamx.EnableWindow(1);
		RU_output_vmin.EnableWindow(1);

		RU_output_vamx.SetReadOnly(0);
		RU_output_vmin.SetReadOnly(0);
	}
}


void CMyForm2::OnBnClickedButton2()				//선택한 파트 활성화 실행버튼
{
	switch (select_measure.GetCurSel()) {
	case 0:
		AC_activate(2);
		DC_activate(0);
		RU_activate(0);
		BAT_activate(0);

		/*AC_state.SetWindowTextA(_T("1"));
		AC_input_vmax.SetWindowTextA(_T("0.0"));
		AC_input_vmin.SetWindowTextA(_T("0.0"));
		AC_input_cmax.SetWindowTextA(_T("0.0"));
		AC_input_cmin.SetWindowTextA(_T("0.0"));*/
		break;
	case 1:
		AC_activate(0);
		DC_activate(2);
		RU_activate(0);
		BAT_activate(0);

		/*DC_output_vmax.SetWindowTextA(_T("0.0"));
		DC_output_vmin.SetWindowTextA(_T("0.0"));
		DC_output_cmax.SetWindowTextA(_T("0.0"));*/
		break;
	case 2:
		AC_activate(0);
		DC_activate(0);
		RU_activate(2);
		BAT_activate(0);

		/*RU_output_vamx.SetWindowTextA(_T("0.0"));
		RU_output_vmin.SetWindowTextA(_T("0.0"));*/
		break;
	case 3:
		AC_activate(0);
		DC_activate(0);
		RU_activate(0);
		BAT_activate(2);

		/*batt_vmax.SetWindowTextA(_T("0.0"));
		batt_vmin.SetWindowTextA(_T("0.0"));
		batt_tvmax.SetWindowTextA(_T("0.0"));
		batt_tvmin.SetWindowTextA(_T("0.0"));*/
		break;
	default:
		break;
	}
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}
