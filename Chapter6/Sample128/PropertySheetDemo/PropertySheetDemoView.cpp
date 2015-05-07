// PropertySheetDemoView.cpp : implementation of the CPropertySheetDemoView class
//

#include "stdafx.h"
#include "PropertySheetDemo.h"

#include "PropertySheetDemoDoc.h"
#include "PropertySheetDemoView.h"

#include "ShapePage.h"
#include "ColorPage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPropertySheetDemoView

IMPLEMENT_DYNCREATE(CPropertySheetDemoView, CView)

BEGIN_MESSAGE_MAP(CPropertySheetDemoView, CView)
	//{{AFX_MSG_MAP(CPropertySheetDemoView)
	ON_COMMAND(ID_MENUSET, OnMenuset)
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPropertySheetDemoView construction/destruction

CPropertySheetDemoView::CPropertySheetDemoView()
{
	// TODO: add construction code here
	m_r=100;
	m_g=0;
	m_b=128;
	m_type=0;
}

CPropertySheetDemoView::~CPropertySheetDemoView()
{
}

BOOL CPropertySheetDemoView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CPropertySheetDemoView drawing

void CPropertySheetDemoView::OnDraw(CDC* pDC)
{
	CPropertySheetDemoDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
	pDC->TextOut(10,10,"ͨ��ִ��ͼ��|���Բ˵������Ե������Ա�����ͼ�����ԣ�");
	CBrush mybrush(RGB(m_r,m_g,m_b));						//����ˢ��
	CBrush *oldbrush;								//����ˢ��ָ��
	oldbrush=pDC->SelectObject(&mybrush);				//��ˢ��ѡ���豸����
	switch (m_type)
	{
		case 0:
			pDC->Rectangle(50,50,220,220);			//����������
			break;
		case 1:
			pDC->Ellipse(50,50,220,220);						//����Բ
			break;
	}
	pDC->SelectObject(oldbrush);						//�ָ�ԭ��ˢ��
}

/////////////////////////////////////////////////////////////////////////////
// CPropertySheetDemoView printing

BOOL CPropertySheetDemoView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CPropertySheetDemoView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CPropertySheetDemoView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CPropertySheetDemoView diagnostics

#ifdef _DEBUG
void CPropertySheetDemoView::AssertValid() const
{
	CView::AssertValid();
}

void CPropertySheetDemoView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CPropertySheetDemoDoc* CPropertySheetDemoView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CPropertySheetDemoDoc)));
	return (CPropertySheetDemoDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CPropertySheetDemoView message handlers

void CPropertySheetDemoView::OnMenuset() 
{
	// TODO: Add your command handler code here
	CPropertySheet propsheet("ͼ�ζ�������");//CPropertySheet�����
	CShapePage pageFirst; //ͼ������ҳ����
	CColorPage pageSecond; //��ˢɫ��������ҳ����
	//����ǰͼ�λ�ˢ��Ϣ��������ҳ
	pageFirst.m_radio=m_type;
	pageSecond.m_r=m_r;
	pageSecond.m_g=m_g;
	pageSecond.m_b=m_b; 
	//�������ҳ��CPropertySheet�����
	propsheet.AddPage(&pageFirst);
	propsheet.AddPage(&pageSecond);
	//����ģ̬���Ա�Ի���
	if (propsheet.DoModal() == IDOK)
	{
		//��ȡ������ҳ���õ�ֵ
		m_type = pageFirst.m_radio;
		m_r=pageSecond.m_r;
		m_g=pageSecond.m_g;
		m_b=pageSecond.m_b; 
		Invalidate(true);//�ػ�ͻ�����
	}	
}
