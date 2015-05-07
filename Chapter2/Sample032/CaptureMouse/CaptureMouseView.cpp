// CaptureMouseView.cpp : implementation of the CCaptureMouseView class
//

#include "stdafx.h"
#include "CaptureMouse.h"

#include "CaptureMouseDoc.h"
#include "CaptureMouseView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCaptureMouseView

IMPLEMENT_DYNCREATE(CCaptureMouseView, CView)

BEGIN_MESSAGE_MAP(CCaptureMouseView, CView)
	//{{AFX_MSG_MAP(CCaptureMouseView)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONDBLCLK()
	ON_WM_LBUTTONUP()
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCaptureMouseView construction/destruction

CCaptureMouseView::CCaptureMouseView()
{
	// TODO: add construction code here

}

CCaptureMouseView::~CCaptureMouseView()
{
}

BOOL CCaptureMouseView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CCaptureMouseView drawing

void CCaptureMouseView::OnDraw(CDC* pDC)
{
	CCaptureMouseDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
	 pDC->TextOut(4,4,"���û��ڿͻ����ڰ���������ʱ����ʵ������겶׽��˫�����������ͷŲ�׽��");
}

/////////////////////////////////////////////////////////////////////////////
// CCaptureMouseView printing

BOOL CCaptureMouseView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CCaptureMouseView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CCaptureMouseView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CCaptureMouseView diagnostics

#ifdef _DEBUG
void CCaptureMouseView::AssertValid() const
{
	CView::AssertValid();
}

void CCaptureMouseView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CCaptureMouseDoc* CCaptureMouseView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CCaptureMouseDoc)));
	return (CCaptureMouseDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CCaptureMouseView message handlers

void CCaptureMouseView::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	SetCapture();//��׽���
	CString s;
	s.Format("�û�������������λ�ã�X=%d,Y=%d",point.x,point.y);
	CClientDC dc(this);										//���DC
	dc.TextOut(30,40,s);						//����ı�
	CView::OnLButtonDown(nFlags, point);
}



void CCaptureMouseView::OnLButtonDblClk(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	ReleaseCapture();//�ͷ����	
	CClientDC dc(this);										//���DC
	dc.TextOut(30,40,"�ͷ�����꣬��ʱ������Ӧ�ͻ����������������");						//����ı�

	CView::OnLButtonDblClk(nFlags, point);
}

void CCaptureMouseView::OnLButtonUp(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	CString s;
	s.Format("�û��ɿ���������λ�ã�X=%d,Y=%d",point.x,point.y);
	CClientDC dc(this);										//���DC
	dc.TextOut(30,80,s);						//����ı�
	
	CView::OnLButtonUp(nFlags, point);
}
