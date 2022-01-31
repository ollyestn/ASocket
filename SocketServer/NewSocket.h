#pragma once
#include <afxsock.h>
class CNewSocket :
    public CAsyncSocket
{
public:
    UINT m_nLength;        //消息长度
    char m_szBuffer[4096];    //消息缓冲区

public:
    virtual void OnReceive(int nErrorCOde);
    virtual void OnSend(int nErrorCOde);
    virtual void OnClose(int nErrorCode);
};

