// BaseDocViewDemo4Doc.cpp : implementation of the CBaseDocViewDemo4Doc class
//

#include "stdafx.h"
#include "BaseDocViewDemo4.h"

#include "BaseDocViewDemo4Doc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CBaseDocViewDemo4Doc

IMPLEMENT_DYNCREATE(CBaseDocViewDemo4Doc, CDocument)

BEGIN_MESSAGE_MAP(CBaseDocViewDemo4Doc, CDocument)
	//{{AFX_MSG_MAP(CBaseDocViewDemo4Doc)
	ON_COMMAND(ID_MENU_UNDO, OnMenuUndo)
	ON_COMMAND(ID_MENU_CLEAR, OnMenuClear)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBaseDocViewDemo4Doc construction/destruction

CBaseDocViewDemo4Doc::CBaseDocViewDemo4Doc()
{
	// TODO: add one-time construction code here

}

CBaseDocViewDemo4Doc::~CBaseDocViewDemo4Doc()
{
}

BOOL CBaseDocViewDemo4Doc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CBaseDocViewDemo4Doc serialization

void CBaseDocViewDemo4Doc::Serialize(CArchive& ar)
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

void CBaseDocViewDemo4Doc::AddLine(CPoint pStar,CPoint pEnd)//�������
{
	CDrawLine *pLine=new CDrawLine(pStar,pEnd);
	m_lineArray.Add(pLine);									//�����������
	SetModifiedFlag(true);//�����޸ı��
}

CDrawLine *CBaseDocViewDemo4Doc::GetLine(int index)
{
	if(index<0||index>m_lineArray.GetUpperBound())					//��Ч������
		return 0;
	return (CDrawLine *)m_lineArray.GetAt(index);					//�������л�ȡ����ָ��
}

int CBaseDocViewDemo4Doc::GetTotalLine()
{
	return m_lineArray.GetSize();								//�����д洢��������Ŀ
}



/////////////////////////////////////////////////////////////////////////////
// CBaseDocViewDemo4Doc diagnostics

#ifdef _DEBUG
void CBaseDocViewDemo4Doc::AssertValid() const
{
	CDocument::AssertValid();
}

void CBaseDocViewDemo4Doc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CBaseDocViewDemo4Doc commands

void CBaseDocViewDemo4Doc::OnMenuUndo() 
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

void CBaseDocViewDemo4Doc::OnMenuClear() 
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

void CBaseDocViewDemo4Doc::SetModifiedFlag(BOOL bModified)
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
