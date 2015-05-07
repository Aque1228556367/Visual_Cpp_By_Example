// ClipTextTransDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ClipTextTrans.h"
#include "ClipTextTransDlg.h"

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
// CClipTextTransDlg dialog

CClipTextTransDlg::CClipTextTransDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CClipTextTransDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CClipTextTransDlg)
	m_strSource = _T("");
	m_strDest = _T("");
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CClipTextTransDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CClipTextTransDlg)
	DDX_Text(pDX, IDC_EDIT1, m_strSource);
	DDX_Text(pDX, IDC_EDIT2, m_strDest);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CClipTextTransDlg, CDialog)
	//{{AFX_MSG_MAP(CClipTextTransDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_COPY, OnCopy)
	ON_BN_CLICKED(IDC_CUT, OnCut)
	ON_BN_CLICKED(IDC_PLASTE, OnPlaste)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CClipTextTransDlg message handlers

BOOL CClipTextTransDlg::OnInitDialog()
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

void CClipTextTransDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CClipTextTransDlg::OnPaint() 
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
HCURSOR CClipTextTransDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CClipTextTransDlg::OnCopy() //����
{
	// TODO: Add your control notification handler code here
	UpdateData(true);
	if (OpenClipboard())//��ϵͳ������
	{
		EmptyClipboard();//���ϵͳ������	
		//����һ�ڴ棬��С����Ҫ�������ַ����Ĵ�С������һ���ڴ���ƾ��
		HGLOBAL hClipboardData;
		hClipboardData = GlobalAlloc(GMEM_DDESHARE,m_strSource.GetLength()+1);	
		//�ڴ���ƾ������������ֵΪָ�����ڴ���ƾ�����ڵ��ض����ݸ�ʽ��ָ��
		char * pchData;
		pchData = (char*)GlobalLock(hClipboardData);	
		strcpy(pchData, LPCSTR(m_strSource));	//�����ر�����ֵ����ȫ���ڴ�	
		GlobalUnlock(hClipboardData);//��ȫ���ڴ���ƾ������	
		SetClipboardData(CF_TEXT,hClipboardData);//��Ҫ���������ݷŵ���������		
		CloseClipboard();//ʹ�����رռ�����
	}
}

void CClipTextTransDlg::OnCut() //����
{
	// TODO: Add your control notification handler code here
	OnCopy();
	m_strSource="";
	UpdateData(false);
}

void CClipTextTransDlg::OnPlaste() //ճ��
{
	// TODO: Add your control notification handler code here
	//��ϵͳ������
	if (OpenClipboard()) 
	{
		//�жϼ������ϵ������Ƿ���ָ�������ݸ�ʽ
		if (::IsClipboardFormatAvailable(CF_TEXT)||::IsClipboardFormatAvailable(CF_OEMTEXT))
		{
			HANDLE hClipboardData = GetClipboardData(CF_TEXT);	//�Ӽ������ϻ������
			//ͨ�����ڴ������������ָ��ָ����ʽ���ݵ�ָ��
			char *pchData = (char*)GlobalLock(hClipboardData);
			m_strDest = pchData;
				UpdateData(false);
			GlobalUnlock(hClipboardData);//���ڴ�������
		}
		else
		{ 
			AfxMessageBox("���а���û���ı���Ϣ");
		}	
		//ʹ�����رռ�����
		CloseClipboard();
	}
}
