// LeftFormView.cpp : implementation file
//

#include "stdafx.h"
#include "MultiViewDemo.h"
#include "LeftFormView.h"
#include "MultiViewDemoDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CLeftFormView

IMPLEMENT_DYNCREATE(CLeftFormView, CFormView)

CLeftFormView::CLeftFormView()
	: CFormView(CLeftFormView::IDD)
{
	//{{AFX_DATA_INIT(CLeftFormView)
	m_Number = _T("");
	m_Name = _T("");
	m_Magor = _T("");
	m_Home = _T("");
	//}}AFX_DATA_INIT
}

CLeftFormView::~CLeftFormView()
{
}

void CLeftFormView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CLeftFormView)
	DDX_Text(pDX, IDC_EDIT1, m_Number);
	DDX_Text(pDX, IDC_EDIT2, m_Name);
	DDX_Text(pDX, IDC_EDIT3, m_Magor);
	DDX_Text(pDX, IDC_EDIT4, m_Home);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CLeftFormView, CFormView)
	//{{AFX_MSG_MAP(CLeftFormView)
	ON_BN_CLICKED(IDC_CHECKIN, OnCheckin)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CLeftFormView diagnostics

#ifdef _DEBUG
void CLeftFormView::AssertValid() const
{
	CFormView::AssertValid();
}

void CLeftFormView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CLeftFormView message handlers

void CLeftFormView::OnCheckin() 
{
	// TODO: Add your control notification handler code here
	UpdateData(true);//��ȡ�Ի���ؼ�����
	if(m_Number.IsEmpty()||m_Name.IsEmpty())//�ж��Ƿ�Ϊ��
	{
		AfxMessageBox("ѧ����������Ϊ�գ�");
		return;
	}
	CMultiViewDemoDoc* pDoc =(CMultiViewDemoDoc*)GetDocument();//��ȡ�ĵ�
	pDoc->infoArray[0].InsertAt(0,m_Number);//�������ݲ�������
	pDoc->infoArray[1].InsertAt(0,m_Name);
	pDoc->infoArray[2].InsertAt(0,m_Magor);
	pDoc->infoArray[3].InsertAt(0,m_Home);
	pDoc->add=true;//���������
	pDoc->UpdateAllViews(NULL);//����������ͼ
	m_Number = _T("");
	m_Name = _T("");
	m_Magor = _T("");
	m_Home = _T("");
	UpdateData(false);//���ؼ��������
}

void CLeftFormView::OnDraw(CDC* pDC) 
{
	// TODO: Add your specialized code here and/or call the base class
	//CDocument* pDoc = GetDocument();
	// TODO: add draw code here
	CMultiViewDemoDoc* pDoc =(CMultiViewDemoDoc*)CLeftFormView::GetDocument();

}
	
