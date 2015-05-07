// NewDialogBar.cpp : implementation file
//

#include "stdafx.h"
#include "DialogBarDemo.h"
#include "NewDialogBar.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CNewDialogBar dialog


CNewDialogBar::CNewDialogBar(CWnd* pParent /*=NULL*/)
{
	//{{AFX_DATA_INIT(CNewDialogBar)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CNewDialogBar::DoDataExchange(CDataExchange* pDX)
{
	CDialogBar::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CNewDialogBar)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CNewDialogBar, CDialogBar)
	//{{AFX_MSG_MAP(CNewDialogBar)
	ON_CBN_SELCHANGE(IDC_COMBO1, OnSelchangeCombo1)
	ON_BN_CLICKED(IDC_BUTTON1, OnButton1)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CNewDialogBar message handlers

BOOL CNewDialogBar::OnInitDialog() 
{
//DialogBar::OnInitDialog();
	
	// TODO: Add extra initialization here
	static char* str[]={"֥�Ӹ繫ţ","�ܶ��ֻ���¹","��������ӥ","�ѳ�76��"};
	CComboBox* pCBox=(CComboBox*)GetDlgItem(IDC_COMBO1);
	for(int i=0;i<4;i++)
	{
		pCBox->AddString(str[i]);
	}
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CNewDialogBar::OnSelchangeCombo1() 
{
	// TODO: Add your control notification handler code here
	CComboBox* pCBox=(CComboBox*)GetDlgItem(IDC_COMBO1);
	int nIndex=pCBox->GetCurSel();
	if(nIndex==CB_ERR)
		return;
	CStatic* pIcon=(CStatic*)GetDlgItem(IDC_STATIC1);
	HICON hIcon=AfxGetApp()->LoadIcon(IDI_ICON1+nIndex);
	pIcon->SetIcon(hIcon);
}

void CNewDialogBar::OnButton1() 
{
	// TODO: Add your control notification handler code here
	AfxMessageBox("ok");
	
}
