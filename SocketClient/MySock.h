#pragma once
#include <afxsock.h>
class CMySock :
    public CAsyncSocket
{
public:
    CMySock();
    ~CMySock();

public:
    BOOL m_bConnected;    //�Ƿ�����
    UINT m_nLength;        //��Ϣ����
    char m_szBuffer[4096];    //��Ϣ������
public:

    virtual void OnReceive(int nErrorCode);
    virtual void OnConnect(int nErrorCode);
    virtual void OnSend(int nErrorCode);
};

