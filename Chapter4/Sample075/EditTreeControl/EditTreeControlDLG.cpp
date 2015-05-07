// EditTreeControlDlg.cpp : implementation file
//

#include "stdafx.h"
#include "EditTreeControl.h"
#include "EditTreeControlDlg.h"

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
// CEditTreeControlDlg dialog

CEditTreeControlDlg::CEditTreeControlDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CEditTreeControlDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CEditTreeControlDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CEditTreeControlDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CEditTreeControlDlg)
	DDX_Control(pDX, IDC_TREE1, m_ctlTree);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CEditTreeControlDlg, CDialog)
	//{{AFX_MSG_MAP(CEditTreeControlDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_NOTIFY(TVN_BEGINLABELEDIT, IDC_TREE1, OnBeginlabeleditTree1)
	ON_NOTIFY(TVN_ENDLABELEDIT, IDC_TREE1, OnEndlabeleditTree1)
	ON_NOTIFY(NM_DBLCLK, IDC_TREE1, OnDblclkTree1)
	ON_BN_CLICKED(IDC_EDIT, OnEdit)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEditTreeControlDlg message handlers

BOOL CEditTreeControlDlg::OnInitDialog()
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
	m_imageList.Create(16, 16, ILC_COLOR, 2, 2);						//����ͼ���б�
	CBitmap bm;
	bm.LoadBitmap(IDB_BITMAP1);									//����Bitmap��Դ
	m_imageList.Add(&bm, RGB(0, 0, 0));							//��ӵ�ͼ���б�
	bm.DeleteObject();
	bm.LoadBitmap(IDB_BITMAP2);
	m_imageList.Add(&bm, RGB(0, 0, 0));

	m_ctlTree.SetImageList(&m_imageList,TVSIL_NORMAL); //Ϊ���οؼ����ͼ���б�

	HTREEITEM hroot=m_ctlTree.InsertItem("�廪��ѧ",1,0,TVI_ROOT);//���һ�����
	HTREEITEM h1=m_ctlTree.InsertItem("��е����ѧԺ",1,0,hroot);//��Ӷ������
	HTREEITEM h2=m_ctlTree.InsertItem("��ѧԺ",1,0,hroot);//��Ӷ������
	HTREEITEM h3=m_ctlTree.InsertItem("���ù���ѧԺ",1,0,hroot);//��Ӷ������
	HTREEITEM h11=m_ctlTree.InsertItem("��е����ϵ",1,0,h1);//����������
	HTREEITEM h12=m_ctlTree.InsertItem("����ϵ ",1,0,h1);//����������
	HTREEITEM h13=m_ctlTree.InsertItem("����ϵ",1,0,h1);//����������
	HTREEITEM h21=m_ctlTree.InsertItem("Ӧ������ϵ",1,0,h2);//����������
	HTREEITEM h22=m_ctlTree.InsertItem("��ѧϵ",1,0,h2);//����������	

	m_ctlTree.SetBkColor(RGB(200,200,255));//�������οؼ��ı���ɫ
	m_ctlTree.SetTextColor(RGB(127,0,0));//�����ı���ɫ
	m_ctlTree.Select(h11,TVGN_CARET);						//����h11Ϊѡ����
	


	return TRUE;  // return TRUE  unless you set the focus to a control


}

void CEditTreeControlDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CEditTreeControlDlg::OnPaint() 
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
HCURSOR CEditTreeControlDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CEditTreeControlDlg::OnBeginlabeleditTree1(NMHDR* pNMHDR, LRESULT* pResult) 
{
	TV_DISPINFO* pTVDispInfo = (TV_DISPINFO*)pNMHDR;
	// TODO: Add your control notification handler code here
		*pResult = 0;
}

void CEditTreeControlDlg::OnEndlabeleditTree1(NMHDR* pNMHDR, LRESULT* pResult) 
{
	TV_DISPINFO* pTVDispInfo = (TV_DISPINFO*)pNMHDR;
	// TODO: Add your control notification handler code here
	CString strText;
	m_ctlTree.GetEditControl()->GetWindowText(strText.GetBuffer(200),200);
	m_ctlTree.SetItemText(m_ctlTree.GetSelectedItem(),strText);//���ñ༭����ı�Ϊ���
	*pResult = 0;
}

void CEditTreeControlDlg::OnDblclkTree1(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	
	*pResult = 0;
}

void CEditTreeControlDlg::OnEdit() 
{
	// TODO: Add your control notification handler code here
	m_ctlTree.ModifyStyle(NULL,TVS_EDITLABELS);//�������οؼ��ķ��
	m_ctlTree.EditLabel(m_ctlTree.GetSelectedItem());//��ǰ������༭״̬
	
}
