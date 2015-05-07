// BaseDlgDemo2View.cpp : implementation of the CBaseDlgDemo2View class
//

#include "stdafx.h"
#include "BaseDlgDemo2.h"

#include "BaseDlgDemo2Doc.h"
#include "BaseDlgDemo2View.h"
#include "MyDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CBaseDlgDemo2View

IMPLEMENT_DYNCREATE(CBaseDlgDemo2View, CView)

BEGIN_MESSAGE_MAP(CBaseDlgDemo2View, CView)
	//{{AFX_MSG_MAP(CBaseDlgDemo2View)
	ON_COMMAND(ID_CREATEDLG, OnCreatedlg)
	ON_COMMAND(ID_CREATEDLG2, OnCreatedlg2)
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBaseDlgDemo2View construction/destruction

CBaseDlgDemo2View::CBaseDlgDemo2View()
{
	// TODO: add construction code here

}

CBaseDlgDemo2View::~CBaseDlgDemo2View()
{
}

BOOL CBaseDlgDemo2View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CBaseDlgDemo2View drawing

void CBaseDlgDemo2View::OnDraw(CDC* pDC)
{
	CBaseDlgDemo2Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
	pDC->TextOut(30,30,szOut);
}

/////////////////////////////////////////////////////////////////////////////
// CBaseDlgDemo2View printing

BOOL CBaseDlgDemo2View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CBaseDlgDemo2View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CBaseDlgDemo2View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CBaseDlgDemo2View diagnostics

#ifdef _DEBUG
void CBaseDlgDemo2View::AssertValid() const
{
	CView::AssertValid();
}

void CBaseDlgDemo2View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CBaseDlgDemo2Doc* CBaseDlgDemo2View::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CBaseDlgDemo2Doc)));
	return (CBaseDlgDemo2Doc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CBaseDlgDemo2View message handlers

void CBaseDlgDemo2View::OnCreatedlg() 
{
	MyDialog dlg;//�����Ի�����ʵ��
	int nRet=dlg.DoModal();//��ʾ�Ի��򣬲���ȥ�Ի���ķ���ֵ	
	szOut.Format("ģ̬�Ի���ķ���ֵΪ %d",nRet);
	Invalidate(true);//������ʾ
}


void CBaseDlgDemo2View::OnCreatedlg2() 
{
	// TODO: Add your command handler code here
	MyDialog* pDialog;										//�Ի��������ָ�� 
	pDialog = new MyDialog();							
   //Check if new succeeded and we got a valid pointer to a dialog object
   if(pDialog != NULL)
   {
	  BOOL ret = pDialog->Create(IDD_DIALOG1,this);				//������ģ̬�Ի���
      if(!ret)   											//����ʧ��
      AfxMessageBox("�����Ի���ʧ��");
	  CRect clientRect,dlgRect;
	  GetClientRect(&clientRect);								//��ȡ�ͻ������ڴ�С
	  ClientToScreen(clientRect);								//ת��Ϊ��Ļ����
	  pDialog->GetWindowRect(&dlgRect);						//��ȡ�Ի��򴰿ڴ�С
	  //�ƶ��Ի��򴰿�
	  pDialog->MoveWindow(clientRect.left+30, clientRect.top+50,dlgRect.Width(),dlgRect.Height());
      pDialog->ShowWindow(SW_SHOW);						//��ʾ�Ի���
	  szOut="��������ָ��λ����ʾ��ģ̬�Ի���";
	  Invalidate(true);//������ʾ
   }
   else
      AfxMessageBox("�����Ի������ʧ��");
}
