// AutoCombo.cpp : implementation file
//

#include "stdafx.h"
#include "AutoComboDemo.h"
#include "AutoCombo.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAutoCombo

CAutoCombo::CAutoCombo()
{
	//��ʼʱ�Զ���ɹ�������Ч�� 
	m_bAutoComplete = TRUE;
}

CAutoCombo::~CAutoCombo()
{
}


BEGIN_MESSAGE_MAP(CAutoCombo, CComboBox)
	//{{AFX_MSG_MAP(CAutoCombo)
	ON_CONTROL_REFLECT(CBN_EDITUPDATE, OnEditupdate)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAutoCombo message handlers

BOOL CAutoCombo::PreTranslateMessage(MSG* pMsg) 
{
	// TODO: Add your specialized code here and/or call the base class
	// ��������Ϣ�������WM_KEYDOWN��Ϣ ���Զ���ɹ��ܾ�����Ч�ģ��������
	// Delete��������Backspace�����£���
	// ˵���û���ʱ�����޸��ı��������ʱ
	// Ӧ�ùر��Զ���ɹ���

	if (pMsg->message == WM_KEYDOWN)
	{
		m_bAutoComplete = TRUE;

		int nVirtKey = (int) pMsg->wParam;
		if (nVirtKey == VK_DELETE || nVirtKey == VK_BACK)
			m_bAutoComplete = FALSE;
	}
	
	return CComboBox::PreTranslateMessage(pMsg);
}

void CAutoCombo::OnEditupdate() 
{
	// TODO: Add your control notification handler code here
	if (!m_bAutoComplete) // �����ǰ�Զ����ģʽ��Ч��ֱ�ӷ���
		return;
	// ȡ����Ͽ��������ı�����
	CString strText;
	GetWindowText(strText);
	int nLength = strText.GetLength();
	// ��õ�ǰ��Ͽ���ѡ����ı���Χ
	DWORD dwCurSel = GetEditSel();
	WORD dStart = LOWORD(dwCurSel);
	WORD dEnd   = HIWORD(dwCurSel);	
	//����Ͽ���б����������Ƿ������ƶ��ı�����ͷ���б���
	if (SelectString(-1, strText) == CB_ERR)
	{
		//���û���ı���ѡ�У�������ԭ�����ַ�������
		SetWindowText(strText);		
		if (dwCurSel != CB_ERR)
			SetEditSel(dStart, dEnd);//�ָ�ԭ���Ĺ��λ��
	}
	
	// ѡ�иո��Զ����ӵ��ı�������
	if (dEnd < nLength && dwCurSel != CB_ERR)
		SetEditSel(dStart, dEnd);
	else
		SetEditSel(nLength, -1);
	
}
