
// ClientDlg.h: 헤더 파일
//

#pragma once
#include "CClientSocket.h"
#include "resource.h"

// CClientDlg 대화 상자
class CClientDlg : public CDialogEx
{
// 생성입니다.
public:
	CClientDlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.


public:
	CClientSocket m_Clinet;

// 대화 상자 데이터입니다.
//#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CLIENT_DIALOG };
//#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
private:
	CImage m_tankImage;
	CImage m_tankImage2;
	CImage m_cannonBallImage;

public:
	CListBox m_List;
	CEdit m_Edit;
	CString m_strData;
	CButton m_ButtonSend;
	CButton m_ButtonConnect;


	double player1X, player2X;
	double player1ballX, player1ballY, player2ballX, player2ballY, angle, power;
	double drawX, drawY;
	bool player1, player2, shooting;
	float PI;
	int turn, player1HP, player2HP;
	double ballSpeed, jumpSpeed;
	const float G = 1.0f;
	const float ground = 150.0f;
	CString name;
	
	void inval();
	void turnChange();
	void hpUpdate();
	double getRadian(int num);
	afx_msg void OnBnClickedButtonSend();
	afx_msg void OnBnClickedButtonConnect();
	BOOL CClientDlg::PreTranslateMessage(MSG* pMsg);
	CStatic m_Text1;
	CStatic m_Text2;
	CStatic m_Text3;
	afx_msg void OnTimer(UINT_PTR nIDEvent);

	double doubleToInt(double num);
	double intToDouble(double num);
	void angleSend();
	void powerSend();
	CStatic m_Text4;
	CStatic m_Text5;
};