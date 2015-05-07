// MyHtmlCtrl.cpp : implementation file
//

#include "stdafx.h"
#include "MyHtmlDlg.h"
#include "MyHtmlCtrl.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMyHtmlCtrl

IMPLEMENT_DYNCREATE(CMyHtmlCtrl, CHtmlView)

CMyHtmlCtrl::CMyHtmlCtrl()
{
	//{{AFX_DATA_INIT(CMyHtmlCtrl)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

CMyHtmlCtrl::~CMyHtmlCtrl()
{
}

void CMyHtmlCtrl::DoDataExchange(CDataExchange* pDX)
{
	CHtmlView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMyHtmlCtrl)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CMyHtmlCtrl, CHtmlView)
	//{{AFX_MSG_MAP(CMyHtmlCtrl)
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMyHtmlCtrl diagnostics
BOOL CMyHtmlCtrl::CreateFromStatic(UINT nID, CWnd* pParent)
{
	CStatic wndStatic;//��̬�ؼ�
	if (!wndStatic.SubclassDlgItem(nID, pParent))//���໯
		return FALSE;
	CRect rc;
	wndStatic.GetWindowRect(&rc);//��̬�ؼ�����
	pParent->ScreenToClient(&rc);//ת��Ϊ��Ļ����
	wndStatic.DestroyWindow();
	// ����HTML�ؼ�(CHtmlView)
	return Create(NULL,						 // ����
		NULL,								//����
		(WS_CHILD | WS_VISIBLE ),			 // ���
		rc,										 // ����
		pParent,									 // ����
		nID,										 //  ID
		NULL);	                                    //��չ���
}

#ifdef _DEBUG
void CMyHtmlCtrl::AssertValid() const
{
	CHtmlView::AssertValid();
}

void CMyHtmlCtrl::Dump(CDumpContext& dc) const
{
	CHtmlView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMyHtmlCtrl message handlers

void CMyHtmlCtrl::OnDestroy() 
{	
	if (m_pBrowserApp) {
		m_pBrowserApp->Release();
		m_pBrowserApp = NULL;
	}
	CWnd::OnDestroy(); // bypass CView doc/frame stuff
	
}

void CMyHtmlCtrl::PostNcDestroy() 
{
	// TODO: Add your specialized code here and/or call the base class	
	//CHtmlView::PostNcDestroy();
}
