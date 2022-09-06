#pragma once


// CConnectDlg 대화 상자

class CConnectDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CConnectDlg)

public:
	CConnectDlg(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CConnectDlg();

public:
	CString m_strIPAddress; // IP컨트롤에 입력받은 서버IP주소 저장하는 변수

// 대화 상자 데이터입니다.
//#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG1 };
//#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	BOOL OnInitDialog();
//	afx_msg void OnBnClickedButton1();
};
