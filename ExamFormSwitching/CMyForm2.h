#pragma once


#define UPPER 0
#define LOWER 1
// CMyForm2 대화 상자

class CMyForm2 : public CFormView
{
	DECLARE_DYNAMIC(CMyForm2)

public:
	CMyForm2();
	CMyForm2(UINT nIDTemplate);
	virtual ~CMyForm2();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_FORM_FORM2 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext = NULL);
	virtual void OnInitialUpdate();
	void CMyForm2::AC_activate(int set);
	void CMyForm2::DC_activate(int set);
	void CMyForm2::BAT_activate(int set);
	void CMyForm2::RU_activate(int set);

	CComboBox select_measure;		//변경할 파트 선택상자
	CEdit AC_state;					//교류 상
	CEdit AC_input_vmax;			//교류 입력전압 상한치
	CEdit AC_input_vmin;			//교류 입력전압 하한치
	CEdit AC_input_cmax;			//교류 입력전류 상한치
	CEdit AC_input_cmin;			//교류 입력전류 하한치
	CEdit batt_vmax;				//축전지 셀 전압 상한치
	CEdit batt_vmin;				//축전지 셀 전압 하한치
	CEdit batt_tvmax;				//축전지 셀 총전압 상한치
	CEdit batt_tvmin;				//축전지 셀 총전압 하한치
//	CEdit DC_ouput_vmax;			
//	CEdit DC_total_vmin;
//	CEdit DC_ouput_cmax;
//	CEdit RU_ouput_vmax;
	CEdit RU_output_vmin;			//정류유니트 모듈 출력전압 상한치
//	CEdit DC_ouput_vmin;
	CEdit DC_output_vmax;			//직류 출력전압 출력전압 상한치
	CEdit DC_output_vmin;			//직류 출력전압 출력전압 하한치
	CEdit DC_output_cmax;			//직류 출력전압 출력전류 상한치
	CEdit RU_output_vamx;			//정류유니트 모듈 출력전압 하한치
	afx_msg void OnBnClickedButton2();
};

typedef struct S2_info {
	int		state;					//상
	int		AD_curr[2];				//교류 입력전압 상하한치
	int		AD_volt[2];				//교류 입력전류 상하한치
	float	DC_volt[2];				//직류 출력전압 상하한치
	float	RU_volt[2];				//정류 모듈 출력전압 상하한치
	float	BC_cell_volt[2];		//축전지 셀전압 상하한치
	float	BC_total_volt[2];		//축전지 셀 총전압 상하한치
	int		DC_curr;				//직류 출력전류 상한치
}S2_info;
