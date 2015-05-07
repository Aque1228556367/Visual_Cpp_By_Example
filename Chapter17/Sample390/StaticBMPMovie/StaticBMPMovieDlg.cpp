// StaticBMPMovieDlg.cpp : implementation file
//

#include "stdafx.h"
#include "StaticBMPMovie.h"
#include "StaticBMPMovieDlg.h"

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
// CStaticBMPMovieDlg dialog

CStaticBMPMovieDlg::CStaticBMPMovieDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CStaticBMPMovieDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CStaticBMPMovieDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CStaticBMPMovieDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CStaticBMPMovieDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CStaticBMPMovieDlg, CDialog)
	//{{AFX_MSG_MAP(CStaticBMPMovieDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_STAR, OnStar)
	ON_BN_CLICKED(IDC_STOP, OnStop)
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CStaticBMPMovieDlg message handlers

BOOL CStaticBMPMovieDlg::OnInitDialog()
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
	GetDlgItem(IDC_STOP)->EnableWindow(false);//ֹͣ��ť��Ч
	m_nCurFrame=0;
	for (int i = 0; i < 6; i++) 
	{
		m_pBmp[i] = new CBitmap;
		m_pBmp[i]->LoadBitmap(IDB_BITMAP1 + i);
	}
	m_pBmp[0]->GetBitmap(&bs);	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CStaticBMPMovieDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CStaticBMPMovieDlg::OnPaint() 
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
HCURSOR CStaticBMPMovieDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CStaticBMPMovieDlg::OnStar() 
{
	// TODO: Add your control notification handler code here
	GetDlgItem(IDC_STAR)->EnableWindow(false);//��ʼ��ť��Ч
	GetDlgItem(IDC_STOP)->EnableWindow(true);//����ֹͣ��ť
	m_nCurFrame = 0;
	SetTimer(1, 300, NULL);//���ö�ʱ��
}

void CStaticBMPMovieDlg::OnStop() 
{
	// TODO: Add your control notification handler code here
	GetDlgItem(IDC_STOP)->EnableWindow(false);//ֹͣ��ť��Ч
	GetDlgItem(IDC_STAR)->EnableWindow(true);//���ʼ��ť
	KillTimer(1);//���ٶ�ʱ��
	
}

void CStaticBMPMovieDlg::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	CDC *pDC = GetDlgItem(IDC_MOVIE)->GetDC();
	CDC dc;
	dc.CreateCompatibleDC(pDC);//��������DC
	dc.SelectObject(m_pBmp[m_nCurFrame]);//����λͼ
	pDC->BitBlt(0, 0, bs.bmWidth, bs.bmHeight, &dc, 0, 0, SRCCOPY);//��ʾλͼ
	m_nCurFrame++;
	m_nCurFrame%=6;
	CDialog::OnTimer(nIDEvent);
}
