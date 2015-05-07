// BaseMouseDemoView.cpp : implementation of the CBaseMouseDemoView class
//

#include "stdafx.h"
#include "BaseMouseDemo.h"

#include "BaseMouseDemoDoc.h"
#include "BaseMouseDemoView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CBaseMouseDemoView

IMPLEMENT_DYNCREATE(CBaseMouseDemoView, CView)

BEGIN_MESSAGE_MAP(CBaseMouseDemoView, CView)
	//{{AFX_MSG_MAP(CBaseMouseDemoView)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBaseMouseDemoView construction/destruction

CBaseMouseDemoView::CBaseMouseDemoView()
{
	// TODO: add construction code here
	//��ʼ����Ա����
	bDrag=false;
	ptDown.x=ptDown.y=0;
	ptUp.x=ptUp.y=0;
}

CBaseMouseDemoView::~CBaseMouseDemoView()
{
}

BOOL CBaseMouseDemoView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CBaseMouseDemoView drawing

void CBaseMouseDemoView::OnDraw(CDC* pDC)
{
	CBaseMouseDemoDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
	pDC->TextOut(4,4,"�������������ƶ���꼴�ɻ�����Բ��ֱ���ͷ������");

	CClientDC dc(this);
	CImage image;
	image.Load( _T("btn_0.png") );
	image.Draw(dc, 0, 40, 94, 20);
}

/////////////////////////////////////////////////////////////////////////////
// CBaseMouseDemoView printing

BOOL CBaseMouseDemoView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CBaseMouseDemoView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CBaseMouseDemoView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CBaseMouseDemoView diagnostics

#ifdef _DEBUG
void CBaseMouseDemoView::AssertValid() const
{
	CView::AssertValid();
}

void CBaseMouseDemoView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CBaseMouseDemoDoc* CBaseMouseDemoView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CBaseMouseDemoDoc)));
	return (CBaseMouseDemoDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CBaseMouseDemoView message handlers

void CBaseMouseDemoView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	bDrag=TRUE;
	ptUp=ptDown=point;//��¼��굱ǰλ��
	CView::OnLButtonDown(nFlags, point);
}

void CBaseMouseDemoView::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	if(bDrag)
	{
		ptUp=point;
		DrawCircle();									//����Բ
		bDrag=FALSE;
	}

	CView::OnLButtonUp(nFlags, point);
}

void CBaseMouseDemoView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	if(bDrag)
	{
		ptUp=point;//��¼���ĵ�ǰλ��
		DrawCircle();									//����Բ
	}
	CView::OnMouseMove(nFlags, point);
}

void CBaseMouseDemoView::DrawCircle()
{
	Invalidate(false);
	CClientDC dc(this);							//��ȡ��ǰView��DC
	CRect rect;
	GetClientRect(rect);							//��ȡ�ͻ���������
	CBrush brush(RGB(255,255,255));
	dc.FillRect(rect,&brush);						//��䱳��ɫΪ��ɫ
	//dc.Ellipse(ptDown.x,ptDown.y,ptUp.x,ptUp.y);		//������Բ(���Ͻ�xy,���½�xy)
	dc.Rectangle(ptDown.x, ptDown.y, ptUp.x, ptUp.y);
	//dc.FillRect(ptDown.x, ptDown.y, ptUp.x, ptUp.y, CBrush() );
	//GetBkColor(dc)

	POINT topLeft;
	topLeft.x = ptDown.x;
	topLeft.y = ptDown.y;
	POINT bottomRight;
	bottomRight.x = ptUp.x;
	bottomRight.y = ptUp.y;
	CRect destRect(topLeft, bottomRight);
}