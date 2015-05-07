// MergFileDemoDlg.cpp : implementation file
//

#include "stdafx.h"
#include "MergFileDemo.h"
#include "MergFileDemoDlg.h"

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
// CMergFileDemoDlg dialog

CMergFileDemoDlg::CMergFileDemoDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CMergFileDemoDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CMergFileDemoDlg)
	m_strpath = _T("");
	m_strfile = _T("");
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMergFileDemoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMergFileDemoDlg)
	DDX_Text(pDX, IDC_EDIT2, m_strpath);
	DDX_Text(pDX, IDC_EDIT1, m_strfile);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CMergFileDemoDlg, CDialog)
	//{{AFX_MSG_MAP(CMergFileDemoDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_FILE, OnFile)
	ON_BN_CLICKED(IDC_MERG, OnMerg)
	ON_BN_CLICKED(IDC_PATH, OnPath)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMergFileDemoDlg message handlers

BOOL CMergFileDemoDlg::OnInitDialog()
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

void CMergFileDemoDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CMergFileDemoDlg::OnPaint() 
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
HCURSOR CMergFileDemoDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CMergFileDemoDlg::OnFile() 
{
	// TODO: Add your control notification handler code here
	CString strFilter;
	strFilter="All Files (s1_*.*)|s1_*.*||";	
	CFileDialog dlg(TRUE, NULL, NULL, OFN_EXPLORER|OFN_HIDEREADONLY|OFN_ENABLESIZING|OFN_FILEMUSTEXIST,strFilter);
	if(dlg.DoModal() == IDOK )								//��ʾ���ļ��Ի���
	{
		m_strfile=dlg.GetPathName();
		UpdateData(false);
	}
	
}

void CMergFileDemoDlg::OnMerg() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	CFile m_SourceFile,m_destFile;
	if(!m_strfile.IsEmpty())//�ļ����༭��Ϊ��
	{
		//���ļ�
		if (!m_SourceFile.Open(m_strfile, CFile::modeRead|CFile::shareDenyNone|CFile::typeBinary)) 
		{
			return;
		}	
		m_SourceFile.Close();
	}
	else
	{	
		AfxMessageBox("��ѡ��Ҫ�ϲ����ļ���");
		return;
	}
	if(m_strpath.IsEmpty())
	{
		AfxMessageBox("��ѡ��һ��������źϲ����ļ���Ŀ¼");
		return;
	}
	CString m_filename = m_strfile.Right((m_strfile.GetLength() - m_strfile.ReverseFind('\\')) - 1);
	if(m_filename.Left(3) != _T("s1_"))
	{
		AfxMessageBox("�ϲ����ļ���ʽ����ȷ��");
		return;
	}
	m_filename = m_filename.Right(m_filename.GetLength() - 3);
	m_strpath = m_strpath + _T("\\") + m_filename;
	//�����ϲ�����ļ�
	if (!m_destFile.Open(m_strpath, CFile::modeWrite|CFile::shareExclusive|CFile::typeBinary|CFile::modeCreate)) 
	{
		return;
	}
	int i = 1;
	BYTE buffer[1000000];
	UINT nCount = 1000000;
	CString name;
	//��ȡҪ�ϲ���С�ļ���·��
	CString m_emergfilepath = m_strfile.Left(m_strfile.ReverseFind('\\')+1);
	DWORD dwRead;
	do {
		//�Զ���λ�ָ��ļ���ǰ��������Ϣ
		name.Format("s%d_",i);
		//��Դ�ļ�
		if (!m_SourceFile.Open(m_emergfilepath+name+m_filename,  
			CFile::modeRead|CFile::shareExclusive|CFile::typeBinary))
		{
			return;
		}
		dwRead = m_SourceFile.Read(buffer, nCount);//��Դ�ļ�������
		m_destFile.Write(buffer, dwRead);//д��ϲ�����ļ�
		i++;
		m_SourceFile.Close();
	}
	while (dwRead > 0);
	CString str="�ļ��ϲ���ɣ�";
	AfxMessageBox(str);
	m_destFile.Close();
	
}

void CMergFileDemoDlg::OnPath() 
{
	// TODO: Add your control notification handler code here
		//����ָ��IMalloc��ָ��
    LPMALLOC  pMalloc;  
    if (::SHGetMalloc(&pMalloc) != NOERROR)
        return; // failed to get allocator
    char szDisplayName[_MAX_PATH];
    char szBuffer[_MAX_PATH];
    BROWSEINFO browseInfo;								//����Ի���ṹ
    browseInfo.hwndOwner = this->m_hWnd;
    browseInfo.pidlRoot = NULL;							//���ø�Ŀ¼Ϊ����
    browseInfo.pszDisplayName = szDisplayName;
    browseInfo.lpszTitle = "ѡ��ɾ���ļ���Ŀ¼";  				//�Ի������
    browseInfo.ulFlags = BIF_RETURNFSANCESTORS|BIF_RETURNONLYFSDIRS;
    browseInfo.lpfn = NULL;     							//δ��
    browseInfo.lParam = 0;      							//δ��
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
            m_strpath = szBuffer;
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
