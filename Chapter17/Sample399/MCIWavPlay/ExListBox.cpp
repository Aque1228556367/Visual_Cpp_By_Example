// ExListBox.cpp : implementation file
//

#include "stdafx.h"
#include "ExListBox.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CExListBox

CExListBox::CExListBox()
{
	m_nMaxWidth=0;
}

CExListBox::~CExListBox()
{
}


BEGIN_MESSAGE_MAP(CExListBox, CListBox)
	//{{AFX_MSG_MAP(CExListBox)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CExListBox message handlers
int CExListBox::AddString(LPCTSTR lpszItem)
{
	int nRet = CListBox::AddString(lpszItem);//���û����AddString����
	//����GetScrollInfo��ô�ֱ�������������Ϣ
    SCROLLINFO scrollInfo;//�������ṹ
    memset(&scrollInfo, 0, sizeof(SCROLLINFO));
    scrollInfo.cbSize = sizeof(SCROLLINFO);
    scrollInfo.fMask  = SIF_ALL;
    GetScrollInfo(SB_VERT, &scrollInfo, SIF_ALL);//��ȡ��ֱ��������Ϣ
	//SCROLLINFO�ĳ�ԱnPage�������б��ÿҳ���ܹ���ʾ����Ŀ����nMax���б������Ŀ��������nMax���ڻ����nPage���ͳ����˴�ֱ��������
	int nScrollWidth = 0;
    if(GetCount()>1&& ((int)scrollInfo.nMax >= (int)scrollInfo.nPage))//����б���д�ֱ������
    {
       nScrollWidth = GetSystemMetrics(SM_CXVSCROLL);//��ȡ��ֱ�������Ŀ��
    }
	//����һ��SIZE����sSize����ʵ�����Ի����CClientDC�� 
    SIZE      sSize;
    CClientDC myDC(this);
	 CFont* pListBoxFont = GetFont();//��ȡ����
    if(pListBoxFont != NULL)
    {
        CFont* pOldFont = myDC.SelectObject(pListBoxFont);
		//����GetTextExtendPoint32()��������ַ����Ŀ��
        GetTextExtentPoint32(myDC.m_hDC, lpszItem, strlen(lpszItem), &sSize);
        m_nMaxWidth = max(m_nMaxWidth, (int)sSize.cx);
		SetHorizontalExtent(m_nMaxWidth + nScrollWidth);//����ˮƽ������
		myDC.SelectObject(pOldFont);     
	}
	 return nRet;

}
