// FullScreenDemoView.cpp : implementation of the CFullScreenDemoView class
//

#include "stdafx.h"
#include "FullScreenDemo.h"

#include "FullScreenDemoDoc.h"
#include "FullScreenDemoView.h"

#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CFullScreenDemoView

IMPLEMENT_DYNCREATE(CFullScreenDemoView, CView)

BEGIN_MESSAGE_MAP(CFullScreenDemoView, CView)
	//{{AFX_MSG_MAP(CFullScreenDemoView)
	ON_WM_KEYDOWN()
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFullScreenDemoView construction/destruction

CFullScreenDemoView::CFullScreenDemoView()
{
	// TODO: add construction code here

}

CFullScreenDemoView::~CFullScreenDemoView()
{
}

BOOL CFullScreenDemoView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CFullScreenDemoView drawing

void CFullScreenDemoView::OnDraw(CDC* pDC)
{
	CFullScreenDemoDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
	pDC->TextOut(10,10,"ִ��ȫ����ʾ�˵��������ʵ�ֿͻ����ڵ�ȫ����ʾ");
	pDC->TextOut(10,40,"����ESC�����ָ���������ʾ��״̬");
}

/////////////////////////////////////////////////////////////////////////////
// CFullScreenDemoView printing

BOOL CFullScreenDemoView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CFullScreenDemoView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CFullScreenDemoView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CFullScreenDemoView diagnostics

#ifdef _DEBUG
void CFullScreenDemoView::AssertValid() const
{
	CView::AssertValid();
}

void CFullScreenDemoView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CFullScreenDemoDoc* CFullScreenDemoView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CFullScreenDemoDoc)));
	return (CFullScreenDemoDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CFullScreenDemoView message handlers

void CFullScreenDemoView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	// TODO: Add your message handler code here and/or call default
	if(nChar==VK_ESCAPE)//������ļ�ΪEsc��
	{
		//��ȡ����ܴ��ڵ�ָ��
		CMainFrame *pFrame=(CMainFrame*)AfxGetApp()->m_pMainWnd;
		//��������������Զ��庯�� EndFullScreen ���˳�ȫ����ʾ״̬
		pFrame->EndFullScreen();
	}
	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}
