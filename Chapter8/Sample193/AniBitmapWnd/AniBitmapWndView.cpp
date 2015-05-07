// AniBitmapWndView.cpp : implementation of the CAniBitmapWndView class
//

#include "stdafx.h"
#include "AniBitmapWnd.h"

#include "AniBitmapWndDoc.h"
#include "AniBitmapWndView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAniBitmapWndView

IMPLEMENT_DYNCREATE(CAniBitmapWndView, CView)

BEGIN_MESSAGE_MAP(CAniBitmapWndView, CView)
	//{{AFX_MSG_MAP(CAniBitmapWndView)
	ON_WM_ERASEBKGND()
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAniBitmapWndView construction/destruction

CAniBitmapWndView::CAniBitmapWndView()
{
	// TODO: add construction code here
	CBitmap bmp;
	bmp.LoadBitmap(IDB_BITMAP1); ///����λͼ
    m_brushBackground.CreatePatternBrush(&bmp);	///����λͼ��ˢ
}

CAniBitmapWndView::~CAniBitmapWndView()
{
}

BOOL CAniBitmapWndView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CAniBitmapWndView drawing

void CAniBitmapWndView::OnDraw(CDC* pDC)
{
	CAniBitmapWndDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
	pDC->SetBkMode(TRANSPARENT);//���ñ�����ɫģʽΪ͸��ɫ
	pDC->TextOut(10,10,"ʹ��λͼ��������ʵ�ֶ�����ʾ�͹رմ���");
}

/////////////////////////////////////////////////////////////////////////////
// CAniBitmapWndView printing

BOOL CAniBitmapWndView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CAniBitmapWndView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CAniBitmapWndView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CAniBitmapWndView diagnostics

#ifdef _DEBUG
void CAniBitmapWndView::AssertValid() const
{
	CView::AssertValid();
}

void CAniBitmapWndView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CAniBitmapWndDoc* CAniBitmapWndView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CAniBitmapWndDoc)));
	return (CAniBitmapWndDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CAniBitmapWndView message handlers

BOOL CAniBitmapWndView::OnEraseBkgnd(CDC* pDC) 
{
	// TODO: Add your message handler code here and/or call default
	CRect rect;
	GetClientRect(&rect);//ȡ�ÿͻ�����
	pDC->FillRect(&rect,&m_brushBackground);//���ñ���ɫ
	return TRUE;
//	return CView::OnEraseBkgnd(pDC);
}
