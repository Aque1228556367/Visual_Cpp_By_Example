// DcDemoView.cpp : implementation of the CDcDemoView class
//

#include "stdafx.h"
#include "DcDemo.h"

#include "DcDemoDoc.h"
#include "DcDemoView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDcDemoView

IMPLEMENT_DYNCREATE(CDcDemoView, CView)

BEGIN_MESSAGE_MAP(CDcDemoView, CView)
	//{{AFX_MSG_MAP(CDcDemoView)
	ON_COMMAND(ID_MENUCIRCLE, OnMenucircle)
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDcDemoView construction/destruction

CDcDemoView::CDcDemoView()
{
	// TODO: add construction code here

}

CDcDemoView::~CDcDemoView()
{
}

BOOL CDcDemoView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CDcDemoView drawing

void CDcDemoView::OnDraw(CDC* pDC)
{
	CDcDemoDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
	pDC->TextOut(10,10,"ʹ��CDC������Ļ��ͼ");		//����ı�
	pDC->Rectangle(30,40,130,140);						//����Ļ�ϻ�һ��������
}

/////////////////////////////////////////////////////////////////////////////
// CDcDemoView printing

BOOL CDcDemoView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CDcDemoView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CDcDemoView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CDcDemoView diagnostics

#ifdef _DEBUG
void CDcDemoView::AssertValid() const
{
	CView::AssertValid();
}

void CDcDemoView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CDcDemoDoc* CDcDemoView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CDcDemoDoc)));
	return (CDcDemoDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CDcDemoView message handlers

void CDcDemoView::OnMenucircle() //�˵�����
{
	// TODO: Add your command handler code here
	CDC*pDC=GetDC();							//ʹ��GetDC()��������CDC���ָ��
	pDC->Ellipse(250,40,350,140);				//��Բ
	ReleaseDC(pDC);							//�ͷ�CDC���ָ��
}
