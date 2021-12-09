#include "pch.h"
#include "NewSocket.h"


void CNewSocket::OnReceive(int nErrorCOde)
{ 
	m_nLength = Receive(m_szBuffer,sizeof(m_szBuffer),0);
// 直接转发消息
	AsyncSelect(FD_WRITE);
}

void CNewSocket::OnSend(int nErrorCode)
{ 
	Send(m_szBuffer,m_nLength,0);
}
