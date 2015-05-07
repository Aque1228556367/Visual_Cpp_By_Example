// UDPSeverDlg.cpp : implementation file
//

#include "stdafx.h"
#include "UDPSever.h"
#include "UDPSeverDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
CUDPSeverDlg::CUDPSeverDlg(CWnd* pParent /*=NULL*/)

/////////////////////////////////////////////////////////////////////////////
// CUDPSeverDlg dialog


	: CDialog(CUDPSeverDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CUDPSeverDlg)
	m_ServerIP = _T("127.0.0.1");
	m_ServerPort = 5800;
	m_ClientIP = _T("127.0.0.1");
	m_ClientPort = 5801;
	m_sendcount = 0;
	m_strSend = _T("");
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CUDPSeverDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CUDPSeverDlg)
	DDX_Text(pDX, IDC_EDIT1, m_ServerIP);
	DDX_Text(pDX, IDC_EDIT2, m_ServerPort);
	DDX_Text(pDX, IDC_EDIT3, m_ClientIP);
	DDX_Text(pDX, IDC_EDIT4, m_ClientPort);
	DDX_Text(pDX, IDC_EDIT5, m_sendcount);
	DDX_Text(pDX, IDC_EDIT6, m_strSend);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CUDPSeverDlg, CDialog)
	//{{AFX_MSG_MAP(CUDPSeverDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_SEND, OnSend)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_STOP, OnStop)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CUDPSeverDlg message handlers

BOOL CUDPSeverDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CUDPSeverDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CUDPSeverDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CUDPSeverDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CUDPSeverDlg::OnSend() 
{
	// TODO: Add your control notification handler code here
	UpdateData();
	if(m_sockSend.Create(m_ServerPort,SOCK_DGRAM,NULL))//�����׽���
	{	
		m_sockSend.Bind(m_ServerPort,m_ServerIP);	//�󶨱����׽ӿ�
		SetTimer(1,3000,NULL);//����һ����ʱ����ʱ����
		GetDlgItem(IDC_SEND)->EnableWindow(false);//���Ͱ�ť��Ч
		GetDlgItem(IDC_STOP)->EnableWindow(true);//ֹͣ��ť��Ч	
	}
	else
	{
		AfxMessageBox("Socket����ʧ�ܣ�");
	}	
}

void CUDPSeverDlg::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	static iIndex=0;//��̬���������ڼ���
	char szSend[20];
	sprintf(szSend,"%010d",iIndex++);//���͵��������뻺����
	int iSend= m_sockSend.SendTo(szSend,10,m_ClientPort,m_ClientIP,0);//����UDP����
	m_strSend=szSend;
	m_sendcount+=iSend;//��¼�������ݵ��ֽ���
	UpdateData(false);
	CDialog::OnTimer(nIDEvent);
}

void CUDPSeverDlg::OnStop() 
{
	// TODO: Add your control notification handler code here
	KillTimer(1);//�����ʱ��
	m_sockSend.Close();//�ر��׽���
	GetDlgItem(IDC_SEND)->EnableWindow(true);//���Ͱ�ť��Ч
	GetDlgItem(IDC_STOP)->EnableWindow(false);//ֹͣ��ť��Ч
}
