// DlgActiveXDemoDlg.cpp : implementation file
//

#include "stdafx.h"
#include "DlgActiveXDemo.h"
#include "DlgActiveXDemoDlg.h"

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
// CDlgActiveXDemoDlg dialog

CDlgActiveXDemoDlg::CDlgActiveXDemoDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgActiveXDemoDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgActiveXDemoDlg)
	m_value = 0.0;
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CDlgActiveXDemoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgActiveXDemoDlg)
	DDX_Control(pDX, IDC_VALUEEDIT, m_edit);
	DDX_Control(pDX, IDC_MSHFLEXGRID1, m_flexgrid);
	DDX_Text(pDX, IDC_VALUEEDIT, m_value);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CDlgActiveXDemoDlg, CDialog)
	//{{AFX_MSG_MAP(CDlgActiveXDemoDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_CAL, OnCal)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgActiveXDemoDlg message handlers

BOOL CDlgActiveXDemoDlg::OnInitDialog()
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
	m_bEditing=false;//��ʼ��
	m_nRow=1;
	m_nCol=1;
	char* colHead[4]={"�绰��","���","ú����","�ϼ�"};
	char* rowHead[4]={"һ��","����","����","����"};
	m_flexgrid.SetRow(0);//��λ������һ��
	for(int nCol=0;nCol<4;nCol++)//�����ͷ
	{
		m_flexgrid.SetCol(nCol+1);
		m_flexgrid.SetText(rowHead[nCol]);
	}
	m_flexgrid.SetCol(0);//��λ������һ��
	for(int nRow=0;nRow<4;nRow++)//�����ͷ
	{
		m_flexgrid.SetRow(nRow+1);
		m_flexgrid.SetText(colHead[nRow]);
	}
	m_edit.ShowWindow(SW_HIDE);//���ر༭��
	m_flexgrid.SetBackColor(RGB(255,200,255));//���ñ���ɫ
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CDlgActiveXDemoDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CDlgActiveXDemoDlg::OnPaint() 
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
HCURSOR CDlgActiveXDemoDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

BEGIN_EVENTSINK_MAP(CDlgActiveXDemoDlg, CDialog)
    //{{AFX_EVENTSINK_MAP(CDlgActiveXDemoDlg)
	ON_EVENT(CDlgActiveXDemoDlg, IDC_MSHFLEXGRID1, -600 /* Click */, OnClickMshflexgrid1, VTS_NONE)
	//}}AFX_EVENTSINK_MAP
END_EVENTSINK_MAP()

void CDlgActiveXDemoDlg::OnClickMshflexgrid1() 
{
	// TODO: Add your control notification handler code here
	CString szText=m_flexgrid.GetText();
	if(!m_bEditing)
	{
		m_nRow=m_flexgrid.GetRow();//��ȡ���ǰ��
		m_nCol=m_flexgrid.GetCol();//��ȡ���ǰ��
		if(m_nRow<4)//�������һ��
		{
			m_bEditing=true;//����༭״̬
			szText=m_flexgrid.GetText();//��ȡ���ԭ��ֵ
			m_value=atof(szText);//ת��Ϊdouble�ʹ����༭�����
			UpdateData(false);//�༭����ʾ���ֵ
			
	        long lRow = m_flexgrid.GetRowSel();//��ȡ������к�
			long lCol = m_flexgrid.GetColSel();  //��ȡ������к�
			CRect rect;
			m_flexgrid.GetWindowRect(rect);  //��ȡ���ؼ��Ĵ��ھ���
			ScreenToClient(rect);             //ת��Ϊ�ͻ�������
			// MSFlexGrid �ؼ��ĺ����ĳ��ȵ�λ��"�(twips)"��
			//��Ҫ����ת��Ϊ���أ�1440 � = 1 Ӣ��
			CDC* pDC =GetDC();
			//�������ص��羵�ת������
			int nTwipsPerDotX = 1440 / pDC->GetDeviceCaps(LOGPIXELSX) ;
			int nTwipsPerDotY = 1440 / pDC->GetDeviceCaps(LOGPIXELSY) ;
			//����ѡ�и�����Ͻǵ����꣨����Ϊ��λ��
			long y = m_flexgrid.GetRowPos(lRow)/nTwipsPerDotY;
			long x = m_flexgrid.GetColPos(lCol)/nTwipsPerDotX;
			//����ѡ�и�ĳߴ磨����Ϊ��λ������1��ʵ�ʵ����У����ּ�1��Ч������
			// long width = m_flexgrid.GetColWidth(lCol)/nTwipsPerDotX+1;
			long height = m_flexgrid.GetRowHeight(lRow)/nTwipsPerDotY+1;
			//�γ�ѡ�и����ڵľ�������
			CRect rc(x,y,x+70,y+height);
			//ת������ԶԻ��������
			rc.OffsetRect(rect.left+1,rect.top+1);
			m_edit.ShowWindow(SW_SHOW);//��ʾ�༭��
			m_edit.MoveWindow(rc,true);
			m_edit.SetFocus();//�༭�򲶻񽹵�
			m_edit.SetSel(0,-1);
		}
	}
	else//�༭���
	{
		int m_nCurrentRow=m_flexgrid.GetRow();//��ȡ���ǰ��
		int m_nCurrentCol=m_flexgrid.GetCol();//��ȡ���ǰ��
		m_flexgrid.SetRow(m_nRow);
		m_flexgrid.SetCol(m_nCol);
		m_flexgrid.SetFocus();//��񲶻񽹵�
		UpdateData(true);//��ȡ�༭��ֵ
		CString str;
		str.Format("%01.2f",m_value);//��ʽ��
		m_flexgrid.SetText(str);//�༭������������Ӧ���
		m_edit.ShowWindow(SW_HIDE);//���ر༭��
		m_bEditing=false;//�˳��༭״̬

	}

}

void CDlgActiveXDemoDlg::OnCal() 
{
	// TODO: Add your control notification handler code here
	if(m_bEditing)//���ڱ༭
	{
		UpdateData(true);//��ȡ�༭��ֵ
		CString str;
		str.Format("%01.2f",m_value);//��ʽ��
		m_flexgrid.SetText(str);//�༭������������Ӧ���
		m_edit.ShowWindow(SW_HIDE);//���ر༭��
		m_bEditing=false;//�˳��༭״̬
	}
	for(int nCol=1;nCol<5;nCol++)
	{
		double dTotal=0;
		m_flexgrid.SetCol(nCol);
		for(int nRow=1;nRow<4;nRow++)
		{
			m_flexgrid.SetRow(nRow);
			CString szCell=m_flexgrid.GetText();
			dTotal+=atof(szCell);//�������
		}
		CString str;
		str.Format("%01.2f",dTotal);//��ʽ��
		m_flexgrid.SetRow(4);//��λ�����һ��
		m_flexgrid.SetText(str);//�༭������������Ӧ���
	}
	
}
