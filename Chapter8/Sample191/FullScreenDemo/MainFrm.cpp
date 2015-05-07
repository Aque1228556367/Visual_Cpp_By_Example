// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "FullScreenDemo.h"

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
	ON_COMMAND(ID_FULLSCREEN, OnFullscreen)
	ON_WM_GETMINMAXINFO()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // status line indicator
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

/////////////////////////////////////////////////////////////////////////////
// CMainFrame construction/destruction

CMainFrame::CMainFrame()
{
	// TODO: add member initialization code here
	m_bFullScreen=false;	
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


void CMainFrame::OnFullscreen() 
{
	// TODO: Add your command handler code here
	GetWindowPlacement(&m_OldWndPlacement);//��ȡ����λ��
	CRect WindowRect;
	GetWindowRect(&WindowRect);//��ȡ���ڴ�С
	CRect ClientRect;
	RepositionBars(0, 0xffff, AFX_IDW_PANE_FIRST, reposQuery, &ClientRect);//��ȡ���������ڵĴ�С
	ClientToScreen(&ClientRect);//ת��Ϊ��Ļ����
	//��ȡ��Ļ�ķֱ���
	int nFullWidth=GetSystemMetrics(SM_CXSCREEN);
	int nFullHeight=GetSystemMetrics(SM_CYSCREEN);
	//������������Ŀͻ���ȫ����ʾ����(0,0)��(nFullWidth, nFullHeight)����, ��(0,0)��(nFullWidth, nFullHeight)������������ԭ���ںͳ�������֮��Ŀͻ���λ�ü�Ĳ�ֵ, �͵õ�ȫ����ʾ�Ĵ���λ��
	m_FullScreenRect.left=WindowRect.left-ClientRect.left;
	m_FullScreenRect.top=WindowRect.top-ClientRect.top;
	m_FullScreenRect.right=WindowRect.right-ClientRect.right+nFullWidth;
	m_FullScreenRect.bottom=WindowRect.bottom-ClientRect.bottom+nFullHeight;
	m_bFullScreen=TRUE; //����ȫ����ʾ��־Ϊ TRUE
	//����ȫ����ʾ״̬
	WINDOWPLACEMENT wndpl;
	wndpl.length=sizeof(WINDOWPLACEMENT);
	wndpl.flags=0;
	wndpl.showCmd=SW_SHOWNORMAL;
	wndpl.rcNormalPosition=m_FullScreenRect;
	SetWindowPlacement(&wndpl);
}

void CMainFrame::OnGetMinMaxInfo(MINMAXINFO FAR* lpMMI) 
{
	// TODO: Add your message handler code here and/or call default
	if(m_bFullScreen)
	{
		//ȫ����ʾ�Ĵ�С
		lpMMI->ptMaxSize.x=m_FullScreenRect.Width();
		lpMMI->ptMaxSize.y=m_FullScreenRect.Height();
		//ȫ����ʾ��λ��
		lpMMI->ptMaxPosition.x=m_FullScreenRect.Width();
		lpMMI->ptMaxPosition.y=m_FullScreenRect.Height();
		//����Track�ߴ�ҲҪ�ı�
		lpMMI->ptMaxTrackSize.x=m_FullScreenRect.Width();
		lpMMI->ptMaxTrackSize.y=m_FullScreenRect.Height();
	}
	CFrameWnd::OnGetMinMaxInfo(lpMMI);
}

void CMainFrame::EndFullScreen()
{
	if(m_bFullScreen)
	{
		//�˳�ȫ����ʾ, �ָ�ԭ������ʾ
		ShowWindow(SW_HIDE);
		SetWindowPlacement(&m_OldWndPlacement);
	}
}
