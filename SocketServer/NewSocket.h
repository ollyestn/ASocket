#pragma once
#include <afxsock.h>
class CNewSocket :
    public CAsyncSocket
{
public:
    UINT m_nLength;        //��Ϣ����
    char m_szBuffer[4096];    //��Ϣ������

public:
    virtual void OnReceive(int nErrorCOde);
    virtual void OnSend(int nErrorCOde);
    virtual void OnClose(int nErrorCode);
};

