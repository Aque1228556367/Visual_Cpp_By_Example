// NewListBox.cpp : implementation file
//

#include "stdafx.h"
#include "TabListDemo.h"
#include "NewListBox.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// NewListBox

NewListBox::NewListBox()
{
}

NewListBox::~NewListBox()
{
}

BEGIN_MESSAGE_MAP(NewListBox, CListBox)
	//{{AFX_MSG_MAP(NewListBox)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// NewListBox message handlers

void NewListBox::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct)
{
	// TODO: Add your code to draw the specified item
	/*CDC dc;
	dc.Attach(lpDrawItemStruct->hDC);//��ȡ�б���DC*/
	CDC dc = lpDrawItemStruct->hDC;
	CRect rect(lpDrawItemStruct->rcItem);//��ȡ�б��ľ�������
	COLORREF bk = dc.GetBkColor();//������ɫ
	COLORREF fg = dc.GetTextColor();//ϵͳ�ı���ɫ
	if(lpDrawItemStruct->itemState & ODS_SELECTED)//���ѡ��
	{
		bk =  RGB(180,180,0 );//������ɫ
		fg = RGB(255,0,0 );//��ɫ�ı�
	}
	dc.SetTextColor(fg);
	CBrush brush(bk);
	dc.FillRect(&rect,&brush);
	if (lpDrawItemStruct->itemState&ODS_SELECTED)
	rect.left +=25;//����25������
	int nBkMode = dc.SetBkMode( TRANSPARENT );//ѡ���ɫ����Ϊ͸��
	CString str;
	GetText(lpDrawItemStruct->itemID,str) ;
	dc.DrawText(str, &rect, DT_LEFT|DT_VCENTER);//��ʾ�ı�
	dc.SetTextColor(fg);
	dc.SetBkMode( nBkMode );
	dc.Detach() ;
}