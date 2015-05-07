// TextProgressBar.cpp : implementation file
//

#include "stdafx.h"
#include "ColorTextProgressBar.h"
#include "TextProgressBar.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTextProgressBar

CTextProgressBar::CTextProgressBar()
{
}

CTextProgressBar::~CTextProgressBar()
{
}


BEGIN_MESSAGE_MAP(CTextProgressBar, CProgressCtrl)
	//{{AFX_MSG_MAP(CTextProgressBar)
	ON_WM_PAINT()
	ON_WM_ERASEBKGND()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTextProgressBar message handlers
void CTextProgressBar::SetRange(int nLower, int nUpper)
{
	m_nLower = nLower;
	m_nUpper = nUpper;
	m_nCurrentPosition = nLower;
	CProgressCtrl::SetRange(nLower, nUpper);
}

int CTextProgressBar::SetPos(int nPos)
{
	m_nCurrentPosition = nPos;//��ȡ��ǰ������λ��
	return (CProgressCtrl::SetPos(nPos));
}

void CTextProgressBar::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	CRect rectClient;
	GetClientRect(&rectClient);//��ȡ����������
	CBrush brush;
	brush.CreateSolidBrush(::GetSysColor(COLOR_3DFACE));//��ȡϵͳ��ˢ
	dc.FillRect(&rectClient, &brush);//������������
	VERIFY(brush.DeleteObject());//ɾ����ˢ
	if (m_nCurrentPosition <= m_nLower || m_nCurrentPosition >m_nUpper)//������û������
	{	
		return;
	}

	brush.CreateSolidBrush(RGB(0, 0,255));//������ɫ��ˢ
	RECT rectFill;//�����������
	float fillwidh=(float)((float)(m_nCurrentPosition-m_nLower)/(float)(m_nUpper-m_nLower))*rectClient.right;
	::SetRect(&rectFill,
					 0,       // ����X����
					 0,									 //����Y����
					(int)fillwidh,          //����X����
					rectClient.bottom+1);			//����Y����
	dc.FillRect(&rectFill,&brush);//������������
	VERIFY(brush.DeleteObject());
	CString percent;
	percent.Format("����ɣ�%.0f%%", 100.0*(float)(m_nCurrentPosition-m_nLower)/(float)(m_nUpper-m_nLower));
	dc.SetTextColor(RGB(255,0,0));//�����ı���ɫ
	dc.SetBkMode(TRANSPARENT);//͸������
	dc.DrawText(percent, &rectClient, DT_VCENTER|DT_CENTER|DT_SINGLELINE);//��ʾ�ı���Ϣ	
	// Do not call CProgressCtrl::OnPaint() for painting messages
}

BOOL CTextProgressBar::OnEraseBkgnd(CDC* pDC) 
{
	// TODO: Add your message handler code here and/or call default
//	return TRUE;
	
	return CProgressCtrl::OnEraseBkgnd(pDC);
}
