#include "pch.h"
#include "MySock.h"
#include "SocketClient.h"
#include "SocketClientDlg.h"

CMySock::CMySock()
{
    m_nLength = 0;
    memset(m_szBuffer, 0, sizeof(m_szBuffer));
    m_bConnected = FALSE;
}

CMySock::~CMySock()
{
    //关闭套接字
    if (m_hSocket != INVALID_SOCKET)
        Close();
}

void CMySock::OnReceive(int nErrorCode)
{
    m_nLength = Receive(m_szBuffer, sizeof(m_szBuffer), 0);

    //下面两行代码用来获取对话框指针
    CSocketClientApp* pApp = (CSocketClientApp*)AfxGetApp();
    CSocketClientDlg* pDlg = (CSocketClientDlg*)pApp->m_pMainWnd;

    pDlg->m_MSGS.InsertString(0, m_szBuffer);
    memset(m_szBuffer, 0, sizeof(m_szBuffer));
    CAsyncSocket::OnReceive(nErrorCode);
}

void CMySock::OnSend(int nErrorCode)
{
    Send(m_szBuffer, m_nLength, 0);
    m_nLength = 0;
    memset(m_szBuffer, 0, sizeof(m_szBuffer));

    //继续提请一个“读”的网络事件，接收Server消息
    AsyncSelect(FD_READ);

    CAsyncSocket::OnSend(nErrorCode);
}

void CMySock::OnConnect(int nErrorCode)
{
    if (nErrorCode == 0)
    {
        m_bConnected = TRUE;
        CSocketClientApp* pApp = (CSocketClientApp*)AfxGetApp();
        CSocketClientDlg* pDlg = (CSocketClientDlg*)pApp->m_pMainWnd;
        memcpy(m_szBuffer, "Connected to ", 13);
        strncat_s(m_szBuffer, sizeof(char) * 4096, pDlg->m_szServerAdr, sizeof(pDlg->m_szServerAdr));
        pDlg->m_MSGS.InsertString(0, m_szBuffer);

        AsyncSelect(FD_READ);    //提请一个“读”的网络事件，准备接收
    }

    CAsyncSocket::OnConnect(nErrorCode);
}