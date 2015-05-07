// CreateThreadDlg.cpp : implementation file
//

#include "stdafx.h"
#include "CreateThread.h"
#include "CreateThreadDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About
DWORD WINAPI ThreadFun(LPVOID pthread)						//�߳���ں���
{
	lpthread temp=(lpthread)pthread;						//�������ṹ��
	temp->progress->SetPos(temp->pos);					
	while(temp->pos<20)
	{
		Sleep(temp->speed);							//�����ٶ�
		temp->pos++;								//���ӽ���
		temp->progress->SetPos(temp->pos);			//���ý���������λ��
		if(temp->pos==20)
		{
			temp->pos=0;							//�����������0
		}
	}
	return true;
}


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
// CCreateThreadDlg dialog

CCreateThreadDlg::CCreateThreadDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CCreateThreadDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CCreateThreadDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CCreateThreadDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCreateThreadDlg)
	DDX_Control(pDX, IDC_PROGRESS3, m_progress3);
	DDX_Control(pDX, IDC_PROGRESS2, m_progress2);
	DDX_Control(pDX, IDC_PROGRESS1, m_progress1);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CCreateThreadDlg, CDialog)
	//{{AFX_MSG_MAP(CCreateThreadDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_STAR1, OnStar1)
	ON_BN_CLICKED(IDC_STAR2, OnStar2)
	ON_BN_CLICKED(IDC_STAR3, OnStar3)
	ON_BN_CLICKED(IDC_PAUSE1, OnPause1)
	ON_BN_CLICKED(IDC_PAUSE2, OnPause2)
	ON_BN_CLICKED(IDC_PAUSE3, OnPause3)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCreateThreadDlg message handlers

BOOL CCreateThreadDlg::OnInitDialog()
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
	m_progress1.SetRange(0,20);//���ý�������Χ
	m_progress2.SetRange(0,20);//���ý�������Χ
	m_progress3.SetRange(0,20);//���ý�������Χ
	GetDlgItem(IDC_PAUSE1)->EnableWindow(FALSE);				//ֹͣ��ť��Ч
	GetDlgItem(IDC_PAUSE2)->EnableWindow(FALSE);				//ֹͣ��ť��Ч
	GetDlgItem(IDC_PAUSE3)->EnableWindow(FALSE);				//ֹͣ��ť��Ч
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CCreateThreadDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CCreateThreadDlg::OnPaint() 
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
HCURSOR CCreateThreadDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CCreateThreadDlg::OnStar1() 
{
	// TODO: Add your control notification handler code here
	DWORD ThreadID;
	DWORD code;
	//�����̲߳���
	thread1.progress=&m_progress1;//����������
	thread1.speed=100;//�ٶ�
	thread1.pos=0;//��ʼλ��
	if(!GetExitCodeThread(hThread1,&code)||(code!=STILL_ACTIVE))
	{
		hThread1=CreateThread(NULL,0,ThreadFun,&thread1,0,&ThreadID);//��������ʼ�߳�
	}
	GetDlgItem(IDC_PAUSE1)->EnableWindow(TRUE);				//ֹͣ��ť��Ч
	GetDlgItem(IDC_STAR1)->EnableWindow(FALSE);					//��ʼ��ť��Ч	
}

void CCreateThreadDlg::OnStar2() 
{
	// TODO: Add your control notification handler code here
	DWORD ThreadID;
	DWORD code;
	//�����߳�
	thread2.progress=&m_progress2;//�߳̽ṹ
	thread2.speed=200;
	thread2.pos=0;
	if(!GetExitCodeThread(hThread2,&code)||(code!=STILL_ACTIVE))
	{
		hThread2=CreateThread(NULL,0,ThreadFun,&thread2,0,&ThreadID);//�����߳�
	}
	GetDlgItem(IDC_PAUSE2)->EnableWindow(TRUE);				//ֹͣ��ť��Ч
	GetDlgItem(IDC_STAR2)->EnableWindow(FALSE);					//��ʼ��ť��Ч
	
}

void CCreateThreadDlg::OnStar3() 
{
	// TODO: Add your control notification handler code here
	DWORD ThreadID;
	DWORD code;
	//�����߳�
	thread3.progress=&m_progress3;//�߳̽ṹ
	thread3.speed=200;
	thread3.pos=0;
	if(!GetExitCodeThread(hThread3,&code)||(code!=STILL_ACTIVE))
	{
		hThread3=CreateThread(NULL,0,ThreadFun,&thread3,0,&ThreadID);//�����߳�
	}
	GetDlgItem(IDC_PAUSE3)->EnableWindow(TRUE);				//ֹͣ��ť��Ч
	GetDlgItem(IDC_STAR3)->EnableWindow(FALSE);					//��ʼ��ť��Ч
	
}

void CCreateThreadDlg::OnPause1() 
{
	// TODO: Add your control notification handler code here
	DWORD code;
	if(GetExitCodeThread(hThread1,&code))
		if(code==STILL_ACTIVE)									//�����ǰ�̻߳��
		{
			TerminateThread(hThread1,0);						//ǰЩ��ֹ�߳�
			CloseHandle(hThread1);								//�����߳̾��
		}
	GetDlgItem(IDC_PAUSE1)->EnableWindow(FALSE);				//ֹͣ��ť��Ч
	GetDlgItem(IDC_STAR1)->EnableWindow(TRUE);					//��ʼ��ť��Ч	
}

void CCreateThreadDlg::OnPause2() 
{
	// TODO: Add your control notification handler code here
	DWORD code;
	if(GetExitCodeThread(hThread2,&code))
		if(code==STILL_ACTIVE)
		{
			TerminateThread(hThread2,0);
			CloseHandle(hThread2);
		}
	GetDlgItem(IDC_PAUSE2)->EnableWindow(FALSE);				//ֹͣ��ť��Ч
	GetDlgItem(IDC_STAR2)->EnableWindow(TRUE);					//��ʼ��ť��Ч
	
}

void CCreateThreadDlg::OnPause3() 
{
	// TODO: Add your control notification handler code here
	DWORD code;
	if(GetExitCodeThread(hThread3,&code))
		if(code==STILL_ACTIVE)
		{
			TerminateThread(hThread3,0);
			CloseHandle(hThread2);
		}
	GetDlgItem(IDC_PAUSE3)->EnableWindow(FALSE);				//ֹͣ��ť��Ч
	GetDlgItem(IDC_STAR3)->EnableWindow(TRUE);					//��ʼ��ť��Ч
	
}
