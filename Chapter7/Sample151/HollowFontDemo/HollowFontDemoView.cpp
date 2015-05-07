// HollowFontDemoView.cpp : implementation of the CHollowFontDemoView class
//

#include "stdafx.h"
#include "HollowFontDemo.h"

#include "HollowFontDemoDoc.h"
#include "HollowFontDemoView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CHollowFontDemoView

IMPLEMENT_DYNCREATE(CHollowFontDemoView, CView)

BEGIN_MESSAGE_MAP(CHollowFontDemoView, CView)
	//{{AFX_MSG_MAP(CHollowFontDemoView)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CHollowFontDemoView construction/destruction

CHollowFontDemoView::CHollowFontDemoView()
{
	// TODO: add construction code here
	LOGFONT font;
	memset(&font,0,sizeof(LOGFONT));				//Ϊ����ṹ����ֵ��Ĭ��ֵ
	font.lfHeight=80;								//����߶�Ϊ50
	font.lfWeight=600;
	font.lfItalic=TRUE;							//����б��
	font.lfCharSet=GB2312_CHARSET;//�����ַ���
	strcpy(font.lfFaceName,"����_GB2312");		//�ַ���
	m_font.CreateFontIndirect(&font); 			//����������
}

CHollowFontDemoView::~CHollowFontDemoView()
{
}

BOOL CHollowFontDemoView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CHollowFontDemoView drawing

void CHollowFontDemoView::OnDraw(CDC* pDC)
{
	CHollowFontDemoDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
	CString str="����������";
	int cx=50,cy=50;//����ı�λ��
	CFont* oldfont=pDC->SelectObject(&m_font);				//��������ѡ���豸����
	pDC->SetBkMode(TRANSPARENT);				//�ı�����͸������ɫ
	pDC->SetTextColor(::GetSysColor(COLOR_3DSHADOW));
	pDC->TextOut(cx+2,cy-2,str);
	pDC->TextOut(cx-2,cy+2,str);
	pDC->SetTextColor(::GetSysColor(COLOR_3DHILIGHT));
	pDC->TextOut(cx+1,cy-1,str);
	pDC->TextOut(cx-1,cy+1,str);
	//����·����������ı�
	pDC->BeginPath();
	pDC->TextOut(cx,cy,str);
	pDC->EndPath();
	pDC->SetPolyFillMode(WINDING);//�������ģʽ
	pDC->StrokeAndFillPath();//����·�����
	pDC->SelectObject(oldfont);//�ָ�����

}

/////////////////////////////////////////////////////////////////////////////
// CHollowFontDemoView printing

BOOL CHollowFontDemoView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CHollowFontDemoView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CHollowFontDemoView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CHollowFontDemoView diagnostics

#ifdef _DEBUG
void CHollowFontDemoView::AssertValid() const
{
	CView::AssertValid();
}

void CHollowFontDemoView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CHollowFontDemoDoc* CHollowFontDemoView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CHollowFontDemoDoc)));
	return (CHollowFontDemoDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CHollowFontDemoView message handlers
