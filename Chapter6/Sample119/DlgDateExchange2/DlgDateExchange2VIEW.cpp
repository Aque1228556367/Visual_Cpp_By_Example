// DlgDateExchange2View.cpp : implementation of the CDlgDateExchange2View class
//

#include "stdafx.h"
#include "DlgDateExchange2.h"


#include "DlgDateExchange2Doc.h"
#include "DlgDateExchange2View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
#define WM_SET_COLOR WM_USER+100//�Զ�����Ϣ
/////////////////////////////////////////////////////////////////////////////
// CDlgDateExchange2View

IMPLEMENT_DYNCREATE(CDlgDateExchange2View, CView)

BEGIN_MESSAGE_MAP(CDlgDateExchange2View, CView)
	//{{AFX_MSG_MAP(CDlgDateExchange2View)
	ON_WM_RBUTTONDOWN()
	ON_MESSAGE(WM_SET_COLOR,OnSetColor) 
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgDateExchange2View construction/destruction

CDlgDateExchange2View::CDlgDateExchange2View()
{
	// TODO: add construction code here
	r=128;
	g=200;
	b=0;
}

CDlgDateExchange2View::~CDlgDateExchange2View()
{
}

BOOL CDlgDateExchange2View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	pDialog = new CTextColorDlg(this);							
   //Check if new succeeded and we got a valid pointer to a dialog object
   if(pDialog != NULL)
   {
	  BOOL ret = pDialog->Create(IDD_DIALOG1,this);				//������ģ̬�Ի���
      if(!ret)   											//����ʧ��
      AfxMessageBox("�����Ի���ʧ��");	
   }
   else
      AfxMessageBox("�Ի��������ʧ��");
	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CDlgDateExchange2View drawing

void CDlgDateExchange2View::OnDraw(CDC* pDC)
{
	CDlgDateExchange2Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
	CFont myfont;									//��������
	LOGFONT font;
	memset(&font,0,sizeof(LOGFONT));
	font.lfHeight=20;										//����߶�
	font.lfWeight=500;
	strcpy(font.lfFaceName,"Arial");							//������ʽ
	myfont.CreateFontIndirect(&font);
	pDC->SelectObject(&myfont);							//DC��������
	COLORREF crColor=RGB(r,g,b);
	pDC->SetTextColor(crColor);							//�����ı���ɫ
	pDC->TextOut(20,20,"��������Ҽ�������ģ̬�Ի���");	//����ı�
	pDC->TextOut(20,50,"ʵ�ַ�ģ̬�Ի�������ݽ�����");	//����ı�
}

/////////////////////////////////////////////////////////////////////////////
// CDlgDateExchange2View printing

BOOL CDlgDateExchange2View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CDlgDateExchange2View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CDlgDateExchange2View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CDlgDateExchange2View diagnostics

#ifdef _DEBUG
void CDlgDateExchange2View::AssertValid() const
{
	CView::AssertValid();
}

void CDlgDateExchange2View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CDlgDateExchange2Doc* CDlgDateExchange2View::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CDlgDateExchange2Doc)));
	return (CDlgDateExchange2Doc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CDlgDateExchange2View message handlers

void CDlgDateExchange2View::OnRButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	  pDialog->ShowWindow(SW_HIDE);						//���ضԻ���
	  CRect dlgRect;
	  pDialog->GetWindowRect(&dlgRect);				//��ȡ�Ի��򴰿ڴ�С
	  ClientToScreen(&point);//�����λ��ת��Ϊ��Ļ����
	  //�ƶ��Ի��򴰿�
	  pDialog->MoveWindow(point.x, point.y,dlgRect.Width(),dlgRect.Height());
	  //����ǰ��ˢ��ֵ����Ի������
	  pDialog->m_blue=b;
	  pDialog->m_green=g;
	  pDialog->m_red=r;
	  pDialog->UpdateData(false);//���¿ؼ�
      pDialog->ShowWindow(SW_SHOW);						//��ʾ�Ի���	
	CView::OnRButtonDown(nFlags, point);
}

void CDlgDateExchange2View::OnSetColor(WPARAM wP,LPARAM lP)
{
	//��ȡ��ģ̬�Ի������õ���ɫֵ
	r=pDialog->m_red;
	g=pDialog->m_green;
	b=pDialog->m_blue;
	Invalidate();//������ͼ
}
