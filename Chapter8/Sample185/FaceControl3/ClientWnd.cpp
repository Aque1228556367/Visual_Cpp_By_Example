// ClientWnd.cpp : implementation file
//

#include "stdafx.h"
#include "FaceControl3.h"
#include "ClientWnd.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CClientWnd

CClientWnd::CClientWnd()
{
	m_rgbBack=RGB(128,128,128);
}

CClientWnd::~CClientWnd()
{
}


BEGIN_MESSAGE_MAP(CClientWnd, CWnd)
	//{{AFX_MSG_MAP(CClientWnd)
	ON_WM_ERASEBKGND()
	ON_COMMAND(ID_CHANGEFRAMEBK, OnChangeframebk)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CClientWnd message handlers

BOOL CClientWnd::OnEraseBkgnd(CDC* pDC) 
{
	// TODO: Add your message handler code here and/or call default
	CBrush Brush (m_rgbBack);	// ����һ���µ�ˢ��
	CBrush* pOldBrush = pDC->SelectObject (&Brush);	// ��ˢ��ѡ���豸����
	//�����Ҫ�߳�����������
	CRect reClip;
	GetClientRect(&reClip);
	//�ػ������
	pDC->PatBlt(reClip.left , reClip.top , reClip.Width () , reClip.Height() , PATCOPY);
	//�ͷ�ˢ��
	pDC->SelectObject(pOldBrush);
	return true;
	//return CWnd::OnEraseBkgnd(pDC);
}

void CClientWnd::OnChangeframebk() 
{
	// TODO: Add your command handler code here
	m_rgbBack=RGB(128,0,128);
	Invalidate(true);
}
