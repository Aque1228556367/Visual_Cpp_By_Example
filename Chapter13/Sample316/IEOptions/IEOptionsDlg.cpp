// IEOptionsDlg.cpp : implementation file
//

#include "stdafx.h"
#include "IEOptions.h"
#include "IEOptionsDlg.h"

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
// CIEOptionsDlg dialog

CIEOptionsDlg::CIEOptionsDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CIEOptionsDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CIEOptionsDlg)
	m_strTitle = _T("");
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CIEOptionsDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CIEOptionsDlg)
	DDX_Control(pDX, IDC_LIST_IE, m_ctrlIE);
	DDX_Text(pDX, IDC_TITLE, m_strTitle);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CIEOptionsDlg, CDialog)
	//{{AFX_MSG_MAP(CIEOptionsDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_SETTITLE, OnSettitle)
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CIEOptionsDlg message handlers

BOOL CIEOptionsDlg::OnInitDialog()
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
	
	//�����б�ؼ��ķ��
	m_ctrlIE.SetExtendedStyle(LVS_EX_CHECKBOXES|LVS_EX_FLATSB
							 |LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);	
	m_ctrlIE.InsertColumn(0, "��ǰ���е�IEʵ���ı���", LVCFMT_LEFT, 340, -1);//����һ��	
	CoInitialize(NULL);//��ʼ��Com����
	if (m_ShellWindowPtr== NULL)
	{
		//����������ʵ��
		if (m_ShellWindowPtr.CreateInstance(__uuidof(SHDocVw::ShellWindows)) != S_OK)
		{
			AfxMessageBox("COMʵ������ʧ��");
			CoUninitialize();
			EndDialog(1);
		}
	}	
	RefreshList();	//ˢ���б�ؼ�
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CIEOptionsDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CIEOptionsDlg::OnPaint() 
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
HCURSOR CIEOptionsDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CIEOptionsDlg::RefreshList()//ˢ���б��
{
	for (int i = 0; i <m_ctrlIE.GetItemCount(); i ++)//�ͷ�IEʵ������
	{
		IWebBrowser2 *pBrowser = (IWebBrowser2 *)m_ctrlIE.GetItemData(i);
		if (pBrowser)
		{
			pBrowser->Release();
		}
	}
	m_ctrlIE.DeleteAllItems();//����б�ؼ�
	if(m_ShellWindowPtr)
	{
		for (int i = 0; i <m_ShellWindowPtr->GetCount(); i++)
		{
			_variant_t v = (long)i;//��õ�i��ieʵ��
			IDispatchPtr spDisp = m_ShellWindowPtr->Item(v);
			SHDocVw::IWebBrowser2Ptr spBrowser(spDisp);
			if (spBrowser)
			{
				spBrowser->AddRef();
				MSHTML::IHTMLDocument2Ptr spDoc = spBrowser->GetDocument();//����ĵ�����
				if(spDoc==NULL)
					continue;	
				BSTR bsTitle;
				spDoc->get_title(&bsTitle);//����ĵ�����
				CString strTitle = (CString)bsTitle;
				//����б��
				int nPos = m_ctrlIE.InsertItem(0, strTitle);
				void * pData = spBrowser;
				m_ctrlIE.SetItemData(nPos, (DWORD)(pData));
			}
		}
	}
}

//�趨ie����
void CIEOptionsDlg::OnSettitle() 
{
	UpdateData(TRUE);
	for (int i = 0; i <m_ctrlIE.GetItemCount(); i++)
	{
		if (m_ctrlIE.GetCheck(i))//��ñ�ѡ�е�ʵ��
		{
			DWORD data = m_ctrlIE.GetItemData(i);	
			IWebBrowser2 *pBrowser = (IWebBrowser2 *)data;//���ie�����ʵ��
			if (pBrowser)
			{	
				IDispatchPtr spDisp;
				pBrowser->get_Document(&spDisp);//���ie�ĵ�����
				MSHTML::IHTMLDocument2Ptr spDoc(spDisp);	
				if(spDoc==NULL)
					continue;		
				BSTR bsTitle = m_strTitle.AllocSysString();
				spDoc->title = bsTitle;//�趨����
			}
		}
	}
	RefreshList();	//ˢ���б��ؼ�
}

//���ٴ���ʱ�����com����
void CIEOptionsDlg::OnDestroy() 
{
	//�������com����
	int n = m_ctrlIE.GetItemCount();
	for (int i = 0; i < n; i ++)
	{
		IWebBrowser2 *pBrowser = (IWebBrowser2 *)m_ctrlIE.GetItemData(i);
		if (pBrowser)
		{
			pBrowser->Release();
		}
	}		
	m_ctrlIE.DeleteAllItems();
	
	if (m_ShellWindowPtr)
	{
		m_ShellWindowPtr.Release();
		m_ShellWindowPtr= 0;
	}
	CoUninitialize();

	CDialog::OnDestroy();	
}
