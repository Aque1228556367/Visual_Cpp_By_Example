// SDIActiveXDemoDoc.cpp : implementation of the CSDIActiveXDemoDoc class
//

#include "stdafx.h"
#include "SDIActiveXDemo.h"

#include "SDIActiveXDemoDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSDIActiveXDemoDoc

IMPLEMENT_DYNCREATE(CSDIActiveXDemoDoc, CDocument)

BEGIN_MESSAGE_MAP(CSDIActiveXDemoDoc, CDocument)
	//{{AFX_MSG_MAP(CSDIActiveXDemoDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSDIActiveXDemoDoc construction/destruction

CSDIActiveXDemoDoc::CSDIActiveXDemoDoc()
{
	// TODO: add one-time construction code here

}

CSDIActiveXDemoDoc::~CSDIActiveXDemoDoc()
{
}

BOOL CSDIActiveXDemoDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CSDIActiveXDemoDoc serialization

void CSDIActiveXDemoDoc::Serialize(CArchive& ar)
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
// CSDIActiveXDemoDoc diagnostics

#ifdef _DEBUG
void CSDIActiveXDemoDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CSDIActiveXDemoDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CSDIActiveXDemoDoc commands
