// SinglePrintDoc.cpp : implementation of the CSinglePrintDoc class
//

#include "stdafx.h"
#include "SinglePrint.h"

#include "SinglePrintDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSinglePrintDoc

IMPLEMENT_DYNCREATE(CSinglePrintDoc, CDocument)

BEGIN_MESSAGE_MAP(CSinglePrintDoc, CDocument)
	//{{AFX_MSG_MAP(CSinglePrintDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSinglePrintDoc construction/destruction

CSinglePrintDoc::CSinglePrintDoc()
{
	// TODO: add one-time construction code here

}

CSinglePrintDoc::~CSinglePrintDoc()
{
}

BOOL CSinglePrintDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)
	m_stringArray.SetSize(8);
	m_stringArray[0]="����������ˣ�";
	m_stringArray[1]="���������������";
	m_stringArray[2]="����������֣�";
	m_stringArray[3]="����������Ʋʡ�";
	m_stringArray[4]="�Ǻ��ϵĽ�����";
	m_stringArray[5]="��Ϧ���е����";
	m_stringArray[6]="���������Ӱ��";
	m_stringArray[7]="������ͷ������";
	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CSinglePrintDoc serialization

void CSinglePrintDoc::Serialize(CArchive& ar)
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
// CSinglePrintDoc diagnostics

#ifdef _DEBUG
void CSinglePrintDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CSinglePrintDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CSinglePrintDoc commands
