// ComboTool.cpp : implementation file
//

#include "stdafx.h"
#include "ComboToolbar.h"
#include "ComboTool.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CComboTool

CComboTool::CComboTool()
{
}

CComboTool::~CComboTool()
{
}


BEGIN_MESSAGE_MAP(CComboTool, CToolBar)
	//{{AFX_MSG_MAP(CComboTool)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CComboTool message handlers
BOOL CComboTool::CreateCombo( DWORD dwStyle, CComboBox *pComboBox, UINT nID,
							 int nWidth, int nHeight )
{
	//������Ͽ�ĳߴ�
	CRect pRect(-nWidth, -nHeight, 0, 0);
	pRect.right -= 2;
	//������Ͽ�Ŀ��������Ʒָ�����λ��
	ASSERT(CommandToIndex(nID) >= 0); 					//��Ӧ�������ϵ�ID�Ƿ���Ч
	SetButtonInfo(CommandToIndex(nID), nID, TBBS_SEPARATOR, nWidth );
	//������Ͽ��ڹ���������Ӧ��λ����ʾ
	if (!pComboBox->Create( dwStyle, pRect, this, nID ))
	{
		  TRACE("Failed to create the combo-box %p .\n", nID);
		  return FALSE;
	}
	GetItemRect( CommandToIndex(nID), &pRect );						//��ȡ�հ�ť��λ��
	pRect.left += 4;
	pRect.right = pRect.left + nWidth;
	pComboBox->SetWindowPos(0, pRect.left, pRect.top+1, 0, 0,
	SWP_NOZORDER | SWP_NOACTIVATE | SWP_NOSIZE | SWP_NOCOPYBITS );	//�����б���λ��
	pComboBox->ShowWindow( SW_SHOW );							//��ʾ�б��
	return TRUE;
}
