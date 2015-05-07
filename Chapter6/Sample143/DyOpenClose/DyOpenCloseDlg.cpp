// DyOpenCloseDlg.cpp : implementation file
//

#include "stdafx.h"
#include "DyOpenClose.h"
#include "DyOpenCloseDlg.h"

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
// CDyOpenCloseDlg dialog

CDyOpenCloseDlg::CDyOpenCloseDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CDyOpenCloseDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDyOpenCloseDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CDyOpenCloseDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDyOpenCloseDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CDyOpenCloseDlg, CDialog)
	//{{AFX_MSG_MAP(CDyOpenCloseDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_TIMER()
	ON_WM_CLOSE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDyOpenCloseDlg message handlers

BOOL CDyOpenCloseDlg::OnInitDialog()
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
	//��ô���Ԥ��Ĵ�С
	CRect dlgRect;
	GetWindowRect(dlgRect);
	CRect desktopRect;
	//�����ڿ�ʼ��С��Ϊ0
	GetDesktopWindow()->GetWindowRect(desktopRect);
	MoveWindow((desktopRect.Width() - dlgRect.Width())/2,
			   (desktopRect.Height() - dlgRect.Height())/2,
			   0,
			   0);
	//��ʼ���仯��С
	m_nWidth=dlgRect.Width();
	m_nHeight=dlgRect.Height();
	m_nDx=2;
	m_nDy=2;
	m_nDx1=2;
	m_nDy1=2;
	//�趨��ʱ��1	
	SetTimer(1,10,NULL);
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CDyOpenCloseDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CDyOpenCloseDlg::OnPaint() 
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
HCURSOR CDyOpenCloseDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CDyOpenCloseDlg::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	CRect dlgRect;
	GetWindowRect(dlgRect);	//��ô�ʱ���ڵ�ʵ�ʴ�С
	CRect desktopRect;
	GetDesktopWindow()->GetWindowRect(desktopRect);	//������洰�ڵĴ�С
	//����Ǵ��ڵ������̣��������󴰿�
	if(nIDEvent == 1)
	{
		MoveWindow(
				  (-m_nDx+desktopRect.Width() - dlgRect.Width()) / 2,
				  (-m_nDy+desktopRect.Height() - dlgRect.Height()) / 2, 
				  +m_nDx+dlgRect.Width(),
				  +m_nDy+dlgRect.Height() );	
		//��Ҫ��������Ԥ��Ŀ��
		if(dlgRect.Width() >=m_nWidth) 
			m_nDx=0; 
		//��Ҫ��������Ԥ��ĸ߶�
		if(dlgRect.Height() >=m_nHeight)
			m_nDy=0;
		//ֹͣ�仯���رն�ʱ��1
		if((dlgRect.Width() >=m_nWidth) && (dlgRect.Height()>=m_nHeight))
			KillTimer(1); 
	}
	
	//ֹͣ�仯���رն�ʱ��1
	if((dlgRect.Width() >=m_nWidth) && (dlgRect.Height() >=m_nHeight))
		KillTimer(1); 
	//����Ǵ��ڹرչ��̣�������С����
	if(nIDEvent == 2)
	{
		MoveWindow((+m_nDx+desktopRect.Width() - dlgRect.Width()) / 2,
			(+m_nDy+desktopRect.Height() - dlgRect.Height()) / 2,
			-m_nDx1+dlgRect.Width(),
			-m_nDy1+dlgRect.Height() );	
		//����ȵ�������ȾͲ��ڱ仯
		if(dlgRect.Width() <= 0) 
			m_nDx1=0;
		//���߶ȵ������߶ȾͲ��ڱ仯
		if(dlgRect.Height() <= 0 )
			m_nDy1=0; 
		//ֹͣ�仯���رն�ʱ��2�����ҹرմ���
		if((dlgRect.Width() <= 0 ) && (dlgRect.Height() <=0))
		{
			KillTimer(2);
			CDialog::OnOK();//�رնԻ���
		}		
	}
	CDialog::OnTimer(nIDEvent);
}

void CDyOpenCloseDlg::OnClose() 
{
	// TODO: Add your message handler code here and/or call default
	//�趨�ر�ʱ�Ķ�ʱ��2
	SetTimer(2,10,NULL);	
//	CDialog::OnClose();
}

void CDyOpenCloseDlg::OnCancel() 
{
	// TODO: Add extra cleanup here
	//�趨�ر�ʱ�Ķ�ʱ��2
	SetTimer(2,10,NULL);	
//	CDialog::OnCancel();
}

void CDyOpenCloseDlg::OnOK() 
{
	// TODO: Add extra validation here
	//�趨�ر�ʱ�Ķ�ʱ��2
	SetTimer(2,10,NULL);	
//	CDialog::OnOK();
}
