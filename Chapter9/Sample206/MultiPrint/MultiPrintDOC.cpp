// MultiPrintDoc.cpp : implementation of the CMultiPrintDoc class
//

#include "stdafx.h"
#include "MultiPrint.h"

#include "MultiPrintDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMultiPrintDoc

IMPLEMENT_DYNCREATE(CMultiPrintDoc, CDocument)

BEGIN_MESSAGE_MAP(CMultiPrintDoc, CDocument)
	//{{AFX_MSG_MAP(CMultiPrintDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMultiPrintDoc construction/destruction

CMultiPrintDoc::CMultiPrintDoc()
{
	// TODO: add one-time construction code here
	m_LinePerPage=6;//ÿҳ��ӡ6��
}

CMultiPrintDoc::~CMultiPrintDoc()
{
}

BOOL CMultiPrintDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)
	m_stringArray.SetSize(16);
	m_stringArray[0]="����������ˣ�";
	m_stringArray[1]="���������������";
	m_stringArray[2]="����������֣�";
	m_stringArray[3]="����������Ʋʡ�";
	m_stringArray[4]="�Ǻ��ϵĽ�����";
	m_stringArray[5]="��Ϧ���е����";
	m_stringArray[6]="���������Ӱ��";
	m_stringArray[7]="������ͷ������";
	m_stringArray[8]="�����ϵ�������";
	m_stringArray[9]="���͵���ˮ����ҡ��";
	m_stringArray[10]="�ڿ��ӵ��Შ�";
	m_stringArray[11]="�Ҹ�����һ��ˮ�ݡ�";
	m_stringArray[12]="�������µ�һ̶��";
	m_stringArray[13]="������Ȫ�������Ϻ磻";
	m_stringArray[14]="����ĸ���䣬";
	m_stringArray[15]="�����Ųʺ��Ƶ��Ρ�";

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CMultiPrintDoc serialization

void CMultiPrintDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

/////////////////////////////////////////////////////////////////////////////
// CMultiPrintDoc diagnostics

#ifdef _DEBUG
void CMultiPrintDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CMultiPrintDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMultiPrintDoc commands
