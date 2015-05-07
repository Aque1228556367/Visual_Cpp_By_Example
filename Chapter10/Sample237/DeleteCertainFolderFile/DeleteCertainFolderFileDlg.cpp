// DeleteCertainFolderFileDlg.cpp : implementation file
//

#include "stdafx.h"
#include "DeleteCertainFolderFile.h"
#include "DeleteCertainFolderFileDlg.h"

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
// CDeleteCertainFolderFileDlg dialog

CDeleteCertainFolderFileDlg::CDeleteCertainFolderFileDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CDeleteCertainFolderFileDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDeleteCertainFolderFileDlg)
	m_strFolder = _T("");
	m_radio = -1;
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CDeleteCertainFolderFileDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDeleteCertainFolderFileDlg)
	DDX_Text(pDX, IDC_EDIT1, m_strFolder);
	DDX_Radio(pDX, IDC_RADIO1, m_radio);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CDeleteCertainFolderFileDlg, CDialog)
	//{{AFX_MSG_MAP(CDeleteCertainFolderFileDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_FOLDER, OnFolder)
	ON_BN_CLICKED(IDC_RADIO1, OnRadio1)
	ON_BN_CLICKED(IDC_RADIO2, OnRadio2)
	ON_BN_CLICKED(IDC_RADIO3, OnRadio3)
	ON_BN_CLICKED(IDC_RADIO4, OnRadio4)
	ON_BN_CLICKED(IDC_RADIO5, OnRadio5)
	ON_BN_CLICKED(IDC_DELETE, OnDelete)
	ON_EN_CHANGE(IDC_EDIT1, OnChangeEdit1)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDeleteCertainFolderFileDlg message handlers

BOOL CDeleteCertainFolderFileDlg::OnInitDialog()
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

void CDeleteCertainFolderFileDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CDeleteCertainFolderFileDlg::OnPaint() 
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
HCURSOR CDeleteCertainFolderFileDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CDeleteCertainFolderFileDlg::OnFolder() 
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
    browseInfo.lpszTitle = "ѡ��ɾ���ļ���Ŀ¼";  				//�Ի������
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
            m_strFolder = szBuffer;
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
	DisplayFileList(m_strFolder);
}

void CDeleteCertainFolderFileDlg::OnRadio1() 
{
	// TODO: Add your control notification handler code here
	
}

void CDeleteCertainFolderFileDlg::OnRadio2() 
{
	// TODO: Add your control notification handler code here
	
}

void CDeleteCertainFolderFileDlg::OnRadio3() 
{
	// TODO: Add your control notification handler code here
	
}

void CDeleteCertainFolderFileDlg::OnRadio4() 
{
	// TODO: Add your control notification handler code here
	
}

void CDeleteCertainFolderFileDlg::OnRadio5() 
{
	// TODO: Add your control notification handler code here
	
}

void CDeleteCertainFolderFileDlg::OnDelete() 
{
	// TODO: Add your control notification handler code here
	UpdateData(true);
	CString m_extern;
	switch (m_radio)			//��ȡҪɾ���ļ����͵ĺ�׺��
	{
	case 0:
		GetDlgItem(IDC_RADIO1)->GetWindowText(m_extern);
		break;
	case 1:
		GetDlgItem(IDC_RADIO2)->GetWindowText(m_extern);
		break;
	case 2:
		GetDlgItem(IDC_RADIO3)->GetWindowText(m_extern);
		break;
	case 3:
		GetDlgItem(IDC_RADIO4)->GetWindowText(m_extern);
		break;
	case 4:
		GetDlgItem(IDC_RADIO5)->GetWindowText(m_extern);
		break;
	}
	if(m_strFolder!="" && m_extern!="")//��ǰĿ¼���ļ����Ͳ�Ϊ��
	{
		CString str,strdel;	
		//��������"C:\\My Documents\\*.txt"������
		char string[60];
		strcpy( string, m_strFolder);
		strcat( string, "\\*" );
		strcat( string, m_extern );	
		CFileFind filefind;
		if(filefind.FindFile(string,0)!=0)//���������ļ�
		{
			while(filefind.FindNextFile()!=0)
			{
				strdel=filefind.GetFilePath();//��ȡ�ļ���
				CFile::Remove(strdel);//ɾ���ļ�
			}
			strdel=filefind.GetFilePath();
			CFile::Remove(strdel);
			AfxMessageBox("�ļ�ɾ����ɣ�");
			DisplayFileList(m_strFolder);//������ʾ�б��
		}
		else
		{
			AfxMessageBox("��ǰĿ¼�£�û���������͵��ļ���");
		}
	}
	else
		AfxMessageBox("��ѡ��Ŀ¼��");
}

void CDeleteCertainFolderFileDlg::DisplayFileList(CString strdir) 
{
	TCHAR szPath [MAX_PATH];
	strcpy(szPath,strdir);
	//DlgDirList����������ListBox�м���ĳ·���µ��ļ�
	int nReslt = DlgDirList(
		szPath,//Ŀ¼
		IDC_LIST1,//ListBox����ԴID
		0,//��ǰѡ�����������·���ľ�̬�ؼ�ID�����������ʾ��Щ��������·������Ϊ0
		DDL_READWRITE|DDL_READONLY|DDL_HIDDEN|DDL_SYSTEM|DDL_ARCHIVE);
}

void CDeleteCertainFolderFileDlg::OnChangeEdit1() 
{
	// TODO: Add your control notification handler code here
	UpdateData(true);
	DisplayFileList(m_strFolder);
}
