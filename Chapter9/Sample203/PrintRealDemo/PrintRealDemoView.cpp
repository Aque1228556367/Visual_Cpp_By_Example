// PrintRealDemoView.cpp : implementation of the CPrintRealDemoView class
//

#include "stdafx.h"
#include "PrintRealDemo.h"

#include "PrintRealDemoDoc.h"
#include "PrintRealDemoView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPrintRealDemoView

IMPLEMENT_DYNCREATE(CPrintRealDemoView, CView)

BEGIN_MESSAGE_MAP(CPrintRealDemoView, CView)
	//{{AFX_MSG_MAP(CPrintRealDemoView)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPrintRealDemoView construction/destruction

CPrintRealDemoView::CPrintRealDemoView()
{
	// TODO: add construction code here

}

CPrintRealDemoView::~CPrintRealDemoView()
{
}

BOOL CPrintRealDemoView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CPrintRealDemoView drawing

void CPrintRealDemoView::OnDraw(CDC* pDC)
{
	CPrintRealDemoDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
/*	if(pDC->IsPrinting())//�ж��Ƿ����ӡ���ӡԤ��������OnPrepareDC()������
	{
		pDC->SetViewportOrg(200,200);
	}*/
	// TODO: add draw code for native data here
	pDC->TextOut(10,10,"ʵ�����������õĴ�ӡ");
	pDC->SetBkMode(TRANSPARENT);
	pDC->Rectangle(10,40,310,350);
	pDC->Ellipse(50,50,210,220);
	pDC->Ellipse(70,240,280,320);
}

/////////////////////////////////////////////////////////////////////////////
// CPrintRealDemoView printing

BOOL CPrintRealDemoView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CPrintRealDemoView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CPrintRealDemoView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CPrintRealDemoView diagnostics

#ifdef _DEBUG
void CPrintRealDemoView::AssertValid() const
{
	CView::AssertValid();
}

void CPrintRealDemoView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CPrintRealDemoDoc* CPrintRealDemoView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CPrintRealDemoDoc)));
	return (CPrintRealDemoDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CPrintRealDemoView message handlers

void CPrintRealDemoView::OnPrepareDC(CDC* pDC, CPrintInfo* pInfo) 
{
	// TODO: Add your specialized code here and/or call the base class
	
	CView::OnPrepareDC(pDC, pInfo);
	//����ӳ��ģʽ
	pDC->SetMapMode(MM_ANISOTROPIC); 
	CSize winSize = CSize(1024,768);
	pDC->SetWindowExt(winSize); 								//�趨���ڴ�С
	//�õ�ʵ���豸ÿ�߼�Ӣ�����������
	int xLogPixPerInch,yLogPixPerInch;
	xLogPixPerInch=pDC->GetDeviceCaps(LOGPIXELSX); 
	yLogPixPerInch=pDC->GetDeviceCaps(LOGPIXELSY);
	//�õ��豸������߼�����ı��� 
	
	if(pDC->IsPrinting())//��ӡ
	{		
		int xExt,yExt;
		xExt=winSize.cx*600/xLogPixPerInch;					//���մ�ӡ�������ӿ�
		yExt=winSize.cy*600/yLogPixPerInch;
		pDC->SetViewportExt(xExt,yExt);						//�趨�ӿڴ�С
	}
	else//����Ļ��ʾ
		pDC->SetViewportExt(winSize.cx,winSize.cy);	

}
