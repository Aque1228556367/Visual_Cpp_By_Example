// DlgDateExchangeView.cpp : implementation of the CDlgDateExchangeView class
//

#include "stdafx.h"
#include "DlgDateExchange.h"

#include "ColorDlg.h"

#include "DlgDateExchangeDoc.h"
#include "DlgDateExchangeView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgDateExchangeView

IMPLEMENT_DYNCREATE(CDlgDateExchangeView, CView)

BEGIN_MESSAGE_MAP(CDlgDateExchangeView, CView)
	//{{AFX_MSG_MAP(CDlgDateExchangeView)
	ON_COMMAND(ID_SETCOLOR, OnSetcolor)
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgDateExchangeView construction/destruction

CDlgDateExchangeView::CDlgDateExchangeView()
{
	// TODO: add construction code here
	r=0;//Ϊ��Ա��������ֵ
	g=0;
	b=255;

}

CDlgDateExchangeView::~CDlgDateExchangeView()
{
}

BOOL CDlgDateExchangeView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CDlgDateExchangeView drawing

void CDlgDateExchangeView::OnDraw(CDC* pDC)
{
	CDlgDateExchangeDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
	CFont myfont;//��������
	LOGFONT font;
	memset(&font,0,sizeof(LOGFONT));
	font.lfHeight=25;//����߶�
	font.lfWeight=500;
	strcpy(font.lfFaceName,"Arial");//������ʽ
	myfont.CreateFontIndirect(&font);
	pDC->SelectObject(&myfont);//DC��������
	COLORREF crColor=RGB(r,g,b);
	pDC->SetTextColor(crColor);//�����ı���ɫ
	pDC->TextOut(20,20,"ʵ��ģ̬�Ի������ݽ���������У�飡");//����ı�
}

/////////////////////////////////////////////////////////////////////////////
// CDlgDateExchangeView printing

BOOL CDlgDateExchangeView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CDlgDateExchangeView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CDlgDateExchangeView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CDlgDateExchangeView diagnostics

#ifdef _DEBUG
void CDlgDateExchangeView::AssertValid() const
{
	CView::AssertValid();
}

void CDlgDateExchangeView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CDlgDateExchangeDoc* CDlgDateExchangeView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CDlgDateExchangeDoc)));
	return (CDlgDateExchangeDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CDlgDateExchangeView message handlers

void CDlgDateExchangeView::OnSetcolor() 
{
	// TODO: Add your command handler code here
	CColorDlg dlg;
	dlg.m_r=r;//���ı�����ɫ��Ϣ�����Ի���ؼ����ݳ�Ա
	dlg.m_g=g;
	dlg.m_b=b;
	if(dlg.DoModal()==IDOK)//����ģ̬�Ի���
	{
		r=dlg.m_r;  //�����ݴӶԻ��򴫸���ͼ
		g=dlg.m_g;
		b=dlg.m_b;
		Invalidate(false);  //������ͼ
	}
}
