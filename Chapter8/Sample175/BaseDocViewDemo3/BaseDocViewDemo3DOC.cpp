// BaseDocViewDemo3Doc.cpp : implementation of the CBaseDocViewDemo3Doc class
//

#include "stdafx.h"
#include "BaseDocViewDemo3.h"

#include "BaseDocViewDemo3Doc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CBaseDocViewDemo3Doc

IMPLEMENT_DYNCREATE(CBaseDocViewDemo3Doc, CDocument)

BEGIN_MESSAGE_MAP(CBaseDocViewDemo3Doc, CDocument)
	//{{AFX_MSG_MAP(CBaseDocViewDemo3Doc)
	ON_COMMAND(ID_MENU_UNDO, OnMenuUndo)
	ON_COMMAND(ID_MENU_CLEAR, OnMenuClear)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBaseDocViewDemo3Doc construction/destruction

CBaseDocViewDemo3Doc::CBaseDocViewDemo3Doc()
{
	// TODO: add one-time construction code here

}

CBaseDocViewDemo3Doc::~CBaseDocViewDemo3Doc()
{
}

BOOL CBaseDocViewDemo3Doc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CBaseDocViewDemo3Doc serialization

void CBaseDocViewDemo3Doc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
		m_lineArray.Serialize(ar);								//�������л�
	}
	else
	{
		// TODO: add loading code here
		m_lineArray.Serialize(ar);			 					//�������л�
	}
}

void CBaseDocViewDemo3Doc::AddLine(CPoint pStar,CPoint pEnd)//�������
{
	CDrawLine *pLine=new CDrawLine(pStar,pEnd);
	m_lineArray.Add(pLine);									//�����������
}

CDrawLine *CBaseDocViewDemo3Doc::GetLine(int index)
{
	if(index<0||index>m_lineArray.GetUpperBound())					//��Ч������
		return 0;
	return (CDrawLine *)m_lineArray.GetAt(index);					//�������л�ȡ����ָ��
}

int CBaseDocViewDemo3Doc::GetTotalLine()
{
	return m_lineArray.GetSize();								//�����д洢��������Ŀ
}



/////////////////////////////////////////////////////////////////////////////
// CBaseDocViewDemo3Doc diagnostics

#ifdef _DEBUG
void CBaseDocViewDemo3Doc::AssertValid() const
{
	CDocument::AssertValid();
}

void CBaseDocViewDemo3Doc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CBaseDocViewDemo3Doc commands

void CBaseDocViewDemo3Doc::OnMenuUndo() 
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

void CBaseDocViewDemo3Doc::OnMenuClear() 
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
