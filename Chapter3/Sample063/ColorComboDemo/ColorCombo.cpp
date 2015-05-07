// ColorCombo.cpp : implementation file
//

#include "stdafx.h"
#include "ColorComboDemo.h"
#include "ColorCombo.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CColorCombo

CColorCombo::CColorCombo()
{
	colors.Add(RGB(0, 0, 0));			// ��ɫ
	colors.Add(RGB(128, 0, 0));			// ���ɫ
	colors.Add(RGB(0, 128, 0));			// ����ɫ
	colors.Add(RGB(128, 128, 0));		// ���ɫ
	colors.Add(RGB(0, 0, 128));			// ����ɫ
	colors.Add(RGB(128, 0, 128));		// ��ש��ɫ
	colors.Add(RGB(0, 128, 128));		// ���ɫ	
	colors.Add(RGB(255, 0, 0));			// ��ɫ
	colors.Add(RGB(0, 255, 0));			// ��ɫ
	colors.Add(RGB(255, 255, 0));		// ��ɫ
	colors.Add(RGB(0, 0, 255));			// ��ɫ
	colors.Add(RGB(255, 0, 255));		// ש��ɫ
	colors.Add(RGB(0, 255, 255));		// ��ɫ
	colors.Add(RGB(255, 255, 255));		// ��ɫ
}

CColorCombo::~CColorCombo()
{
}


BEGIN_MESSAGE_MAP(CColorCombo, CComboBox)
	//{{AFX_MSG_MAP(CColorCombo)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CColorCombo message handlers

void CColorCombo::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct) 
{
	// TODO: Add your code to draw the specified item
	CDC dc;
	dc.Attach(lpDrawItemStruct->hDC);//��ȡDC
	CRect rect(&(lpDrawItemStruct->rcItem));//��ȡ�ؼ�����
	CBrush brush(colors[lpDrawItemStruct->itemID]);
	rect.InflateRect(-2, -2);
	dc.FillRect(rect, &brush);//����������
	if (lpDrawItemStruct->itemState & ODS_SELECTED)//���ѡ��
			dc.DrawFocusRect(rect);//��ʾѡ����
	CBrush frameBrush(RGB(0, 0, 0));//��ɫ��ˢ
	dc.FrameRect(rect, &frameBrush);//���Ʊ߽�
	rect.InflateRect(-1, -1);//����1һ������
	dc.Detach();//�Ƿ�DC
	
}

void CColorCombo::PreSubclassWindow() 
{
	// TODO: Add your specialized code here and/or call the base class
	for (int nColors = 0; nColors < colors.GetSize(); nColors++)//����б���
		AddString("");
	SetCurSel(0);//����Ĭ��ѡ����
	CComboBox::PreSubclassWindow();
}
