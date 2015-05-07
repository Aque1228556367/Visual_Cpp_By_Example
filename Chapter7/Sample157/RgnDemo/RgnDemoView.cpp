// RgnDemoView.cpp : implementation of the CRgnDemoView class
//

#include "stdafx.h"
#include "RgnDemo.h"

#include "RgnDemoDoc.h"
#include "RgnDemoView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRgnDemoView

IMPLEMENT_DYNCREATE(CRgnDemoView, CView)

BEGIN_MESSAGE_MAP(CRgnDemoView, CView)
	//{{AFX_MSG_MAP(CRgnDemoView)
	ON_WM_MOUSEMOVE()
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CRgnDemoView construction/destruction

CRgnDemoView::CRgnDemoView()
{
	// TODO: add construction code here
	rgnA.CreateRectRgn(0,0,0,0);						//������ʼ��������ֵ����
	rgnB.CreateRectRgn(0,0,0,0);						//������ʼ��������ֵ����
	str="";
}

CRgnDemoView::~CRgnDemoView()
{
}

BOOL CRgnDemoView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CRgnDemoView drawing

void CRgnDemoView::OnDraw(CDC* pDC)
{
	CRgnDemoDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
	pDC->TextOut(10,270,str);						//����ı�
	CRgn rgn1,rgn2; 								//����CRgn����
	rgn1.CreateRectRgn(20,70,200,120);	 				//��������
	rgn2.CreateEllipticRgn(50,25,150,250); 				//��Բ����
	rgnA.CombineRgn(&rgn1,&rgn2,RGN_AND); 			//��������Ľ���
	rgnB.CombineRgn(&rgn1,&rgn2,RGN_XOR); 			//�������������
	pDC->SelectClipRgn(&rgnA);						//��rgnA����Ϊ�������� 
	CRect rect(0,0,400,400); 
	CBrush brush,brush2; 
	brush.CreateSolidBrush(RGB(255,0,0)); 
	CBrush *poldBrush = pDC->SelectObject(&brush); 		//ѡ���Զ��廭ˢ 
	pDC->Rectangle(&rect); 							//��������
	pDC->SelectObject(poldBrush); 						//��ˢ�ָ�ԭֵ 
	pDC->SelectClipRgn(&rgnB);						//��rgnB����Ϊ�������� 
	brush2.CreateHatchBrush(HS_DIAGCROSS, RGB(0, 128, 128)); 	//ѡ���Զ��廭ˢ
	poldBrush = pDC->SelectObject(&brush2);	 			//ѡ���Զ��廭ˢ 
	pDC->Rectangle(&rect); 							//��������
	pDC->SelectObject(poldBrush); 						//��ˢ�ָ�ԭֵ 
	brush.DeleteObject();
	brush2.DeleteObject();
}

/////////////////////////////////////////////////////////////////////////////
// CRgnDemoView printing

BOOL CRgnDemoView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CRgnDemoView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CRgnDemoView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CRgnDemoView diagnostics

#ifdef _DEBUG
void CRgnDemoView::AssertValid() const
{
	CView::AssertValid();
}

void CRgnDemoView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CRgnDemoDoc* CRgnDemoView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CRgnDemoDoc)));
	return (CRgnDemoDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CRgnDemoView message handlers

void CRgnDemoView::OnMouseMove(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	if (rgnA.PtInRegion(point))							//���λ��������A��
	{
			str="���λ������ͼ�εĽ�������";
	}
	else if (rgnB.PtInRegion(point))					//���λ��������B��
	{
			str="���λ������ͼ�εĽ�����������";;
	}
	else
	{
		str="��겻������ͼ�ε�������";
	}
	CRect rect(0,250,400,300);//�趨�������򣬼��ı�����
	InvalidateRect(&rect);//���´���
	CView::OnMouseMove(nFlags, point);
}
