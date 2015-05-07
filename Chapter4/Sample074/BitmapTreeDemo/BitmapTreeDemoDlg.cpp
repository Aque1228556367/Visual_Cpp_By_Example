// BitmapTreeDemoDlg.cpp : implementation file
//

#include "stdafx.h"
#include "BitmapTreeDemo.h"
#include "BitmapTreeDemoDlg.h"

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
// CBitmapTreeDemoDlg dialog

CBitmapTreeDemoDlg::CBitmapTreeDemoDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CBitmapTreeDemoDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CBitmapTreeDemoDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CBitmapTreeDemoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CBitmapTreeDemoDlg)
	DDX_Control(pDX, IDC_TREE1, m_ctlTree);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CBitmapTreeDemoDlg, CDialog)
	//{{AFX_MSG_MAP(CBitmapTreeDemoDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBitmapTreeDemoDlg message handlers

BOOL CBitmapTreeDemoDlg::OnInitDialog()
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
	m_ctlTree.SetBKImage("Blue hills.bmp"); //���ñ���λͼ

	TVINSERTSTRUCT tvInsert;
	tvInsert.hParent = NULL;
	tvInsert.hInsertAfter = NULL;
	tvInsert.item.mask = TVIF_TEXT;
	tvInsert.item.pszText = _T("�����Ƽ���ѧ");
	
	HTREEITEM hCountry = m_ctlTree.InsertItem(&tvInsert);
	HTREEITEM hPA = m_ctlTree.InsertItem(TVIF_TEXT,
		_T("�����ѧԺ"), 0, 0, 0, 0, 0, hCountry, NULL);
	
	HTREEITEM hWA = m_ctlTree.InsertItem(_T("���ӿ�ѧ�빤��ѧԺ"),
		0, 0, hCountry, hPA);
		
	m_ctlTree.InsertItem(_T("�����Ӳ������"), hPA, TVI_SORT);
	m_ctlTree.InsertItem(_T("��������밲ȫ"), hPA, TVI_SORT);
	m_ctlTree.InsertItem(_T("����ԭ��"), hPA, TVI_SORT);
	
	m_ctlTree.InsertItem(_T("ң����Ϣ����"), hWA, TVI_SORT);
	m_ctlTree.InsertItem(_T("�״＼��"), hWA, TVI_SORT);
	m_ctlTree.InsertItem(_T("ͨ�ż���"), hWA, TVI_SORT);

	m_ctlTree.Expand(hCountry,TVE_EXPAND);


	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CBitmapTreeDemoDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CBitmapTreeDemoDlg::OnPaint() 
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
HCURSOR CBitmapTreeDemoDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}
