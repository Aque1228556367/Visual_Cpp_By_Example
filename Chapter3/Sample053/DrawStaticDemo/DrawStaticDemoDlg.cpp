// DrawStaticDemoDlg.cpp : implementation file
//

#include "stdafx.h"
#include "DrawStaticDemo.h"
#include "DrawStaticDemoDlg.h"

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
// CDrawStaticDemoDlg dialog

CDrawStaticDemoDlg::CDrawStaticDemoDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CDrawStaticDemoDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDrawStaticDemoDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CDrawStaticDemoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDrawStaticDemoDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CDrawStaticDemoDlg, CDialog)
	//{{AFX_MSG_MAP(CDrawStaticDemoDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_DRAW, OnStaticDraw)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDrawStaticDemoDlg message handlers

BOOL CDrawStaticDemoDlg::OnInitDialog()
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

void CDrawStaticDemoDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CDrawStaticDemoDlg::OnPaint() 
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
HCURSOR CDrawStaticDemoDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CDrawStaticDemoDlg::OnStaticDraw() 
{
	// TODO: Add your control notification handler code here
    CWnd* pWnd=GetDlgItem(IDC_STATICDRAW);
    CDC* pDC=pWnd->GetDC();
    pWnd->Invalidate();
    pWnd->UpdateWindow();
    pDC->Rectangle(0,0,200,200);
    //�������ʶ���**************��X��Y��
    CPen* pPenRed=new CPen;
    pPenRed->CreatePen(PS_SOLID,2,RGB(255,0,0));
    CGdiObject* pOldPen=pDC->SelectObject(pPenRed);
    pDC->MoveTo(10,10);
    pDC->LineTo(10,180);
    pDC->LineTo(180,180);
    //дX���ֵ
    CString str;
    str.Format("0");
    pDC->SetTextColor(RGB(0,255,0));
    pDC->TextOut(10,183,str);
    str.Format("50");
    pDC->TextOut(60,183,str);
    str.Format("100");
    pDC->TextOut(110,183,str);
    str.Format("150");
    pDC->TextOut(160,183,str);
    //дX��̶���
    for(int  i=0;i<156;i+=5)
    {
        if((i&1)==0)
        {//10�ı���
            pDC->MoveTo(i+10,180);
            pDC->LineTo(i+10,184);
        }
        else
        {
            pDC->MoveTo(i+10,180);
            pDC->LineTo(i+10,182);

        }
    }
	//ʹ����ɫ���ʻ�����Բ
	CPen* pPenBlue=new CPen;
    pPenBlue->CreatePen(PS_SOLID,2,RGB(0,0,255));
	pDC->SelectObject(pPenBlue);
	pDC->Ellipse(50,50,140,120);
    pDC->SelectObject(pOldPen);//����ԭ����
    //ɾ���µĻ���
    delete pPenRed;
	delete pPenBlue;
}
