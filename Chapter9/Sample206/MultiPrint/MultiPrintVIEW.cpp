// MultiPrintView.cpp : implementation of the CMultiPrintView class
//

#include "stdafx.h"
#include "MultiPrint.h"

#include "MultiPrintDoc.h"
#include "MultiPrintView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMultiPrintView

IMPLEMENT_DYNCREATE(CMultiPrintView, CScrollView)

BEGIN_MESSAGE_MAP(CMultiPrintView, CScrollView)
	//{{AFX_MSG_MAP(CMultiPrintView)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CScrollView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMultiPrintView construction/destruction

CMultiPrintView::CMultiPrintView():m_rectPrint(0,0,1440*6,-1440*10)
{
	// TODO: add construction code here
}

CMultiPrintView::~CMultiPrintView()
{
}

BOOL CMultiPrintView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CScrollView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CMultiPrintView drawing

void CMultiPrintView::OnDraw(CDC* pDC)
{
	CMultiPrintDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
	pDC->Rectangle(m_rectPrint+CRect(-1600,700,1600,-700));//������ʾ����߿�
	CFont font;
	LOGFONT ft;
	memset(&ft,0,sizeof(LOGFONT));					//Ϊ����ṹ����ֵ��Ĭ��ֵ
	ft.lfHeight=450;									//����߶�
	ft.lfCharSet=GB2312_CHARSET;						//�����ַ���
	strcpy(ft.lfFaceName,"����_GB2312");					//�ַ���
	font.CreateFontIndirect(&ft);
	CFont* pOldFont=pDC ->SelectObject(&font);
	int j=pDoc->m_stringArray.GetSize();
	int nHeight=(m_rectPrint.Height()-1200)/(j+2);//ÿ�еļ��
	for(int i=0;i<j;i++)
	{
		pDC->TextOut(3000,i*nHeight-1000,pDoc->m_stringArray[i]);//����ı�
	}
	pDC->SelectObject(pOldFont);
}

void CMultiPrintView::OnInitialUpdate()
{
	CScrollView::OnInitialUpdate();
	CSize sizeTotal(m_rectPrint.Width(),-m_rectPrint.Height()+700);//��������
	CSize sizePage(sizeTotal.cx/2,sizeTotal.cy/2);
	CSize sizeLine(sizeTotal.cx/50,sizeTotal.cy/50);
	SetScrollSizes(MM_TWIPS, sizeTotal,sizePage,sizeLine);
}

/////////////////////////////////////////////////////////////////////////////
// CMultiPrintView printing

BOOL CMultiPrintView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	CMultiPrintDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	pInfo->SetMaxPage(pDoc->m_stringArray.GetUpperBound()/pDoc->m_LinePerPage+1);//����ÿҳ��ʾ���������ô�ӡҳ��
	return DoPreparePrinting(pInfo);
}

void CMultiPrintView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CMultiPrintView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CMultiPrintView diagnostics

#ifdef _DEBUG
void CMultiPrintView::AssertValid() const
{
	CScrollView::AssertValid();
}

void CMultiPrintView::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}

CMultiPrintDoc* CMultiPrintView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMultiPrintDoc)));
	return (CMultiPrintDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMultiPrintView message handlers

void CMultiPrintView::OnPrint(CDC* pDC, CPrintInfo* pInfo) 
{
	// TODO: Add your specialized code here and/or call the base class
	CMultiPrintDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	int i,nStar,nEnd,nHeight;
	pDC->SetMapMode(MM_TWIPS);//����ӳ��ģʽ
	pDC->Rectangle(m_rectPrint+CRect(-1600,700,1600,-700));//���ƴ�ӡ����߿�
	CFont font;
	LOGFONT ft;
	memset(&ft,0,sizeof(LOGFONT));					//Ϊ����ṹ����ֵ��Ĭ��ֵ
	ft.lfHeight=700;									//����߶�
	ft.lfCharSet=GB2312_CHARSET;						//�����ַ���
	strcpy(ft.lfFaceName,"����_GB2312");					//�ַ���
	font.CreateFontIndirect(&ft);
	CFont* pOldFont=pDC ->SelectObject(&font);//��������
	m_nPage=pInfo->m_nCurPage;
	nStar=(m_nPage-1)*(pDoc->m_LinePerPage);
	nEnd=nStar+(pDoc->m_LinePerPage);
	nHeight=(m_rectPrint.Height())/(pDoc->m_LinePerPage+1);//ÿ�еļ��
	for( i=nStar;i<nEnd;i++)
	{
		if(i>pDoc->m_stringArray.GetUpperBound())//��������߽�
			break;
		pDC->TextOut(3000,(i-nStar)*nHeight-2000,pDoc->m_stringArray[i]);//����ı�
	}
	pDC->SelectObject(pOldFont);
//	CScrollView::OnPrint(pDC, pInfo);//����Ĭ�Ϻ�����OnDraw�ĵ���
}
