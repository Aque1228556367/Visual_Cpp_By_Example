// BmpZoomPartDoc.cpp : implementation of the CBmpZoomPartDoc class
//

#include "stdafx.h"
#include "BmpZoomPart.h"

#include "BmpZoomPartDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CBmpZoomPartDoc

IMPLEMENT_DYNCREATE(CBmpZoomPartDoc, CDocument)

BEGIN_MESSAGE_MAP(CBmpZoomPartDoc, CDocument)
	//{{AFX_MSG_MAP(CBmpZoomPartDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBmpZoomPartDoc construction/destruction

CBmpZoomPartDoc::CBmpZoomPartDoc()
{
	// TODO: add one-time construction code here

}

CBmpZoomPartDoc::~CBmpZoomPartDoc()
{
}

BOOL CBmpZoomPartDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CBmpZoomPartDoc serialization

void CBmpZoomPartDoc::Serialize(CArchive& ar)
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
// CBmpZoomPartDoc diagnostics

#ifdef _DEBUG
void CBmpZoomPartDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CBmpZoomPartDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CBmpZoomPartDoc commands
