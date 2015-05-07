// BottomEdieView.cpp : implementation file
//

#include "stdafx.h"
#include "MultiViewDemo.h"
#include "BottomEditView.h"
#include "MultiViewDemoDoc.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CBottomEdieView

IMPLEMENT_DYNCREATE(CBottomEditView, CEditView)

CBottomEditView::CBottomEditView()
{
}

CBottomEditView::~CBottomEditView()
{
}


BEGIN_MESSAGE_MAP(CBottomEditView, CEditView)
	//{{AFX_MSG_MAP(CBottomEdieView)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBottomEdieView drawing

void CBottomEditView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: add draw code here
}

/////////////////////////////////////////////////////////////////////////////
// CBottomEdieView diagnostics

#ifdef _DEBUG
void CBottomEditView::AssertValid() const
{
	CEditView::AssertValid();
}

void CBottomEditView::Dump(CDumpContext& dc) const
{
	CEditView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CBottomEdieView message handlers
void CBottomEditView::OnInitialUpdate() 
{
	CEditView::OnInitialUpdate();
	// TODO: Add your specialized code here and/or call the base class
	CEdit &mEdit=GetEditCtrl();//��ȡ�༭��ͼ�ؼ�
	mEdit.SetWindowText("�ȴ��û�����ѧ����Ϣ��");//������ʾ��Ϣ
	mEdit.EnableWindow(false);//�༭�ؼ����ɱ༭
}
void CBottomEditView::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint) 
{
	// TODO: Add your specialized code here and/or call the base class
	CMultiViewDemoDoc* pDoc =(CMultiViewDemoDoc*)GetDocument();//��ȡ�ĵ�ָ��
	if(pDoc->add)//���������
	{
		CString str;
		str="�����ѧ��Ϊ"+pDoc->infoArray[0].GetAt(0)+"��ѧ����Ϣ��";
		CEdit &mEdit=GetEditCtrl();//��ȡ�༭��ͼ�ؼ�
		mEdit.SetWindowText(str);//��ʾ��Ϣ
	}
}