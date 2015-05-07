// CreateShortCutDlg.cpp : implementation file
//

#include "stdafx.h"
#include "CreateShortCut.h"
#include "CreateShortCutDlg.h"

#include "LinkNameDlg.h"

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
// CCreateShortCutDlg dialog

CCreateShortCutDlg::CCreateShortCutDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CCreateShortCutDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CCreateShortCutDlg)
	m_radio = 0;
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CCreateShortCutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCreateShortCutDlg)
	DDX_Radio(pDX, IDC_RADIO1, m_radio);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CCreateShortCutDlg, CDialog)
	//{{AFX_MSG_MAP(CCreateShortCutDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_CREATE, OnCreate)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCreateShortCutDlg message handlers

BOOL CCreateShortCutDlg::OnInitDialog()
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
	CoInitialize (NULL);//��ʼ��Com
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CCreateShortCutDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CCreateShortCutDlg::OnPaint() 
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
HCURSOR CCreateShortCutDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

//����ļ���
BOOL CCreateShortCutDlg::BrowseForFolder(LPITEMIDLIST pidlRoot,LPITEMIDLIST *ppidlDestination,LPCSTR lpszTitle)
{    
	BROWSEINFO BrInfo ;//����ṹ��
    ZeroMemory( &BrInfo, sizeof(BrInfo)) ;
    BrInfo.hwndOwner = HWND_DESKTOP ;
    BrInfo.pidlRoot = pidlRoot ;
    BrInfo.lpszTitle = lpszTitle ;
    *ppidlDestination= SHBrowseForFolder(&BrInfo); //����ļ���
    if(NULL == *ppidlDestination)//�û�ѡ����ȡ����ť
        return FALSE ;
    return TRUE ;
}

BOOL CCreateShortCutDlg::GetShortcutCrt(LPSTR szPath)//ȡ��Ҫ�����Ŀ�ݷ�ʽ������
{
    LPITEMIDLIST pidlBeginAt, pidlDestination ;   
    // ȡ�ÿ�ʼ�˵��������PIDL
    SHGetSpecialFolderLocation( HWND_DESKTOP, nBeginAt, &pidlBeginAt) ;
    // ȡ��Ҫ�����Ŀ�ݷ�ʽ���ڵ�λ��
    if( !BrowseForFolder(pidlBeginAt,&pidlDestination, "��ѡ���ݷ�ʽ���ڵ�λ�ã�"))
        return FALSE ;
    // ��PIDLת��Ϊ·����
    SHGetPathFromIDList( pidlDestination, szPath) ;
    // ȡ�ÿ�ݷ�ʽ����
    CLinkNameDlg name_dlg;
	if(name_dlg.DoModal() == IDCANCEL)    
        return FALSE ;
    //�ѿ�ݷ�ʽ������չ��.LNK��ӵ�·�������γ������Ŀ�ݷ�ʽ�����ļ���
    wsprintf(szPath+lstrlen(szPath),"\\%s.lnk", name_dlg.m_linkname) ;
    return TRUE ;
}

//������ݷ�ʽ
BOOL CCreateShortCutDlg::CreateLink (LPSTR szPath,LPSTR szLink)
{
	HRESULT hres ;
	IShellLink * psl ;
	IPersistFile* ppf ;
	WORD wsz[ MAX_PATH] ;
    //����һ��IShellLinkʵ��
    hres = CoCreateInstance( CLSID_ShellLink, NULL, CLSCTX_INPROC_SERVER, IID_IShellLink,(void **)&psl) ;
	if( FAILED( hres))
        return FALSE ;
    psl -> SetPath( szPath) ;//����Ŀ��Ӧ�ó���
    //���ÿ�ݼ�(�˴���ΪShift+Ctrl+'T')
    psl -> SetHotkey( MAKEWORD( 'T',HOTKEYF_SHIFT |HOTKEYF_CONTROL)) ;
    //��IShellLink��ȡ��IPersistFile�ӿڣ����ڱ����ݷ�ʽ�������ļ� (*.lnk)
    hres = psl -> QueryInterface( IID_IPersistFile,(void**)&ppf) ;
	if( FAILED( hres))
        return FALSE ;
	// ȷ�������ļ���ΪANSI��ʽ
	MultiByteToWideChar( CP_ACP, 0, szLink, -1, wsz, MAX_PATH) ;
    //����IPersistFile::Save�������ݷ�ʽ�������ļ� (*.lnk)
	hres = ppf -> Save( wsz, STGM_READWRITE) ;
    //�ͷ�IPersistFile��IShellLink�ӿ�
	ppf -> Release( ) ;
	psl -> Release( ) ;
	return TRUE;
}

// ֪ͨshell�йر仯
void CCreateShortCutDlg::NotifyShell(LONG wEventId,LPSTR szPath)
{    
    SHChangeNotify( wEventId,SHCNF_FLUSH | SHCNF_PATH,szPath,0);
    //ȡ��szPath�ĸ�Ŀ¼
    char* p;
    for( p=szPath+lstrlen(szPath)-1;*p != '\\'; p--);
    *p='\0';
    SHChangeNotify(SHCNE_UPDATEDIR|SHCNE_INTERRUPT,SHCNF_FLUSH | SHCNF_PATH,szPath,0);
}

//ȡ�ÿ�ݷ�ʽ��Ŀ��Ӧ�ó�����
BOOL CCreateShortCutDlg::SelectMenuItem( LPSTR szFileName)
{
    OPENFILENAME ofn ;
    static CHAR szFilter[] = "Programs\0*.exe\0" ;
    ZeroMemory(&ofn, sizeof( OPENFILENAME)) ;
    ofn.lStructSize = sizeof( OPENFILENAME) ;
    ofn.hwndOwner = HWND_DESKTOP;
    ofn.lpstrFilter = szFilter ;
    ofn.nFilterIndex = 0 ;
    ofn.nMaxFile = MAX_PATH ;
    ofn.lpstrTitle = "��ѡ��Ŀ��Ӧ�ó���:" ;
    ofn.lpstrFile = szFileName ;
    ofn.Flags = OFN_FILEMUSTEXIST |OFN_PATHMUSTEXIST | OFN_EXPLORER ;
    //�ļ����
    if(!GetOpenFileName( &ofn))//ѡ����ȡ����ť
        return FALSE ;
    return TRUE ;
}

void CCreateShortCutDlg::OnCreate() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	if(m_radio==0)//�����洴��
	{
		nBeginAt=CSIDL_DESKTOPDIRECTORY ;   //������ʼ�ļ���Ϊ���� 
	}
	else//�ڿ�ʼ�˵�����
	{
		nBeginAt=CSIDL_STARTMENU;//������ʼ�ļ���Ϊ����ʼ���˵�
	}
	char szPath[MAX_PATH]="";//��ݷ�ʽ��Ŀ��Ӧ�ó�����
    char szLink[MAX_PATH]="";//��ݷ�ʽ�������ļ���
    if( !SelectMenuItem( szPath))// ȡ�ÿ�ݷ�ʽ��Ŀ��Ӧ�ó�����
        return ;
    if( !GetShortcutCrt( szLink))// ȡ���½���ݷ�ʽ���ڵ��ļ��У����γ��������ļ���
        return ;
    if(!CreateLink( szPath, szLink) )// ������ݷ�ʽ
        return;
    NotifyShell( SHCNE_CREATE|SHCNE_INTERRUPT, szLink) ;// ֪ͨshell�йر仯
}
