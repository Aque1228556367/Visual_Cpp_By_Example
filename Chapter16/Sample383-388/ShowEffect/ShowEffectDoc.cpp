// ShowEffectDoc.cpp : implementation of the CShowEffectDoc class
//

#include "stdafx.h"
#include "ShowEffect.h"

#include "ShowEffectDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CShowEffectDoc

IMPLEMENT_DYNCREATE(CShowEffectDoc, CDocument)

BEGIN_MESSAGE_MAP(CShowEffectDoc, CDocument)
	//{{AFX_MSG_MAP(CShowEffectDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CShowEffectDoc construction/destruction

CShowEffectDoc::CShowEffectDoc()
{
	// TODO: add one-time construction code here
	m_hDIB = NULL;								// ��ʼ������
	m_palDIB = NULL;
	m_sizeDoc = CSize(1,1);

}

CShowEffectDoc::~CShowEffectDoc()
{
	if (m_hDIB != NULL)								// �ж��Ƿ���DIB����
	{		
		::GlobalFree((HGLOBAL) m_hDIB);
	}
	if (m_palDIB != NULL)							// �жϵ�ɫ���Ƿ����
	{
		delete m_palDIB;
	}

}

BOOL CShowEffectDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CShowEffectDoc serialization

void CShowEffectDoc::Serialize(CArchive& ar)
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
// CShowEffectDoc diagnostics

#ifdef _DEBUG
void CShowEffectDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CShowEffectDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CShowEffectDoc commands

BOOL CShowEffectDoc::OnOpenDocument(LPCTSTR lpszPathName) 
{
	CFile file;
	if (!file.Open(lpszPathName, CFile::modeRead | CFile::shareDenyWrite))	// ���ļ�
	{
		return FALSE;	
	}	
	DeleteContents();
	m_hDIB=m_dib.LoadFile(file);					//����ReadDIBFile()��ȡͼ��
	if(m_hDIB==NULL)
	{	
		AfxMessageBox("ͼ���ʽ����ȷ��");			// ��ʾ����	
		return FALSE;
	}		
	SetDib();									// ��ʼ��DIB
	if (m_hDIB == NULL)							// �ж϶�ȡ�ļ��Ƿ�ɹ�
	{		
		AfxMessageBox("��ȡͼ��ʱ����");				// ��ʾ����				
		return FALSE;								// ����FALSE
	}		
	SetPathName(lpszPathName);					// �����ļ�����		
	return TRUE;								// ����TRUE

}
void CShowEffectDoc::SetDib()
{	
	LPSTR lpDIB = (LPSTR) ::GlobalLock((HGLOBAL) m_hDIB);	
	// �ж�ͼ���Ƿ����
	if (m_dib.GetWidth(lpDIB) > INT_MAX ||m_dib.GetHeight(lpDIB) > INT_MAX){
		::GlobalUnlock((HGLOBAL) m_hDIB);				
		::GlobalFree((HGLOBAL) m_hDIB);					// �ͷ�DIB����	
		m_hDIB = NULL;								// ����DIBΪ��		
		AfxMessageBox("��ʼ��ʧ��");		
		return;
	}
	// �����ĵ���С	
	m_sizeDoc = CSize((int)m_dib.GetWidth(lpDIB), (int)m_dib.GetHeight(lpDIB)); 
	::GlobalUnlock((HGLOBAL) m_hDIB);	
	m_palDIB = new CPalette;							// �����µ�ɫ��		
	if (m_palDIB == NULL)							// �ж��Ƿ񴴽��ɹ�
	{		
		::GlobalFree((HGLOBAL) m_hDIB);					// ʧ��		
		m_hDIB = NULL;								// ����DIB����Ϊ��
		return;
	}	
	// ����ConstructPalette��������ɫ��
	if (m_dib.ConstructPalette(m_hDIB, m_palDIB) == NULL)
	{				
		delete m_palDIB;								// ɾ��
		m_palDIB = NULL;								// ����Ϊ��	
		return;										// ���ؿ�
	}
}
