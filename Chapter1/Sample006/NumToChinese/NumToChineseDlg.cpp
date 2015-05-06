// NumToChineseDlg.cpp : implementation file
//

#include "stdafx.h"
#include "NumToChinese.h"
#include "NumToChineseDlg.h"

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
// CNumToChineseDlg dialog

CNumToChineseDlg::CNumToChineseDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CNumToChineseDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CNumToChineseDlg)
	m_dmoney = 0.0;
	m_strChineseCapital = _T("");
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CNumToChineseDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CNumToChineseDlg)
	DDX_Text(pDX, IDC_EDIT1, m_dmoney);
	DDX_Text(pDX, IDC_EDIT2, m_strChineseCapital);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CNumToChineseDlg, CDialog)
	//{{AFX_MSG_MAP(CNumToChineseDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_TRANS, OnTrans)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CNumToChineseDlg message handlers

BOOL CNumToChineseDlg::OnInitDialog()
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

void CNumToChineseDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CNumToChineseDlg::OnPaint() 
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
HCURSOR CNumToChineseDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CNumToChineseDlg::OnTrans() 
{
	// TODO: Add your control notification handler code here
	UpdateData(true);
	m_strChineseCapital=ChineseCapitalMoney(m_dmoney);
	UpdateData(false);


}
//���������ͽ��������Ĵ�д���

CString CNumToChineseDlg::ChineseCapitalMoney(double Num)
{
	CString szChMoney,szNum; 
	int iLen, iNum, iAddZero=0;
	TCHAR* hzUnit[18]={_T("��"),_T("��"),_T("Ԫ"),_T("ʰ"),_T("��"),_T("Ǫ"),_T("��"),_T("ʰ"),_T("��"),_T("Ǫ"),_T("��"),_T("ʰ"),_T("��"),_T("Ǫ"),_T("��"),_T("ʰ"),_T("��"),_T("Ǫ")};
	TCHAR* hzNum[10]={_T("��"),_T("Ҽ"),_T("��"),_T("��"),_T("��"),_T("��"),_T("½"),_T("��"),_T("��"),_T("��")};
	szNum.Format(_T("%18.0f"), Num*100); //ֻ�ǵ���
	szNum.TrimLeft();
	iLen=szNum.GetLength();
	if(iLen>15 || iLen==0 || Num<0)return ""; //���ݴ��󷵻�

	for(int i=0;i<iLen;i++)
	{
		iNum=_ttoi((LPCTSTR)szNum.Mid(i,1));
		if(iNum==0)//���Ϊ0
			iAddZero++;
		else
		{
			if(iAddZero>0) 
				szChMoney+=_T("��");
			szChMoney+=hzNum[iNum];//ת��Ϊ��Ӧ������
			iAddZero=0;
		}   
		if(iNum!=0||iLen-i==3||iLen-i==11||((iLen-i+1)%8==0&&iAddZero<4))
		szChMoney+=hzUnit[iLen-i-1];//�����Ӧ�ĺ���
	}
	if(szNum.Right(2)==_T("00")) //û�нǺͷ�
	 szChMoney+=_T("��");
	return szChMoney;
}
