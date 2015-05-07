// UseDlgRegularDllView.cpp : implementation of the CUseDlgRegularDllView class
//

#include "stdafx.h"
#include "UseDlgRegularDll.h"

#include "UseDlgRegularDllDoc.h"
#include "UseDlgRegularDllView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CUseDlgRegularDllView

IMPLEMENT_DYNCREATE(CUseDlgRegularDllView, CView)

BEGIN_MESSAGE_MAP(CUseDlgRegularDllView, CView)
	//{{AFX_MSG_MAP(CUseDlgRegularDllView)
	ON_WM_LBUTTONDBLCLK()
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CUseDlgRegularDllView construction/destruction

CUseDlgRegularDllView::CUseDlgRegularDllView()
{
	// TODO: add construction code here
	m_r=25;
	m_g=160;
	m_b=128;

}

CUseDlgRegularDllView::~CUseDlgRegularDllView()
{
}

BOOL CUseDlgRegularDllView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CUseDlgRegularDllView drawing

void CUseDlgRegularDllView::OnDraw(CDC* pDC)
{
	CUseDlgRegularDllDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
	CFont myfont;									//��������
	LOGFONT font;
	memset(&font,0,sizeof(LOGFONT));
	font.lfHeight=24;										//����߶�
	font.lfWeight=300;
	strcpy(font.lfFaceName,"Arial");							//������ʽ
	myfont.CreateFontIndirect(&font);
	pDC->SelectObject(&myfont);							//DC��������
	COLORREF crColor=RGB(m_r,m_g,m_b);
	pDC->SetTextColor(crColor);							//�����ı���ɫ
	pDC->TextOut(20,20,"˫��������������DLL�����ĶԻ�����ʾ�ı���ɫ��");	//����ı�

}

/////////////////////////////////////////////////////////////////////////////
// CUseDlgRegularDllView printing

BOOL CUseDlgRegularDllView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CUseDlgRegularDllView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CUseDlgRegularDllView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CUseDlgRegularDllView diagnostics

#ifdef _DEBUG
void CUseDlgRegularDllView::AssertValid() const
{
	CView::AssertValid();
}

void CUseDlgRegularDllView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CUseDlgRegularDllDoc* CUseDlgRegularDllView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CUseDlgRegularDllDoc)));
	return (CUseDlgRegularDllDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CUseDlgRegularDllView message handlers

void CUseDlgRegularDllView::OnLButtonDblClk(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	typedef void (*PFDlgShow)(int,int,int);					//�궨��PFDlgShow����ָ������
	HINSTANCE hdll;								//DLL�ľ��
	PFDlgShow dlgshow;								//����ָ��
	hdll=LoadLibrary("..\\DlgRegularDll.dll");					//LoadLibrary����װ��DLL
	if(hdll!=NULL)
	{
		//GetProcAddress�������ShowDlg������ַ
		dlgshow=(PFDlgShow)GetProcAddress(hdll,"ShowDlg");
		dlgshow(m_r,m_g,m_b);								//����DLL��ʾ�Ի���
	}
	else
	{
		AfxMessageBox("����DLLʧ�ܣ�");
		return;
	}
	FreeLibrary(hdll);									//�ͷ�DLL
	CView::OnLButtonDblClk(nFlags, point);
}
