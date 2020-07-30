
// ExamFormSwitchingDlg.h: 헤더 파일
//

#pragma once
#include "CMyForm1.h"
#include "CMyForm2.h"
#include "CMyForm3.h"
#include "CMyForm4.h"
#include "CMyForm5.h"
#include "Port.h"

// CExamFormSwitchingDlg 대화 상자
class CExamFormSwitchingDlg : public CDialogEx
{
// 생성입니다.
public:
	CExamFormSwitchingDlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.
	Port* port = NULL;	
	BOOL connected = false;//포트 변수 가져오기

	LRESULT	OnThreadClosed(WPARAM length, LPARAM lpara);
	LRESULT	OnReceive(WPARAM length, LPARAM lpara);
// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ExamFormSwitching_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.

	CMyForm1 *m_pForm1;
	CMyForm2 *m_pForm2;
	CMyForm3 *m_pForm3;
	CMyForm4* m_pForm4;
	CMyForm5* m_pForm5;
	
	//정류기 정보
	S1_info s1;
	S2_info s2;
	S3_info s3;
	S5_info s5;

	// 현재 시간 가져오기
	CTime cTime = CTime::GetCurrentTime();
	CString strDate, strTime, port_name; // 반환되는 날짜와 시간을 저장할 CString 변수 선언

	//나눠져서 들어오는 데이터를 위한 작업(complete flag는 데이터가 완전히 전송되지 않았을 경우 종료 문자를 받을 때까지 받지 않는다)
	int total_length = 0, count = 0;
	BOOL complete = false;
	LPSTR save_data = "";
	CString save_str = _T("");

	void AllocForms();
	void ShowForm(int idx);
	void activate_form1(BOOL flag);
	void activate_form2(BOOL flag);
	void activate_form3(BOOL flag);
	//void activate_form4(BOOL flag);
	void activate_form5(BOOL flag);
	void Rectifier_init();
	unsigned char get_crc(CString data, int flag);
// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnDestroy();
	afx_msg void OnBnClickedRadioForm1();
	afx_msg void OnBnClickedRadioForm2();
	afx_msg void OnBnClickedRadioForm3();
	afx_msg void OnBnClickedRadioForm4();
	afx_msg void OnBnClickedRadioForm5();
	CComboBox baud_rate;
	CComboBox comport_list;
	afx_msg void OnCbnSelchangeCombo3();
	afx_msg void OnBnClickedButton1();
	CButton connect_button;
	afx_msg void OnBnClickedButton2();
	CButton data_set;
};

#define CRC_CHECK  0
#define CRC_INSERT 1
