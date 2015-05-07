// UIThread.cpp : implementation file
//

#include "stdafx.h"
#include "UIThreadDemo.h"
#include "UIThread.h"
#include "UIDlg.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CUIThread

IMPLEMENT_DYNCREATE(CUIThread, CWinThread)

CUIThread::CUIThread()
{
}

CUIThread::~CUIThread()
{
}

BOOL CUIThread::InitInstance()
{
	// TODO:  perform and per-thread initialization here
	CUIDlg  *pDlg=new CUIDlg;
	pDlg->Create(IDD_DIALOG1);								//������ģ̬�Ի���
	pDlg->ShowWindow(SW_SHOW);							//��ʾ�Ի�
	m_pMainWnd = pDlg;										//���Ի�����Ϊ������
	return TRUE;
}

int CUIThread::ExitInstance()
{
	// TODO:  perform any per-thread cleanup here
	if(m_pMainWnd!= NULL)
		delete m_pMainWnd;	//ɾ����ָ̬��
	return CWinThread::ExitInstance();
}

BEGIN_MESSAGE_MAP(CUIThread, CWinThread)
	//{{AFX_MSG_MAP(CUIThread)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CUIThread message handlers
