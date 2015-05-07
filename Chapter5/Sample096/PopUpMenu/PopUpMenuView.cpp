// PopUpMenuView.cpp : implementation of the CPopUpMenuView class
//

#include "stdafx.h"
#include "PopUpMenu.h"

#include "PopUpMenuDoc.h"
#include "PopUpMenuView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPopUpMenuView

IMPLEMENT_DYNCREATE(CPopUpMenuView, CView)

BEGIN_MESSAGE_MAP(CPopUpMenuView, CView)
	//{{AFX_MSG_MAP(CPopUpMenuView)
	ON_COMMAND(ID_MENURED, OnMenured)
	ON_UPDATE_COMMAND_UI(ID_MENURED, OnUpdateMenured)
	ON_COMMAND(ID_MENUGREEN, OnMenugreen)
	ON_UPDATE_COMMAND_UI(ID_MENUGREEN, OnUpdateMenugreen)
	ON_COMMAND(ID_MENUBLUE, OnMenublue)
	ON_UPDATE_COMMAND_UI(ID_MENUBLUE, OnUpdateMenublue)
	ON_WM_RBUTTONDOWN()
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPopUpMenuView construction/destruction

CPopUpMenuView::CPopUpMenuView()
{
	// TODO: add construction code here

}

CPopUpMenuView::~CPopUpMenuView()
{
}

BOOL CPopUpMenuView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CPopUpMenuView drawing

void CPopUpMenuView::OnDraw(CDC* pDC)
{
	CPopUpMenuDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// CPopUpMenuView printing

BOOL CPopUpMenuView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CPopUpMenuView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CPopUpMenuView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CPopUpMenuView diagnostics

#ifdef _DEBUG
void CPopUpMenuView::AssertValid() const
{
	CView::AssertValid();
}

void CPopUpMenuView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CPopUpMenuDoc* CPopUpMenuView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CPopUpMenuDoc)));
	return (CPopUpMenuDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CPopUpMenuView message handlers

void CPopUpMenuView::OnMenured() 
{
	// TODO: Add your command handler code here
	CClientDC dc(this);											//���DC
	CBrush brush;
	brush.CreateSolidBrush(RGB(255,0,0));//������ˢ
	CRect rect;
	GetClientRect(&rect);//��ȡ�ͻ�������
	dc.FillRect(rect,&brush);//���ͻ���
	brush.DeleteObject();//ɾ����ˢ
	m_menuradio=0;
}

void CPopUpMenuView::OnUpdateMenured(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	
}

void CPopUpMenuView::OnMenugreen() 
{
	// TODO: Add your command handler code here
	CClientDC dc(this);											//���DC
	CBrush brush;
	brush.CreateSolidBrush(RGB(0,255,0));//������ˢ
	CRect rect;
	GetClientRect(&rect);//��ȡ�ͻ�������
	dc.FillRect(rect,&brush);//���ͻ���
	brush.DeleteObject();//ɾ����ˢ
	m_menuradio=1;
	
}

void CPopUpMenuView::OnUpdateMenugreen(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code her
	
}

void CPopUpMenuView::OnMenublue() 
{

	// TODO: Add your command handler code here
	CClientDC dc(this);											//���DC
	CBrush brush;
	brush.CreateSolidBrush(RGB(0,0,255));//������ˢ
	CRect rect;
	GetClientRect(&rect);//��ȡ�ͻ�������
	dc.FillRect(rect,&brush);//���ͻ���
	brush.DeleteObject();//ɾ����ˢ
	m_menuradio=2;

	
}

void CPopUpMenuView::OnUpdateMenublue(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->SetRadio(m_menuradio==3);
	
}

void CPopUpMenuView::OnRButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	CMenu menu;
	menu.LoadMenu(IDR_MENU1);
	CMenu* pPop=menu.GetSubMenu(0);//���������˵�
	pPop->CheckMenuRadioItem(0,2,m_menuradio,MF_BYPOSITION);//���õ�ѡ���
	CPoint pt;
	GetCursorPos(&pt);											//������λ��
	pPop->TrackPopupMenu(TPM_LEFTALIGN,pt.x,pt.y,this);			//���������˵�	
	CView::OnRButtonDown(nFlags, point);
}
