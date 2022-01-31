#pragma once
#include <afxsock.h>

#include "NewSocket.h"

class CMyServerSocket :
    public CAsyncSocket
{

public:
    //CNewSocket* m_pSocket;
    CPtrList m_pSocketList;

public:
    virtual void OnAccept(int nErrorCode);


};

