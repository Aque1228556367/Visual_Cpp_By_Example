// WindowDcDemoView.cpp : implementation of the CWindowDcDemoView class
//

#include "stdafx.h"
#include "WindowDcDemo.h"

#include "WindowDcDemoDoc.h"
#include "WindowDcDemoView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CWindowDcDemoView

IMPLEMENT_DYNCREATE(CWindowDcDemoView, CView)

BEGIN_MESSAGE_MAP(CWindowDcDemoView, CView)
	//{{AFX_MSG_MAP(CWindowDcDemoView)
	ON_WM_PAINT()
	ON_COMMAND(ID_FRAMEDRAW, OnFramedraw)
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CWindowDcDemoView construction/destruction

CWindowDcDemoView::CWindowDcDemoView()
{
	// TODO: add construction code here

}

CWindowDcDemoView::~CWindowDcDemoView()
{
}

BOOL CWindowDcDemoView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CWindowDcDemoView drawing

void CWindowDcDemoView::OnDraw(CDC* pDC)
{
	CWindowDcDemoDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here



}

/////////////////////////////////////////////////////////////////////////////
// CWindowDcDemoView printing

BOOL CWindowDcDemoView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CWindowDcDemoView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CWindowDcDemoView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CWindowDcDemoView diagnostics

#ifdef _DEBUG
void CWindowDcDemoView::AssertValid() const
{
	CView::AssertValid();
}

void CWindowDcDemoView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CWindowDcDemoDoc* CWindowDcDemoView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CWindowDcDemoDoc)));
	return (CWindowDcDemoDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CWindowDcDemoView message handlers

void CWindowDcDemoView::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	// TODO: Add your message handler code here

	// Do not call CView::OnPaint() for painting messages
}

void CWindowDcDemoView::OnFramedraw() 
{
	// TODO: Add your command handler code here
	CRect rc;									//�����������򣬴洢������������
	CFrameWnd *pFrm = GetTopLevelFrame();			//�������ܴ���ָ��
	pFrm ->GetWindowRect(&rc);					//�õ��������ķ�Χ�ŵ�rc��
	CWindowDC dc(pFrm);						//����CWindowDC�����
	CPen pen1; 								//�Զ��廭��
	pen1.CreatePen(PS_SOLID,0,RGB(255,0,0));
	CPen *poldPen = dc.SelectObject(&pen1); 	//ѡ���»��ʣ����ز�����ԭֵ
	CRect rect1(0,0,140,100);  					//�������
	dc.Ellipse(&rect1);  						//������Բ	
	dc.TextOut(10,40,"���������ڻ�ͼ");
}
