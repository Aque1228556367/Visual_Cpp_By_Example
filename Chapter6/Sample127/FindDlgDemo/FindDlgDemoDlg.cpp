// FindDlgDemoDlg.cpp : implementation file
//

#include "stdafx.h"
#include "FindDlgDemo.h"
#include "FindDlgDemoDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
static const UINT MsgFindReplace=::RegisterWindowMessage(FINDMSGSTRING);
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
// CFindDlgDemoDlg dialog

CFindDlgDemoDlg::CFindDlgDemoDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CFindDlgDemoDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CFindDlgDemoDlg)
	m_str = _T("");
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CFindDlgDemoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CFindDlgDemoDlg)
	DDX_Control(pDX, IDC_EDIT1, m_ctlEdit);
	DDX_Text(pDX, IDC_EDIT1, m_str);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CFindDlgDemoDlg, CDialog)
	//{{AFX_MSG_MAP(CFindDlgDemoDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_FIND, OnFind)
	//}}AFX_MSG_MAP

	ON_REGISTERED_MESSAGE(MsgFindReplace, OnFindReplace)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFindDlgDemoDlg message handlers

BOOL CFindDlgDemoDlg::OnInitDialog()
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
	pFindReplaceDlg=NULL;
	curpos=-1;
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CFindDlgDemoDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CFindDlgDemoDlg::OnPaint() 
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
HCURSOR CFindDlgDemoDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CFindDlgDemoDlg::OnFind() 
{
	// TODO: Add your control notification handler code here
	UpdateData(true);
	pos=0;
	if(pFindReplaceDlg)//�ж��Ƿ��Ѵ���һ���Ի���
	{		
		pFindReplaceDlg->SetActiveWindow();//���滻�Ի����Ѵ򿪣���ʹ֮��Ϊ�����
		return;
	}
	//���������滻�Ի���
	pFindReplaceDlg=new CFindReplaceDialog;
	pFindReplaceDlg->Create(FALSE,NULL,NULL,FR_DOWN,this);
	
}

LRESULT CFindDlgDemoDlg::OnFindReplace(WPARAM, LPARAM lParam)
{
	//�ж϶Ի����Ƿ񱻹ر�
	if(pFindReplaceDlg->IsTerminating())
	pFindReplaceDlg=NULL;
	//��ȡ��ǰ����/�滻�Ի����ָ��
	CFindReplaceDialog* pDlg = CFindReplaceDialog::GetNotifier(lParam);
	CString m_FindString = pDlg->GetFindString(); 						//Ҫ���ҵ��ַ���
	int strlen=m_FindString.GetLength();//��ȡ�����ı��ĳ���
	CString m_ReplaceString = pDlg->GetReplaceString(); 					//Ҫ�滻���ַ���
	int placelen=m_ReplaceString.GetLength();//��ȡ�滻�ı��ĳ���
	CString strpos;
	if( pDlg->FindNext() ) 							//������"����"��ť��������һ��
	{ 
		pos=m_str.Find(m_FindString,pos);
		if(pos==-1)//δ�ҵ����ҵ��ַ�
		{
			AfxMessageBox("������ϣ�û���ҵ�ָ���ַ���");
			pos=0;
		}
		else
		{
			m_ctlEdit.SetFocus();
			m_ctlEdit.SetSel(pos,pos+strlen);
			curpos=pos;
			pos++;
		}
	}
	if(pDlg->ReplaceCurrent()) 									//������"�滻"��ť��
	{
		if(curpos>=0)
		{
			m_ctlEdit.SetFocus();
			m_ctlEdit.SetSel(curpos,curpos+strlen);
			m_ctlEdit.ReplaceSel(m_ReplaceString);
			UpdateData(true);
			m_ctlEdit.SetSel(curpos,curpos+placelen);
			pos=curpos+placelen;
		}
	} 
	if( pDlg->ReplaceAll() ) 									//������"ȫ���滻"��ť
	{ 
		m_str.Replace(m_FindString,m_ReplaceString);//�滻�ַ���
		UpdateData(false);
	} 
	return 0;

}

