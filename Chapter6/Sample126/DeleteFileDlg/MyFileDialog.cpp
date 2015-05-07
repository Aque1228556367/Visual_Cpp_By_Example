// MyFileDialog.cpp : implementation file
//

#include "stdafx.h"
#include "DeleteFileDlg.h"
#include "MyFileDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMyFileDialog

IMPLEMENT_DYNAMIC(CMyFileDialog, CFileDialog)

CMyFileDialog::CMyFileDialog():
		CFileDialog(TRUE, NULL, NULL, OFN_FILEMUSTEXIST|OFN_ENABLETEMPLATE,NULL,NULL)
{
		SetTemplate(IDD_MYFILEDLG,IDD_MYFILEDLG);//�����ļ��Ի����ģ��ΪIDD_MYFILEDLG
}


BEGIN_MESSAGE_MAP(CMyFileDialog, CFileDialog)
	//{{AFX_MSG_MAP(CMyFileDialog)
	ON_BN_CLICKED(IDC_DLETEFILE, OnDletefile)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


void CMyFileDialog::OnDletefile() 
{
	// TODO: Add your control notification handler code here
	CString pathName = GetPathName();//��ȡѡ���ļ�
	if(pathName.IsEmpty())
	{
		AfxMessageBox("û��ѡ���ļ���");
		return;
	}
	if(MessageBox("ȷ��ɾ���ļ���","��ʾ",MB_OKCANCEL)!=IDOK)
	{
		return;//��ɾ���ļ��˳�
	}
	CFile::Remove(pathName);
	GetDlgItem(IDC_STATIC1)->SetWindowText("ɾ���ļ�"+pathName);	
}
