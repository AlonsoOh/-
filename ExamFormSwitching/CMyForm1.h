#pragma once


// CMyForm1 대화 상자
#define MODULE_MAX 30	//모듈 최대 개수
#define R_PHASE 0		//R상 상태
#define S_PHASE 1		//S상 상태
#define T_PHASE 2		//T상 상태
#define VOLTAGE	0
#define CURRENT 1
#define NM 0			//정상
#define NC 1			//탈장
#define CF 2			//통신
#define MD 3			//모드
#define CL 4			//전류 limit
#define UV 5			//저전압
#define OV 6			//고전압
#define TH 7			//온도
#define AF 8			//입력

class CMyForm1 : public CFormView
{
	DECLARE_DYNAMIC(CMyForm1)

public:
	CMyForm1();
	CMyForm1(UINT nIDTemplate);
	virtual ~CMyForm1();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_FORM_FORM1 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext = NULL);
	virtual void OnInitialUpdate();
	//CComboBox section1_facility;
	afx_msg void OnCbnSelchangeCombo1();
	afx_msg void OnCbnSelchangeCombo4();
	void CMyForm1::AC_activate(BOOL set);
	void CMyForm1::DC_activate(BOOL set);
	void CMyForm1::MOD_activate(BOOL set, int mod);
	CComboBox *mod_state[MODULE_MAX + 1];				//정류 유니트 모듈 상태
	CEdit *volt_mod[MODULE_MAX + 1];					//정류 유니트 모듈 전압
	CEdit *curr_mod[MODULE_MAX + 1];					//정류 유니트 모듈 전류
	CComboBox mod1_state;
	CComboBox mod2_state;
	CComboBox mod3_state;
	CComboBox mod4_state;
	CComboBox mod5_state;
	CComboBox mod6_state;
	CComboBox mod7_state;
	CComboBox mod8_state;
	CComboBox mod9_state;
	CComboBox mod10_state;
	CComboBox mod11_state;
	CComboBox mod12_state;
	CComboBox mod13_state;
	CComboBox mod14_state;
	CComboBox mod15_state;
	CComboBox mod16_state;
	CComboBox mod17_state;
	CComboBox mod18_state;
	CComboBox mod19_state;
	CComboBox mod20_state;
	CComboBox mod21_state;
	CComboBox mod22_state;
	CComboBox mod23_state;
	CComboBox mod24_state;
	CComboBox mod25_state;
	CComboBox mod26_state;
	CComboBox mod27_state;
	CComboBox mod28_state;
	CComboBox mod29_state;
	CComboBox mod30_state;
	afx_msg void OnCbnSelchangeCombo3();
	CComboBox operate_mode;					//운전모드
	CComboBox charge_mode;					//충전모드
	CComboBox monitor_state;				//감시장치간 통신
	CEdit facility_no;						//시설번호
	CEdit section1_date;					//일자
	CEdit section1_time;					//시간
	CEdit AC_state;							//교류 상
	CEdit AC_temp;							//교류부 주위 온도
	CEdit AC_ouput_volt;					//교류 출력 전압
	CEdit AC_load_curr;						//교류 부하 전류
	CEdit AC_batt_curr;						//교류 축전지 전류
	CEdit AC_rv;							//R상 전압
	CEdit AC_sv;							//S상 전압
	CEdit AC_tv;							//T상 전압
	CEdit AC_rc;							//R상 전류
	CEdit AC_sc;							//S상 전류
	CEdit AC_tc;							//T상 전류
	afx_msg void OnCbnSelchangeCombo34();
	CEdit extend_com;						//확장랙간 통신
	CButton load_fuse_error;				//부하 fuse 이상
	CButton batt_fuse_error;				//축전지 fuse 이상
	CEdit volt_mod1;						
	CEdit volt_mod2;						
	CEdit volt_mod3;
	CEdit volt_mod4;
	CEdit volt_mod5;
	CEdit volt_mod6;
	CEdit volt_mod7;
	CEdit volt_mod8;
	CEdit volt_mod9;
	CEdit volt_mod10;
	CEdit volt_mod11;
	CEdit volt_mod12;
	CEdit volt_mod13;
	CEdit volt_mod14;
	CEdit volt_mod15;
	CEdit volt_mod16;
	CEdit volt_mod17;
	CEdit volt_mod18;
	CEdit volt_mod19;
	CEdit volt_mod20;
	CEdit volt_mod21;
	CEdit volt_mod22;
	CEdit volt_mod23;
	CEdit volt_mod24;
	CEdit volt_mod25;
	CEdit volt_mod26;
	CEdit volt_mod27;
	CEdit volt_mod28;
	CEdit volt_mod29;
	CEdit volt_mod30;
	CEdit curr_mod1;
	CEdit curr_mod2;
	CEdit curr_mod3;
	CEdit curr_mod4;
	CEdit curr_mod5;
	CEdit curr_mod6;
	CEdit curr_mod7;
	CEdit curr_mod8;
	CEdit curr_mod9;
	CEdit curr_mod10;
	CEdit curr_mod11;
	CEdit curr_mod12;
	CEdit curr_mod13;
	CEdit curr_mod14;
	CEdit curr_mod15;
	CEdit curr_mod16;
	CEdit curr_mod17;
	CEdit curr_mod18;
	CEdit curr_mod19;
	CEdit curr_mod20;
	CEdit curr_mod21;
	CEdit curr_mod22;
	CEdit curr_mod23;
	CEdit curr_mod24;
	CEdit curr_mod25;
	CEdit curr_mod26;
	CEdit curr_mod27;
	CEdit curr_mod28;
	CEdit curr_mod29;
	CEdit curr_mod30;
	//CComboBox alarm_target;
	//afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedRadio7();
	afx_msg void OnCbnSelchangeCombo15();
	afx_msg void OnCbnSelchangeCombo17();
	CButton AD_alarm;							//교류배전부 경보대상 체크박스
	CButton DC_alarm;							//직류제어부 경보대상 체크박스
	CButton RU_alarm;							//정류유니트부 경보대상 체크박스
	CButton BU_alarm;							//축전지부 경보대상 체크박스
	afx_msg void OnBnClickedCheck11();
	afx_msg void OnBnClickedCheck2();
	CComboBox OV_box;
	CComboBox LC_box;
	CComboBox RV_box;
	CComboBox SV_box;
	CComboBox TV_box;
	CComboBox RC_box;
	CComboBox SC_box;
	CComboBox TC_box;
};

typedef struct S1_module {						//모듈 정보 구조체
	float voltage;								//모듈 전압
	int current;								//모듈 전류
	unsigned char state;						//모듈 상태
}S1_module;

typedef struct S1_info {
	S1_module mod[MODULE_MAX + 1];
	int		facility_no;				//시설번호
	int		sur_temp;					//주위 온도
	float	output_volt;				//출력전압
	int		load_cur;					//부하 전류
	int		batt_cur;					//축전지 전류
	int		ADphase_info[3][2];			//RST 전압 전류		
	int		module_quantity;			//모듈 수
	char	phase;						//상
	char	AD_phase[3];				//RST 상태, 출력전압, 부하전류
	char	alarm_target;				//경보대상
	char	operate_mode;				//운전모드
	char	charge_mode;				//충전모도
	char	extend_comm;				//확장랙간 통신
	char	monitor_comm;				//감시장치간 통신
	char	DC_state[2];				//0: 부하 fuse, 1 : 축전지 fuse
}S1_info;