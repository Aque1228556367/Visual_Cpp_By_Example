// MirroBmpDemoView.cpp : implementation of the CMirroBmpDemoView class
//

#include "stdafx.h"
#include "MirroBmpDemo.h"

#include "MirroBmpDemoDoc.h"
#include "MirroBmpDemoView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMirroBmpDemoView

IMPLEMENT_DYNCREATE(CMirroBmpDemoView, CView)

BEGIN_MESSAGE_MAP(CMirroBmpDemoView, CView)
	//{{AFX_MSG_MAP(CMirroBmpDemoView)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMirroBmpDemoView construction/destruction

CMirroBmpDemoView::CMirroBmpDemoView()
{
	// TODO: add construction code here
	m_Bitmap.LoadBitmap(IDB_BITMAP1);//����λͼ
}

CMirroBmpDemoView::~CMirroBmpDemoView()
{
}

BOOL CMirroBmpDemoView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CMirroBmpDemoView drawing

void CMirroBmpDemoView::OnDraw(CDC* pDC)
{
	CMirroBmpDemoDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
	int nWidth, nHeight;
	CDC *pMemDC = new CDC;
	pMemDC->CreateCompatibleDC(pDC);	//��������ʾ�豸���ݵ��ڴ��豸����
	//��ȡλͼ�ߴ�
	BITMAP bm;
	m_Bitmap.GetBitmap(&bm);
	nWidth = bm.bmWidth;
	nHeight = bm.bmHeight;	
	CBitmap *m_pBitmap = (CBitmap *) pMemDC->SelectObject(&m_Bitmap);	//��λͼѡ���ڴ泡��
	pDC->BitBlt(25,25,nWidth,nHeight,pMemDC,0,0,SRCCOPY);//��ʾλͼ
	CPen pen, *pOldPen;
	pen.CreatePen(PS_DASH, 1, RGB(0, 0, 255));	 				//�������߻���
	pOldPen=pDC->SelectObject(&pen);
	//����Y��
	pDC->MoveTo(25+nWidth+10,25);
	pDC->LineTo(25+nWidth+10,350);
	//��Y�᾵����ʾλͼ
	pDC->StretchBlt(25+nWidth+20 , 25, nWidth, nHeight, pMemDC, 
		nWidth-1, 0, -nWidth, nHeight, SRCCOPY );
	pDC->TextOut(25+nWidth+60, 25+nHeight+10, "Y�᾵��ͼ��");
	//����X��
	pDC->MoveTo(25,25+nHeight+10);
	pDC->LineTo(500,25+nHeight+10);
	//��X�᾵����ʾλͼ
	pDC->StretchBlt(25, 25+nHeight+20, nWidth, nHeight, pMemDC, 
		0, nHeight-1, nWidth, -nHeight, SRCCOPY );
	pDC->TextOut(80, 25+2*nHeight+20, "X�᾵��ͼ��");
	//�ָ��豸�����ĵ�ԭ�л���
	pDC->SelectObject(pOldPen);
	pen.DeleteObject();
	delete pMemDC;
}

/////////////////////////////////////////////////////////////////////////////
// CMirroBmpDemoView printing

BOOL CMirroBmpDemoView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CMirroBmpDemoView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CMirroBmpDemoView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CMirroBmpDemoView diagnostics

#ifdef _DEBUG
void CMirroBmpDemoView::AssertValid() const
{
	CView::AssertValid();
}

void CMirroBmpDemoView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMirroBmpDemoDoc* CMirroBmpDemoView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMirroBmpDemoDoc)));
	return (CMirroBmpDemoDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMirroBmpDemoView message handlers
