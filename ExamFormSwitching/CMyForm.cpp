// CMyForm.cpp: 구현 파일
//

#include "stdafx.h"
#include "ExamFormSwitching.h"
#include "CMyForm.h"
#include "afxdialogex.h"


// CMyForm 대화 상자

IMPLEMENT_DYNAMIC(CMyForm, CFormView)

CMyForm::CMyForm()
	: CFormView(IDD_FORM_MYFORM)
{

}

CMyForm::CMyForm(UINT nIDTemplate)
	: CFormView(nIDTemplate)
{

}

CMyForm::~CMyForm()
{
}

void CMyForm::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CMyForm, CFormView)
END_MESSAGE_MAP()


// CMyForm 메시지 처리기


BOOL CMyForm::Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.

	return CFormView::Create(lpszClassName, lpszWindowName, dwStyle, rect, pParentWnd, nID, pContext);
}


void CMyForm::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
}
