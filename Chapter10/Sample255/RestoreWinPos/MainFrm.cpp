// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "RestoreWinPos.h"

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
	ON_WM_CLOSE()
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
	CWinApp* pApp = AfxGetApp();
    int s, t, b, r, l;	
	//�����ע����ж��������ݲ�Ϊ��
    if ( -1 != (s = pApp->GetProfileInt("RestoreFrame", "Status",-1)) &&
		-1 != (t = pApp->GetProfileInt("RestoreFrame", "Top",-1)) &&
		-1 != (l = pApp->GetProfileInt("RestoreFrame", "Left",-1)) &&
		-1 != (b = pApp->GetProfileInt("RestoreFrame", "Bottom",-1)) &&
		-1 != (r = pApp->GetProfileInt("RestoreFrame", "Right",-1))
		) 
	{
		
		//�ָ�����״̬
        pApp->m_nCmdShow = s;	
		//�ָ����ڿ�Ⱥ͸߶�
        cs.cx = r - l;
        cs.cy = b - t;
	}
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


void CMainFrame::OnClose() 
{
	// TODO: Add your message handler code here and/or call default
	//����������λ��
    CWinApp* app = AfxGetApp();
    WINDOWPLACEMENT wp;
    GetWindowPlacement(&wp);
	//������λ��д��ע�����
    app->WriteProfileInt("RestoreFrame", "Status",wp.showCmd);
    app->WriteProfileInt("RestoreFrame", "Top", wp.rcNormalPosition.top);
    app->WriteProfileInt("RestoreFrame","Left", wp.rcNormalPosition.left);
    app->WriteProfileInt("RestoreFrame", "Bottom", wp.rcNormalPosition.bottom);
    app->WriteProfileInt("RestoreFrame", "Right", wp.rcNormalPosition.right);
	CFrameWnd::OnClose();
}
