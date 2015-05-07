// UIThreadDemoView.cpp : implementation of the CUIThreadDemoView class
//

#include "stdafx.h"
#include "UIThreadDemo.h"
#include "UIDlg.h"
#include "UIThread.h"
#include "UIThreadDemoDoc.h"
#include "UIThreadDemoView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CUIThreadDemoView


IMPLEMENT_DYNCREATE(CUIThreadDemoView, CView)

BEGIN_MESSAGE_MAP(CUIThreadDemoView, CView)
	//{{AFX_MSG_MAP(CUIThreadDemoView)
	ON_WM_TIMER()
	ON_WM_CREATE()
	ON_COMMAND(ID_UI_THREAD, OnUiThread)
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CUIThreadDemoView construction/destruction

CUIThreadDemoView::CUIThreadDemoView()
{
	// TODO: add construction code here

}

CUIThreadDemoView::~CUIThreadDemoView()
{
}

BOOL CUIThreadDemoView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CUIThreadDemoView drawing

void CUIThreadDemoView::OnDraw(CDC* pDC)
{
	CUIThreadDemoDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// CUIThreadDemoView printing

BOOL CUIThreadDemoView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CUIThreadDemoView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CUIThreadDemoView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CUIThreadDemoView diagnostics

#ifdef _DEBUG
void CUIThreadDemoView::AssertValid() const
{
	CView::AssertValid();
}

void CUIThreadDemoView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CUIThreadDemoDoc* CUIThreadDemoView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CUIThreadDemoDoc)));
	return (CUIThreadDemoDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CUIThreadDemoView message handlers

void CUIThreadDemoView::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	if(nIDEvent==1)
	{
	CClientDC dc(this);									//���DC
	CFont myfont;	
	CFont*oldfont;	
	LOGFONT font;
	memset(&font,0,sizeof(LOGFONT));						//Ϊ����ṹ����ֵ��Ĭ��ֵ
	font.lfHeight=30;									//����߶�Ϊ50
	font.lfWeight=600;
	strcpy(font.lfFaceName,"Arial");
	myfont.CreateFontIndirect(&font); 						//����������
	oldfont=dc.SelectObject(&myfont);						//��������ѡ���豸����*/
	CTime m_time;
	m_time=CTime::GetCurrentTime();						//��ȡ��ǰʱ������
	CString str=m_time.Format("��ǰʱ�䣺%H:%M:%S");			//��ʽ��
	dc.TextOut(20,20,str);//��ʾʱ��
	dc.SelectObject(oldfont);								//�ָ��豸�����еľ�����
	}
	CView::OnTimer(nIDEvent);
}

int CUIThreadDemoView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;
	// TODO: Add your specialized creation code here
	SetTimer(1,100,NULL);								//���ö�ʱ����ÿ0.1�봥��һ��	
	return 0;
}

void CUIThreadDemoView::OnUiThread() 
{
	// TODO: Add your command handler code here
/*	CUIDlg  *pDlg=new CUIDlg;
	pDlg->Create(IDD_DIALOG1);								//������ģ̬�Ի���
	pDlg->ShowWindow(SW_SHOW);							//��ʾ�Ի�*/
	//ʹ��AfxBeginThread���������û������߳�
	CWinThread *pThread=AfxBeginThread(RUNTIME_CLASS(CUIThread),0,0,NULL);	
}
