// BitmapDemoView.cpp : implementation of the CBitmapDemoView class
//

#include "stdafx.h"
#include "BitmapDemo.h"

#include "BitmapDemoDoc.h"
#include "BitmapDemoView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CBitmapDemoView

IMPLEMENT_DYNCREATE(CBitmapDemoView, CView)

BEGIN_MESSAGE_MAP(CBitmapDemoView, CView)
	//{{AFX_MSG_MAP(CBitmapDemoView)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBitmapDemoView construction/destruction

CBitmapDemoView::CBitmapDemoView()
{
	// TODO: add construction code here

}

CBitmapDemoView::~CBitmapDemoView()
{
}

BOOL CBitmapDemoView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CBitmapDemoView drawing

void CBitmapDemoView::OnDraw(CDC* pDC)
{
	CBitmapDemoDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
	CBitmap bitmap;										//����CBitmap����
	CDC dcMemory;							
	bitmap.LoadBitmap(IDB_BITMAP1);						//����λͼ��Դ
	dcMemory.CreateCompatibleDC(pDC);						//�����ڴ��豸����
	dcMemory.SelectObject(& bitmap);						//��λͼѡ���ڴ��豸������
	pDC->BitBlt(0,0,200,150,&dcMemory,0,0,SRCCOPY);	//���ڴ��豸�������Ƶ���ǰ�豸������
	pDC->TextOut(40,170,"ԭʼλͼͼ��");
	pDC->StretchBlt(210,0,300,226,&dcMemory,0,0,200,150,SRCCOPY);	//�Ŵ�1.5����ʾλͼ
	pDC->TextOut(280,240,"�Ŵ�1.5�����ͼ��");
}

/////////////////////////////////////////////////////////////////////////////
// CBitmapDemoView printing

BOOL CBitmapDemoView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CBitmapDemoView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CBitmapDemoView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CBitmapDemoView diagnostics

#ifdef _DEBUG
void CBitmapDemoView::AssertValid() const
{
	CView::AssertValid();
}

void CBitmapDemoView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CBitmapDemoDoc* CBitmapDemoView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CBitmapDemoDoc)));
	return (CBitmapDemoDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CBitmapDemoView message handlers
