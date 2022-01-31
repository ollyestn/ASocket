#include "pch.h"
#include "MyServerSocket.h"



void CMyServerSocket::OnAccept(int nErrorCode)
{
    //侦听到连接请求，调用Accept函数
    CNewSocket* pSocket = new CNewSocket();
    if (Accept(*pSocket))
    {
        pSocket->AsyncSelect(FD_READ);
        m_pSocketList.AddTail(pSocket);
    }
    else
        delete pSocket;
}