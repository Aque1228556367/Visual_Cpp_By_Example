// BrushDemoView.cpp : implementation of the CBrushDemoView class
//

#include "stdafx.h"
#include "BrushDemo.h"

#include "BrushDemoDoc.h"
#include "BrushDemoView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CBrushDemoView

IMPLEMENT_DYNCREATE(CBrushDemoView, CView)

BEGIN_MESSAGE_MAP(CBrushDemoView, CView)
	//{{AFX_MSG_MAP(CBrushDemoView)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBrushDemoView construction/destruction

CBrushDemoView::CBrushDemoView()
{
	// TODO: add construction code here

}

CBrushDemoView::~CBrushDemoView()
{
}

BOOL CBrushDemoView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CBrushDemoView drawing

void CBrushDemoView::OnDraw(CDC* pDC)
{
	CBrushDemoDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
	CBrush brush[8], *pOldBrush;
	//����ʵ��ˢ��
	brush[0].CreateSolidBrush(RGB(200, 0, 200));
	//����һ��������ʽHS_BDIAGONAL ��ˢ��
	brush[1].CreateHatchBrush(HS_BDIAGONAL, RGB(128, 0, 0));
	//����һ��������ʽHS_CROSS��ˢ��
	brush[2].CreateHatchBrush(HS_CROSS, RGB(0, 0, 128));
	//����һ��������ʽHS_DIAGCROSS��ˢ��
	brush[3].CreateHatchBrush(HS_DIAGCROSS, RGB(0, 128, 0));
	//����һ��������ʽHS_FDIAGONAL��ˢ��
	brush[4].CreateHatchBrush(HS_FDIAGONAL, RGB(128, 128, 0 ));
	//����һ��������ʽHS_VERTICAL��ˢ��
	brush[5].CreateHatchBrush(HS_VERTICAL, RGB(0, 128, 128));
	//����һ��������ʽHS_HORIZONTAL��ˢ��
	brush[6].CreateHatchBrush(HS_HORIZONTAL, RGB(128, 128, 128));
	//����һ��ʹ��λͼͼ����ˢ��
	CBitmap bitmap;
	bitmap.LoadBitmap(IDB_BITMAP1);
	brush[7].CreatePatternBrush(&bitmap);
	pOldBrush=pDC->SelectObject(&brush[0]);					//����ˢ��1
	pDC->Rectangle(10, 10, 160, 110);
	pDC->TextOut(10, 115, "ʵ��ˢ��");
	pDC->SelectObject(&brush[1]);							//����ˢ��2
	pDC->Rectangle(180, 10, 330, 110);
	pDC->TextOut(180, 115, "HS_BDIAGONAL��ʽˢ��");
	pDC->SelectObject(&brush[2]);							//����ˢ��3
	pDC->Rectangle(350, 10, 500, 110);
	pDC->TextOut(350, 115, "HS_CROSS��ʽˢ��");
	pDC->SelectObject(&brush[3]);							//����ˢ��4
	pDC->Rectangle(520, 10, 670, 110);
	pDC->TextOut(520, 115, "HS_DIAGCROSS��ʽˢ��");
	pDC->SelectObject(&brush[4]);							//����ˢ��5
	pDC->Rectangle(10, 140, 160, 240);
	pDC->TextOut(10, 245, "HS_FDIAGONAL��ʽˢ��");	
	pDC->SelectObject(&brush[5]);							//����ˢ��6
	pDC->Rectangle(180, 140, 330, 240);
	pDC->TextOut(180, 245, "HS_VERTICAL��ʽˢ��");
	pDC->SelectObject(&brush[6]);							//����ˢ��7
	pDC->Rectangle(350, 140, 500, 240);
	pDC->TextOut(350, 245, "HS_VERTICAL��ʽˢ��");
	pDC->SelectObject(&brush[7]);							//����ˢ��8
	pDC->Rectangle(520, 140, 670, 240);
	pDC->TextOut(520, 245, "λͼͼ��ˢ��");
	//�ָ��豸�����ĵ�ԭ�л�ˢ
	pDC->SelectObject(pOldBrush);
	//ɾ���������Ļ�ˢ��Դ
	for (int i=0; i<9; i++)
	brush[i].DeleteObject();
}

/////////////////////////////////////////////////////////////////////////////
// CBrushDemoView printing

BOOL CBrushDemoView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CBrushDemoView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CBrushDemoView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CBrushDemoView diagnostics

#ifdef _DEBUG
void CBrushDemoView::AssertValid() const
{
	CView::AssertValid();
}

void CBrushDemoView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CBrushDemoDoc* CBrushDemoView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CBrushDemoDoc)));
	return (CBrushDemoDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CBrushDemoView message handlers
