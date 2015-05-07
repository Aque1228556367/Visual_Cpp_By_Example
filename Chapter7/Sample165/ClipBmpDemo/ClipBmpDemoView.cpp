// ClipBmpDemoView.cpp : implementation of the CClipBmpDemoView class
//

#include "stdafx.h"
#include "ClipBmpDemo.h"

#include "ClipBmpDemoDoc.h"
#include "ClipBmpDemoView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CClipBmpDemoView

IMPLEMENT_DYNCREATE(CClipBmpDemoView, CView)

BEGIN_MESSAGE_MAP(CClipBmpDemoView, CView)
	//{{AFX_MSG_MAP(CClipBmpDemoView)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CClipBmpDemoView construction/destruction

CClipBmpDemoView::CClipBmpDemoView()
{
	// TODO: add construction code here
	bmp.LoadBitmap(IDB_BITMAP1);
}

CClipBmpDemoView::~CClipBmpDemoView()
{
}

BOOL CClipBmpDemoView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CClipBmpDemoView drawing

void CClipBmpDemoView::OnDraw(CDC* pDC)
{
	CClipBmpDemoDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
	BITMAP Bitmap;
	bmp.GetBitmap(&Bitmap);
	//�����ڴ��豸����
	CDC MemDC;
	MemDC.CreateCompatibleDC(pDC);
	//��λͼѡ���ڴ��豸����
	CBitmap* pOldBmp = MemDC.SelectObject(&bmp);
	//������Բ�βü�����ѡ���ڴ��豸����
	CRgn rgn;
	rgn.CreateEllipticRgn(0,0,Bitmap.bmWidth,Bitmap.bmHeight);
	pDC->SelectClipRgn(&rgn);
	//��ʾ�豸����
	pDC->BitBlt(0,0,Bitmap.bmWidth,Bitmap.bmHeight,&MemDC,0,0,SRCCOPY);
	//��ԭ�ڴ��豸����
	MemDC.SelectObject(pOldBmp);
	MemDC.DeleteDC();
	CClientDC dc(this);
	dc.TextOut(10,170,"ͨ���������ʵ����ʾ��Բλͼ��");
}

/////////////////////////////////////////////////////////////////////////////
// CClipBmpDemoView printing

BOOL CClipBmpDemoView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CClipBmpDemoView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CClipBmpDemoView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CClipBmpDemoView diagnostics

#ifdef _DEBUG
void CClipBmpDemoView::AssertValid() const
{
	CView::AssertValid();
}

void CClipBmpDemoView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CClipBmpDemoDoc* CClipBmpDemoView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CClipBmpDemoDoc)));
	return (CClipBmpDemoDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CClipBmpDemoView message handlers
