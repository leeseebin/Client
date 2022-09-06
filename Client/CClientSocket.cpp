#include "pch.h"
#include "CClientSocket.h"

#include "ClientDlg.h"

CClientSocket::CClientSocket(void)
{
}

CClientSocket::~CClientSocket(void)
{
}

void CClientSocket::OnClose(int nErrorCode)
{
	ShutDown();
	Close();
	CSocket::OnClose(nErrorCode);

	AfxMessageBox(_T("������ ������ �Ǿ� ���� �ʽ��ϴ�."));
}

void CClientSocket::OnReceive(int nErrorCode)
{
	CString temp = _T("");

	char szBuffer[1024];
	::ZeroMemory(szBuffer, 1024);
	//wchar_t bb[] = L"0001";
	//char cc[] = "0001";
	////���� Ŭ���̾�Ʈ ������ �̿��Ͽ� �����͸� �޾Ƽ�
	if (Receive(szBuffer, 1024) > 0)
	{
		CClientDlg* pMain = (CClientDlg*)AfxGetMainWnd();

		if (memcmp(szBuffer, L"0001", 8) == 0)//ä��
		{
			char receiveStr[1024];
			memcpy(receiveStr, szBuffer+8, 1016);

			pMain->m_List.AddString(LPCTSTR(receiveStr));
			pMain->m_List.SetCurSel(pMain->m_List.GetCount() - 1);
		}

		else if (memcmp(szBuffer, L"1003", 8) == 0)//�÷��̾�1�� ��ǥ����
		{
			char receiveStr[1024];
			memcpy(receiveStr, szBuffer + 8, 1016);

			int p1x = 0;
			p1x = _ttoi(LPCTSTR(receiveStr));
			pMain->player1X = p1x;
			pMain->inval();
		}
		else if (memcmp(szBuffer, L"2003", 8) == 0)//�÷��̾�2�� ��ǥ����
		{
			char receiveStr[1024];
			memcpy(receiveStr, szBuffer + 8, 1016);

			int p2x = 0;
			p2x = _ttoi(LPCTSTR(receiveStr));
			pMain->player2X = p2x;
			pMain->inval();
		}
		else if (memcmp(szBuffer, L"4011", 8) == 0)//��źx��ǥ�ޱ�
		{
			char receiveStr[1024];
			memcpy(receiveStr, szBuffer + 8, 1016);

			double receiveDouble = _ttoi(LPCTSTR(receiveStr));
			pMain->player1ballX = pMain->intToDouble(receiveDouble);
		}
		else if (memcmp(szBuffer, L"4012", 8) == 0)//��źy��ǥ �ޱ�
		{
			char receiveStr[1024];
			memcpy(receiveStr, szBuffer + 8, 1016);

			double receiveDouble = _ttoi(LPCTSTR(receiveStr));
			pMain->player1ballY = pMain->intToDouble(receiveDouble);
			pMain->inval();
		}
		else if (memcmp(szBuffer, L"4013", 8) == 0)//�߻��ٴ� ��ȣ����
		{
			pMain->shooting = true;
			pMain->inval();
		}
		else if (memcmp(szBuffer, L"4014", 8) == 0)//��ź��󠺴ٴ� ��ȣ����
		{
			pMain->turnChange();
			pMain->shooting = false;
			pMain->inval();
			pMain->hpUpdate();
		}
		else if (memcmp(szBuffer, L"4019", 8) == 0)//�÷��̾�1�� HP����
		{
			char receiveStr[1024];
			memcpy(receiveStr, szBuffer + 8, 1016);
			pMain->player1HP = _ttoi(LPCTSTR(receiveStr));
			pMain->hpUpdate();

			pMain->turnChange();
			pMain->shooting = false;
			pMain->inval();
		}
		else if (memcmp(szBuffer, L"4029", 8) == 0)//�÷��̾�2�� HP����
		{
			char receiveStr[1024];
			memcpy(receiveStr, szBuffer + 8, 1016);
			pMain->player2HP = _ttoi(LPCTSTR(receiveStr));
			pMain->hpUpdate();

			pMain->turnChange();
			pMain->shooting = false;
			pMain->inval();
		}
		else if (memcmp(szBuffer, L"9991", 8) == 0)//�÷��̾�1
		{
			pMain->player1 = true;
			pMain->inval();
		}
		else if (memcmp(szBuffer, L"9992", 8) == 0)//�÷��̾�2
		{
			pMain->player2 = true;
			pMain->inval();
		}
	}

	CSocket::OnReceive(nErrorCode);

}

