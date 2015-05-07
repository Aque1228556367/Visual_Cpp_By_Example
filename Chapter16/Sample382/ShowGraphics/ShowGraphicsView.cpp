// ShowGraphicsView.cpp : implementation of the CShowGraphicsView class
//

#include "stdafx.h"
#include "ShowGraphics.h"

#include "ShowGraphicsDoc.h"
#include "ShowGraphicsView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CShowGraphicsView

IMPLEMENT_DYNCREATE(CShowGraphicsView, CScrollView)

BEGIN_MESSAGE_MAP(CShowGraphicsView, CScrollView)
	//{{AFX_MSG_MAP(CShowGraphicsView)
	ON_COMMAND(ID_NORMAL, OnNormal)
	ON_COMMAND(ID_ENLARGE, OnEnlarge)
	ON_COMMAND(ID_ENSMALL, OnEnsmall)
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CScrollView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CShowGraphicsView construction/destruction

CShowGraphicsView::CShowGraphicsView()
{
	//��ʼ����Ա����
	m_nScale = 100;
	m_lPciture = NULL;

}

CShowGraphicsView::~CShowGraphicsView()
{
}

BOOL CShowGraphicsView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CScrollView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CShowGraphicsView drawing

void CShowGraphicsView::OnDraw(CDC* pDC)
{
	CShowGraphicsDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
	if (!m_lPciture)
		return;
	// ��ȡͼ��ĳ��ȺͿ��
	long hmWidth;
	long hmHeight;
	m_lPciture->get_Width(&hmWidth);//ͼ��ĳ���
	m_lPciture->get_Height(&hmHeight);//ͼ��Ŀ��
	SIZE sz;
	sz.cx = hmWidth;
	sz.cy = hmHeight;
	pDC->HIMETRICtoDP (&sz);//��OLE����ߴ�ת��Ϊ����ֵ 
	sz.cx = (sz.cx * m_nScale) / 100;
	sz.cy = (sz.cy * m_nScale) / 100;
	RECT rc;
	GetClientRect(&rc);
	SetScrollSizes(MM_TEXT, sz);//���ù������ڵĳߴ�
	// ��ʾͼ��
	m_lPciture->Render(pDC->m_hDC,
				  0,			//	ˮƽ����λ��
				  0,			//	��ֱ����λ��
				  sz.cx,		//	ˮƽ�ߴ�
				  sz.cy,		//	��ֱ�ߴ�
				  0,		//	Դͼ���ˮƽƫ��
				  hmHeight,	//	Դͼ��Ĵ�ֱƫ��
				  hmWidth,		//����Դͼ���ˮƽ����
				  -hmHeight,	//����Դͼ��Ĵ�ֱ����
				  &rc);			//��ʾͼ��ľ�������
}

void CShowGraphicsView::OnInitialUpdate()
{
	CScrollView::OnInitialUpdate();

	CSize sizeTotal;
	// TODO: calculate the total size of this view
	sizeTotal.cx = sizeTotal.cy = 100;
	SetScrollSizes(MM_TEXT, sizeTotal);
}

/////////////////////////////////////////////////////////////////////////////
// CShowGraphicsView printing

BOOL CShowGraphicsView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CShowGraphicsView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CShowGraphicsView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CShowGraphicsView diagnostics

#ifdef _DEBUG
void CShowGraphicsView::AssertValid() const
{
	CScrollView::AssertValid();
}

void CShowGraphicsView::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}

CShowGraphicsDoc* CShowGraphicsView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CShowGraphicsDoc)));
	return (CShowGraphicsDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CShowGraphicsView message handlers

void CShowGraphicsView::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint) 
{
	// TODO: Add your specialized code here and/or call the base class
	if (pSender == this)
		return;
	LPSTREAM pStream = NULL;
	DWORD dwSize = GetDocument()->GetGlobalSize();
	HGLOBAL hGlobal = GetDocument()->GetGlobalBuffer();
	if (m_lPciture)//����Ѿ�����ͼ��������
	{
		m_lPciture->Release();
		m_lPciture = NULL;
		Invalidate ();
	}
	if (hGlobal == NULL)
		return;
	// ��ȫ���ڴ��У�����IStream*
	HRESULT hr = CreateStreamOnHGlobal(hGlobal, TRUE, &pStream);
	_ASSERTE(SUCCEEDED(hr) && pStream);
	//��ͼ���ļ�����IPicture����
	hr = ::OleLoadPicture(pStream, dwSize, FALSE, IID_IPicture, (LPVOID *)&m_lPciture);
	_ASSERTE(SUCCEEDED(hr) && m_lPciture);	
	pStream->Release();
	m_nScale = 100;//������ʾ
	long hmWidth, hmHeight;
	m_lPciture->get_Width(&hmWidth);//ͼ��ĳ���
	m_lPciture->get_Height(&hmHeight);//ͼ��Ŀ��
	Invalidate ();
}

void CShowGraphicsView::OnNormal() //������ʾ
{
	// TODO: Add your command handler code here
	if (m_nScale == 100)
		return;
	m_nScale = 100;
	ScrollToPosition (CPoint (0, 0));
	Invalidate ();
}

void CShowGraphicsView::OnEnlarge() //�Ŵ�һ��
{
	// TODO: Add your command handler code here
	if (m_nScale == 200)
		return;
	m_nScale = 200;
	ScrollToPosition (CPoint (0, 0));
	Invalidate ();
}

void CShowGraphicsView::OnEnsmall() //��Сһ��
{
	// TODO: Add your command handler code here
	if (m_nScale == 50)
		return;
	m_nScale = 50;
	ScrollToPosition (CPoint (0, 0));
	Invalidate ();
}
