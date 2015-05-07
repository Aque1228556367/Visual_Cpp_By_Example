// WorkThreadDemoView.cpp : implementation of the CWorkThreadDemoView class
//

#include "stdafx.h"
#include "WorkThreadDemo.h"
#include "UIDlg.h"
#include "UIThread.h"
#include "WorkThreadDemoDoc.h"
#include "WorkThreadDemoView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CWorkThreadDemoView


IMPLEMENT_DYNCREATE(CWorkThreadDemoView, CView)

BEGIN_MESSAGE_MAP(CWorkThreadDemoView, CView)
	//{{AFX_MSG_MAP(CWorkThreadDemoView)
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
// CWorkThreadDemoView construction/destruction

CWorkThreadDemoView::CWorkThreadDemoView()
{
	// TODO: add construction code here

}

CWorkThreadDemoView::~CWorkThreadDemoView()
{
}

BOOL CWorkThreadDemoView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CWorkThreadDemoView drawing

void CWorkThreadDemoView::OnDraw(CDC* pDC)
{
	CWorkThreadDemoDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// CWorkThreadDemoView printing

BOOL CWorkThreadDemoView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CWorkThreadDemoView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CWorkThreadDemoView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CWorkThreadDemoView diagnostics

#ifdef _DEBUG
void CWorkThreadDemoView::AssertValid() const
{
	CView::AssertValid();
}

void CWorkThreadDemoView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CWorkThreadDemoDoc* CWorkThreadDemoView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CWorkThreadDemoDoc)));
	return (CWorkThreadDemoDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CWorkThreadDemoView message handlers

void CWorkThreadDemoView::OnTimer(UINT nIDEvent) 
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

int CWorkThreadDemoView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;
	// TODO: Add your specialized creation code here
	SetTimer(1,1000,NULL);								//���ö�ʱ����ÿ�봥��һ��	
	return 0;
}

void CWorkThreadDemoView::OnUiThread() 
{
	// TODO: Add your command handler code here
/*	CUIDlg  *pDlg=new CUIDlg;
	pDlg->Create(IDD_DIALOG1);								//������ģ̬�Ի���
	pDlg->ShowWindow(SW_SHOW);							//��ʾ�Ի�*/
	//ʹ��AfxBeginThread���������û������߳�
	CWinThread *pThread=AfxBeginThread(RUNTIME_CLASS(CUIThread),0,0,NULL);	
}
