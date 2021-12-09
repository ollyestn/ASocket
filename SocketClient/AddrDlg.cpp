// AddrDlg.cpp: 实现文件
//

#include "pch.h"
#include "SocketClient.h"
#include "AddrDlg.h"
#include "afxdialogex.h"


// CAddrDlg 对话框

IMPLEMENT_DYNAMIC(CAddrDlg, CDialogEx)

CAddrDlg::CAddrDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_ADDR, pParent)
	, m_Addr(_T("127.0.0.1"))
	, m_Port(1088)
{

}

CAddrDlg::~CAddrDlg()
{
}

void CAddrDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_ADDR, m_Addr);
	DDX_Text(pDX, IDC_EDIT_PORT, m_Port);
}


BEGIN_MESSAGE_MAP(CAddrDlg, CDialogEx)
END_MESSAGE_MAP()


// CAddrDlg 消息处理程序
