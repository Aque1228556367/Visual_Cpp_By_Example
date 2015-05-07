// FixSplitterWnd.cpp: implementation of the CFixSplitterWnd class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "StaticSplitWnd4.h"
#include "FixSplitterWnd.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
BEGIN_MESSAGE_MAP(CFixSplitterWnd, CSplitterWnd)//��Ϣӳ��
	//{{AFX_MSG_MAP(CStaticSplitWnd4View)
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_WM_SETCURSOR()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
CFixSplitterWnd::CFixSplitterWnd(BOOL b_lock)//���캯��
{
	m_block=b_lock;

}

CFixSplitterWnd::~CFixSplitterWnd()
{

}
void CFixSplitterWnd::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	if(!m_block)
		CSplitterWnd::OnLButtonDown(nFlags, point);
	else
		CWnd::OnLButtonDown(nFlags, point);
}

void CFixSplitterWnd::OnMouseMove(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	if(!m_block)
		CSplitterWnd::OnMouseMove(nFlags, point);
	else
		CWnd::OnMouseMove(nFlags, point);
}

BOOL CFixSplitterWnd::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message) 
{
	// TODO: Add your message handler code here and/or call default
	if(!m_block)
		return CSplitterWnd::OnSetCursor(pWnd, nHitTest, message);
	else
		return CWnd::OnSetCursor(pWnd, nHitTest, message);
}

void CFixSplitterWnd::OnDrawSplitter(CDC *pDC, ESplitType nType, const CRect &rectArg)
{

  if(pDC==NULL) 
  { 
	RedrawWindow(rectArg,NULL,RDW_INVALIDATE|RDW_NOCHILDREN);
	return;
  } 
  ASSERT_VALID(pDC);
  CRect rc=rectArg;
  switch(nType) 
  { 
  case splitBorder:
   //�ػ��ָ�ڱ߽�,ʹ֮Ϊ��ɫ 
    pDC->Draw3dRect(rc,RGB(180,0,0),RGB(180,0,0));
    rc.InflateRect(-1,-1); 
    pDC->Draw3dRect(rc,RGB(180,0,0),RGB(180,0,0)); 
    return; 
  case splitBar: 
  //�ػ��ָ�����ʹ֮Ϊ��ɫ 
    pDC->FillSolidRect(rc,RGB(0,255,255));
    return; 
	default: 
    ASSERT(FALSE); 
  } 
} 


