// MultiDocDemoDoc.cpp : implementation of the CMultiDocDemoDoc class
//

#include "stdafx.h"
#include "MultiDocDemo.h"

#include "MultiDocDemoDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMultiDocDemoDoc

IMPLEMENT_DYNCREATE(CMultiDocDemoDoc, CDocument)

BEGIN_MESSAGE_MAP(CMultiDocDemoDoc, CDocument)
	//{{AFX_MSG_MAP(CMultiDocDemoDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMultiDocDemoDoc construction/destruction

CMultiDocDemoDoc::CMultiDocDemoDoc()
{
	// TODO: add one-time construction code here

}

CMultiDocDemoDoc::~CMultiDocDemoDoc()
{
}

BOOL CMultiDocDemoDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)
	m_str="���ĵ�Ӧ�ó���ʵ����";//����ı�
	CFontDialog dlg;//����Ի���
	dlg.GetCurrentFont(&m_lf);
	if(dlg.DoModal()==IDOK)//��ʾ�Ի���
		dlg.GetCurrentFont(&m_lf);//��ȡ�û����õ�������Ϣ
	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CMultiDocDemoDoc serialization

void CMultiDocDemoDoc::Serialize(CArchive& ar)
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
// CMultiDocDemoDoc diagnostics

#ifdef _DEBUG
void CMultiDocDemoDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CMultiDocDemoDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMultiDocDemoDoc commands
