// UIDlg.cpp : implementation file
//

#include "stdafx.h"
#include "WorkThreadDemo.h"
#include "UIDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CUIDlg dialog
UINT ThreadFunc(LPVOID lpParam)									//�̺߳���
{
  CProgressCtrl* pInfo=(CProgressCtrl*)lpParam;							//�̺߳�������
  for(int pos=0;pos<30;pos++)
	{
		pInfo->SetPos(pos);//���ý���������
		Sleep(500);//ֹͣ0.5��
	}	
  return 0;
}



CUIDlg::CUIDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CUIDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CUIDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CUIDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CUIDlg)
	DDX_Control(pDX, IDC_PROGRESS1, m_progress);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CUIDlg, CDialog)
	//{{AFX_MSG_MAP(CUIDlg)
	ON_BN_CLICKED(IDC_STAR, OnStar)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CUIDlg message handlers

void CUIDlg::OnStar() 
{
	// TODO: Add your control notification handler code here
	CWinThread* pThread=AfxBeginThread(ThreadFunc,&m_progress);				//�����µ��̲߳���ʼִ��
}

BOOL CUIDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();	
	// TODO: Add extra initialization here
	m_progress.SetRange(0,30);//���ý�������Χ
	return TRUE;  
}
