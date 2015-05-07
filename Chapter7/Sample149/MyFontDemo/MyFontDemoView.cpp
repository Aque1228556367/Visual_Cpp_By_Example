// MyFontDemoView.cpp : implementation of the CMyFontDemoView class
//

#include "stdafx.h"
#include "MyFontDemo.h"

#include "MyFontDemoDoc.h"
#include "MyFontDemoView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMyFontDemoView

IMPLEMENT_DYNCREATE(CMyFontDemoView, CView)

BEGIN_MESSAGE_MAP(CMyFontDemoView, CView)
	//{{AFX_MSG_MAP(CMyFontDemoView)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMyFontDemoView construction/destruction

CMyFontDemoView::CMyFontDemoView()
{
	// TODO: add construction code here

}

CMyFontDemoView::~CMyFontDemoView()
{
}

BOOL CMyFontDemoView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CMyFontDemoView drawing

void CMyFontDemoView::OnDraw(CDC* pDC)
{
	CMyFontDemoDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
	CFont myfont,*oldfont;	
	LOGFONT font;
	memset(&font,0,sizeof(LOGFONT));				//Ϊ����ṹ����ֵ��Ĭ��ֵ
	font.lfHeight=50;								//����߶�Ϊ50
	font.lfWeight=600;
	font.lfItalic=TRUE;							//����б��
	font.lfUnderline=TRUE;							//�����»���
	strcpy(font.lfFaceName,"Times New Roman");		//�ַ���
	myfont.CreateFontIndirect(&font); 				//����������
	oldfont=pDC->SelectObject(&myfont);				//��������ѡ���豸����
	pDC->SetTextColor(RGB(100,10,210));				//�ı���ɫ
	pDC->SetBkMode(TRANSPARENT);				//�ı�����͸������ɫ
	pDC->TextOut(10,20,"ʹ��CFont�����Լ������壡");	//�����������"������"�ַ���
	TEXTMETRIC tm; 							//����TEXTMETRIC�ṹtm
	pDC->GetTextMetrics(&tm);					//��ȡ������Ϣ
	CString str1,str2,str3;
	str1.Format("����߶�Ϊ��%d������",tm.tmHeight);
	str2.Format("�����ƽ���ַ����Ϊ��%d������",tm.tmAveCharWidth);
	pDC->SelectObject(oldfont);						//�ָ��豸�����еľ�����
	pDC->SetTextColor(RGB(0,0,128));				//�趨������ı����õ���ɫ
	pDC->TextOut(10,100,str1);						//��ϵͳĬ���������str1�ַ���
	pDC->TextOut(10,120,str2);						//��ϵͳĬ���������str2�ַ���
}

/////////////////////////////////////////////////////////////////////////////
// CMyFontDemoView printing

BOOL CMyFontDemoView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CMyFontDemoView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CMyFontDemoView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CMyFontDemoView diagnostics

#ifdef _DEBUG
void CMyFontDemoView::AssertValid() const
{
	CView::AssertValid();
}

void CMyFontDemoView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMyFontDemoDoc* CMyFontDemoView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMyFontDemoDoc)));
	return (CMyFontDemoDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMyFontDemoView message handlers
