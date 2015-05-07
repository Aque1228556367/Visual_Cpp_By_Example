// TransBmpDemoView.cpp : implementation of the CTransBmpDemoView class
//

#include "stdafx.h"
#include "TransBmpDemo.h"

#include "TransBmpDemoDoc.h"
#include "TransBmpDemoView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTransBmpDemoView

IMPLEMENT_DYNCREATE(CTransBmpDemoView, CView)

BEGIN_MESSAGE_MAP(CTransBmpDemoView, CView)
	//{{AFX_MSG_MAP(CTransBmpDemoView)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTransBmpDemoView construction/destruction

CTransBmpDemoView::CTransBmpDemoView()
{
	// TODO: add construction code here

}

CTransBmpDemoView::~CTransBmpDemoView()
{
}

BOOL CTransBmpDemoView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CTransBmpDemoView drawing

void CTransBmpDemoView::OnDraw(CDC* pDC)
{
	CTransBmpDemoDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
	//��ʾ�ײ�λͼ
	CBitmap bmp;
	bmp.LoadBitmap(IDB_BITMAP1);
	BITMAP bm;
	bmp.GetBitmap(&bm);
	//��ȡλͼ�Ĵ�С
	int nWidth,nHeight;
	nWidth=bm.bmWidth;
	nHeight=bm.bmHeight;
	CDC MemDC;
	MemDC.CreateCompatibleDC(pDC);//���������ڴ�DC
	CBitmap* pOldBmp = MemDC.SelectObject(&bmp);
	pDC->BitBlt(20,20,nWidth,nHeight,&MemDC,0,0,SRCCOPY);//��ʾλͼ
	MemDC.SelectObject(pOldBmp);
	MemDC.DeleteDC();
	//��ʾ�ϲ�͸��λͼ
	DrawTransparent(pDC,20,20,RGB(0,0,0));
	pDC->TextOut(40,250,"ʵ����ʾ͸��λͼ");
}

/////////////////////////////////////////////////////////////////////////////
// CTransBmpDemoView printing

BOOL CTransBmpDemoView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CTransBmpDemoView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CTransBmpDemoView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CTransBmpDemoView diagnostics

#ifdef _DEBUG
void CTransBmpDemoView::AssertValid() const
{
	CView::AssertValid();
}

void CTransBmpDemoView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CTransBmpDemoDoc* CTransBmpDemoView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CTransBmpDemoDoc)));
	return (CTransBmpDemoDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CTransBmpDemoView message handlers
void CTransBmpDemoView::DrawTransparent(CDC *pDC, int x, int y, COLORREF crColour)
{
	CDC dcImage, dcMask;
	CBitmap bmp;
	bmp.LoadBitmap(IDB_BITMAP2);//IDB_BITMAP2�Ǵ���ʾ����ͼ����ԴID
	BITMAP bm;
	bmp.GetBitmap(&bm);
	//��ȡλͼ�Ĵ�С
	int nWidth,nHeight;
	nWidth=bm.bmWidth;
	nHeight=bm.bmHeight;
	//Ϊͼ��mask������һ��DC
	dcImage.CreateCompatibleDC(pDC);
	dcMask.CreateCompatibleDC(pDC);
	//��ͼ��װ��image DC
	CBitmap* pOldBitmapImage=dcImage.SelectObject(&bmp);
	//Ϊ�����롱λͼ����һ����ɫbitmap
	CBitmap bitmapMask;
	bitmapMask.CreateBitmap(nWidth, nHeight, 1, 1, NULL); //��maskλͼװ��mask DC
	CBitmap* pOldBitmapMask = dcMask.SelectObject(&bitmapMask); //��͸��ɫ���������롱λͼ
	dcImage.SetBkColor(crColour);//crColor��λͼ�е�͸��ɫ��Ϊ��ɫ
	dcMask.BitBlt(0, 0, nWidth, nHeight, &dcImage, 0, 0, SRCCOPY);//��3������ʵ�ʵĻ���
	pDC->BitBlt(x, y, nWidth, nHeight, &dcImage, 0, 0, SRCINVERT);
	pDC->BitBlt(x, y, nWidth, nHeight, &dcMask, 0, 0, SRCAND);
	pDC->BitBlt(x, y, nWidth, nHeight, &dcImage, 0, 0, SRCINVERT); //�ָ�ԭ������
	dcImage.SelectObject(pOldBitmapImage);
	dcMask.SelectObject(pOldBitmapMask);
}
