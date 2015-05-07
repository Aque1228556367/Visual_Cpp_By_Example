// SplitFileDemoDlg.cpp : implementation file
//

#include "stdafx.h"
#include "SplitFileDemo.h"
#include "SplitFileDemoDlg.h"

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
// CSplitFileDemoDlg dialog

CSplitFileDemoDlg::CSplitFileDemoDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSplitFileDemoDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSplitFileDemoDlg)
	m_strfile = _T("");
	m_strpath = _T("");
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CSplitFileDemoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSplitFileDemoDlg)
	DDX_Text(pDX, IDC_EDIT1, m_strfile);
	DDX_Text(pDX, IDC_EDIT2, m_strpath);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CSplitFileDemoDlg, CDialog)
	//{{AFX_MSG_MAP(CSplitFileDemoDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_GETFILE, OnGetfile)
	ON_BN_CLICKED(IDC_GETPATH, OnGetpath)
	ON_BN_CLICKED(IDC_SPLIT, OnSplit)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSplitFileDemoDlg message handlers

BOOL CSplitFileDemoDlg::OnInitDialog()
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

void CSplitFileDemoDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CSplitFileDemoDlg::OnPaint() 
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
HCURSOR CSplitFileDemoDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CSplitFileDemoDlg::OnGetfile() 
{
	// TODO: Add your control notification handler code here
	CString strFilter;
	strFilter="All Files (*.*)|*.*||";	
	CFileDialog dlg(TRUE, NULL, NULL, OFN_EXPLORER|OFN_HIDEREADONLY|OFN_ENABLESIZING|OFN_FILEMUSTEXIST,strFilter);
	if(dlg.DoModal() == IDOK )								//��ʾ���ļ��Ի���
	{
		m_strfile=dlg.GetPathName();
		UpdateData(false);
	}

	
}

void CSplitFileDemoDlg::OnGetpath() 
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

void CSplitFileDemoDlg::OnSplit() 
{
	// TODO: Add your control notification handler code here
	CFile m_SourceFile,destFile;
	int len;
	if(!m_strfile.IsEmpty())//�ļ����༭��Ϊ��
	{
		//���ļ�
		if (!m_SourceFile.Open(m_strfile, CFile::modeRead|CFile::shareDenyNone|CFile::typeBinary)) 
		{
			return;
		}
		len=m_SourceFile.GetLength();//��ȡ�ļ��ĳ���
	}
	else
	{	
		AfxMessageBox("��ѡ��һ��Ҫ�ָ���ļ���");
		return;
	}
	if(m_strpath.IsEmpty())
	{
		AfxMessageBox("��ѡ��һ��������ŷָ���ļ���Ŀ¼");
		return;
	}
	DWORD dwRead;
	int nCount = 1000000;//�ָ��ļ��Ĵ�СΪ1M
	BYTE buffer[1000000];
	int i=1;
	CString name;
	if(len<=nCount)
	{
		AfxMessageBox("�ļ���СС��1M�����÷ָ");
		return;
	}
	//�ָ��ļ�
	do {
			dwRead = m_SourceFile.Read(buffer, nCount);
			if(dwRead!=0)
			//��̬����һ���½��ļ�����ǰ������
			{	
				name.Format("s%d_",i);
				CString newpath; 
				//�ж�ѡ��Ŀ¼δβ�Ƿ�����"\"��
				if(m_strpath.Right(1)=='\\')
					newpath = m_strpath;
				else
				newpath = m_strpath + _T("\\");
				//�����ָ��ļ�
				if (!destFile.Open(newpath+name+m_SourceFile.GetFileName(),  
				CFile::modeWrite|CFile::shareExclusive| CFile::typeBinary|CFile::modeCreate)) 
				{
			
					m_SourceFile.Close();
					return;
				}
				destFile.Write(buffer, dwRead);//д��Դ�ļ����ݵ��ָ��ļ�
				destFile.Close();//�رշָ��ļ�
				i++;
				}
			}
	while (dwRead>0); 
	CString str;
	str.Format("�ָ���ɣ����ָ�Ϊ%d���ļ�",i);
	AfxMessageBox(str);
	m_SourceFile.Close();
}
