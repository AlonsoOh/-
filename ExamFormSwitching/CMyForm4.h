#pragma once
#include "Port.h"
// CMyForm4 폼 보기

class CMyForm4 : public CFormView
{
	DECLARE_DYNCREATE(CMyForm4)

public:
	CMyForm4();           // 동적 만들기에 사용되는 protected 생성자입니다.
	CMyForm4(UINT nIDTemplate);
	virtual ~CMyForm4();

#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_FORM_FORM4 };
#endif
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.
	unsigned char get_crc(CString data);
	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext = NULL);
	virtual void OnInitialUpdate();
	Port* test_port;
	/*void CMyForm4::FR_activate(BOOL set);
	void CMyForm4::AR_activate(BOOL set);

	CComboBox record_type;
	CComboBox data_num;
	CComboBox alarm_state;
	afx_msg void OnBnClickedButton2();
	CEdit FR_temp;
	CEdit FR_output_volt;
	CEdit FR_load_curr;
	CEdit FR_batt_curr;
	CEdit FR_rv;
	CEdit FR_sv;
	CEdit FR_tv;
	CEdit FR_rc;
	CEdit FR_sc;
	CEdit FR_tc;
	CEdit facility_no;
	CEdit monitor_point;
	CEdit alarm_data;
	CEdit set_data;
	CEdit alarm_date;
	CEdit alarm_time;*/
	CEdit send_box;
	CEdit record_box;
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton4();
	afx_msg void OnBnClickedButton5();
	afx_msg void OnBnClickedButton6();
	afx_msg void OnBnClickedButton7();
	afx_msg void OnBnClickedButton8();
	afx_msg void OnBnClickedButton9();
	afx_msg void OnBnClickedButton10();
	afx_msg void OnBnClickedButton11();
	afx_msg void OnBnClickedButton12();
	afx_msg void OnBnClickedButton13();
	afx_msg void OnBnClickedButton14();
	afx_msg void OnEnChangeEdit2();
};


