// BaseDocViewDemo2Doc.cpp : implementation of the CBaseDocViewDemo2Doc class
//

#include "stdafx.h"
#include "BaseDocViewDemo2.h"

#include "BaseDocViewDemo2Doc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CBaseDocViewDemo2Doc

IMPLEMENT_DYNCREATE(CBaseDocViewDemo2Doc, CDocument)

BEGIN_MESSAGE_MAP(CBaseDocViewDemo2Doc, CDocument)
	//{{AFX_MSG_MAP(CBaseDocViewDemo2Doc)
	ON_COMMAND(ID_MENU_UNDO, OnMenuUndo)
	ON_COMMAND(ID_MENU_CLEAR, OnMenuClear)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBaseDocViewDemo2Doc construction/destruction

CBaseDocViewDemo2Doc::CBaseDocViewDemo2Doc()
{
	// TODO: add one-time construction code here

}

CBaseDocViewDemo2Doc::~CBaseDocViewDemo2Doc()
{
}

BOOL CBaseDocViewDemo2Doc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CBaseDocViewDemo2Doc serialization

void CBaseDocViewDemo2Doc::Serialize(CArchive& ar)
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

void CBaseDocViewDemo2Doc::AddLine(CPoint pStar,CPoint pEnd)//�������
{
	CDrawLine *pLine=new CDrawLine(pStar,pEnd);
	m_lineArray.Add(pLine);									//�����������
}

CDrawLine *CBaseDocViewDemo2Doc::GetLine(int index)
{
	if(index<0||index>m_lineArray.GetUpperBound())					//��Ч������
		return 0;
	return (CDrawLine *)m_lineArray.GetAt(index);					//�������л�ȡ����ָ��
}

int CBaseDocViewDemo2Doc::GetTotalLine()
{
	return m_lineArray.GetSize();								//�����д洢��������Ŀ
}



/////////////////////////////////////////////////////////////////////////////
// CBaseDocViewDemo2Doc diagnostics

#ifdef _DEBUG
void CBaseDocViewDemo2Doc::AssertValid() const
{
	CDocument::AssertValid();
}

void CBaseDocViewDemo2Doc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CBaseDocViewDemo2Doc commands

void CBaseDocViewDemo2Doc::OnMenuUndo() 
{
	// TODO: Add your command handler code here
	int index;
	index=m_lineArray.GetUpperBound();						//��ȡ��������Ԫ��
	if(index>=0)
	{
		delete m_lineArray.GetAt(index); 						//ɾ������
		m_lineArray.RemoveAt(index);							//ɾ���������
	}
	UpdateAllViews(NULL);
}

void CBaseDocViewDemo2Doc::OnMenuClear() 
{
	// TODO: Add your command handler code here
	int index;
	index=m_lineArray.GetUpperBound();						//��ȡ��������Ԫ��
	if(index>=0)
	{
		m_lineArray.RemoveAll();					//�������
	}
	UpdateAllViews(NULL);//������ͼ
}
