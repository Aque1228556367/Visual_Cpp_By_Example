// FaceControl4View.cpp : implementation of the CFaceControl4View class
//

#include "stdafx.h"
#include "FaceControl4.h"

#include "FaceControl4Doc.h"
#include "FaceControl4View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CFaceControl4View

IMPLEMENT_DYNCREATE(CFaceControl4View, CView)

BEGIN_MESSAGE_MAP(CFaceControl4View, CView)
	//{{AFX_MSG_MAP(CFaceControl4View)
	ON_COMMAND(ID_CHAGEVIEWBK, OnChageviewbk)
	ON_WM_ERASEBKGND()
	ON_COMMAND(ID_CHANGEFRAMEICON, OnChangeframeicon)
	ON_COMMAND(ID_CHANGECHILDICON, OnChangechildicon)
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFaceControl4View construction/destruction

CFaceControl4View::CFaceControl4View()
{
	// TODO: add construction code here
	m_rgbBack = RGB(128 , 128 , 128);

}

CFaceControl4View::~CFaceControl4View()
{
}

BOOL CFaceControl4View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CFaceControl4View drawing

void CFaceControl4View::OnDraw(CDC* pDC)
{
	CFaceControl4Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// CFaceControl4View printing

BOOL CFaceControl4View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CFaceControl4View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CFaceControl4View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CFaceControl4View diagnostics

#ifdef _DEBUG
void CFaceControl4View::AssertValid() const
{
	CView::AssertValid();
}

void CFaceControl4View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CFaceControl4Doc* CFaceControl4View::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CFaceControl4Doc)));
	return (CFaceControl4Doc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CFaceControl4View message handlers

void CFaceControl4View::OnChageviewbk() //�ı䱳��ɫ
{
	// TODO: Add your command handler code here
	m_rgbBack=RGB(0,128,128);
	Invalidate(true);
}

BOOL CFaceControl4View::OnEraseBkgnd(CDC* pDC) 
{
	// TODO: Add your message handler code here and/or call default
	CBrush Brush (m_rgbBack);	// ����һ���µ�ˢ��
	CBrush* pOldBrush = pDC->SelectObject (&Brush);	// ��ˢ��ѡ���豸����
	//�����Ҫ�߳�����������
	CRect reClip;
	GetClientRect(&reClip);
	//�ػ������
	pDC->PatBlt(reClip.left , reClip.top , reClip.Width () , reClip.Height() , PATCOPY);
	//�ͷ�ˢ��
	pDC->SelectObject (pOldBrush);
	return TRUE;//���뷵��TURE
	//return CView::OnEraseBkgnd(pDC);
}

void CFaceControl4View::OnChangeframeicon() 
{
	// TODO: Add your command handler code here
	HICON hIcon=AfxGetApp() ->LoadIcon(IDI_ICON1);//����ͼ����Դ
	ASSERT(hIcon);
	AfxGetMainWnd()->SendMessage(WM_SETICON ,TRUE,(LPARAM)hIcon);//������ܷ�����Ϣ����ͼ��	
}

void CFaceControl4View::OnChangechildicon() 
{
	// TODO: Add your command handler code here
	HICON hIcon = AfxGetApp()->LoadIcon(IDI_ICON2);//����ͼ����Դ
	ASSERT(hIcon);
	GetParent()->SendMessage(WM_SETICON,TRUE,(LPARAM)hIcon);//���ӿ�ܷ�����Ϣ����ͼ��	
}
