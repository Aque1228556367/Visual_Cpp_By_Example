// MyDialog.cpp : implementation file
//

#include "stdafx.h"
#include "BaseDlgDemo2.h"
#include "MyDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// MyDialog dialog


MyDialog::MyDialog(CWnd* pParent /*=NULL*/)
	: CDialog(MyDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(MyDialog)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void MyDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(MyDialog)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(MyDialog, CDialog)
	//{{AFX_MSG_MAP(MyDialog)
	ON_BN_CLICKED(IDC_BUTTON1, OnButton1)
	ON_BN_CLICKED(IDC_BUTTON2, OnButton2)
	ON_BN_CLICKED(IDC_BUTTON3, OnButton3)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// MyDialog message handlers

void MyDialog::OnButton1() //ȷ����ť
{
	// TODO: Add your control notification handler code here
	CDialog::OnOK();//����OnOK()�����˳��Ի���
	
}

void MyDialog::OnButton2() //ȡ����ť
{
	// TODO: Add your control notification handler code here
	CDialog::OnCancel();//����OnCancel()�����˳��Ի���
}

void MyDialog::OnButton3() //�رհ�ť
{
	// TODO: Add your control notification handler code here
	int nRet = 5; // �Զ��巵��ֵ
	CDialog::EndDialog(nRet); // ����EndDialog�˳��Ի���
}
