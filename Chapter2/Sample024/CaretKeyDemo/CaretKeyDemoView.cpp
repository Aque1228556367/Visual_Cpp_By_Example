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
	//��ʼλ�������ڣ�0��0��
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
	CreateSolidCaret(3, 18);							//���������
	SetCaretPos(ptCharacter);							//��������Ƶ���ǰ�ַ������
	ShowCaret();									//��ʾ�����
}

void CCaretKeyDemoView::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: Add your message handler code here and/or call default
	if( GetCaretPos().x - ptStartPos.x < 0 )
	{
		ptStartPos.x = 0;
		SetCaretPos(ptStartPos);
	}
	HideCaret();	//���ز����
	if(nChar==13)//�����˻س���
	{
		//����
		ptCharacter.x=0;
		ptCharacter.y=ptCharacter.y+25;

		SetCaretPos(ptCharacter);//��������Ƶ������
		ShowCaret();//��ʾ�����
	}
	else if( nChar==8 )//�����˸��
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
			ShowCaret();//��ʾ�����
		}
		else
			ShowCaret();//��ʾ�����
			//HideCaret();	//���ز����
	}
	else
	{
		CClientDC dc(this);
		dc.TextOut(ptCharacter.x,ptCharacter.y,(LPCTSTR)&nChar);//��ʾ�ַ�
		CSize textsize;
		textsize=dc.GetTextExtent((LPCTSTR)&nChar);					//��ȡ��ǰ�ַ���С
		//ǰ������һ���ַ�λ��
		ptCharacter.x=ptCharacter.x+textsize.cx;
		preTextsize = textsize;//��¼��ǰ�ַ���С

		SetCaretPos(ptCharacter);//��������Ƶ������
		ShowCaret();//��ʾ�����
	}

	//SetCaretPos(ptCharacter);//��������Ƶ������
	//ShowCaret();//��ʾ�����
	//HideCaret();	//���ز����
	CView::OnChar(nChar, nRepCnt, nFlags);
}