// GetFileSystemDlg.cpp : implementation file
//

#include "stdafx.h"
#include "GetFileSystem.h"
#include "GetFileSystemDlg.h"

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
// CGetFileSystemDlg dialog

CGetFileSystemDlg::CGetFileSystemDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CGetFileSystemDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CGetFileSystemDlg)
	m_strFileSyetem = _T("");
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CGetFileSystemDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CGetFileSystemDlg)
	DDX_Control(pDX, IDC_COMBO1, m_ctlDriver);
	DDX_Text(pDX, IDC_EDIT1, m_strFileSyetem);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CGetFileSystemDlg, CDialog)
	//{{AFX_MSG_MAP(CGetFileSystemDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_CBN_SELCHANGE(IDC_COMBO1, OnSelchangeCombo1)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGetFileSystemDlg message handlers

BOOL CGetFileSystemDlg::OnInitDialog()
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
	DWORD dwNum;//ʵ�ʴ洢�������ŵ��ַ�������
	HANDLE hHeap;
	LPSTR lp;
	CString strLogdrive;

	//���ʵ�ʴ洢�������ŵ��ַ�������
	dwNum=GetLogicalDriveStrings(0,NULL)*sizeof(TCHAR);
	//����ַ�����Ϊ�գ����ʾ������������
	if (dwNum!=0) 
	{
		//�����ַ����ռ�
		hHeap=GetProcessHeap();
		lp=(LPSTR)HeapAlloc(hHeap,HEAP_ZERO_MEMORY,dwNum);
		//��ñ����������������ַ���
		GetLogicalDriveStrings(HeapSize(hHeap,0,lp),lp);
		//��������һ�����ŵ���������
		while (*lp!=0) 
		{
			m_ctlDriver.AddString(lp);
			lp=_tcschr(lp,0)+1;
		}
	}
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CGetFileSystemDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CGetFileSystemDlg::OnPaint() 
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
HCURSOR CGetFileSystemDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CGetFileSystemDlg::OnSelchangeCombo1() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	//��õ�ǰѡ���������
	CString strRootPathName;
	int nselect=m_ctlDriver.GetCurSel();				//��ȡ��ǰ��Ͽ�ѡ�������
	m_ctlDriver.GetLBText(nselect,strRootPathName);			//��̬�ı���ʾ��ǰ��Ͽ�ѡ��ı���
	//�������������ļ�ϵͳ
	LPCTSTR lpRootPathName = strRootPathName;
	LPTSTR lpVolumeNameBuffer=new char[12];
	DWORD nVolumeNameSize=12;
	DWORD VolumeSerialNumber;
	DWORD MaximumComponentLength;
	DWORD FileSystemFlags;
	LPTSTR lpFileSystemNameBuffer=new char[10];
	DWORD nFileSystemNameSize=10;
	GetVolumeInformation(lpRootPathName,
				lpVolumeNameBuffer, nVolumeNameSize,
				&VolumeSerialNumber, 
				&MaximumComponentLength,
				&FileSystemFlags,
				lpFileSystemNameBuffer, nFileSystemNameSize);
	//��ʾ���������ļ�ϵͳ
	m_strFileSyetem.Format("%s",lpFileSystemNameBuffer);
	UpdateData(false);
}
