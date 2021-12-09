#include "pch.h"
#include "MyServerSocket.h"



void CMyServerSocket::OnAccept(int nErrorCode)
{
    //�������������󣬵���Accept����
    CNewSocket* pSocket = new CNewSocket();
    if (Accept(*pSocket))
    {
        pSocket->AsyncSelect(FD_READ);
        m_pSocket = pSocket;
    }
    else
        delete pSocket;
}