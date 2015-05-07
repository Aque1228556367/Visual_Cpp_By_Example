// BitmapStatusBar.cpp : implementation file
//

#include "stdafx.h"
#include "StatusBmp.h"
#include "BitmapStatusBar.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CBitmapStatusBar

CBitmapStatusBar::CBitmapStatusBar()
{
}

CBitmapStatusBar::~CBitmapStatusBar()
{
}


BEGIN_MESSAGE_MAP(CBitmapStatusBar, CStatusBar)
	//{{AFX_MSG_MAP(CBitmapStatusBar)
	ON_WM_DRAWITEM()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBitmapStatusBar message handlers
void CBitmapStatusBar::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct)
{
	switch(lpDrawItemStruct->itemID)
        {
        case 1:
            //����Դ��ѡ��λͼ
            CBitmap pBitmap;
            //����λͼ,ʹ��Import���ļ�������Դ,���Բ��ܵ�ɫ������
            pBitmap.LoadBitmap(IDB_BITMAP1);

            //��״̬��(StatusBar)���ӵ�һ��CDC����
            CDC dc,SourceDC;
            dc.Attach(lpDrawItemStruct->hDC);

            //�õ�pane�Ĵ�С������
            CRect rect(&lpDrawItemStruct->rcItem);

            //����ǰλͼ�������CDC
            SourceDC.CreateCompatibleDC(NULL);//���ɼ��ݵ�CDC
            CBitmap* pOldBitmap = SourceDC.SelectObject(&pBitmap);//ѡ��λͼ
            dc.BitBlt(rect.left, rect.top, rect.Width(), rect.Height(),
                     &SourceDC, 0, 0, SRCCOPY);//BitBlt
            SourceDC.SelectObject(pOldBitmap);//ɾ��CDC����ѡ���λͼ
            pBitmap.DeleteObject();//ɾ��λͼ

            //��״̬��(StatusBar)��CDC�������,����hDC������CDC����ʱ��ɾ��
            dc.Detach();
            return;
        }
	CStatusBar::DrawItem(lpDrawItemStruct);
}

void CBitmapStatusBar::OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct) 
{

	CStatusBar::OnDrawItem(nIDCtl, lpDrawItemStruct);
}

