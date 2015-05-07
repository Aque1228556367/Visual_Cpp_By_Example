// ScrollProgressDemoDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ScrollProgressDemo.h"
#include "ScrollProgressDemoDlg.h"

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
// CScrollProgressDemoDlg dialog

CScrollProgressDemoDlg::CScrollProgressDemoDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CScrollProgressDemoDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CScrollProgressDemoDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CScrollProgressDemoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CScrollProgressDemoDlg)
	DDX_Control(pDX, IDC_PROGRESS2, m_ctlProgressV);
	DDX_Control(pDX, IDC_PROGRESS1, m_ctlProgressH);
	DDX_Control(pDX, IDC_SCROLLBAR2, m_crlScrollV);
	DDX_Control(pDX, IDC_SCROLLBAR1, m_crlScrollH);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CScrollProgressDemoDlg, CDialog)
	//{{AFX_MSG_MAP(CScrollProgressDemoDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_HSCROLL()
	ON_WM_VSCROLL()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CScrollProgressDemoDlg message handlers

BOOL CScrollProgressDemoDlg::OnInitDialog()
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
	m_crlScrollH.SetScrollRange(0,100);		//����ˮƽ������Χ
	m_crlScrollV.SetScrollRange(0,100);		//���ô�ֱ������Χ
	m_crlScrollH.SetScrollPos(0);			//����ˮƽ�����ؼ���ʼֵ
	m_crlScrollV.SetScrollPos(0);			//���ô�ֱ�����ؼ���ʼֵ
	m_ctlProgressH.SetRange(0,100);			//����ˮƽ�������ķ�Χ
	m_ctlProgressV.SetRange(0,100);			//���ô�ֱ�������ķ�Χ
	m_ctlProgressH.SetPos(0);//����ˮƽ�������ĳ�ʼλ��
	m_ctlProgressV.SetPos(0);//���ô�ֱ�������ĳ�ʼλ��


	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CScrollProgressDemoDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CScrollProgressDemoDlg::OnPaint() 
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
HCURSOR CScrollProgressDemoDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CScrollProgressDemoDlg::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	// TODO: Add your message handler code here and/or call default
	m_crlScrollH.SetFocus();//ˮƽ������������뽹��
	int pos=m_crlScrollH.GetScrollPos();
	switch (nSBCode)
	{
		case SB_ENDSCROLL:		//	End��
			return;
		case SB_LINELEFT:		//�������ͷ
			pos -= 2;//���󲽽�2
			if (pos < 0)
				pos = 0;
			break;
		case SB_LINERIGHT:		//�����Ҽ�ͷ
			pos += 2;//���Ҳ���2
			if (pos > 100)
				pos = 100;
			break;
		case SB_PAGELEFT:		//����PgUp��
			pos-= 10;//���󲽽�10
			if (pos < 0)
				pos = 0;
			break;
		case SB_PAGERIGHT:		//����PgDn��
			pos+= 10;//���Ҳ���10
			if (pos > 100)
				pos = 100;
			break;
		case SB_THUMBPOSITION:	//Scroll to absolute position. The current position is specified by the nPos parameter.
			pos = nPos;
			break;
		case SB_THUMBTRACK:		//Drag scroll box to specified position. The current position is specified by the nPos parameter
			pos = nPos;
			break;
	}
	m_crlScrollH.SetScrollPos(pos);//����ˮƽ��������λ��
	m_ctlProgressH.SetPos(pos);//����ˮƽ��������λ��
	CDialog::OnHScroll(nSBCode, nPos, pScrollBar);
}

void CScrollProgressDemoDlg::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	// TODO: Add your message handler code here and/or call default
	m_crlScrollV.SetFocus();//��ֱ������������뽹��
	int pos=m_crlScrollV.GetScrollPos();
	switch (nSBCode)
	{
		case SB_ENDSCROLL:		//	End��
			return;
		case SB_LINEUP:		//������/���ͷ
			pos -= 2;//���²���2
			if (pos < 0)
				pos = 0;
			break;
		case SB_LINEDOWN:		//������/�Ҽ�ͷ
			pos += 2;//���ϲ���2
			if (pos > 100)
				pos = 100;
			break;
		case SB_PAGEDOWN:		//����PgUp��
			pos-= 10;//���²���10
			if (pos < 0)
				pos = 0;
			break;
		case SB_PAGEUP:		//����PgDn��
			pos+= 10;//���ϲ���10
			if (pos > 100)
				pos = 100;
			break;
		case SB_THUMBPOSITION:	//Scroll to absolute position. The current position is specified by the nPos parameter.
			pos = nPos;
			break;
		case SB_THUMBTRACK:		//Drag scroll box to specified position. The current position is specified by the nPos parameter
			pos = nPos;
			break;
	}
	m_crlScrollV.SetScrollPos(pos);//���ô�ֱ��������λ��
	m_ctlProgressV.SetPos(pos);//���ô�ֱ��������λ��	
	CDialog::OnVScroll(nSBCode, nPos, pScrollBar);
}
