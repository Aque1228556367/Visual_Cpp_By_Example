// BmpZoomPartView.cpp : implementation of the CBmpZoomPartView class
//

#include "stdafx.h"
#include "BmpZoomPart.h"

#include "BmpZoomPartDoc.h"
#include "BmpZoomPartView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CBmpZoomPartView

IMPLEMENT_DYNCREATE(CBmpZoomPartView, CView)

BEGIN_MESSAGE_MAP(CBmpZoomPartView, CView)
	//{{AFX_MSG_MAP(CBmpZoomPartView)
	ON_WM_LBUTTONDOWN()
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBmpZoomPartView construction/destruction

CBmpZoomPartView::CBmpZoomPartView()
{
	// TODO: add construction code here
	bFirstload=true;
	bFistLdown=true;
	m_pBitmap = new CBitmap;
	m_pdcMem = new CDC;
	s=20;//Դ�����С
	d=40;//�Ŵ�������С
}

CBmpZoomPartView::~CBmpZoomPartView()
{
}

BOOL CBmpZoomPartView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CBmpZoomPartView drawing

void CBmpZoomPartView::OnDraw(CDC* pDC)
{
	CBmpZoomPartDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
	pDC->TextOut(5,180,"��λͼ�ϵ��������ʵ�־ֲ��Ŵ�λͼ��");
	if(bFirstload)//��һ�����У�����λͼ����ʾ
	{
		BITMAP bm;
		bFirstload = !bFirstload;
		m_pBitmap->LoadBitmap(IDB_BITMAP1);//����λͼ
		m_pdcMem->CreateCompatibleDC(pDC);//�����ڴ�DC
		m_pdcMem->SelectObject(m_pBitmap);
		m_pBitmap->GetObject(sizeof(bm),&bm);
		m_sizeSource.cx = bm.bmWidth;//λͼ�Ŀ��
		m_sizeSource.cy = bm.bmHeight;//λͼ�ĸ߶�
		pDC->BitBlt(20,20,m_sizeSource.cx,m_sizeSource.cy,
			m_pdcMem,0,0,SRCCOPY);//��ʾλͼ
	}
	else//ֱ����ʾ
	{
		pDC->BitBlt(20,20,m_sizeSource.cx,m_sizeSource.cy,
			m_pdcMem,0,0,SRCCOPY);//��ʾλͼ
	}
}



/////////////////////////////////////////////////////////////////////////////
// CBmpZoomPartView printing

BOOL CBmpZoomPartView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CBmpZoomPartView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CBmpZoomPartView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CBmpZoomPartView diagnostics

#ifdef _DEBUG
void CBmpZoomPartView::AssertValid() const
{
	CView::AssertValid();
}

void CBmpZoomPartView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CBmpZoomPartDoc* CBmpZoomPartView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CBmpZoomPartDoc)));
	return (CBmpZoomPartDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CBmpZoomPartView message handlers

void CBmpZoomPartView::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default	
	CRect rc(20,20,m_sizeSource.cx+20,m_sizeSource.cy+20);//λͼ����
	if(rc.PtInRect(point))//��λͼ��Χ��
	{
		CRect srect,drect,mrect;//����Ҫ�Ŵ�ľֲ����ε�Դͼ��λ�ú�Ŀ��λ��
		//Դͼ��λ��
		srect.left = point.x-20-s;
		srect.top = point.y-20-s;
		srect.right = point.x-20+s;
		srect.bottom = point.y-20+s;
		//�Ŵ��ͼ������
		drect.left = point.x-d;
		drect.top = point.y-d;
		drect.right = point.x+d;
		drect.bottom = point.y+d;
		CDC * pDC = GetDC();
		OnPrepareDC(pDC);
		if (!bFistLdown)
		{
			//��¼�ϴε���������λ�ô�������
			mrect.left = oldx - d;
			mrect.top = oldy - d;
			mrect.right = oldx + d;
			mrect.bottom = oldy + d;
			//�ָ�λͼ
			pDC->BitBlt(mrect.left,mrect.top,d*2,d*2,
			m_pdcMem,mrect.left-20,mrect.top-20,SRCCOPY);
		}	
		bFistLdown=false;
		//�Ŵ�ֲ�λͼ
		pDC->StretchBlt(drect.left,drect.top,drect.Width(),drect.Height(),m_pdcMem,srect.left,
		srect.top,srect.Width(),srect.Height(),SRCCOPY);
		ReleaseDC(pDC);
		oldx = point.x; 
		oldy = point.y;
	}
	else
	{
		Invalidate();
	}
	CView::OnLButtonDown(nFlags, point);
}
