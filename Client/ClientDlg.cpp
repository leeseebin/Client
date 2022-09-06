
// ClientDlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "Client.h"
#include "ClientDlg.h"
#include "afxdialogex.h"
#include "CConnectDlg.h"
#include <math.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

// 구현입니다.
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CClientDlg 대화 상자



CClientDlg::CClientDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_CLIENT_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CClientDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_List);
	DDX_Text(pDX, IDC_EDIT_DATA, m_strData);
	DDX_Control(pDX, IDC_BUTTON_SEND, m_ButtonSend);
	DDX_Control(pDX, IDC_BUTTON_CONNECT, m_ButtonConnect);
	DDX_Control(pDX, IDC_TEXT1, m_Text1);
	DDX_Control(pDX, IDC_TEXT2, m_Text2);
	DDX_Control(pDX, IDC_TEXT3, m_Text3);
	DDX_Control(pDX, IDC_TEXT4, m_Text4);
	DDX_Control(pDX, IDC_TEXT5, m_Text5);
}

BEGIN_MESSAGE_MAP(CClientDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_SEND, &CClientDlg::OnBnClickedButtonSend)
	ON_BN_CLICKED(IDC_BUTTON_CONNECT, &CClientDlg::OnBnClickedButtonConnect)
//	ON_WM_KEYDOWN()
ON_WM_TIMER()
//ON_STN_CLICKED(IDC_TEXT3, &CClientDlg::OnStnClickedText3)
END_MESSAGE_MAP()


// CClientDlg 메시지 처리기

BOOL CClientDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.

	// IDM_ABOUTBOX는 시스템 명령 범위에 있어야 합니다.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.
	player1X = 5;
	player2X = 500;
	player1ballX = -30;
	player1ballY = -30;
	power = 0;
	angle = 30;
	turn = 1;
	player1ballY = 150;
	player1HP = 10;
	player2HP = 10;
	PI = 3.1415926535897;

	m_tankImage.Load(L"tank.bmp");
	m_tankImage2.Load(L"tank2.bmp");
	m_cannonBallImage.Load(L"cannonball.bmp");

	CString angleStr;
	angleStr.Format(_T("%f"), angle);
	m_Text1.SetWindowTextW(angleStr);
	CString powerStr;
	powerStr.Format(_T("%f"), power);
	m_Text2.SetWindowTextW(powerStr);
	hpUpdate();

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CClientDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 애플리케이션의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CClientDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.
		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CPaintDC dc(this);


		dc.Rectangle(player1X, ground, player1X + 30, ground + 30);
		dc.Rectangle(player2X, ground, player2X + 30, ground + 30);
		//m_tankImage.Draw(dc, player1X, ground);
		m_tankImage.StretchBlt(dc, player1X, ground, 30, 30, SRCCOPY);
		m_tankImage2.StretchBlt(dc, player2X, ground, 30,30, SRCCOPY);

		double num = NULL;
		if (player1)
			num = getRadian(angle);
		else if (player2)
			num = getRadian(angle);

		drawX = cos(num) * 30;
		drawY = sin(num) * 30;

		if (player1)
		{
			dc.MoveTo(player1X + 30, ground + 7);
			dc.LineTo(player1X + drawX + 30, ground - drawY + 7);
		}
		else if (player2)
		{
			dc.MoveTo(player2X , ground + 7);
			dc.LineTo(player2X - drawX , ground - drawY + 7);
		}
		if (shooting)
		{
			dc.Ellipse(player1ballX, player1ballY, player1ballX + 15, player1ballY + 15);
			m_cannonBallImage.StretchBlt(dc, player1ballX, player1ballY, 15, 15, SRCCOPY);
		}
		//CDialogEx::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CClientDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CClientDlg::OnBnClickedButtonSend()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	UpdateData(TRUE);

	//사용자가 UI에서 입력한 메시지 전송해 해당메시지가 제대로 송신되 서버사 수신하면 에코형식으로 다시 재전송받아 리스트에 출력.
	m_strData.Insert(0, (_T("0001")));
	m_Clinet.Send(m_strData, m_strData.GetLength() * 2);
	/*CString str;
	GetDlgItemText(IDC_EDIT_DATA, str);
	int len = str.GetLength();
	char* szBuffer = LPSTR(LPCTSTR(str));
	m_Clinet.Send(szBuffer, len * 2);*/

	m_strData = _T("");
	UpdateData(FALSE);
}


void CClientDlg::OnBnClickedButtonConnect()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	CConnectDlg dlg;
	if (dlg.DoModal() == IDOK)
	{
		m_Clinet.Create();//클라이언트 소켓생성

		m_Clinet.Connect(dlg.m_strIPAddress, 7000);//서버의 IP주소와 포트번호 설정해 서버에 연결시도

		m_ButtonSend.EnableWindow(TRUE);//보내기 버튼 활성화

		m_ButtonConnect.EnableWindow(FALSE);//서버연결 비활성화

		CString str;
		str.Format(_T("9999"));
		m_Clinet.Send(str, str.GetLength() * 2);
	}
}

void CClientDlg::inval()
{
	Invalidate();
}

double CClientDlg::getRadian(int num)
{
	return num * (PI / 180);
	
}

BOOL CClientDlg::PreTranslateMessage(MSG* pMsg)
{
	int move;
	if (pMsg->message == WM_KEYDOWN)
	{
		if (pMsg->wParam == VK_RIGHT)
		{
			move = 1;
			CString str;
			str.Format(_T("%d"), move);
			str.Insert(0, _T("0002"));

			m_Clinet.Send(str, str.GetLength() * 2);
			return true;
		}
		else if (pMsg->wParam == VK_LEFT)
		{
			move = -1;
			CString str;
			str.Format(_T("%d"), move);
			str.Insert(0, _T("0002"));

			m_Clinet.Send(str, str.GetLength() * 2);
			return true;
		}
		else if (pMsg->wParam == VK_UP && angle<90)
		{
			angle += 5;
			CString angleStr;
			angleStr.Format(_T("%f"), angle);
			m_Text1.SetWindowTextW(angleStr);
			inval();
		}
		else if (pMsg->wParam == VK_DOWN && angle>15)
		{
			angle -= 5;
			CString angleStr;
			angleStr.Format(_T("%f"), angle);
			m_Text1.SetWindowTextW(angleStr);
			inval();

		}
		else if (pMsg->wParam == VK_SPACE && power<30)
		{
			power += 1;
			CString powerStr;
			powerStr.Format(_T("%f"), power);
			m_Text2.SetWindowTextW(powerStr);
		}
	}
	if (pMsg->message == WM_KEYUP)
	{
		if (pMsg->wParam == VK_SPACE)
		{
			SetTimer(2001, 0, NULL);


			/*double num = getRadian(angle);
			ballSpeed = cos(num) * (power + 5) /2;
			jumpSpeed = sin(num) * (power + 5) /2;
			player1ballX = player1X+30;
			player1ballY = ground-1;

			shooting = true;

			SetTimer(1394, 100, NULL);*/

			
			
			CString powerStr;
			powerStr.Format(_T("%d"), power);
			m_Text2.SetWindowTextW(powerStr);
		}
	}

	if (pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_SPACE) //space누를때 꺼지는현상 방지
		return TRUE;
	if (pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_RETURN) //Enter도 방지
		return TRUE;

	return CDialog::PreTranslateMessage(pMsg);
}

void CClientDlg::OnTimer(UINT_PTR nIDEvent)
{
	 //TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	switch (nIDEvent)
	{
	case 1394:
	{
		player1ballX += ballSpeed;
		jumpSpeed -= G;
		player1ballY -= jumpSpeed;
		inval();
		if (player1ballY + 15 > ground + 30)
		{
			KillTimer(1394);
			shooting = false;
		}
		break;
	}
	case 2001:
	{
		CString angleStr;
		double sendAngle = doubleToInt(angle);
		angleStr.Format(_T("%f"), sendAngle);
		angleStr.Insert(0, _T("4001"));
		m_Clinet.Send(angleStr, angleStr.GetLength() * 2);
		KillTimer(2001);
		SetTimer(2002, 0, NULL);
		break;
	}
	case 2002:
	{
		CString powerStr;
		double sendPower = doubleToInt(power);
		powerStr.Format(_T("%f"), sendPower);
		powerStr.Insert(0, _T("4002"));
		m_Clinet.Send(powerStr, powerStr.GetLength() * 2);
		power = 0;
		KillTimer(2002);
		break;
	}
	}
	CDialogEx::OnTimer(nIDEvent);
}

double CClientDlg::doubleToInt(double num)
{
	num = num * 10000;
	return num;
}

double CClientDlg::intToDouble(double num)
{
	num = num / 10000;
	return num;

}

void CClientDlg::angleSend()
{
	CString angleStr;
	double sendAngle = doubleToInt(angle);
	angleStr.Format(_T("%f"), sendAngle);
	angleStr.Insert(0, _T("4001"));
	m_Clinet.Send(angleStr, angleStr.GetLength() * 2);
}

void CClientDlg::powerSend()
{
	CString powerStr;
	double sendPower = doubleToInt(power);
	powerStr.Format(_T("%f"), sendPower);
	powerStr.Insert(0, _T("4002"));
	m_Clinet.Send(powerStr, powerStr.GetLength() * 2);
}

void CClientDlg::turnChange()
{
	if (turn == 1)
	{
		turn = 2;
		CString turnStr;
		turnStr.Format(_T("Player2 Turn"));
		m_Text3.SetWindowTextW(turnStr);
	}
	else if (turn == 2)
	{
		turn = 1;
		CString turnStr;
		turnStr.Format(_T("Player1 Turn"));
		m_Text3.SetWindowTextW(turnStr);
	}
	player1ballX = -30;
	player1ballY = -30;
}

void CClientDlg::hpUpdate()
{
	CString hpStr;
	hpStr.Format(_T("%d"), player1HP);
	m_Text4.SetWindowTextW(hpStr);
	hpStr.Format(_T("%d"), player2HP);
	m_Text5.SetWindowTextW(hpStr);
}
