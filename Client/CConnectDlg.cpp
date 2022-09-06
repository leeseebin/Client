// CConnectDlg.cpp: 구현 파일
//

#include "pch.h"
#include "Client.h"
#include "CConnectDlg.h"
#include "afxdialogex.h"


// CConnectDlg 대화 상자

IMPLEMENT_DYNAMIC(CConnectDlg, CDialogEx)

CConnectDlg::CConnectDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG1, pParent)
{

}

CConnectDlg::~CConnectDlg()
{
}

void CConnectDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CConnectDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &CConnectDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CConnectDlg 메시지 처리기

void CConnectDlg::OnBnClickedOk()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	GetDlgItemText(IDC_IPADDRESS1, m_strIPAddress);

	CDialogEx::OnOK();
}

BOOL CConnectDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	SetDlgItemText(IDC_IPADDRESS1, _T("127.0.0.1"));//루프백으로 초기화

	return TRUE;
}


//void CConnectDlg::OnBnClickedButton1()
//{
//	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
//}
