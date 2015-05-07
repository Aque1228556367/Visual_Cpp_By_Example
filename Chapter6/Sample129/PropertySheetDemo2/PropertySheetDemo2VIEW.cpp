// PropertySheetDemo2View.cpp : implementation of the CPropertySheetDemo2View class
//

#include "stdafx.h"
#include "PropertySheetDemo2.h"

#include "PropertySheetDemo2Doc.h"
#include "PropertySheetDemo2View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPropertySheetDemo2View

IMPLEMENT_DYNCREATE(CPropertySheetDemo2View, CView)

BEGIN_MESSAGE_MAP(CPropertySheetDemo2View, CView)
	//{{AFX_MSG_MAP(CPropertySheetDemo2View)
	ON_COMMAND(ID_MENUSET, OnMenuset)
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)

	ON_MESSAGE(WM_USER_APPLY, OnApply)//�����Ϣӳ��
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPropertySheetDemo2View construction/destruction

CPropertySheetDemo2View::CPropertySheetDemo2View():m_Sheet("ͼ����������")
{
	// TODO: add construction code here
	m_r=100;
	m_g=0;
	m_b=128;
	m_type=0;
}

CPropertySheetDemo2View::~CPropertySheetDemo2View()
{
}

BOOL CPropertySheetDemo2View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CPropertySheetDemo2View drawing

void CPropertySheetDemo2View::OnDraw(CDC* pDC)
{
	CPropertySheetDemo2Doc* pDoc = GetDocument();
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
// CPropertySheetDemo2View printing

BOOL CPropertySheetDemo2View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CPropertySheetDemo2View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CPropertySheetDemo2View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CPropertySheetDemo2View diagnostics

#ifdef _DEBUG
void CPropertySheetDemo2View::AssertValid() const
{
	CView::AssertValid();
}

void CPropertySheetDemo2View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CPropertySheetDemo2Doc* CPropertySheetDemo2View::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CPropertySheetDemo2Doc)));
	return (CPropertySheetDemo2Doc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CPropertySheetDemo2View message handlers

void CPropertySheetDemo2View::OnMenuset() 
{
	// TODO: Add your command handler code here
	//����ǰͼ�λ�ˢ��Ϣ��������ҳ
	m_Sheet.pageFirst.m_radio=m_type;
	m_Sheet.pageSecond.m_r=m_r;
	m_Sheet.pageSecond.m_g=m_g;
	m_Sheet.pageSecond.m_b=m_b; 
	//����ģ̬���Ա�Ի���
	if (m_Sheet.DoModal() == IDOK)
	{
		//��ȡ������ҳ���õ�ֵ
		m_type = m_Sheet.pageFirst.m_radio;
		m_r=m_Sheet.pageSecond.m_r;
		m_g=m_Sheet.pageSecond.m_g;
		m_b=m_Sheet.pageSecond.m_b; 
		Invalidate(true);//�ػ�ͻ�����
	}	
}
void CPropertySheetDemo2View::OnApply(WPARAM wParam, LPARAM lParam)
{

	m_Sheet.pageFirst.UpdateData(true);
	//��ȡ���Ա�Ի�����ؼ�������ֵ
	m_type = m_Sheet.pageFirst.m_radio;
	m_r=m_Sheet.pageSecond.m_r;
	m_g=m_Sheet.pageSecond.m_g;
	m_b=m_Sheet.pageSecond.m_b; 
	Invalidate(true);//�ػ�ͻ�����
}
