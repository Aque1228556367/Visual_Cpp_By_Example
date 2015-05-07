// DyBMPMovieView.cpp : implementation of the CDyBMPMovieView class
//

#include "stdafx.h"
#include "DyBMPMovie.h"

#include "DyBMPMovieDoc.h"
#include "DyBMPMovieView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDyBMPMovieView

IMPLEMENT_DYNCREATE(CDyBMPMovieView, CView)

BEGIN_MESSAGE_MAP(CDyBMPMovieView, CView)
	//{{AFX_MSG_MAP(CDyBMPMovieView)
	ON_WM_CREATE()
	ON_WM_TIMER()
	ON_WM_ERASEBKGND()
	ON_WM_SIZE()
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDyBMPMovieView construction/destruction

CDyBMPMovieView::CDyBMPMovieView()
{
	// TODO: add construction code here
	//��������ı���ˢ��
	CBitmap* pBitmap = new CBitmap;
	ASSERT(pBitmap);
	pBitmap->LoadBitmap(IDB_BACKGROUND);//����λͼ
	m_BKBrush.CreatePatternBrush(pBitmap);//��������ˢ
	delete pBitmap;//�ͷ��ڴ�
}

CDyBMPMovieView::~CDyBMPMovieView()
{
}

BOOL CDyBMPMovieView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CDyBMPMovieView drawing

void CDyBMPMovieView::OnDraw(CDC* pDC)
{
	CDyBMPMovieDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// CDyBMPMovieView printing

BOOL CDyBMPMovieView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CDyBMPMovieView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CDyBMPMovieView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CDyBMPMovieView diagnostics

#ifdef _DEBUG
void CDyBMPMovieView::AssertValid() const
{
	CView::AssertValid();
}

void CDyBMPMovieView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CDyBMPMovieDoc* CDyBMPMovieView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CDyBMPMovieDoc)));
	return (CDyBMPMovieDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CDyBMPMovieView message handlers

int CDyBMPMovieView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// TODO: Add your specialized creation code here
	for (int i=0; i<6; ++i)//װ��λͼͼ��
		m_Bitmap[i].LoadBitmap(IDB_BITMAP1+i);
	BITMAP bm;//BITMAP�ṹ
	m_Bitmap[0].GetBitmap(&bm);
	m_nFrameWidth  = bm.bmWidth;//���ͼ��Ŀ��
	m_nFrameHeight = bm.bmHeight;//���ͼ��ĸ߶�
	//����ˮƽ�ʹ�ֱ����Ĳ�����
	m_nStepX = 20;
	m_nStepY = 15;
	m_ptCurPos = CPoint(0, 0);//��ǰ����ʾλ��
	m_nCurFrameNo = 0;	//��ʼ��ʾ��ͼ����
	SetTimer(1, 150, NULL);//�趨��ʱ��
	return 0;
}

void CDyBMPMovieView::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	//�����һ����ʾ��ͼ��ľ�������С
	CRect rect(m_ptCurPos.x, m_ptCurPos.y, m_ptCurPos.x+m_nFrameWidth, m_ptCurPos.y+m_nFrameHeight);
	InvalidateRect(&rect);//ʹ�������������Ч	
	UpdateWindow();//���´�����ʾ
	
	//��ȡ�ͻ������δ�С
	CRect ClientRect;
	GetClientRect(&ClientRect);
	//�����µ���ʾλ��
	if (m_ptCurPos.x+m_nFrameWidth+m_nStepX >= ClientRect.right ||
		m_ptCurPos.x+m_nStepX <= ClientRect.left)//�������ұ߽�
		m_nStepX = -m_nStepX;
	if (m_ptCurPos.y+m_nFrameHeight+m_nStepY >= ClientRect.bottom ||
		m_ptCurPos.y+m_nStepY <= ClientRect.top)//�������±߽�
		m_nStepY = -m_nStepY;
	m_ptCurPos.x += m_nStepX; 
	m_ptCurPos.y += m_nStepY;
	//���濪ʼ��ʾһ��ͼ��
	CClientDC dc(this);//��ȡDC
	CDC MemDC;
	if (! MemDC.CreateCompatibleDC(&dc))//��������DC
		return;
	CBitmap *pOldBitmap = (CBitmap *)MemDC.SelectObject(&m_Bitmap[m_nCurFrameNo]);
	dc.BitBlt(m_ptCurPos.x, m_ptCurPos.y,
			  m_nFrameWidth, m_nFrameHeight,
			  &MemDC,
			  0, 0,
			  SRCCOPY);
	MemDC.SelectObject(pOldBitmap);
	m_nCurFrameNo++;
	if (m_nCurFrameNo >=6)
		m_nCurFrameNo = 0;
	CView::OnTimer(nIDEvent);
}

BOOL CDyBMPMovieView::OnEraseBkgnd(CDC* pDC) 
{
	// TODO: Add your message handler code here and/or call default
	// ����ԭ����ͼ��ˢ��
	CBrush* pOldBrush = pDC->SelectObject(&m_BKBrush);	
	//�����Ҫ���µļ���������
	CRect rect;
	pDC->GetClipBox(&rect);     	
	pDC->PatBlt(rect.left, rect.top, rect.Width(), rect.Height(),PATCOPY);
	pDC->SelectObject(pOldBrush);
	return TRUE;
//	return CView::OnEraseBkgnd(pDC);
}

void CDyBMPMovieView::OnSize(UINT nType, int cx, int cy) 
{
	CView::OnSize(nType, cx, cy);
	
	// TODO: Add your message handler code here
	m_ptCurPos = CPoint(0, 0);
	m_nCurFrameNo = 0;
}

void CDyBMPMovieView::OnDestroy() 
{
	CView::OnDestroy();
	
	// TODO: Add your message handler code here
	//�����ʱ��
	KillTimer(1);	
}
