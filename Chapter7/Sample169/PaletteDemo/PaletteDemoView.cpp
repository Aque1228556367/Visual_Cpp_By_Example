// PaletteDemoView.cpp : implementation of the CPaletteDemoView class
//

#include "stdafx.h"
#include "PaletteDemo.h"

#include "PaletteDemoDoc.h"
#include "PaletteDemoView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPaletteDemoView

IMPLEMENT_DYNCREATE(CPaletteDemoView, CView)

BEGIN_MESSAGE_MAP(CPaletteDemoView, CView)
	//{{AFX_MSG_MAP(CPaletteDemoView)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPaletteDemoView construction/destruction

CPaletteDemoView::CPaletteDemoView()
{
	// TODO: add construction code here
	LPLOGPALETTE pLogPal;							//����LOGPALETTE�ṹ
	pLogPal=(LPLOGPALETTE)malloc(sizeof(LOGPALETTE)+sizeof(PALETTEENTRY)*256);//ΪLOGPALETTE�ṹ�����ڴ�
	//�ֱ�����LOGPALETTE�ṹ�����ֵĲ���
	pLogPal->palVersion=0x300;
	pLogPal->palNumEntries=256;
	for(int i=0;i<64;i++){
	pLogPal->palPalEntry[i].peRed=i*4; 					//��ʼ����ɫ
	pLogPal->palPalEntry[i].peGreen=0;
	pLogPal->palPalEntry[i].peBlue=0;
	pLogPal->palPalEntry[i].peFlags=0;}
	for(i=64;i<128;i++){
	pLogPal->palPalEntry[i].peRed=0; 					//��ʼ����ɫ
	pLogPal->palPalEntry[i].peGreen=(i-64)*4;
	pLogPal->palPalEntry[i].peBlue=0;
	pLogPal->palPalEntry[i].peFlags=0;}
	for(i=128;i<192;i++){
	pLogPal->palPalEntry[i].peRed=0; 					//��ʼ����ɫ
	pLogPal->palPalEntry[i].peGreen=0;
	pLogPal->palPalEntry[i].peBlue=(i-128)*4;
	pLogPal->palPalEntry[i].peFlags=0;}
	for(i=192;i<256;i++){
	pLogPal->palPalEntry[i].peRed=(i-192)*4; 					//��ʼ����ɫ
	pLogPal->palPalEntry[i].peGreen=(i-192)*4;
	pLogPal->palPalEntry[i].peBlue=(i-192)*4;
	pLogPal->palPalEntry[i].peFlags=0;}
	m_Palette.CreatePalette(pLogPal);							//�����߼���ɫ��
}

CPaletteDemoView::~CPaletteDemoView()
{
}

BOOL CPaletteDemoView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CPaletteDemoView drawing

void CPaletteDemoView::OnDraw(CDC* pDC)
{
	CPaletteDemoDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
	pDC->SelectPalette(&m_Palette,FALSE);					//����ɫ��ѡ���豸������
	pDC->RealizePalette();							//���߼���ɫ��ʵ�ֵ�ϵͳ��ɫ��
	int x,y;											//�洢�������ʼ������
	CPen mypen;
	CPen*oldpen;
	mypen.CreatePen(PS_SOLID,2,RGB(255,255,255));			//���ɻ���
	oldpen=pDC->SelectObject(&mypen);						//�ѻ���ѡ���豸����	
	for(int i=0;i<64;i++)
	{
	CBrush mybrush(PALETTEINDEX(i*4));					//���ɲ�ͬ��ɫˢ��
	CBrush *oldbrush;									//����ˢ��ָ��
	oldbrush=pDC->SelectObject(&mybrush);					//��ˢ��ѡ���豸����
	x=(i%8)*24+20;
	y=(i/8)*24+10;
	pDC->Rectangle(x,y,x+24,y+24);							//���Ʒ���
	pDC->SelectObject(oldbrush);							//�ָ�ԭ��ˢ��
	}
	pDC->SelectObject(oldpen);								//�ָ�ԭ�еı�
	pDC->TextOut(30,210,"������ʹ�õ�ɫ��");

}

/////////////////////////////////////////////////////////////////////////////
// CPaletteDemoView printing

BOOL CPaletteDemoView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CPaletteDemoView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CPaletteDemoView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CPaletteDemoView diagnostics

#ifdef _DEBUG
void CPaletteDemoView::AssertValid() const
{
	CView::AssertValid();
}

void CPaletteDemoView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CPaletteDemoDoc* CPaletteDemoView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CPaletteDemoDoc)));
	return (CPaletteDemoDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CPaletteDemoView message handlers
