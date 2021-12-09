#pragma once
#include <afxsock.h>
class CMySock :
    public CAsyncSocket
{
public:
    CMySock();
    ~CMySock();

public:
    BOOL m_bConnected;    //是否连接
    UINT m_nLength;        //消息长度
    char m_szBuffer[4096];    //消息缓冲区
public:

    virtual void OnReceive(int nErrorCode);
    virtual void OnConnect(int nErrorCode);
    virtual void OnSend(int nErrorCode);
};

