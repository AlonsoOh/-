#pragma once
// CMyForm5 폼 보기
class CMyForm5 : public CFormView
{
	DECLARE_DYNCREATE(CMyForm5)

public:
	CMyForm5();           // 동적 만들기에 사용되는 protected 생성자입니다.
	CMyForm5(UINT nIDTemplate);
	virtual ~CMyForm5();

#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_FORM_FORM5 };
#endif
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext = NULL);
	virtual void OnInitialUpdate();
	afx_msg void OnCbnSelchangeCombo1();
	void CMyForm5::SY_activate(BOOL set);
	CComboBox system_setting;		
	CEdit bat;						//경보발생한 시설 번호 표시
	CEdit ac;
	CEdit dc;
	CEdit ru;
	CEdit batt_part;				//축전지 조수
	//afx_msg void OnBnClickedButton2();
	//afx_msg void OnBnClickedButton1();
	CEdit password;					//비밀번호
	CEdit system_set;				// 시스템 설정 상태(예 : 단상 220V / 25A)
};

typedef struct S5_info {
	CString password = _T("000000");			//비밀번호
	char	system_set = char(0x31);			//시스템 상태
	int		bat_num = int(5);					//축전지 조수
	int		alarm_AD = int(3);					//경보발생 시설 번호 0이면 경보발생 없음(발생한 시설 번호의 비트에 on이 된다.)
	int		alarm_DC = int(3);
	int		alarm_RU = int(0);
	int		alarm_BU = int(0);
}S5_info;