// BaseDocViewDemo5Doc.cpp : implementation of the CBaseDocViewDemo5Doc class
//

#include "stdafx.h"
#include "BaseDocViewDemo5.h"

#include "BaseDocViewDemo5Doc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CBaseDocViewDemo5Doc

IMPLEMENT_DYNCREATE(CBaseDocViewDemo5Doc, CDocument)

BEGIN_MESSAGE_MAP(CBaseDocViewDemo5Doc, CDocument)
	//{{AFX_MSG_MAP(CBaseDocViewDemo5Doc)
	ON_COMMAND(ID_MENU_UNDO, OnMenuUndo)
	ON_COMMAND(ID_MENU_CLEAR, OnMenuClear)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBaseDocViewDemo5Doc construction/destruction

CBaseDocViewDemo5Doc::CBaseDocViewDemo5Doc()
{
	// TODO: add one-time construction code here

}

CBaseDocViewDemo5Doc::~CBaseDocViewDemo5Doc()
{
}

BOOL CBaseDocViewDemo5Doc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CBaseDocViewDemo5Doc serialization

void CBaseDocViewDemo5Doc::Serialize(CArchive& ar)
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

void CBaseDocViewDemo5Doc::AddLine(CPoint pStar,CPoint pEnd)//�������
{
	CDrawLine *pLine=new CDrawLine(pStar,pEnd);
	m_lineArray.Add(pLine);									//�����������
	SetModifiedFlag(true);//�����޸ı��
}

CDrawLine *CBaseDocViewDemo5Doc::GetLine(int index)
{
	if(index<0||index>m_lineArray.GetUpperBound())					//��Ч������
		return 0;
	return (CDrawLine *)m_lineArray.GetAt(index);					//�������л�ȡ����ָ��
}

int CBaseDocViewDemo5Doc::GetTotalLine()
{
	return m_lineArray.GetSize();								//�����д洢��������Ŀ
}



/////////////////////////////////////////////////////////////////////////////
// CBaseDocViewDemo5Doc diagnostics

#ifdef _DEBUG
void CBaseDocViewDemo5Doc::AssertValid() const
{
	CDocument::AssertValid();
}

void CBaseDocViewDemo5Doc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CBaseDocViewDemo5Doc commands

void CBaseDocViewDemo5Doc::OnMenuUndo() 
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
	SetModifiedFlag(true);//�����޸ı��
}

void CBaseDocViewDemo5Doc::OnMenuClear() 
{
	// TODO: Add your command handler code here
	int index;
	index=m_lineArray.GetUpperBound();						//��ȡ��������Ԫ��
	if(index>=0)
	{
		m_lineArray.RemoveAll();					//�������
	}
	UpdateAllViews(NULL);//������ͼ
	SetModifiedFlag(true);//�����޸ı��
}

void CBaseDocViewDemo5Doc::SetModifiedFlag(BOOL bModified)
{
	CString strTitle = GetTitle();//��ȡ�ĵ��ı���
    CString strDirtyFlag = " �ĵ��ѱ��޸ģ�ע�Ᵽ��!"; //ע��������ǰ��Ŀո�
	//���类�޸���
    if (!IsModified() && bModified)
    {
		//������Ҳ�޸�
        SetTitle(strTitle + strDirtyFlag);
    }
    else if ( IsModified() && !bModified )//�Ѿ��������ĵ�
    {
        int nTitleLength = strTitle.GetLength();
        int nDirtyLength = strDirtyFlag.GetLength();
        SetTitle( strTitle.Left(nTitleLength - nDirtyLength) );//�ָ�ԭ���ı���
    }
    UpdateFrameCounts();
    CDocument::SetModifiedFlag(bModified);
}
