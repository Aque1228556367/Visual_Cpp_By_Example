// TCPClientDlg.cpp : implementation file
//

#include "stdafx.h"
#include "TCPClient.h"
#include "TCPClientDlg.h"

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

/////////////////////////////////////////////////////////////////////////////
// CTCPClientDlg dialog

CTCPClientDlg::CTCPClientDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CTCPClientDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CTCPClientDlg)
	m_ServerIP = _T("127.0.0.1");
	m_ServerPort = 4800;
	m_ReceiveData = _T("");
	m_receivecount = 0;
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CTCPClientDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTCPClientDlg)
	DDX_Text(pDX, IDC_EDIT1, m_ServerIP);
	DDX_Text(pDX, IDC_EDIT2, m_ServerPort);
	DDX_Text(pDX, IDC_EDIT3, m_ReceiveData);
	DDX_Text(pDX, IDC_EDIT4, m_receivecount);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CTCPClientDlg, CDialog)
	//{{AFX_MSG_MAP(CTCPClientDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_RECEIVE, OnReceive)
	ON_BN_CLICKED(IDC_STOP, OnStop)
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTCPClientDlg message handlers

BOOL CTCPClientDlg::OnInitDialog()
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

void CTCPClientDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CTCPClientDlg::OnPaint() 
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
HCURSOR CTCPClientDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CTCPClientDlg::OnReceive() 
{
	// TODO: Add your control notification handler code here
	UpdateData();
	if(m_sockReceive.Create())		//�����׽���
	{
		//������������
		m_sockReceive.Connect(m_ServerIP,m_ServerPort);//���ӷ��������ɹ��󷵻�
		SetTimer(1,1000,NULL);								//����һ����ʱ����ʱ����
		m_ReceiveData="�ɹ����ӷ�����!";
		UpdateData(false);
		GetDlgItem(IDC_RECEIVE)->EnableWindow(false);				//���հ�ť��Ч
		GetDlgItem(IDC_STOP)->EnableWindow(true);					//ֹͣ��ť��Ч
	}
	else
	{
		AfxMessageBox("Socket����ʧ�ܣ�");
	}			
}

void CTCPClientDlg::OnStop() 
{
	// TODO: Add your control notification handler code here
	KillTimer(1);											//�رն�ʱ��
	m_sockReceive.Close();									//�ر��׽���
	m_ReceiveData="ֹͣ��������!";
	UpdateData(false);
	GetDlgItem(IDC_RECEIVE)->EnableWindow(true);				//���հ�ť��Ч
	GetDlgItem(IDC_STOP)->EnableWindow(false);					//ֹͣ��ť��Ч	
}

void CTCPClientDlg::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	char szRecv[20];
	int iRecv =m_sockReceive.Receive(szRecv,10,0);//����TCP����
	if(iRecv>=0)
	{
		szRecv[iRecv]=NULL;
		m_ReceiveData=szRecv;										//��¼��������
		m_receivecount+=iRecv;									//�����ֽ���
		m_ReceiveData=m_ReceiveData;
	}
	else									//���û�н��յ��κ�����
	{
		m_ReceiveData="û���յ�����!";
	}
	UpdateData(false);
	CDialog::OnTimer(nIDEvent);
}
