// SinglePrintView.cpp : implementation of the CSinglePrintView class
//

#include "stdafx.h"
#include "SinglePrint.h"

#include "SinglePrintDoc.h"
#include "SinglePrintView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSinglePrintView

IMPLEMENT_DYNCREATE(CSinglePrintView, CScrollView)

BEGIN_MESSAGE_MAP(CSinglePrintView, CScrollView)
	//{{AFX_MSG_MAP(CSinglePrintView)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CScrollView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSinglePrintView construction/destruction

CSinglePrintView::CSinglePrintView():m_rectPrint(0,0,1440*6,-1440*10)
{
	// TODO: add construction code here
}

CSinglePrintView::~CSinglePrintView()
{
}

BOOL CSinglePrintView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CScrollView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CSinglePrintView drawing

void CSinglePrintView::OnDraw(CDC* pDC)
{
	CSinglePrintDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
	pDC->Rectangle(m_rectPrint+CRect(-1600,700,1600,-700));//���ƴ�ӡ����߿�
	CFont font;
	LOGFONT ft;
	memset(&ft,0,sizeof(LOGFONT));					//Ϊ����ṹ����ֵ��Ĭ��ֵ
	ft.lfHeight=650;									//����߶�
	ft.lfCharSet=GB2312_CHARSET;						//�����ַ���
	strcpy(ft.lfFaceName,"����_GB2312");					//�ַ���
	font.CreateFontIndirect(&ft);
	CFont* pOldFont=pDC ->SelectObject(&font);
	int j=pDoc->m_stringArray.GetSize();
	int nHeight=(m_rectPrint.Height()-1200)/9;//ÿ�еļ��
	for(int i=0;i<j;i++)
	{
		pDC->TextOut(3000,i*nHeight-1000,pDoc->m_stringArray[i]);//����ı�
	}
	pDC->SelectObject(pOldFont);
}

void CSinglePrintView::OnInitialUpdate()
{
	CScrollView::OnInitialUpdate();
	CSize sizeTotal(m_rectPrint.Width(),-m_rectPrint.Height()+700);//��������
	CSize sizePage(sizeTotal.cx/2,sizeTotal.cy/2);
	CSize sizeLine(sizeTotal.cx/50,sizeTotal.cy/50);
	SetScrollSizes(MM_TWIPS, sizeTotal,sizePage,sizeLine);
}

/////////////////////////////////////////////////////////////////////////////
// CSinglePrintView printing

BOOL CSinglePrintView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	pInfo->SetMaxPage(1);
	return DoPreparePrinting(pInfo);
}

void CSinglePrintView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CSinglePrintView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CSinglePrintView diagnostics

#ifdef _DEBUG
void CSinglePrintView::AssertValid() const
{
	CScrollView::AssertValid();
}

void CSinglePrintView::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}

CSinglePrintDoc* CSinglePrintView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CSinglePrintDoc)));
	return (CSinglePrintDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CSinglePrintView message handlers
