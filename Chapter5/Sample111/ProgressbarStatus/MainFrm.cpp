// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "ProgressbarStatus.h"

#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	//{{AFX_MSG_MAP(CMainFrame)
	ON_WM_CREATE()
	ON_COMMAND(ID_MENUTEST, OnMenutest)
	ON_WM_SIZE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // status line indicator
	ID_INDICATOR_PROGRESS,//��ʾ����������
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

/////////////////////////////////////////////////////////////////////////////
// CMainFrame construction/destruction

CMainFrame::CMainFrame()
{
	// TODO: add member initialization code here
	m_bCreated=false;
	
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP
		| CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}

	if (!m_wndStatusBar.Create(this) ||
		!m_wndStatusBar.SetIndicators(indicators,
		  sizeof(indicators)/sizeof(UINT)))
	{
		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
	}

	// TODO: Delete these three lines if you don't want the toolbar to
	//  be dockable
	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndToolBar);

	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMainFrame message handlers


void CMainFrame::OnMenutest() 
{
	// TODO: Add your command handler code here
	//��øø��ӵľ�������
	CRect rect;
	m_wndStatusBar.GetItemRect(1, &rect);  
	//����������ؼ���δ�������ȴ�����
	if (m_bCreated == FALSE)
	{
		//�����������ؼ�
		m_ProgressBar.Create(WS_VISIBLE|WS_CHILD, rect, &m_wndStatusBar, 1); 
		//���ý���������ֵ��Χ
		m_ProgressBar.SetRange(0,100); 
		//���ý������Ĳ�����Ŀ
		m_ProgressBar.SetStep(1); 
		//�������ؼ������Ѿ���������m_bProgressBarCreated�ó�TRUE
		m_bCreated = TRUE;
	}
	// ģ��һ����ʱ���������
	for (int i = 0; i < 100; i++)
	{
		Sleep(50);
		m_ProgressBar.StepIt();
	}
	AfxMessageBox("���н�����");	
}



void CMainFrame::OnSize(UINT nType, int cx, int cy) 
{
	CFrameWnd::OnSize(nType, cx, cy);
	// TODO: Add your message handler code here
	//����������Ѿ���������������ĳߴ磬����������
	if (m_bCreated)
	{
		RECT rc;
		//�����ʾ������
		m_wndStatusBar.GetItemRect(1, &rc);
		// ���°��Ž������ؼ���λ��
		m_ProgressBar.SetWindowPos(&wndTop, rc.left, rc.top, rc.right - rc.left,rc.bottom - rc.top, 0); 
	}		
}
