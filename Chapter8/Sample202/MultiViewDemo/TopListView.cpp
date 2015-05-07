// TopListView.cpp : implementation file
//

#include "stdafx.h"
#include "MultiViewDemo.h"
#include "TopListView.h"
#include "MultiViewDemoDoc.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTopListView

IMPLEMENT_DYNCREATE(CTopListView, CListView)



CTopListView::CTopListView()
{
}

CTopListView::~CTopListView()
{
}


BEGIN_MESSAGE_MAP(CTopListView, CListView)
	//{{AFX_MSG_MAP(CTopListView)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTopListView drawing



void CTopListView::OnDraw(CDC* pDC)
{
}

/////////////////////////////////////////////////////////////////////////////
// CTopListView diagnostics

#ifdef _DEBUG
void CTopListView::AssertValid() const
{
	CListView::AssertValid();
}

void CTopListView::Dump(CDumpContext& dc) const
{
	CListView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CTopListView message handlers

void CTopListView::OnInitialUpdate() 
{
	CListView::OnInitialUpdate();
	CString m_ColumnLabelStr[] ={"ѧ��","����","רҵ","����"};//��ͷ�ֶ�
	// TODO: Add your specialized code here and/or call the base class
	CListCtrl& listctrl=GetListCtrl();//��ȡ�б��ӿؼ�
	listctrl.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES|LVS_EX_UNDERLINEHOT);
	int width[6]={80,80,110,150};//���еĳ�ʼ���
	for(int i=0; i<4; i++)
	{
		listctrl.InsertColumn(i, m_ColumnLabelStr[i], LVCFMT_LEFT, width[i]);//���ñ�ͷ
	}	
}

BOOL CTopListView::PreCreateWindow(CREATESTRUCT& cs) 
{
	// TODO: Add your specialized code here and/or call the base class
	cs.style=cs.style|LVS_REPORT;//���óɱ����б���ʾ
	return CListView::PreCreateWindow(cs);
}

void CTopListView::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint) 
{
	// TODO: Add your specialized code here and/or call the base class
	CMultiViewDemoDoc* pDoc =(CMultiViewDemoDoc*)GetDocument();//��ȡ�ĵ�ָ��
	if(pDoc->add)//���������
	{
		CListCtrl& listctrl=GetListCtrl();//��ȡ�б�ؼ�
		listctrl.DeleteAllItems();//ɾ��������	
		for(int i=0;i<pDoc->infoArray[0].GetSize();i++)//�б���в�������
		{
			listctrl.InsertItem(i,pDoc->infoArray[0].GetAt(i));
			listctrl.SetItemText(i,1,pDoc->infoArray[1].GetAt(i));
			listctrl.SetItemText(i,2,pDoc->infoArray[2].GetAt(i));
			listctrl.SetItemText(i,3,pDoc->infoArray[3].GetAt(i));
		}
	}	
}
