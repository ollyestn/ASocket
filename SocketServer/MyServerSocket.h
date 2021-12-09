#pragma once
#include <afxsock.h>

#include "NewSocket.h"

class CMyServerSocket :
    public CAsyncSocket
{

public:
    CNewSocket* m_pSocket;

public:
    virtual void OnAccept(int nErrorCode);


};

