#pragma once
#define	PLUG		0
#define UNPLUG		1
#define _FAILED		2
#define NOTSET		3
#define AUTO_FL		0
#define AUTO_EQ		1
#define PASS_FL		2
#define PASS_EQ		3


// CMyForm3 대화 상자

class CMyForm3 : public CFormView
{
	DECLARE_DYNAMIC(CMyForm3)

public:
	CMyForm3();
	CMyForm3(UINT nIDTemplate);
	virtual ~CMyForm3();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_FORM_FORM3 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext = NULL);
	virtual void OnInitialUpdate();
	void CMyForm3::DT_activate(int set);
	void CMyForm3::RUst_activate(int set);
	void CMyForm3::RUout_activate(int set);
	void CMyForm3::CM_activate(int set);
	void CMyForm3::AC_activate(int set);
	void CMyForm3::FI_activate(int set);
	CComboBox select_box;				//활성화할 파트 고르는 combo box
	CComboBox charge_mode;				//충전모드 
	CComboBox *module_set[31];
	CEdit section3_date;				//날짜 박스
	CEdit section3_time;				//시간 박스
	afx_msg void OnBnClickedButton2();
	CEdit RU_volt;						//정류모듈 출력전압
	CEdit RU_curr;						//정류모듈 출력전류
	CEdit ec_volt;						//균등충전 전압	
	CEdit fc_volt;						//부동충전 전압
	CEdit ec_point;						//균등충전 조건전류점
	CEdit ec_curr;						//균등충전 종지전류
	CEdit endtime;						//종지시간
	CEdit ec_interval;					//균등충전주기
	CEdit fixed_interval;				//정시저장주기
	CEdit num_cases;					//경보 저장 건 수
	CComboBox mod1;						//모듈 실장 유무 표시 box
	CComboBox mod2;
	CComboBox mod3;
	CComboBox mod4;
	CComboBox mod5;
	CComboBox mod6;
	CComboBox mod7;
	CComboBox mod8;
	CComboBox mod9;
	CComboBox mod10;
	CComboBox mod11;
	CComboBox mod12;
	CComboBox mod13;
	CComboBox mod14;
	CComboBox mod15;
	CComboBox mod16;
	CComboBox mod17;
	CComboBox mod18;
	CComboBox mod19;
	CComboBox mod20;
	CComboBox mod21;
	CComboBox mod22;
	CComboBox mod23;
	CComboBox mod24;
	CComboBox mod25;
	CComboBox mod26;
	CComboBox mod27;
	CComboBox mod28;
	CComboBox mod29;
	CComboBox mod30;
	//CComboBox select_module;				//모듈 선택 박스
	afx_msg void OnCbnSelchangeCombo42();
	afx_msg void OnCbnSelchangeCombo47();
};

typedef struct time_info {					//시간 정보 구조체
	int		year;							//연, 월, 일, 시, 분, 초
	int		month;
	int		date;
	int		hour;
	int		minute;
	int		second;
}time_info;

typedef struct S3_info {
	time_info	sys_time;					//시스템 시간
	int			module_info[31];			//모듈 실장 유무 정보
	float		OR_volt;					//출력 전압, 전류
	int			OR_curr;
	int			CM_mode;					//충전모드
	float		EQ_volt;					//균등충전 전압
	float		FL_volt;					//부동충전 전압
	int			AC_point;					//균등충전 조건전류점
	int			AC_final_curr;				//균등충전 종지전류
	int			AC_final_time;				//종지시간
	int			AC_interval;				//균등충전주기
	int			PT_interval;				//정시저장 주기
	int			PT_num;						//경보 저장 건 수
}S3_info;
