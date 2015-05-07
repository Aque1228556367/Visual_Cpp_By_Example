// SearchFileDlg.cpp : implementation file
//

#include "stdafx.h"
#include "SearchFile.h"
#include "SearchFileDlg.h"
#include "DirDialog.h"
#include "winreg.h"
#include <afxmt.h>  
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
#define WM_USERMSG WM_USER+100//�Զ�����Ϣ
/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About
MyTHREADPARAM m_param;//�̺߳�������		
CMutex m_mutexThreadCount,m_mutexFileCount,m_mutexThreadParam,m_mutexPath;
UINT uThreadCount=0;//�߳���Ŀ��ʼ��Ϊ0
int nFileCount=0;//�ҵ��ļ�������


UINT SearchFileThread(LPVOID pParam)//�����߳���ں���
{
	
	MyTHREADPARAM * m_pParam=(MyTHREADPARAM *)pParam;
	CString strPath=m_pParam->strPath;
	CString strFileName=m_pParam->strFileName;
	CListBox *m_pListInfo=(CListBox *)m_pParam->m_pListInfo;

	m_mutexThreadCount.Lock();
	uThreadCount++;
	m_mutexThreadCount.Unlock();
	HANDLE hFile;
	WIN32_FIND_DATA *pInfo=new WIN32_FIND_DATA;
	hFile = ::FindFirstFile(strPath+"\\*.*",pInfo);
	if(hFile==INVALID_HANDLE_VALUE)//δ�ҵ��ļ����ļ���
	{
		delete pInfo;
		m_mutexThreadCount.Lock();
		uThreadCount--;//�̼߳����ر�
		if(uThreadCount==0)
		::PostMessage(m_pParam->hwnd,WM_USERMSG,0,0);			//�����̷߳�����Ϣ	
		m_mutexThreadCount.Unlock();
		return 0;
	}
	do{
		if(pInfo->cFileName[0]=='.')
			continue;
		char cFileName[MAX_PATH];
		strcpy(cFileName,pInfo->cFileName);
		CString strFile=cFileName;
		if(pInfo->dwFileAttributes==FILE_ATTRIBUTE_DIRECTORY)//����õ������ļ���
		{
			
			m_mutexThreadParam.Lock();
			m_param.strPath=strPath+"\\"+strFile;//���ļ���·�������̺߳�������
			m_param.strFileName=strFileName;
			AfxBeginThread(SearchFileThread, &m_param, THREAD_PRIORITY_NORMAL);//��ʼһ���µĹ����߳�
			m_mutexThreadParam.Unlock();
		}
		else//��ȡ�����ļ�
		{
			if(strFile==strFileName)//�ҵ�Ҫ�������ļ�
			{
				m_mutexFileCount.Lock();
				nFileCount++;//�ļ���Ŀ��1
				m_mutexFileCount.Unlock();
				m_mutexPath.Lock();
				TRACE0(strPath);
				CString string;
				string=strPath+"\\"+strFile;//�ļ�·��������
				m_pParam->m_pListInfo->AddString(string);//���б�������һ��
				m_mutexPath.Unlock();
			}
		}		
	}
	while(::FindNextFile( hFile,pInfo));
	::FindClose(hFile);	//������Ϲر��ļ����
	delete pInfo;//�ͷ��ڴ�
	m_mutexThreadCount.Lock();
	uThreadCount--;//�����̼߳�������
	if(uThreadCount==0)
		::PostMessage(m_pParam->hwnd,WM_USERMSG,0,0);			//�����̷߳�����Ϣ
	m_mutexThreadCount.Unlock();	
	return 0;
}

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
// CSearchFileDlg dialog

CSearchFileDlg::CSearchFileDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSearchFileDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSearchFileDlg)
	m_FileName = _T("");
	m_strPath = _T("");
	m_status = _T("����������ȴ��ļ���������");
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CSearchFileDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSearchFileDlg)
	DDX_Control(pDX, IDC_LIST1, m_ctrList);
	DDX_Text(pDX, IDC_EDIT_FILE_NAME, m_FileName);
	DDX_Text(pDX, IDC_EDIT_ROOT_DIR, m_strPath);
	DDX_Text(pDX, IDC_STATUS, m_status);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CSearchFileDlg, CDialog)
	//{{AFX_MSG_MAP(CSearchFileDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_FIND, OnButtonFind)
	ON_BN_CLICKED(IDC_BUTTON_VIEW, OnButtonView)
	//}}AFX_MSG_MAP
	ON_MESSAGE(WM_USERMSG,OnMsg)//��Ϣӳ��
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSearchFileDlg message handlers

BOOL CSearchFileDlg::OnInitDialog()
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

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CSearchFileDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CSearchFileDlg::OnPaint() 
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
HCURSOR CSearchFileDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}


void CSearchFileDlg::OnButtonFind() 
{
	uThreadCount=0;//�����̵߳ĳ�ʼ����
	UpdateData(TRUE);
	m_param.strPath=m_strPath;
	m_param.strFileName=m_FileName;
	m_param.m_pListInfo=&m_ctrList;
	m_param.hwnd=GetSafeHwnd();									//��ȡ���̴߳���ָ��
	m_status = _T("���ڽ����ļ�����");						//���ó���״̬
	UpdateData(false);
	m_ctrList.ResetContent();
	nFileCount=0;
	AfxBeginThread(SearchFileThread, &m_param, THREAD_PRIORITY_NORMAL);//���������߳�
}

void CSearchFileDlg::OnButtonView() 
{
	CDirDialog dlg;//�ļ�·���Ի���
	if(dlg.DoBrowse(this)==IDOK)
		m_strPath=dlg.m_strPath;//��ȡ�û�ѡ���·��
	UpdateData(FALSE);
}

void CSearchFileDlg::OnMsg() //�ļ���������֪ͨ�û�
{
	m_status.Format("�ļ��������������ҵ�%d���ļ���",nFileCount);
	UpdateData(false);
}
