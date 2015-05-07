// ClockStatic.cpp : implementation file
//

#include "stdafx.h"
#include "PicClockDemo.h"
#include "ClockStatic.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CClockStatic
//COLORREF CClockStatic::origin=RGB(255,0,0);
CClockStatic::CClockStatic()
{
	for(int i=0;i<12;i++)
	{
		HBITMAP temp;
		temp=(HBITMAP)::CreateMappedBitmap(AfxGetApp()->m_hInstance,i+IDB_BITMAP0,0,NULL,0);
		m_hBitmap[i]=(HBITMAP)::CopyImage(temp,IMAGE_BITMAP,0,0,LR_COPYRETURNORG|LR_COPYDELETEORG);//����λͼ
	}
}

CClockStatic::~CClockStatic()
{
	for(int i=0;i<11;i++)
	{
		if(m_hBitmap[i])
			::DeleteObject(m_hBitmap[i]);
	}
}

BEGIN_MESSAGE_MAP(CClockStatic, CStatic)
	//{{AFX_MSG_MAP(CClockStatic)
	ON_WM_ERASEBKGND()
	ON_WM_TIMER()
	ON_WM_DESTROY()
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CClockStatic message handlers
/*��ܵ��������Ա�����������ڴ��ڱ����໯֮ǰ����������Ҫ�����໯*/
void CClockStatic::PreSubclassWindow()
{
	// TODO: Add your specialized code here and/or call the base class
	m_nTimer=SetTimer(1,1000,NULL);//����ʱ�ӣ�ID��1��ʱ�䣺1000ms������ص�����
	::GetObject(m_hBitmap[0],sizeof BITMAP,&m_bm);//��m_hBitmap��䵽�ṹm_bm
	CStatic::PreSubclassWindow();
}

BOOL CClockStatic::OnEraseBkgnd(CDC* pDC)
{
	// TODO: Add your message handler code here and/or call default
	CBrush brush;
	brush.CreateSolidBrush(::GetSysColor(COLOR_WINDOWTEXT));
	CBrush* pOldBrush=pDC->SelectObject(&brush);
	CRect rectClient;
	GetClientRect(&rectClient);
	pDC->PatBlt(0,0,rectClient.Width(),rectClient.Height(),PATCOPY);
	pDC->SelectObject(pOldBrush);
	return CStatic::OnEraseBkgnd(pDC);
}

void CClockStatic::OnTimer(UINT nIDEvent)
{
	// TODO: Add your message handler code here and/or call default
	if(nIDEvent==m_nTimer)
	{
		CRect rectClient;
		GetClientRect(&rectClient);//��ȡ��̬��ͻ�����
		m_Height=rectClient.Height();
		m_Width=rectClient.Width()/8;//Ҫ��ʾ8��λͼ
		CTime time=CTime::GetCurrentTime();//��ȡ��ǰʱ��
		int nh1=time.GetHour()/10;//Сʱ�ĵ�һλ
		ShowPic(nh1,0);
		int nh2=time.GetHour()%10;//Сʱ�ĵڶ�λ
		ShowPic(nh2,1);
		int nm1=time.GetMinute()/10;//���ӵĵ�һλ
		ShowPic(nm1,3);
		int nm2=time.GetMinute()%10;//���ӵĵڶ�λ
		ShowPic(nm2,4);
		int ns1=time.GetSecond()/10;//��ĵ�һλ
		ShowPic(ns1,6);
		int ns2=time.GetSecond()%10;//��ĵڶ�λ
		ShowPic(ns2,7);
		ShowPic(10,2);//��ʾ������
		ShowPic(10,5);
	}
	CStatic::OnTimer(nIDEvent);
}

void CClockStatic::OnDestroy()
{
	CStatic::OnDestroy();
	KillTimer(m_nTimer);//����ʱ��
	// TODO: Add your message handler code here
}

void CClockStatic::OnPaint()
{
	CPaintDC dc(this); // device context for painting

	// TODO: Add your message handler code here

	// Do not call CStatic::OnPaint() for painting messages
}

void CClockStatic::ShowPic(UINT digit,UINT pos)
{
	CClientDC dc(this);
	CDC dcMem;
	dcMem.CreateCompatibleDC(&dc);//�����ڴ�DC
	CBitmap* pBitmap=CBitmap::FromHandle(m_hBitmap[digit]);//��ȡλͼ
	CBitmap* pOldBitmap=dcMem.SelectObject(pBitmap);
	//���ڴ��Ӹ���λͼ��������ָ���ߴ���ʾ
	dc.StretchBlt(m_Width*pos,0,m_Width,m_Height,&dcMem,0,0,m_bm.bmWidth,m_bm.bmHeight,SRCCOPY);
	dcMem.SelectObject(pOldBitmap);
	dcMem.DeleteDC();
}