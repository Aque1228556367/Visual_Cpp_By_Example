// DynaMemuView.cpp : implementation of the CDynaMemuView class
//

#include "stdafx.h"
#include "DynaMemu.h"

#include "DynaMemuDoc.h"
#include "DynaMemuView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDynaMemuView

IMPLEMENT_DYNCREATE(CDynaMemuView, CView)

BEGIN_MESSAGE_MAP(CDynaMemuView, CView)
	//{{AFX_MSG_MAP(CDynaMemuView)
	ON_COMMAND(ID_MENUCREATE, OnMenucreate)
	ON_UPDATE_COMMAND_UI(ID_MENUCREATE, OnUpdateMenucreate)
	ON_COMMAND(IDS_MENUNEW, OnMenunew)
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDynaMemuView construction/destruction

CDynaMemuView::CDynaMemuView()
{
	// TODO: add construction code here
	m_bcreate=true;

}

CDynaMemuView::~CDynaMemuView()
{
}

BOOL CDynaMemuView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CDynaMemuView drawing

void CDynaMemuView::OnDraw(CDC* pDC)
{
	CDynaMemuDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// CDynaMemuView printing

BOOL CDynaMemuView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CDynaMemuView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CDynaMemuView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CDynaMemuView diagnostics

#ifdef _DEBUG
void CDynaMemuView::AssertValid() const
{
	CView::AssertValid();
}

void CDynaMemuView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CDynaMemuDoc* CDynaMemuView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CDynaMemuDoc)));
	return (CDynaMemuDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CDynaMemuView message handlers

void CDynaMemuView::OnMenucreate() 
{
	// TODO: Add your command handler code here
	CClientDC dc(this);											//���DC
	dc.TextOut(30,40,"�������˵�������Ӧ�ɹ����Ѿ�������²˵���!");				//����ı�
	CWnd *pWnd=AfxGetApp()->GetMainWnd( );					//��ô���ָ��
	CMenu * pMenu=pWnd->GetMenu( );							//���menuָ��
	pMenu=pMenu->GetSubMenu(4);							//��ò˵���("����"��)
	pMenu->AppendMenu(MF_SEPARATOR);						//���ӷָ���
	//���Ӳ˵���"ֹͣ����(&S)"
	pMenu->AppendMenu(MF_STRING,IDS_MENUNEW,"�²˵���(&N)"); 										//�ı���������
	m_bcreate=false;
}

void CDynaMemuView::OnUpdateMenucreate(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(m_bcreate);
}
void CDynaMemuView::OnMenunew() 
{
	// TODO: Add your command handler code here
	CClientDC dc(this);											//���DC
	dc.TextOut(30,40,"����ӵĲ˵�����Ӧ�ɹ�����ɾ����ӵ��²˵���!");				//����ı�
	CWnd *pWnd=AfxGetApp()->GetMainWnd( );					//��ô���ָ��
	CMenu * pMenu=pWnd->GetMenu( );							//���menuָ��
	pMenu=pMenu->GetSubMenu(4);							//��ò˵���("����"��)
	pMenu->RemoveMenu(2, MF_BYPOSITION);				//��"ֹͣ����"�˵���ɾ��
	pMenu->RemoveMenu(1, MF_BYPOSITION);					//���ָ���ɾ��
	m_bcreate=true;
}