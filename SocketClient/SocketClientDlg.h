
// SocketClientDlg.h: 头文件
//

#pragma once

#include "MySock.h"

// CSocketClientDlg 对话框
class CSocketClientDlg : public CDialogEx
{
// 构造
public:
	CSocketClientDlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SOCKETCLIENT_DIALOG };
#endif

protected:
	int TryCount;
	CMySock m_clientSocket;
	UINT m_szPort;
public:
	char m_szServerAdr[256];

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CEdit m_MSG;
	CListBox m_MSGS;
	afx_msg void OnBnClickedButConnect();
	afx_msg void OnBnClickedButSend();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnBnClickedButExit();
};
