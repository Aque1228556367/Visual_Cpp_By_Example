// PrintRealDemo2View.cpp : implementation of the CPrintRealDemo2View class
//

#include "stdafx.h"
#include "PrintRealDemo2.h"

#include "PrintRealDemo2Doc.h"
#include "PrintRealDemo2View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPrintRealDemo2View

IMPLEMENT_DYNCREATE(CPrintRealDemo2View, CView)

BEGIN_MESSAGE_MAP(CPrintRealDemo2View, CView)
	//{{AFX_MSG_MAP(CPrintRealDemo2View)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPrintRealDemo2View construction/destruction

CPrintRealDemo2View::CPrintRealDemo2View()
{
	// TODO: add construction code here

}

CPrintRealDemo2View::~CPrintRealDemo2View()
{
}

BOOL CPrintRealDemo2View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CPrintRealDemo2View drawing

void CPrintRealDemo2View::OnDraw(CDC* pDC)
{
	CPrintRealDemo2Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here	
	if(pDC->IsPrinting())//�ж��Ƿ����ӡ���ӡԤ��������OnPrepareDC()����
	{
		pDC->SetViewportOrg(250,400);//�����ӿ�����ԭ��
	}
	//����Ϊ��ʾ�ʹ�ӡ������
	pDC->TextOut(10,10,"ʵ�����������õĴ�ӡ");
	pDC->SetBkMode(TRANSPARENT);
	pDC->Rectangle(10,40,310,350);
	pDC->Ellipse(50,50,210,220);
	pDC->Ellipse(70,240,280,320);
}

/////////////////////////////////////////////////////////////////////////////
// CPrintRealDemo2View printing

BOOL CPrintRealDemo2View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CPrintRealDemo2View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CPrintRealDemo2View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CPrintRealDemo2View diagnostics

#ifdef _DEBUG
void CPrintRealDemo2View::AssertValid() const
{
	CView::AssertValid();
}

void CPrintRealDemo2View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CPrintRealDemo2Doc* CPrintRealDemo2View::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CPrintRealDemo2Doc)));
	return (CPrintRealDemo2Doc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CPrintRealDemo2View message handlers

void CPrintRealDemo2View::OnPrepareDC(CDC* pDC, CPrintInfo* pInfo) 
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
