// ComboStatusBar.cpp : implementation file
//

#include "stdafx.h"
#include "StatusCombo.h"
#include "ComboStatusBar.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CComboStatusBar

CComboStatusBar::CComboStatusBar()
{
}

CComboStatusBar::~CComboStatusBar()
{
}


BEGIN_MESSAGE_MAP(CComboStatusBar, CStatusBar)
	//{{AFX_MSG_MAP(CComboStatusBar)
	ON_CBN_SELCHANGE(IDC_COMBO,OnComboSelChange)//�����Ϣӳ��
	ON_WM_CREATE()
	ON_WM_SIZE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CComboStatusBar message handlers

int CComboStatusBar::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CStatusBar::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// TODO: Add your specialized creation code here
	BOOL bSuccess=FALSE;
	CRect PaneRect(0,0,0,0);
	PaneRect.bottom+=100;//�趨չ����Ĵ�С
	bSuccess = m_Combo.Create(WS_CHILD|WS_VISIBLE|
		WS_VSCROLL|CBS_DROPDOWNLIST|CBS_AUTOHSCROLL,
		PaneRect, this, IDC_COMBO);//������Ͽ�
	if (!bSuccess)
		return 0;
	m_Combo.AddString("״̬����̣�");//����б���
	m_Combo.AddString("��������̣�");
	m_Combo.AddString("�˵���̣�");
	m_Combo.AddString("������̣�");
	m_Combo.SetCurSel(0);//�趨Ĭ��ѡ����	
	return 0;
}

CComboBox &CComboStatusBar::GetCombo()
{
	return m_Combo;
}

void CComboStatusBar::OnComboSelChange()
{
	CString str;
	m_Combo.GetLBText(m_Combo.GetCurSel(),str);
	//����ѡ������ʾ����
	AfxMessageBox(str);
}

void CComboStatusBar::OnSize(UINT nType, int cx, int cy) 
{
	CStatusBar::OnSize(nType, cx, cy);
	UINT inx;
	CRect rect;
	//����Ͽ��ƶ���ID_INDICATOR_NUM��
	inx=CommandToIndex(ID_SEPARATOR);
	GetItemRect(inx,&rect);
	rect.top-=2;//����λ��
	rect.right=rect.left+150;//�ұ�λ��
	m_Combo.MoveWindow(rect);//�ƶ���Ͽ�
}
