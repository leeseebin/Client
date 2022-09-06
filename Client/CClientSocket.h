#pragma once
#include <afxsock.h>
class CClientSocket :
	public CSocket
{
public:
	CClientSocket(void);
	~CClientSocket(void);
	virtual void OnClose(int nErrorCode);
	virtual void OnReceive(int nErrorCode);
};

