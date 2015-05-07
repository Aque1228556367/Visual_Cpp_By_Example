// ViewControlBoxView.cpp : implementation of the CViewControlBoxView class
//

#include "stdafx.h"
#include "ViewControlBox.h"

#include "ViewControlBoxDoc.h"
#include "ViewControlBoxView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CViewControlBoxView

IMPLEMENT_DYNCREATE(CViewControlBoxView, CView)

BEGIN_MESSAGE_MAP(CViewControlBoxView, CView)
	//{{AFX_MSG_MAP(CViewControlBoxView)
	ON_WM_CREATE()
	ON_BN_CLICKED(IDC_BUTTON, OnClickButton)//��ť�ؼ�����Ϣӳ��
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CViewControlBoxView construction/destruction

CViewControlBoxView::CViewControlBoxView()
{
	// TODO: add construction code here

}

CViewControlBoxView::~CViewControlBoxView()
{
}

BOOL CViewControlBoxView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CViewControlBoxView drawing

void CViewControlBoxView::OnDraw(CDC* pDC)
{
	CViewControlBoxDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// CViewControlBoxView printing

BOOL CViewControlBoxView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CViewControlBoxView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CViewControlBoxView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CViewControlBoxView diagnostics

#ifdef _DEBUG
void CViewControlBoxView::AssertValid() const
{
	CView::AssertValid();
}

void CViewControlBoxView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CViewControlBoxDoc* CViewControlBoxView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CViewControlBoxDoc)));
	return (CViewControlBoxDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CViewControlBoxView message handlers

BOOL CViewControlBoxView::Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext) 
{
	// TODO: Add your specialized code here and/or call the base class
	
	return CWnd::Create(lpszClassName, lpszWindowName, dwStyle, rect, pParentWnd, nID, pContext);
}

int CViewControlBoxView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// TODO: Add your specialized creation code here
	//�����б��
	m_listbox.Create(
		WS_CHILD|WS_VISIBLE|LBS_STANDARD|WS_HSCROLL,	//�б����
		CRect(20,20,200,100),	//�б���С	
		this,//��ָ��
		IDC_LISTBOX);//���б���Ӧ��ID��
	//���б��������ַ���
	m_listbox.AddString("Visual C++");
	m_listbox.AddString("Visual J++");
	m_listbox.AddString("Visual Basic");
	m_listbox.AddString("Visual stadio.net");
	m_listbox.AddString("Others");
	//������ť
	m_button.Create(
		"��ť�ؼ�",//��ť����
		WS_CHILD|WS_VISIBLE|WS_BORDER,	//��ť���
		CRect(50,100,150,130),	//��ť��С��λ��
		this,//��ť��ָ��
		IDC_BUTTON);	//�ð�ť���Ӧ��ID��
	return 0;
}
void CViewControlBoxView::OnClickButton()
{
	AfxMessageBox("��ť����ִ�гɹ�!");
}