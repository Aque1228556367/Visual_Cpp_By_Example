// CaretKeyDemoView.cpp : implementation of the CCaretKeyDemoView class
//

#include "stdafx.h"
#include "CaretKeyDemo.h"

#include "CaretKeyDemoDoc.h"
#include "CaretKeyDemoView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCaretKeyDemoView

IMPLEMENT_DYNCREATE(CCaretKeyDemoView, CView)

BEGIN_MESSAGE_MAP(CCaretKeyDemoView, CView)
	//{{AFX_MSG_MAP(CCaretKeyDemoView)
	ON_WM_SETFOCUS()
	ON_WM_CHAR()
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCaretKeyDemoView construction/destruction

CCaretKeyDemoView::CCaretKeyDemoView()
{
	// TODO: add construction code here
	//初始位置设置在（0，0）
	ptCharacter.x=0;
	ptCharacter.y=0;
	ptStartPos = ptCharacter;
	//CWnd::GetCaretPos();
}

CCaretKeyDemoView::~CCaretKeyDemoView()
{
}

BOOL CCaretKeyDemoView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CCaretKeyDemoView drawing

void CCaretKeyDemoView::OnDraw(CDC* pDC)
{
	CCaretKeyDemoDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
	if( GetCaretPos().x - ptStartPos.x < 0 )
	{
		ptStartPos.x = 0;
		SetCaretPos(ptStartPos);
	}
}

/////////////////////////////////////////////////////////////////////////////
// CCaretKeyDemoView printing

BOOL CCaretKeyDemoView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CCaretKeyDemoView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CCaretKeyDemoView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CCaretKeyDemoView diagnostics

#ifdef _DEBUG
void CCaretKeyDemoView::AssertValid() const
{
	CView::AssertValid();
}

void CCaretKeyDemoView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CCaretKeyDemoDoc* CCaretKeyDemoView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CCaretKeyDemoDoc)));
	return (CCaretKeyDemoDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CCaretKeyDemoView message handlers

void CCaretKeyDemoView::OnSetFocus(CWnd* pOldWnd)
{
	CView::OnSetFocus(pOldWnd);

	// TODO: Add your message handler code here
	CreateSolidCaret(3, 18);							//创建插入符
	SetCaretPos(ptCharacter);							//将插入符移到当前字符输入点
	ShowCaret();									//显示插入符
}

void CCaretKeyDemoView::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: Add your message handler code here and/or call default
	if( GetCaretPos().x - ptStartPos.x < 0 )
	{
		ptStartPos.x = 0;
		SetCaretPos(ptStartPos);
	}
	HideCaret();	//隐藏插入符
	if(nChar==13)//按下了回车键
	{
		//换行
		ptCharacter.x=0;
		ptCharacter.y=ptCharacter.y+25;

		SetCaretPos(ptCharacter);//将插入符移到键入点
		ShowCaret();//显示插入符
	}
	else if( nChar==8 )//按下退格键
	{
		if( GetCaretPos() != ptStartPos )
		{
			CClientDC dc(this);
			CPoint prePtChar;
			prePtChar.x = ptCharacter.x - preTextsize.cx;
			prePtChar.y = ptCharacter.y;
			CRect eraseRect(prePtChar, preTextsize);
			dc.FillSolidRect( &eraseRect, dc.GetBkColor() );
			ptCharacter = prePtChar;

			SetCaretPos(prePtChar);
			ShowCaret();//显示插入符
		}
		else
			ShowCaret();//显示插入符
			//HideCaret();	//隐藏插入符
	}
	else
	{
		CClientDC dc(this);
		dc.TextOut(ptCharacter.x,ptCharacter.y,(LPCTSTR)&nChar);//显示字符
		CSize textsize;
		textsize=dc.GetTextExtent((LPCTSTR)&nChar);					//获取当前字符大小
		//前进到下一个字符位置
		ptCharacter.x=ptCharacter.x+textsize.cx;
		preTextsize = textsize;//记录当前字符大小

		SetCaretPos(ptCharacter);//将插入符移到键入点
		ShowCaret();//显示插入符
	}

	//SetCaretPos(ptCharacter);//将插入符移到键入点
	//ShowCaret();//显示插入符
	//HideCaret();	//隐藏插入符
	CView::OnChar(nChar, nRepCnt, nFlags);
}