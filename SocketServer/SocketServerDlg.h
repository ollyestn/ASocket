
// SocketServerDlg.h: 头文件
//

#pragma once

#include "MyServerSocket.h"

// CSocketServerDlg 对话框
class CSocketServerDlg : public CDialogEx
{
// 构造
public:
	CSocketServerDlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SOCKETSERVER_DIALOG };
#endif

public:
		CMyServerSocket    m_srvrSocket;
		//int UserPort;

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
	afx_msg void OnBnClickedBtnListen();	
	DECLARE_MESSAGE_MAP()
public:
	int UserPort;
};
