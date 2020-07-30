// CMyForm5.cpp: 구현 파일
//

#include "stdafx.h"
#include "afxdialogex.h"
#include "ExamFormSwitching.h"
#include "CMyForm5.h"
#include "Port.h"

// CMyForm5

IMPLEMENT_DYNCREATE(CMyForm5, CFormView)

CMyForm5::CMyForm5()
	: CFormView(IDD_FORM_FORM5)
{

}

CMyForm5::CMyForm5(UINT nIDTemplate)
	: CFormView(nIDTemplate)
{

}

CMyForm5::~CMyForm5()
{
}

void CMyForm5::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	//DDX_Control(pDX, IDC_COMBO1, system_setting);
	DDX_Control(pDX, IDC_EDIT1, bat);
	DDX_Control(pDX, IDC_EDIT2, ac);
	DDX_Control(pDX, IDC_EDIT3, dc);
	DDX_Control(pDX, IDC_EDIT4, ru);
	DDX_Control(pDX, IDC_EDIT5, batt_part);
	DDX_Control(pDX, IDC_EDIT6, password);
	DDX_Control(pDX, IDC_EDIT7, system_set);
}

BEGIN_MESSAGE_MAP(CMyForm5, CFormView)
	ON_CBN_SELCHANGE(IDC_COMBO1, &CMyForm5::OnCbnSelchangeCombo1)
	//ON_BN_CLICKED(IDC_BUTTON2, &CMyForm5::OnBnClickedButton2)
	//ON_BN_CLICKED(IDC_BUTTON1, &CMyForm5::OnBnClickedButton1)
END_MESSAGE_MAP()


BOOL CMyForm5::Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.

	return CFormView::Create(lpszClassName, lpszWindowName, dwStyle, rect, pParentWnd, nID, pContext);
}


void CMyForm5::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();
	/*this->system_setting.InsertString(0, _T("단상 220V/25A"));
	this->system_setting.InsertString(1, _T("3상 380V/50A"));
	this->system_setting.InsertString(2, _T("3상 220V/100A"));
	this->system_setting.InsertString(3, _T("3상 380V/100A"));*/
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
}

// CMyForm5 진단

#ifdef _DEBUG
void CMyForm5::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CMyForm5::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CMyForm5 메시지 처리기


void CMyForm5::OnCbnSelchangeCombo1()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


/*void CMyForm5::OnBnClickedButton1()
{
	password.EnableWindow(0);
	//password.SetWindowTextA(_T(""));
	SY_activate(1);

	system_setting.SetCurSel(0);
	bat.SetWindowTextA(_T("1"));
	ac.SetWindowTextA(_T("1"));
	dc.SetWindowTextA(_T("1"));
	ru.SetWindowTextA(_T("1"));
	batt_part.SetWindowTextA(_T("1"));
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}*/

/*void CMyForm5::OnBnClickedButton2()
{
	password.EnableWindow(1);
	SY_activate(0);

	password.SetWindowTextA(_T("1234567"));
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}*/

void CMyForm5::SY_activate(BOOL set) {
	system_set.EnableWindow(set);
	bat.EnableWindow(set);
	ac.EnableWindow(set);
	dc.EnableWindow(set);
	ru.EnableWindow(set);
	batt_part.EnableWindow(set);

	system_set.SetReadOnly(set);
	bat.SetReadOnly(set);
	ac.SetReadOnly(set);
	dc.SetReadOnly(set);
	ru.SetReadOnly(set);
	batt_part.SetReadOnly(set);

	if (!set) {
		//system_setting.SetCurSel(0);
		bat.SetWindowTextA(_T(""));
		ac.SetWindowTextA(_T(""));
		dc.SetWindowTextA(_T(""));
		ru.SetWindowTextA(_T(""));
		batt_part.SetWindowTextA(_T(""));
	}
}



