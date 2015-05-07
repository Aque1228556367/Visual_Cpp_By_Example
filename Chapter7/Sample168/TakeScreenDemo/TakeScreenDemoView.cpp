// TakeScreenDemoView.cpp : implementation of the CTakeScreenDemoView class
//

#include "stdafx.h"
#include "TakeScreenDemo.h"

#include "TakeScreenDemoDoc.h"
#include "TakeScreenDemoView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTakeScreenDemoView

IMPLEMENT_DYNCREATE(CTakeScreenDemoView, CView)

BEGIN_MESSAGE_MAP(CTakeScreenDemoView, CView)
	//{{AFX_MSG_MAP(CTakeScreenDemoView)
	ON_COMMAND(ID_MENUSCREEN, OnMenuscreen)
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTakeScreenDemoView construction/destruction

CTakeScreenDemoView::CTakeScreenDemoView()
{
	// TODO: add construction code here
	bTakeScreen=false;
	m_hbmp=NULL;

}

CTakeScreenDemoView::~CTakeScreenDemoView()
{
}

BOOL CTakeScreenDemoView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CTakeScreenDemoView drawing

void CTakeScreenDemoView::OnDraw(CDC* pDC)
{
	CTakeScreenDemoDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
	if(bTakeScreen)
	{
		 CBitmap *Bitmap;
         Bitmap=CBitmap::FromHandle(m_hbmp);
         CDC MemDC;
         MemDC.CreateCompatibleDC(pDC);
         CBitmap *pOldBitmap=MemDC.SelectObject(Bitmap);
         BITMAP bm;
		 Bitmap->GetBitmap(&bm);
         pDC->BitBlt(10,10,bm.bmWidth,bm.bmHeight,&MemDC,0,0,SRCCOPY);
         MemDC.SelectObject(pOldBitmap);
	}
}

/////////////////////////////////////////////////////////////////////////////
// CTakeScreenDemoView printing

BOOL CTakeScreenDemoView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CTakeScreenDemoView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CTakeScreenDemoView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CTakeScreenDemoView diagnostics

#ifdef _DEBUG
void CTakeScreenDemoView::AssertValid() const
{
	CView::AssertValid();
}

void CTakeScreenDemoView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CTakeScreenDemoDoc* CTakeScreenDemoView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CTakeScreenDemoDoc)));
	return (CTakeScreenDemoDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CTakeScreenDemoView message handlers

void CTakeScreenDemoView::OnMenuscreen() 
{
	// TODO: Add your command handler code here
	bTakeScreen=true;
	m_hbmp=TakeScreen();//��ȡȫ��Ļ��HBITMAP
	Invalidate();//������ͼ
}

HBITMAP CTakeScreenDemoView::TakeScreen()//ץȡ��Ļ��HBITMAP
{
   HWND hWnd = ::GetDesktopWindow();//�����Ļ��HWND.
   HDC hScreenDC = ::GetDC(hWnd);   //�����Ļ��HDC.
   HDC MemDC = ::CreateCompatibleDC(hScreenDC);
   RECT rect; 
   ::GetWindowRect(hWnd,&rect);//��ȡ���ھ���
   SIZE screensize;
   screensize.cx=rect.right-rect.left;//��Ļ���
   screensize.cy=rect.bottom-rect.top;//��Ļ�߶�
   HBITMAP Bitmap = ::CreateCompatibleBitmap(hScreenDC,screensize.cx,screensize.cy);
   HGDIOBJ hOldBMP = ::SelectObject(MemDC,Bitmap);
   ::BitBlt(MemDC,0,0,screensize.cx,screensize.cy,hScreenDC,rect.left,rect.top,SRCCOPY);
   ::SelectObject(MemDC,hOldBMP);
   ::DeleteObject(MemDC);
   ::ReleaseDC(hWnd,hScreenDC);
   return Bitmap;
}
