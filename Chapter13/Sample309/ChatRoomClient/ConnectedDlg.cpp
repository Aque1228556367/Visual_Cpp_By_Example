// ConnectedDlg1.cpp : implementation file
//

#include "stdafx.h"
#include "ChatRoomClient.h"
#include "ConnectedDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CConnectedDlg dialog


CConnectedDlg::CConnectedDlg(CServerSocket * tmp,CWnd* pParent /*=NULL*/)
	: CDialog(CConnectedDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CConnectedDlg)
	m_IDC_EDIT_ADDRESS = _T("");
	m_IDC_EDIT_NIKENAME = _T("");
	//}}AFX_DATA_INIT
	myServerSocket=tmp;
}


void CConnectedDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CConnectedDlg)
	DDX_Text(pDX, IDC_EDIT_ADDRESS, m_IDC_EDIT_ADDRESS);
	DDX_Text(pDX, IDC_EDIT_NIKENAME, m_IDC_EDIT_NIKENAME);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CConnectedDlg, CDialog)
	//{{AFX_MSG_MAP(CConnectedDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CConnectedDlg message handlers

void CConnectedDlg::OnOK() 
{
	// TODO: Add extra validation here
	UpdateData(TRUE);
	char*address;
	int n;
	if (!myServerSocket->Create())//���������׽���
	{
		myServerSocket->Close();
		AfxMessageBox("Socket�������󣡣�");
		return;
	}
	n=m_IDC_EDIT_ADDRESS.GetLength();
	address=new char(n+1);//��ȡ��������IP��ַ
	sprintf(address,"%s",m_IDC_EDIT_ADDRESS.GetBuffer(n));
	address[n]=0;
	if (!myServerSocket->Connect(address,4848))//���ӷ�����
	{
		myServerSocket->Close();
		AfxMessageBox("�������Ӵ��������¼���������ַ����д�Ƿ���ȷ��");
		return;
	}
	myServerSocket->NikeName=m_IDC_EDIT_NIKENAME;
	CDialog::OnOK();
}
