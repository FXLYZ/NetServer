
// NetServerDlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "NetServer.h"
#include "NetServerDlg.h"
#include "afxdialogex.h"
#include<ctime>

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
public:
	afx_msg void OnBnClickedButton1();
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


// CNetServerDlg 对话框



CNetServerDlg::CNetServerDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_NETSERVER_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CNetServerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT2, Content);
	DDX_Control(pDX, IDC_BUTTON1, StartButton);
	DDX_Control(pDX, IDC_BUTTON3, EndButton);
	DDX_Control(pDX, IDC_BUTTON4, ClearButton);
}

BEGIN_MESSAGE_MAP(CNetServerDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_EN_CHANGE(IDC_EDIT2, &CNetServerDlg::OnEnChangeEdit2)
	ON_BN_CLICKED(IDC_BUTTON1, &CNetServerDlg::OnBnClickedButton1)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BUTTON3, &CNetServerDlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &CNetServerDlg::OnBnClickedButton4)
END_MESSAGE_MAP()


// CNetServerDlg 消息处理程序

BOOL CNetServerDlg::OnInitDialog()
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
	StartButton.EnableWindow(1);
	EndButton.EnableWindow(0);
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CNetServerDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CNetServerDlg::OnPaint()
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
HCURSOR CNetServerDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CNetServerDlg::OnEnChangeEdit2()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}


void CAboutDlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
}


void CNetServerDlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	BOOL bflag = mysocket.Create(2001, SOCK_DGRAM, FD_READ | FD_WRITE);
	if (!bflag)
	{
		Content.SetWindowTextW(L"socket创建失败");
	}
	else
	{
		StartButton.EnableWindow(0);
		EndButton.EnableWindow(1);
		line = 0;
		SetTimer(1, 1000, NULL);
	}
}


void CNetServerDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
		//接受地址和端口
	CString sIP(L"127.0.0.1");
	UINT uport = 2000;
	char* buf = new char[100];
	int isR = mysocket.ReceiveFrom(buf, 100, sIP, uport, 0);
	CString sResult(buf), temp;
	Content.GetWindowTextW(temp);
	CString sline;
	if (isR == -1)
	{
		//temp = temp + sline + L":没有收到数据\r\n";
	}
	else
	{
		/*SYSTEMTIME st;
		GetLocalTime(&st);*/
		line++;
		sline.Format(_T("%d"), line);
		CTime time = CTime::GetCurrentTime();
		CString strDate, strTime,Responese;
		strDate.Format(L"%d-%d-%d", time.GetYear(), time.GetMonth(), time.GetDay());
		strTime.Format(L"%d:%d:%d", time.GetHour(), time.GetMinute(), time.GetSecond());
		if (!sResult.Compare(L"TIME"))
		{
			Responese = strTime;
			mysocket.SendTo(strTime, 100, uport, sIP, 0);
		}
		else if (!sResult.Compare(L"DATE"))
		{
			Responese = strDate;
			mysocket.SendTo(strDate, 100, uport, sIP, 0);
		}
		else
		{
			Responese = L"WRONG";
			mysocket.SendTo(Responese, 100, uport, sIP, 0);
		}
		temp.Format(temp + sline + L":  IP=%s  PORT=%d   Receive=%s  Response=%s\r\n", sIP, uport, sResult,Responese);
	}
	Content.SetWindowTextW(temp);
	delete[]buf;
	CDialogEx::OnTimer(nIDEvent);
}


void CNetServerDlg::OnBnClickedButton3()
{
	// TODO: 在此添加控件通知处理程序代码
	StartButton.EnableWindow(1);
	EndButton.EnableWindow(0);
	KillTimer(1);
	mysocket.Close();
}


void CNetServerDlg::OnBnClickedButton4()
{
	// TODO: 在此添加控件通知处理程序代码
	Content.SetWindowTextW(L"");
}
