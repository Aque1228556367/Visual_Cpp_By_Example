// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "StaticSplitWnd3.h"
#include "MainFrm.h"

#include "StaticSplitWnd3View.h"
#include "View2.h"
#include "View3.h"
#include "View4.h"

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
	ON_COMMAND(ID_CHANGESIZE, OnChangesize)
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


BOOL CMainFrame::OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext) 
{	
	m_wndSplitter1.Lock();//�����ָ���
	m_wndSplitter2.UnLock();//�������ָ���
	//����һ����̬�������ڣ���Ϊ����һ�� 
    if(m_wndSplitter1.CreateStatic(this,3,1)==NULL) 
      return FALSE;
    //��CStaticSplitWnd3View���ӵ�0��0�д�����
    m_wndSplitter1.CreateView(0,0,RUNTIME_CLASS(CStaticSplitWnd3View),CSize(100,50), pContext); 
	m_wndSplitter1.CreateView(1,0,RUNTIME_CLASS(CView2),CSize(100,50),pContext); //��CView2���ӵ�1��0��
    if(m_wndSplitter2.CreateStatic(&m_wndSplitter1,1,2,WS_CHILD|WS_VISIBLE, m_wndSplitter1.IdFromRowCol(2, 0))==NULL) 
      return FALSE; //����2��0���ٷֿ�1��2�� 
    //��CView3�����ӵ��ڶ������������0��0��
    m_wndSplitter2.CreateView(0,0,RUNTIME_CLASS(CView3),CSize(400,300),pContext); 
	//��CView4�����ӵ��ڶ������������0��1��
    m_wndSplitter2.CreateView(0,1,RUNTIME_CLASS(CView4),CSize(400,300),pContext);   
	return TRUE; 
//	return CFrameWnd::OnCreateClient(lpcs, pContext);
}

void CMainFrame::OnChangesize() 
{
	// TODO: Add your command handler code here
	CRect rect;
	GetClientRect(&rect);//��ȡ�ͻ����ڳߴ�
	m_wndSplitter1.SetRowInfo(0,rect.Height()/2,10);//��0�д�������Ϊ�ͻ����ڸ߶ȵ�һ��
	m_wndSplitter1.RecalcLayout();//���´���ߴ�
}
