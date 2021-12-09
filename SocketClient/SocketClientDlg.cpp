
// SocketClientDlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "SocketClient.h"
#include "SocketClientDlg.h"
#include "afxdialogex.h"
#include "AddrDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CSocketClientDlg 对话框



CSocketClientDlg::CSocketClientDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_SOCKETCLIENT_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CSocketClientDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_MSG, m_MSG);
	DDX_Control(pDX, IDC_LIST_MSGS, m_MSGS);
}

BEGIN_MESSAGE_MAP(CSocketClientDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUT_CONNECT, &CSocketClientDlg::OnBnClickedButConnect)
	ON_BN_CLICKED(IDC_BUT_SEND, &CSocketClientDlg::OnBnClickedButSend)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BUT_EXIT, &CSocketClientDlg::OnBnClickedButExit)
END_MESSAGE_MAP()


// CSocketClientDlg 消息处理程序

BOOL CSocketClientDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CSocketClientDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CSocketClientDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CSocketClientDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CSocketClientDlg::OnBnClickedButConnect()
{
	// TODO: 在此添加控件通知处理程序代码
	m_clientSocket.ShutDown(2);
	m_clientSocket.m_hSocket = INVALID_SOCKET;
	m_clientSocket.m_bConnected = FALSE;
	CAddrDlg m_Dlg;
	//默认端口1088
	m_Dlg.m_Port = 1088;
	if (m_Dlg.DoModal() == IDOK && !m_Dlg.m_Addr.IsEmpty())
	{
		
			memcpy(m_szServerAdr, m_Dlg.m_Addr, sizeof(m_szServerAdr));
		m_szPort = m_Dlg.m_Port;
		//建立计时器，每1秒尝试连接一次，直到连上或TryCount>10
		SetTimer(1, 1000, NULL);
		TryCount = 0;
	}
}


void CSocketClientDlg::OnBnClickedButSend()
{
	// TODO: 在此添加控件通知处理程序代码
	if (m_clientSocket.m_bConnected)
	{
		m_clientSocket.m_nLength = m_MSG.GetWindowText(m_clientSocket.m_szBuffer, sizeof(m_clientSocket.m_szBuffer));
		m_clientSocket.AsyncSelect(FD_WRITE);
		m_MSG.SetWindowText("");
	}
}


void CSocketClientDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if (m_clientSocket.m_hSocket == INVALID_SOCKET)
	{
		BOOL bFlag = m_clientSocket.Create(0, SOCK_STREAM, FD_CONNECT);
		if (!bFlag)
		{

			AfxMessageBox("Socket Error!");
			m_clientSocket.Close();
			PostQuitMessage(0);
			return;
		}
	}

	m_clientSocket.Connect(m_szServerAdr, m_szPort);

	TryCount++;
	if (TryCount >= 10 || m_clientSocket.m_bConnected)
	{
		KillTimer(1);
		if (TryCount >= 10)
			AfxMessageBox("Connect Failed!");

		return;
	}

	//CDialog::OnTimer(nIDEvent);
	CDialogEx::OnTimer(nIDEvent);
}


void CSocketClientDlg::OnBnClickedButExit()
{
	// TODO: 在此添加控件通知处理程序代码
	//关闭Socket
	m_clientSocket.ShutDown(2);
	//关闭对话框
	EndDialog(0);
}
