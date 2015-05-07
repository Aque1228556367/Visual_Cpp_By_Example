// ImageStatic.cpp : implementation file
//

#include "stdafx.h"
#include "ImageZoomDemo.h"
#include "ImageStatic.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CImageStatic

CImageStatic::CImageStatic()
{
	m_Type =0;
}

CImageStatic::~CImageStatic()
{
}


BEGIN_MESSAGE_MAP(CImageStatic, CStatic)
	//{{AFX_MSG_MAP(CImageStatic)
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CImageStatic message handlers
void CImageStatic::SetImage(UINT resID)
{
	m_bmp.LoadBitmap(resID);//����λͼ
}
void CImageStatic::SetType(int nType)
{
	m_Type =  nType;	
	Invalidate();//�ػ�ؼ�����
}

void CImageStatic::OnPaint() 
{
	CPaintDC dc(this); // device context for painting	
	// TODO: Add your message handler code here
	CRect r;
	GetClientRect(&r);	//��ÿؼ��ͻ����ڴ�С
	HBRUSH brush = (HBRUSH)::GetStockObject(GRAY_BRUSH); 
	::FillRect(dc.m_hDC,&r,brush);//��䱳��
	dc.SetStretchBltMode(HALFTONE);
	//��λͼѡ���ڴ�DC��
	CDC memdc;
	memdc.CreateCompatibleDC( &dc );
	CBitmap* pOldBmp= memdc.SelectObject(&m_bmp);
	//���λͼ����
	BITMAP bmp;
	m_bmp.GetBitmap(&bmp);
	switch(m_Type)//��ʼ����
	{
	case 0://ԭʼ��С
			dc.BitBlt(r.left,r.top,r.Width(),r.Height(),&memdc,0,0,SRCCOPY);
		break;
	case 1://�����
		dc.StretchBlt(r.left,r.top,r.Width(),bmp.bmHeight,&memdc,0,0,
			bmp.bmWidth,bmp.bmHeight,SRCCOPY);
		break;
	case 2://���߶�
		dc.StretchBlt(r.left,r.top,bmp.bmWidth,r.Height(),&memdc,0,0,
			bmp.bmWidth,bmp.bmHeight,SRCCOPY);
		break;
	case 3://��������
		dc.StretchBlt(r.left,r.top,r.Width(),r.Height(),&memdc,0,0,
			bmp.bmWidth,bmp.bmHeight,SRCCOPY);
		break;
	case 4://������ʾ����СΪ���ڵ�һ��
		dc.StretchBlt(r.Width()/4,r.Height()/4,r.Width()/2,r.Height()/2,&memdc,0,0,
			bmp.bmWidth,bmp.bmHeight,SRCCOPY);
		break;
	}
	memdc.SelectObject(pOldBmp);//��ԭ��ˢ
	// Do not call CStatic::OnPaint() for painting messages
}
