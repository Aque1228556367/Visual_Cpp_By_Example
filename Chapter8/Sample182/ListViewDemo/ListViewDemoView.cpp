// ListViewDemoView.cpp : implementation of the CListViewDemoView class
//

#include "stdafx.h"
#include "ListViewDemo.h"

#include "ListViewDemoDoc.h"
#include "ListViewDemoView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CListViewDemoView

IMPLEMENT_DYNCREATE(CListViewDemoView, CListView)

BEGIN_MESSAGE_MAP(CListViewDemoView, CListView)
	//{{AFX_MSG_MAP(CListViewDemoView)
	ON_NOTIFY_REFLECT(NM_DBLCLK, OnDblclk)
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CListView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CListView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CListView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CListViewDemoView construction/destruction

CListViewDemoView::CListViewDemoView()
{
	// TODO: add construction code here

}

CListViewDemoView::~CListViewDemoView()
{
}

BOOL CListViewDemoView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CListView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CListViewDemoView drawing

void CListViewDemoView::OnDraw(CDC* pDC)
{
	CListViewDemoDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
}

void CListViewDemoView::OnInitialUpdate()
{
	CListView::OnInitialUpdate();
	// TODO: You may populate your ListView with items by directly accessing
	//  its list control through a call to GetListCtrl().
	//�����б�ؼ�Ϊ��������񣬵�һ�а���ĸ˳�򣬲��ÿؼ�������ʾѡ������
	GetListCtrl().ModifyStyle(0,LVS_REPORT|LVS_SHOWSELALWAYS|LVS_SORTASCENDING);
	//���б��ϻ��ߣ��ָ��б���к��У��ڶ��ַ�������û�ѡ�����С�
	GetListCtrl().SendMessage(LVM_SETEXTENDEDLISTVIEWSTYLE,0,LVS_EX_GRIDLINES|LVS_EX_FULLROWSELECT);
	CDC*pDC=GetDC();
	TEXTMETRIC tm;
	pDC->GetTextMetrics(&tm);
	//���б�������ӱ�ͷ
	GetListCtrl().InsertColumn(0,"����",LVCFMT_LEFT,30*tm.tmAveCharWidth,0);
	GetListCtrl().InsertColumn(1,"��ͥסַ",LVCFMT_LEFT,70*tm.tmAveCharWidth,1);
	GetListCtrl().InsertItem(0,"����");//������
	GetListCtrl().SetItemText(0,1,"ɽ��ʡ��̨��Ĳƽ��");
	GetListCtrl().InsertItem(1,"��С��");//������
	GetListCtrl().SetItemText(1,1,"ɽ��ʡ��ɽ��");
	GetListCtrl().InsertItem(2,"��С��");//������
	GetListCtrl().SetItemText(2,1,"����ʡ��ɳ��");
}

/////////////////////////////////////////////////////////////////////////////
// CListViewDemoView printing

BOOL CListViewDemoView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CListViewDemoView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CListViewDemoView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CListViewDemoView diagnostics

#ifdef _DEBUG
void CListViewDemoView::AssertValid() const
{
	CListView::AssertValid();
}

void CListViewDemoView::Dump(CDumpContext& dc) const
{
	CListView::Dump(dc);
}

CListViewDemoDoc* CListViewDemoView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CListViewDemoDoc)));
	return (CListViewDemoDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CListViewDemoView message handlers

void CListViewDemoView::OnDblclk(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	 for(int i=0; i<GetListCtrl().GetItemCount(); i++)					//���������б�ؼ�
      {
           if( GetListCtrl().GetItemState(i, LVIS_SELECTED) == LVIS_SELECTED )//��ȡѡ����
           {
				CString str=GetListCtrl().GetItemText(i,0);					//��ȡ���и��е���Ϣ
				AfxMessageBox("������"+str);
           }
      }
	*pResult = 0;
}
