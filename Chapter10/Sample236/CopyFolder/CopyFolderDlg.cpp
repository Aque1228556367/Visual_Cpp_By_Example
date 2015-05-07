// CopyFolderDlg.cpp : implementation file
//

#include "stdafx.h"
#include "CopyFolder.h"
#include "CopyFolderDlg.h"

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
// CCopyFolderDlg dialog

CCopyFolderDlg::CCopyFolderDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CCopyFolderDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CCopyFolderDlg)
	m_strDestFolder = _T("");
	m_strSourceFolder = _T("");
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CCopyFolderDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCopyFolderDlg)
	DDX_Text(pDX, IDC_EDIT2, m_strDestFolder);
	DDX_Text(pDX, IDC_EDIT1, m_strSourceFolder);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CCopyFolderDlg, CDialog)
	//{{AFX_MSG_MAP(CCopyFolderDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_RFOLDER, OnRfolder)
	ON_BN_CLICKED(IDC_DFOLDER, OnDfolder)
	ON_BN_CLICKED(IDC_COPY, OnCopy)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCopyFolderDlg message handlers

BOOL CCopyFolderDlg::OnInitDialog()
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

void CCopyFolderDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CCopyFolderDlg::OnPaint() 
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
HCURSOR CCopyFolderDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CCopyFolderDlg::OnRfolder() 
{
	// TODO: Add your control notification handler code here
	//����ָ��IMalloc��ָ��
    LPMALLOC  pMalloc;  
    if (::SHGetMalloc(&pMalloc) != NOERROR)
        return; // failed to get allocator
    char szDisplayName[_MAX_PATH];
    char szBuffer[_MAX_PATH];
    BROWSEINFO browseInfo;							//����Ի���ṹ
    browseInfo.hwndOwner = this->m_hWnd;
    browseInfo.pidlRoot = NULL;						//���ø�Ŀ¼Ϊ����
    browseInfo.pszDisplayName = szDisplayName;
    browseInfo.lpszTitle = "ѡ��Ҫ���Ƶ�ԴĿ¼";  				//�Ի������
    browseInfo.ulFlags = BIF_RETURNFSANCESTORS|BIF_RETURNONLYFSDIRS;
    browseInfo.lpfn = NULL;     						//δ��
    browseInfo.lParam = 0;      						//δ��
    LPITEMIDLIST lpItemIDList;
    if ((lpItemIDList = ::SHBrowseForFolder(&browseInfo))!= NULL)
    {
		//�õ�Ŀ¼��·��
        if (::SHGetPathFromIDList(lpItemIDList, szBuffer))
        {
            if (szBuffer[0] == '\0')
            {
                return ;
            }
            m_strSourceFolder = szBuffer;
			UpdateData(false);
        }
        else
        {
			AfxMessageBox("���ܵõ���ѡ���ļ��У�",MB_ICONSTOP|MB_OK);
			return;
        }
        pMalloc->Free(lpItemIDList);
        pMalloc->Release();
    }

	
}

void CCopyFolderDlg::OnDfolder() 
{
	// TODO: Add your control notification handler code here
	//����ָ��IMalloc��ָ��
    LPMALLOC  pMalloc;  
    if (::SHGetMalloc(&pMalloc) != NOERROR)
        return; // failed to get allocator
    char szDisplayName[_MAX_PATH];
    char szBuffer[_MAX_PATH];
    BROWSEINFO browseInfo;							//����Ի���ṹ
    browseInfo.hwndOwner = this->m_hWnd;
    browseInfo.pidlRoot = NULL;						//���ø�Ŀ¼Ϊ����
    browseInfo.pszDisplayName = szDisplayName;
    browseInfo.lpszTitle = "ѡ���Ƶ�Ŀ��Ŀ¼";  				//�Ի������
    browseInfo.ulFlags = BIF_RETURNFSANCESTORS|BIF_RETURNONLYFSDIRS;
    browseInfo.lpfn = NULL;     						//δ��
    browseInfo.lParam = 0;      						//δ��
    LPITEMIDLIST lpItemIDList;
    if ((lpItemIDList = ::SHBrowseForFolder(&browseInfo))!= NULL)
    {
		//�õ�Ŀ¼��·��
        if (::SHGetPathFromIDList(lpItemIDList, szBuffer))
        {
            if (szBuffer[0] == '\0')
            {
                return ;
            }
            m_strDestFolder = szBuffer;
			UpdateData(false);
        }
        else
        {
			AfxMessageBox("���ܵõ���ѡ���ļ��У�",MB_ICONSTOP|MB_OK);
			return;
        }
        pMalloc->Free(lpItemIDList);
        pMalloc->Release();
    }

	
}

void CCopyFolderDlg::OnCopy() 
{
	// TODO: Add your control notification handler code here
   UpdateData(true);
   SHFILEOPSTRUCT  sfo;//�ṹ��
   char szSource[MAX_PATH];
   char szDest[MAX_PATH];
   lstrcpy(szSource,m_strSourceFolder);//ԴĿ¼
   lstrcpy(szDest,m_strDestFolder);//Ŀ��Ŀ¼
   szSource[lstrlen(szSource)+1] = 0;
   szDest[lstrlen(szDest)+1] = 0;
   sfo.hwnd = NULL;//����ָ��
   sfo.wFunc = FO_COPY;//��������Ϊ����
   sfo.pFrom = (LPCSTR)szSource;//ԴĿ¼
   sfo.pTo = (LPCSTR)szDest;//Ŀ��Ŀ¼
   sfo.fFlags =   FOF_NOCONFIRMATION |		//�����и��ƹ����п��ܵ����ĶԻ�����á�ȫ�ǡ�ѡ��
                  FOF_SIMPLEPROGRESS |		//ʹ�ý�����
                  FOF_NOCONFIRMMKDIR ;		//���Զ�������Ŀ¼
   sfo.hNameMappings = 0;
   sfo.lpszProgressTitle = "�ļ��п���";//�������ı���

   if(SHFileOperation(&sfo)==0)			//�����ɹ���SHFileOperation����0
	   AfxMessageBox("�ɹ���ɿ�����");
   else
	   AfxMessageBox("��������");
}
