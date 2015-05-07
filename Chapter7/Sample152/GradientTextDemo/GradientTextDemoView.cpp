// GradientTextDemoView.cpp : implementation of the CGradientTextDemoView class
//

#include "stdafx.h"
#include "GradientTextDemo.h"

#include "GradientTextDemoDoc.h"
#include "GradientTextDemoView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CGradientTextDemoView

IMPLEMENT_DYNCREATE(CGradientTextDemoView, CView)

BEGIN_MESSAGE_MAP(CGradientTextDemoView, CView)
	//{{AFX_MSG_MAP(CGradientTextDemoView)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGradientTextDemoView construction/destruction

CGradientTextDemoView::CGradientTextDemoView()
{
	// TODO: add construction code here

}

CGradientTextDemoView::~CGradientTextDemoView()
{
}

BOOL CGradientTextDemoView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CGradientTextDemoView drawing

void CGradientTextDemoView::OnDraw(CDC* pDC)
{
	CGradientTextDemoDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
	//�õ��ͻ����Ĵ�С
	CRect rcClient;
	GetClientRect (rcClient);	
	//��������ַ���.
	CString str (_T ("������ת���ı�!"));
	//���͸������
	pDC->SetBkMode (TRANSPARENT);
	CFont font;
	LOGFONT ft;
	memset(&ft,0,sizeof(LOGFONT));				//Ϊ����ṹ����ֵ��Ĭ��ֵ
	ft.lfHeight=17;								//����߶�Ϊ80
	ft.lfWeight=600;
	ft.lfItalic=TRUE;							//����б��
	ft.lfCharSet=GB2312_CHARSET;				//�����ַ���
	strcpy(ft.lfFaceName,"����_GB2312");			//�ַ���
	int r=10;
	int g=250;
	//ÿ��20������ַ���
	for (int nAngle=0; nAngle<3600; nAngle+=200)
	{
		//�趨�µ���ת�Ƕ�
		ft.lfEscapement=nAngle;
		
		//�������岢ѡ���豸����
		font.CreateFontIndirect(&ft);
		CFont* pOldFont=pDC ->SelectObject(&font);
		pDC->SetTextColor (RGB (r,g,200));
		r+=12;
		g-=12;
		//�������
		pDC->TextOut(rcClient.left + rcClient.Width()/2,rcClient.top + rcClient.Height()/2,str);	
		//ԭ������
		pDC->SelectObject(pOldFont);
		font.DeleteObject();
	}
}

/////////////////////////////////////////////////////////////////////////////
// CGradientTextDemoView printing

BOOL CGradientTextDemoView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CGradientTextDemoView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CGradientTextDemoView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CGradientTextDemoView diagnostics

#ifdef _DEBUG
void CGradientTextDemoView::AssertValid() const
{
	CView::AssertValid();
}

void CGradientTextDemoView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CGradientTextDemoDoc* CGradientTextDemoView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CGradientTextDemoDoc)));
	return (CGradientTextDemoDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CGradientTextDemoView message handlers
