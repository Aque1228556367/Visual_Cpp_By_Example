// reatReport.cpp : implementation file
//

#include "stdafx.h"
#include "VideoVoiceTrans.h"
#include "reatReport.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CreatReport dialog


CreatReport::CreatReport(CWnd* pParent /*=NULL*/)
	: CDialog(CreatReport::IDD, pParent)
{
	//{{AFX_DATA_INIT(CreatReport)
	m_Address = _T("");
	m_Type = _T("");
	m_Name = _T("");
	m_Scribe = _T("");
	m_Reporter = _T("");
	m_Data = 0;
	//}}AFX_DATA_INIT
}


void CreatReport::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CreatReport)
	DDX_Text(pDX, IDC_ADDRESS, m_Address);
	DDV_MaxChars(pDX, m_Address, 30);
	DDX_Text(pDX, IDC_CODE, m_Type);
	DDV_MaxChars(pDX, m_Type, 30);
	DDX_Text(pDX, IDC_NAME, m_Name);
	DDV_MaxChars(pDX, m_Name, 30);
	DDX_Text(pDX, IDC_SCRIBE, m_Scribe);
	DDX_Text(pDX, IDC_REPORTNAME, m_Reporter);
	DDV_MaxChars(pDX, m_Reporter, 6);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER1, m_Data);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CreatReport, CDialog)
	//{{AFX_MSG_MAP(CreatReport)
	ON_BN_CLICKED(IDC_SAVEREPORT, OnSavereport)
	ON_BN_CLICKED(IDC_DATABASE, OnDatabase)
	ON_BN_CLICKED(IDC_CLEAR, OnClear)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CreatReport message handlers

void CreatReport::OnSavereport() 
{
	// TODO: Add your control notification handler code here
	UpdateData(true);
	if(m_Address.IsEmpty())
	{
		AfxMessageBox("������֧Ԯ��λ���ƣ�");
		return;
	}
	if(m_Type.IsEmpty())
	{
		AfxMessageBox("������װ���ͺţ�");
		return;
	}
	if(m_Name.IsEmpty())
	{
		AfxMessageBox("������װ�����ƣ�");
		return;
	}
	if(m_Scribe.IsEmpty())
	{
		AfxMessageBox("��������Ϲ��̣�");
		return;
	}
	
	if(m_Reporter.IsEmpty())
	{
		AfxMessageBox("�����뱨����������");
		return;
	}
	//���ļ��Ի���
	CFileDialog myFileDlg(FALSE,"txt",_T("��ϱ����ļ�"),NULL,"Text(*.txt|All Files(*.*)|*.*||)",NULL);
//	myFileDlg.m_ofn.lpstrFileTitle=_T("��ѡ�񱣴�·����");
	CString strfilename;
	if(myFileDlg.DoModal()!=IDOK)
		return;
	strfilename=myFileDlg.GetFileName();
	CStdioFile ExportFile;
	ExportFile.Open(strfilename,CFile::modeCreate | CFile::modeWrite,NULL);
	//CString time;
	CTime t=CTime::GetCurrentTime();
	CString time="��ϱ��洴��ʱ�䣺    20%y-%m-%d%H:%M:%S";
	time=t.Format(time);
	ExportFile.WriteString(time+"\n\n");
	ExportFile.WriteString("֧Ԯ��λ��    "+m_Address+"\n\n");
	ExportFile.WriteString("װ���ͺţ�    "+m_Type+"\n\n");
	ExportFile.WriteString("װ�����ƣ�    "+m_Name+"\n\n");
	ExportFile.WriteString("��Ϲ��̣� \n\n         "+m_Scribe+"\n\n");
	ExportFile.WriteString("�����ˣ�     "+m_Reporter+"\n\n");
	CString strdata="20%y-%m-%d";
	strdata=m_Data.Format(strdata);
	ExportFile.WriteString("֧Ԯʱ�䣺    "+strdata+"\n\n");
	ExportFile.Close();
	AfxMessageBox("�������ɳɹ���");


}

void CreatReport::OnCancel() 
{
	// TODO: Add extra cleanup here
	
	CDialog::OnCancel();
}

void CreatReport::OnDatabase() 
{
	// TODO: Add your control notification handler code here
	
}

void CreatReport::OnClear() 
{
	// TODO: Add your control notification handler code here
	m_Address = _T("");
	m_Type = _T("");
	m_Name = _T("");
	m_Scribe = _T("");
	m_Reporter = _T("");
	m_Data = 0;
	UpdateData(false);
	
}
