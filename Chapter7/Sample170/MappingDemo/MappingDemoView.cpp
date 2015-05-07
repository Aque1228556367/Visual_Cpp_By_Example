// MappingDemoView.cpp : implementation of the CMappingDemoView class
//

#include "stdafx.h"
#include "MappingDemo.h"

#include "MappingDemoDoc.h"
#include "MappingDemoView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMappingDemoView

IMPLEMENT_DYNCREATE(CMappingDemoView, CView)

BEGIN_MESSAGE_MAP(CMappingDemoView, CView)
	//{{AFX_MSG_MAP(CMappingDemoView)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMappingDemoView construction/destruction

CMappingDemoView::CMappingDemoView()
{
	// TODO: add construction code here

}

CMappingDemoView::~CMappingDemoView()
{
}

BOOL CMappingDemoView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CMappingDemoView drawing

void CMappingDemoView::OnDraw(CDC* pDC)
{
	CMappingDemoDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
	CRect rect;
	GetClientRect(rect);								//��ȡ�ͻ����ߴ磨���أ�
	CPen mypen;
	CPen*oldpen;
	mypen.CreatePen(PS_SOLID,1,RGB(0,0,255));			//���ɻ���
	oldpen=pDC->SelectObject(&mypen);						//�ѻ���ѡ���豸����
	pDC->SetMapMode(MM_ANISOTROPIC);//����ӳ�䷽ʽ,X��Y���Զ���������
	pDC->SetWindowExt(100,100);					//������DC��صĴ��ڳߴ�
	pDC->SetViewportExt(rect.right,-rect.bottom);	//�����Ӵ��ߴ�Ϊ�����ͻ���
	pDC->SetViewportOrg(rect.right/2, rect.bottom/2);//�Ӵ�����ԭ��Ϊ�ͻ��������ĵ�
	pDC->Ellipse(-50, -50, 50, 50);				//������Բ
	pDC->SetMapMode(MM_ISOTROPIC);				//����ӳ�䷽ʽ,�����ݺ�ı���Ϊ1��1
	pDC->SetWindowExt(100,100);					//������DC��صĴ��ڳߴ�
	pDC->SetViewportExt(rect.right/2,-rect.bottom/2);//�����Ӵ��ߴ�Ϊ�����ͻ�����һ���С
	pDC->SetViewportOrg(rect.right/2, rect.bottom/2);//�Ӵ�����ԭ��Ϊ�ͻ��������ĵ�
	pDC->Ellipse(-50, -50, 50, 50);					//����Բ

	pDC->TextOut(-80,0,"ʹ�ò�ͬ��ӳ�䷽ʽ���л�ͼ");
	pDC->SelectObject(oldpen);								//�ָ�ԭ�еı�

}

/////////////////////////////////////////////////////////////////////////////
// CMappingDemoView printing

BOOL CMappingDemoView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CMappingDemoView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CMappingDemoView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CMappingDemoView diagnostics

#ifdef _DEBUG
void CMappingDemoView::AssertValid() const
{
	CView::AssertValid();
}

void CMappingDemoView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMappingDemoDoc* CMappingDemoView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMappingDemoDoc)));
	return (CMappingDemoDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMappingDemoView message handlers
