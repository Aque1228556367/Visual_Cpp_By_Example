// MapFileTransDlg.cpp : implementation file
//

#include "stdafx.h"
#include "MapFileTrans.h"
#include "MapFileTransDlg.h"

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
// CMapFileTransDlg dialog

CMapFileTransDlg::CMapFileTransDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CMapFileTransDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CMapFileTransDlg)
	m_strSource = _T("");
	m_strDest = _T("");
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMapFileTransDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMapFileTransDlg)
	DDX_Text(pDX, IDC_EDIT1, m_strSource);
	DDX_Text(pDX, IDC_EDIT2, m_strDest);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CMapFileTransDlg, CDialog)
	//{{AFX_MSG_MAP(CMapFileTransDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_SAVE, OnSave)
	ON_BN_CLICKED(IDC_READ, OnRead)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMapFileTransDlg message handlers

BOOL CMapFileTransDlg::OnInitDialog()
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

void CMapFileTransDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CMapFileTransDlg::OnPaint() 
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
HCURSOR CMapFileTransDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CMapFileTransDlg::OnSave() //�������ݵ��ڴ�ӳ�����
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	HANDLE hMapping;   //�����ڴ�ӳ�����
	LPSTR lpData;   
	hMapping=CreateFileMapping((HANDLE)0xFFFFFFFF,NULL,PAGE_READWRITE,0,0x100,"SHAREFILE");   
	if(hMapping==NULL)   
	{   
		AfxMessageBox("�����ڴ��ļ�ӳ��ʧ�ܣ�");
		return;
	}
	//���ļ�����ͼӳ�䵽һ�����̵ĵ�ַ�ռ��ϣ�����LPVOID���͵��ڴ�ָ��
	lpData=(LPSTR)MapViewOfFile(hMapping,FILE_MAP_ALL_ACCESS,0,0,0);   
	if(lpData==NULL)   
	{   
		AfxMessageBox("ӳ���ļ���ͼʧ�ܣ�");
		return;
	}
	sprintf(lpData,m_strSource);   //�����ӳ���ڴ�д����
	UnmapViewOfFile(lpData);   //�ͷ�ӳ���ڴ�	
	
	
}

void CMapFileTransDlg::OnRead() //���ڴ�ӳ����������
{
	// TODO: Add your control notification handler code here
	//�����ڴ�ӳ�����
	HANDLE hMapping; 
	LPSTR lpData; 
	hMapping=CreateFileMapping((HANDLE)0xFFFFFFFF,NULL,PAGE_READWRITE,0,0x100,"SHAREFILE");
	if(hMapping==NULL) 
	{ 
		AfxMessageBox("�����ڴ��ļ�ӳ��ʧ�ܣ�");
		return;
	}

	//���ļ�����ͼӳ�䵽һ�����̵ĵ�ַ�ռ��ϣ�����LPVOID���͵��ڴ�ָ��
	lpData=(LPSTR)MapViewOfFile(hMapping,FILE_MAP_ALL_ACCESS,0,0,0); 
	if(lpData==NULL) 
	{
		AfxMessageBox("ӳ���ļ���ͼʧ�ܣ�");
		return;
	}
	//�����ӳ���ڴ�����ݸ������ر���
	m_strDest.Format("%s",lpData);	
	UnmapViewOfFile(lpData);//�ͷ�ӳ���ڴ�
	UpdateData(FALSE);
}
