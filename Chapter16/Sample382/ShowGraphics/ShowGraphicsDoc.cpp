// ShowGraphicsDoc.cpp : implementation of the CShowGraphicsDoc class
//

#include "stdafx.h"
#include "ShowGraphics.h"

#include "ShowGraphicsDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CShowGraphicsDoc

IMPLEMENT_DYNCREATE(CShowGraphicsDoc, CDocument)

BEGIN_MESSAGE_MAP(CShowGraphicsDoc, CDocument)
	//{{AFX_MSG_MAP(CShowGraphicsDoc)
	ON_COMMAND(ID_FILE_OPEN, OnFileOpen)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CShowGraphicsDoc construction/destruction

CShowGraphicsDoc::CShowGraphicsDoc()
{
	// TODO: add one-time construction code here

}

CShowGraphicsDoc::~CShowGraphicsDoc()
{
}

BOOL CShowGraphicsDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CShowGraphicsDoc serialization

void CShowGraphicsDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		if (m_hBuf != NULL)//��ʼ������
		{
			GlobalFree (m_hBuf);
			m_hBuf = NULL;
			m_dwSize = 0;
			UpdateAllViews (NULL, 1);
		}
		m_dwSize = ar.GetFile()->GetLength ();//��ȡ�ļ�����
		m_hBuf = GlobalAlloc(GMEM_MOVEABLE, m_dwSize);//�����ڴ�
		char *tmp = (char *) GlobalLock (m_hBuf);
		if (tmp == NULL)
			return;
		ar.Read (tmp, m_dwSize);//���ļ����ݵ��ڴ�
		GlobalUnlock (m_hBuf);
		POSITION pos = GetFirstViewPosition();
		while (pos != NULL)
		{
			CView* pView = GetNextView(pos);
			pView->UpdateWindow();//������ͼ
		}
	}
}

/////////////////////////////////////////////////////////////////////////////
// CShowGraphicsDoc diagnostics

#ifdef _DEBUG
void CShowGraphicsDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CShowGraphicsDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CShowGraphicsDoc commands

void CShowGraphicsDoc::OnFileOpen() 
{
	// TODO: Add your command handler code here
	CFileDialog cfd (TRUE);//���ļ��Ի���
	cfd.m_ofn.lpstrFilter	= _T("Supported Files Types(*.bmp;*.gif;*.jpg;*.ico;*.emf;*.wmf;)\0*.bmp;*.gif;*.jpg;*.ico;*.emf;*.wmf;\0Bitmaps (*.bmp)\0*.bmp\0GIF Files (*.gif)\0*.gif\0JPEG Files (*.jpg)\0*.jpg\0Icons (*.ico)\0*.ico\0Enhanced Metafiles (*.emf)\0*.emf\0Windows Metafiles (*.wmf)\0*.wmf\0\0");
	cfd.m_ofn.lpstrTitle	= _T("Open Picture File");
	cfd.m_ofn.nMaxFile	= MAX_PATH;
	if (cfd.DoModal () == IDCANCEL)//���ô��ļ��Ի���
		return;
	if (m_hBuf != NULL)//��ʼ������
	{
		GlobalFree (m_hBuf);
		m_hBuf = NULL;
		m_dwSize = 0;
	}
	CDocument::OnNewDocument ();
	CString strPath = cfd.GetPathName();//��ȡ�ļ�·��
	AfxGetApp()->OpenDocumentFile (strPath);//���ļ�����ȡ���ݵ��ڴ�
}
HGLOBAL CShowGraphicsDoc::GetGlobalBuffer()
{
	return (m_hBuf);
}

DWORD CShowGraphicsDoc::GetGlobalSize()
{
	return (m_dwSize);
}

void CShowGraphicsDoc::DeleteContents() 
{
	// TODO: Add your specialized code here and/or call the base class
	if (m_hBuf != NULL)
	{
		GlobalFree (m_hBuf);//�ͷ�ȫ���ڴ�
		m_hBuf = NULL;
		m_dwSize = 0;
		UpdateAllViews (NULL, 1);//������ͼ
	}
	CDocument::DeleteContents();
}
