// DatePickerDemoDlg.cpp : implementation file
//

#include "stdafx.h"
#include "DatePickerDemo.h"
#include "DatePickerDemoDlg.h"

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
// CDatePickerDemoDlg dialog

CDatePickerDemoDlg::CDatePickerDemoDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CDatePickerDemoDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDatePickerDemoDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CDatePickerDemoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDatePickerDemoDlg)
	DDX_Control(pDX, IDC_DATETIMEPICKER1, m_ctlDateTime);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CDatePickerDemoDlg, CDialog)
	//{{AFX_MSG_MAP(CDatePickerDemoDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_SET, OnSet)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDatePickerDemoDlg message handlers

BOOL CDatePickerDemoDlg::OnInitDialog()
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
	
	// TODO: Add extra initialization 	
	m_ctlDateTime.SetFormat("ddd',' MMM dd',' yyyy");//�趨�ؼ�����ʾ��ʽ
	//����ʱ����ϡ�����
	COleDateTime MinTime(COleDateTime::GetCurrentTime()-COleDateTimeSpan(30,0,0,0));
	COleDateTime MaxTime(COleDateTime::GetCurrentTime()+COleDateTimeSpan(30,0,0,0));
	m_ctlDateTime.SetRange(&MinTime, &MaxTime);//�趨�ؼ���ѡ��ʱ�䷶Χ	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CDatePickerDemoDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CDatePickerDemoDlg::OnPaint() 
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
HCURSOR CDatePickerDemoDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CDatePickerDemoDlg::OnSet() 
{
	// TODO: Add your control notification handler code here
	CString msg;
	CTime MinTime, MaxTime;
	DWORD result = m_ctlDateTime.GetRange(&MinTime, &MaxTime);//��ȡʱ���
	msg = _T("\n��ѡʱ�������: ");
	if (result & GDTR_MIN) 
		msg += MinTime.Format("%#x");
	else
		msg += _T("None.");
	msg += _T("\n��ѡʱ�������: ");
	if (result & GDTR_MAX) 
		msg += MaxTime.Format("%#x");
	else
		msg += _T("None.");
	CTime time;
	m_ctlDateTime.GetTime(time);
	msg += _T("\n��ǰ�趨ʱ��: ");
	msg += time.Format("%#x");
	AfxMessageBox(msg);
}
