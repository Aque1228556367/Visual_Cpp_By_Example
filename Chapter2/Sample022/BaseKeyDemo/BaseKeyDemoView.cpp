// BaseKeyDemoView.cpp : implementation of the CBaseKeyDemoView class
//

#include "stdafx.h"
#include "BaseKeyDemo.h"

#include "BaseKeyDemoDoc.h"
#include "BaseKeyDemoView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CBaseKeyDemoView

IMPLEMENT_DYNCREATE(CBaseKeyDemoView, CView)

BEGIN_MESSAGE_MAP(CBaseKeyDemoView, CView)
	//{{AFX_MSG_MAP(CBaseKeyDemoView)
	ON_WM_KEYDOWN()
	ON_WM_KEYUP()
	ON_WM_CHAR()
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBaseKeyDemoView construction/destruction

CBaseKeyDemoView::CBaseKeyDemoView()
{
	// TODO: add construction code here
	bShiftdown=bShiftup=bShiftB=FALSE;//����ֵ

}

CBaseKeyDemoView::~CBaseKeyDemoView()
{
}

BOOL CBaseKeyDemoView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CBaseKeyDemoView drawing

void CBaseKeyDemoView::OnDraw(CDC* pDC)
{
	CBaseKeyDemoDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
	if(bShiftdown)										//������Shift��
	{
		pDC->TextOut(20,20,"�û�������Shift��!");
	}
	if(bShiftup)											//�ͷ���Shift��
	{
		pDC->TextOut(20,20,"�û��ͷ���Shift��!");
	}
	if(bShiftB)										//ͬʱ������Shift����B��
	{
		pDC->TextOut(20,20,"�û�ͬʱ����Shift����B��!");
		bShiftB=FALSE;
	}
}

/////////////////////////////////////////////////////////////////////////////
// CBaseKeyDemoView printing

BOOL CBaseKeyDemoView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CBaseKeyDemoView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CBaseKeyDemoView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CBaseKeyDemoView diagnostics

#ifdef _DEBUG
void CBaseKeyDemoView::AssertValid() const
{
	CView::AssertValid();
}

void CBaseKeyDemoView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CBaseKeyDemoDoc* CBaseKeyDemoView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CBaseKeyDemoDoc)));
	return (CBaseKeyDemoDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CBaseKeyDemoView message handlers

void CBaseKeyDemoView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	// TODO: Add your message handler code here and/or call default
	if(nChar==VK_SHIFT)								//�ж�Shift���Ƿ񱻰���
	{
		//AfxMessageBox("dd");
		bShiftdown=TRUE;
		bShiftup=FALSE;
		Invalidate(TRUE);										//��ʾ��Ϣ
	}
	
	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}

void CBaseKeyDemoView::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	// TODO: Add your message handler code here and/or call default
	if(nChar==VK_SHIFT)								//�ж�Shift���Ƿ��ͷ�
	{
		//AfxMessageBox("dd");
		bShiftup=TRUE;
		Invalidate(TRUE);										//��ʾ��Ϣ
		bShiftdown=FALSE;
	}	
	CView::OnKeyUp(nChar, nRepCnt, nFlags);
}

void CBaseKeyDemoView::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	// TODO: Add your message handler code here and/or call default
	if((nChar==98)||(nChar==66))						//�ж��Ƿ��û����ַ���B����b��
	{
		if(bShiftdown)
		{
			bShiftB=TRUE;
			bShiftdown=FALSE;
			Invalidate(TRUE);								//��ʾ��Ϣ
		}	
	}	
	CView::OnChar(nChar, nRepCnt, nFlags);
}
