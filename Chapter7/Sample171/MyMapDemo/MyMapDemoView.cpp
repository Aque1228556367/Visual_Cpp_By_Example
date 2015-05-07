// MyMapDemoView.cpp : implementation of the CMyMapDemoView class
//

#include "stdafx.h"
#include "MyMapDemo.h"

#include "MyMapDemoDoc.h"
#include "MyMapDemoView.h"

#include <math.h>
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMyMapDemoView

IMPLEMENT_DYNCREATE(CMyMapDemoView, CView)

BEGIN_MESSAGE_MAP(CMyMapDemoView, CView)
	//{{AFX_MSG_MAP(CMyMapDemoView)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMyMapDemoView construction/destruction

CMyMapDemoView::CMyMapDemoView()
{
	// TODO: add construction code here

}

CMyMapDemoView::~CMyMapDemoView()
{
}

BOOL CMyMapDemoView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CMyMapDemoView drawing

void CMyMapDemoView::OnDraw(CDC* pDC)
{
	CMyMapDemoDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
	//����ӳ��ģʽΪ MM_ANISOTROPIC
	pDC->SetMapMode(MM_ANISOTROPIC);
	//���ô������Ͻǵ����꣨��4����2�����Ŵ�100������ͬ
	pDC->SetWindowOrg(int(-400*3.14159), 200);
	//���ô��ڶ���
	pDC->SetWindowExt(int(800*3.14159), -400);
	//��ÿͻ�������
	CRect rc;
	GetClientRect(rc);
	//�����ӿڵ�����ԭ��
	pDC->SetViewportOrg(0, 0);
	//�����ӿڶ���
	pDC->SetViewportExt(rc.Width(), rc.Height());
	//������ɫʵ�߻���
	CPen pen(PS_SOLID,1,RGB(0, 0, 255));
	CPen pen1(PS_DASH, 1, RGB(0,0, 0)), *pOldPen;
	pOldPen=pDC->SelectObject(&pen);				//������ɫʵ�߻���
	pDC->MoveTo(int(-4000*3.14159), 0);
	for (double x=(-4*3.14159);x<=0; x+=0.01)				//���Ƹ�������������
	{
		pDC->LineTo(int(100*x),int(100*sin(x)));
	}
	for (x=0; x<=4*3.14159; x+=0.01)					//������������������
	{
		pDC->LineTo(int(100*x), int(100*sin(x)));
	}
	pDC->SelectObject(&pen1);						//�������߻���
	pDC->MoveTo(int(-400*3.14159),0);				//����X��
	pDC->LineTo(int(400*3.14159), 0);
	pDC->MoveTo(0, -200);						//����Y��
	pDC->LineTo(0, 200);
	// �ָ��豸������ԭ�еĻ���
	pDC->SelectObject(pOldPen);
	pen.DeleteObject();
	pen1.DeleteObject();

}

/////////////////////////////////////////////////////////////////////////////
// CMyMapDemoView printing

BOOL CMyMapDemoView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CMyMapDemoView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CMyMapDemoView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CMyMapDemoView diagnostics

#ifdef _DEBUG
void CMyMapDemoView::AssertValid() const
{
	CView::AssertValid();
}

void CMyMapDemoView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMyMapDemoDoc* CMyMapDemoView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMyMapDemoDoc)));
	return (CMyMapDemoDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMyMapDemoView message handlers
