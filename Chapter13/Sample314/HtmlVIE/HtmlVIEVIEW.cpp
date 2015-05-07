// HtmlVIEView.cpp : implementation of the CHtmlVIEView class
//

#include "stdafx.h"
#include "HtmlVIE.h"
#include "mainfrm.h"
#include "HtmlVIEDoc.h"
#include "HtmlVIEView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CHtmlVIEView

IMPLEMENT_DYNCREATE(CHtmlVIEView, CHtmlView)

BEGIN_MESSAGE_MAP(CHtmlVIEView, CHtmlView)
	//{{AFX_MSG_MAP(CHtmlVIEView)
	ON_BN_CLICKED(IDC_GO, OnGo)
	ON_BN_CLICKED(IDC_REFLESH, OnReflesh)
	ON_BN_CLICKED(IDC_STOP, OnStop)
	ON_BN_CLICKED(IDC_BACK, OnBack)
	ON_CBN_EDITCHANGE(IDC_COMBO1, OnEditchangeCombo1)
	ON_CBN_SELCHANGE(IDC_COMBO1, OnSelchangeCombo1)
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CHtmlView::OnFilePrint)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CHtmlVIEView construction/destruction

CHtmlVIEView::CHtmlVIEView()
{
	// TODO: add construction code here

}

CHtmlVIEView::~CHtmlVIEView()
{
}

BOOL CHtmlVIEView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CHtmlView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CHtmlVIEView drawing

void CHtmlVIEView::OnDraw(CDC* pDC)
{
	CHtmlVIEDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
}

void CHtmlVIEView::OnInitialUpdate()
{
	CHtmlView::OnInitialUpdate();
	// TODO: This code navigates to a popular spot on the web.
	//  change the code to go where you'd like.
	Navigate2(_T("http://www.microsoft.com/visualc/"),NULL,NULL);
}

/////////////////////////////////////////////////////////////////////////////
// CHtmlVIEView printing


/////////////////////////////////////////////////////////////////////////////
// CHtmlVIEView diagnostics

#ifdef _DEBUG
void CHtmlVIEView::AssertValid() const
{
	CHtmlView::AssertValid();
}

void CHtmlVIEView::Dump(CDumpContext& dc) const
{
	CHtmlView::Dump(dc);
}

CHtmlVIEDoc* CHtmlVIEView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CHtmlVIEDoc)));
	return (CHtmlVIEDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CHtmlVIEView message handlers

void CHtmlVIEView::OnGo() //����
{
	// TODO: Add your control notification handler code here
	CClientDC dc(this);
	dc.TextOut(4,18,CString("��������<")+m_site+">...");					//��ʾ��Ϣ
	Navigate2(m_site);								//����ҳ
	Invalidate(FALSE);										//������ͼ
	CMainFrame *pframe=(CMainFrame *)AfxGetMainWnd();			//��ȡ�����ָ��
	CDialogBar *pbar=pframe->GetDialogBar();						//��ȡ�Ի���ָ��
	CComboBox *pcombobox;
	pcombobox=(CComboBox *)pbar->GetDlgItem(IDC_COMBO1);
	pcombobox->AddString(m_site);									//����б��	
}

void CHtmlVIEView::OnReflesh() //ˢ��
{
	// TODO: Add your control notification handler code here
	Refresh();												//ˢ��
	Invalidate(FALSE);										//������ͼ
}

void CHtmlVIEView::OnStop() //ֹͣ
{
	// TODO: Add your control notification handler code here
	Stop();												//ֹͣ������ҳ
	Invalidate(FALSE);										//������ͼ

}
void CHtmlVIEView::OnBack() //����
{
	// TODO: Add your control notification handler code here
	GoBack();
	Invalidate(FALSE);										//������ͼ
}

void CHtmlVIEView::OnEditchangeCombo1() 
{
	// TODO: Add your control notification handler code here
	CMainFrame *pframe=(CMainFrame *)AfxGetMainWnd();			//��ȡ�����ָ��
	CDialogBar *pbar=pframe->GetDialogBar();						//��ȡ�Ի���ָ��
	pbar->GetDlgItemText(IDC_COMBO1,m_site);					//��ȡ��Ͽ��е�����	
}

void CHtmlVIEView::OnSelchangeCombo1() 
{
	// TODO: Add your control notification handler code here
	CMainFrame *pframe=(CMainFrame *)AfxGetMainWnd();			//��ȡ�����ָ��
	CDialogBar *pbar=pframe->GetDialogBar();						//��ȡ�Ի���ָ��
	pbar->GetDlgItemText(IDC_COMBO1,m_site);					//��ȡ��Ͽ��е�����
	OnGo();												//ִ�д���ҳ		
}
