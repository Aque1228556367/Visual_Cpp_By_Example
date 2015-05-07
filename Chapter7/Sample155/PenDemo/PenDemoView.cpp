// PenDemoView.cpp : implementation of the CPenDemoView class
//

#include "stdafx.h"
#include "PenDemo.h"

#include "PenDemoDoc.h"
#include "PenDemoView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPenDemoView

IMPLEMENT_DYNCREATE(CPenDemoView, CView)

BEGIN_MESSAGE_MAP(CPenDemoView, CView)
	//{{AFX_MSG_MAP(CPenDemoView)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPenDemoView construction/destruction

CPenDemoView::CPenDemoView()
{
	// TODO: add construction code here

}

CPenDemoView::~CPenDemoView()
{
}

BOOL CPenDemoView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CPenDemoView drawing

void CPenDemoView::OnDraw(CDC* pDC)
{
	CPenDemoDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
	CPen pen[5];
	pen[0].CreatePen(PS_SOLID, 3, RGB(255, 0, 0)); 					//����ʵ�߻���
	pen[1].CreatePen(PS_DASH, 1, RGB(0, 255, 0));	 				//�������߻���
	pen[2].CreatePen(PS_DOT, 1, RGB(0, 0, 255));					//�������߻���
	pen[3].CreatePen(PS_DASHDOT, 1, RGB(0, 255, 255));				//�����㻮�߻���
	pen[4].CreatePen(PS_DASHDOTDOT, 1, RGB(255, 0, 255)); 			//����˫�㻮�߻���	
	// ����ָ���豸������ԭ�л��ʵ�ָ��
	CPen *pOldPen;
	//��ʵ�߻��ʻ��ƾ���
	pOldPen=pDC->SelectObject(&pen[0]);
	pDC->Rectangle(10, 10, 110, 110);
	pDC->TextOut(10, 115, "���ƾ���");
	//ʹ�����߻��ʺͺ���Polyline����������
	pDC->SelectObject(&pen[1]);								//�������߻���
	CPoint pts[]={CPoint(190, 20), CPoint(200, 60), CPoint(270, 40), CPoint(210, 80), 
	CPoint(250, 100), CPoint(300, 30), CPoint(310, 80)};
	pDC->Polyline(pts, 7);										//���ƶ������
	pDC->TextOut(180, 115, "���ƶ������");	
	// ʹ��Pie��Arc�����ͼ�ͻ���
	pDC->SelectObject(&pen[2]);								//������߻���
	pDC->Ellipse(10, 140, 160, 240);						//������Բ
	pDC->SelectObject(&pen[3]);								//����㻮�߻���
	pDC->Pie(20, 150, 150, 230, 160, 160, 10, 160);
	pDC->SelectObject(&pen[4]);								//����˫�㻮�߻���
	pDC->Arc(20, 150, 150, 230, 10, 220, 160, 220);
	pDC->TextOut(10, 245, "������Բ�����κͱ�ͼ");
	pDC->SetTextColor(RGB(0,0,255));
	pDC->TextOut(220, 200, "ʹ�ò�ͬ�Ļ��ʻ��Ƹ���ͼ��");
	//�ָ��豸�����ĵ�ԭ�л���
	pDC->SelectObject(pOldPen);
	//ɾ���������Ļ�����Դ
	for (int i=0; i<5; i++)
	pen[i].DeleteObject();
}

/////////////////////////////////////////////////////////////////////////////
// CPenDemoView printing

BOOL CPenDemoView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CPenDemoView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CPenDemoView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CPenDemoView diagnostics

#ifdef _DEBUG
void CPenDemoView::AssertValid() const
{
	CView::AssertValid();
}

void CPenDemoView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CPenDemoDoc* CPenDemoView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CPenDemoDoc)));
	return (CPenDemoDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CPenDemoView message handlers
