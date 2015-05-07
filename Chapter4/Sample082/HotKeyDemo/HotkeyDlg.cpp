// HotkeyDlg.cpp : implementation file
//

#include "stdafx.h"
#include "HotKeyDemo.h"
#include "HotkeyDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CHotkeyDlg dialog


CHotkeyDlg::CHotkeyDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CHotkeyDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CHotkeyDlg)
	//}}AFX_DATA_INIT
}


void CHotkeyDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CHotkeyDlg)
	DDX_Control(pDX, IDC_HOTKEY1, m_ctlHotKey);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CHotkeyDlg, CDialog)
	//{{AFX_MSG_MAP(CHotkeyDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CHotkeyDlg message handlers

void CHotkeyDlg::OnOK() 
{
	// TODO: Add extra validation here
	WORD m_wVkCode;
	WORD m_wModifier;
	m_ctlHotKey.GetHotKey(m_wVkCode, m_wModifier);//��ȡ�ȼ��ؼ����õ��ȼ�
	//����һ���������������ص��ȼ�ֵ��WM_RETHOTKEY��Ϣ��������
	AfxGetMainWnd()->SendMessage(WM_SETHOTKEY,(WPARAM)MAKEWORD(m_wVkCode,m_wModifier));
	//����GetHotKey()�������ص���ϼ�(modifier)ת����RegisterHotKey()��������ʹ�õ�ֵ
	UINT mod = 0;
	if (m_wModifier&HOTKEYF_ALT)mod|=MOD_ALT;
	if (m_wModifier&HOTKEYF_CONTROL) mod|=MOD_CONTROL;
	if (m_wModifier&HOTKEYF_SHIFT) mod|=MOD_SHIFT;
	if (m_wModifier&HOTKEYF_EXT) mod|=MOD_WIN;
	m_wModifier=mod;
	//ע���ȼ�
	::RegisterHotKey(
	AfxGetMainWnd()->m_hWnd, //�����ȼ��Ĵ���ָ��
	111 , // �ȼ���ʶ
	m_wModifier, // ��־
	m_wVkCode //�������
	);

	CDialog::OnOK();
}
