// FilePara.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "RadarDataShow.h"
#include "FilePara.h"


// CFilePara �Ի���

IMPLEMENT_DYNAMIC(CFilePara, CDialog)
CFilePara::CFilePara(CWnd* pParent /*=NULL*/)
	: CDialog(CFilePara::IDD, pParent)
	, m_Radio1(0)
	, m_Radio3(1)
	, m_Slice(0)
	, m_Polebegin(0)
	, m_Poleend(0)
{

}

CFilePara::~CFilePara()
{
}

void CFilePara::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_OUTSHOW, m_Outshow);
	DDX_Control(pDX, IDC_RADIO1, mb_Radio1);
	DDX_Control(pDX, IDC_RADIO5, mb_Radio3);
	DDX_Control(pDX, IDC_SLICE, mb_Slice);
	DDX_Control(pDX, IDC_POLEBEGIN, mb_Polebegin);
	DDX_Control(pDX, IDC_POLEEND, mb_Poleend);

	DDX_Radio(pDX, IDC_RADIO1, m_Radio1);
	DDX_Radio(pDX, IDC_RADIO5, m_Radio3);

	DDX_Text(pDX, IDC_SLICE, m_Slice);
	DDX_Text(pDX, IDC_POLEBEGIN, m_Polebegin);
	DDX_Text(pDX, IDC_POLEEND, m_Poleend);
}


BEGIN_MESSAGE_MAP(CFilePara, CDialog)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_RADIO1, OnBnClickedRadio1)
	ON_BN_CLICKED(IDC_RADIO2, OnBnClickedRadio2)
	ON_BN_CLICKED(IDC_RADIO5, OnBnClickedRadio5)
	ON_BN_CLICKED(IDC_RADIO6, OnBnClickedRadio6)
END_MESSAGE_MAP()


// CFilePara ��Ϣ�������

BOOL CFilePara::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	if(m_Sampleslice<=1)
	{
		CButton* pButton1=(CButton*)GetDlgItem(IDC_RADIO1);
		ASSERT(pButton1);
		if(pButton1)
		{
			pButton1->SetCheck(BST_UNCHECKED);
		}


		CButton* pButton=(CButton*)GetDlgItem(IDC_RADIO2);
		ASSERT(pButton);
		if(pButton)
		{
			pButton->SetCheck(BST_CHECKED);
		}
		
		OnBnClickedRadio2();

		mb_Radio1.EnableWindow(FALSE);
		mb_Slice.EnableWindow(FALSE);
	}


	if(m_Samplepole<=100)
	{	
		m_Radio3=1;
		mb_Radio3.EnableWindow(FALSE);
		mb_Polebegin.EnableWindow(FALSE);
		mb_Poleend.EnableWindow(FALSE);
	}
	



	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣��OCX ����ҳӦ���� FALSE
}

void CFilePara::OnPaint()
{
	// device context for painting
	// TODO: �ڴ������Ϣ����������
	// ��Ϊ��ͼ��Ϣ���� CDialog::OnPaint()

	CRect rect1;
	CWnd* pWnd1;
	pWnd1=GetDlgItem(IDC_OUTSHOW);
	pWnd1->GetClientRect(&rect1);
	CPaintDC dc(pWnd1);

	dc.FillSolidRect(&rect1,RGB(100,200,100));

	CString row1,row2,row3,row4;
	char ctime[8],cnum[8],cslice[8],cpole[8];
	sprintf(ctime,"%d",m_Timewindow);
	sprintf(cnum,"%d",m_Samplenum);
	sprintf(cslice,"%d",m_Sampleslice);
	sprintf(cpole,"%d",m_Samplepole);

	row1="�״����ʱ��Ϊ: "+(CString)ctime+"ns";
	row2="�״��������Ϊ: "+(CString)cnum;
	row3="�������ݼ�¼������Ϊ: "+(CString)cslice;
	row4="��������ÿ����������Ϊ: "+(CString)cpole;

	dc.TextOut(10,5,row1);
	dc.TextOut(10,35,row2);
	dc.TextOut(10,65,row3);
	dc.TextOut(10,95,row4);


	CDialog::OnPaint();

}

void CFilePara::OnBnClickedRadio1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	mb_Slice.EnableWindow(TRUE);
}

void CFilePara::OnBnClickedRadio2()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	mb_Slice.EnableWindow(FALSE);
}

void CFilePara::OnBnClickedRadio5()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	mb_Polebegin.EnableWindow(TRUE);
	mb_Poleend.EnableWindow(TRUE);
}

void CFilePara::OnBnClickedRadio6()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	mb_Polebegin.EnableWindow(FALSE);
	mb_Poleend.EnableWindow(FALSE);
}

void CFilePara::OnOK()
{
	// TODO: �ڴ����ר�ô����/����û���
	UpdateData(TRUE);
	if(m_Radio1==0)
	{
		if(m_Slice<=0||m_Slice>m_Sampleslice)
		{
			AfxMessageBox ("��ѡ�Ĵ������治��ȷ!",MB_OK);
			return;
		}
	}
	//else
	//{
	//	m_Slice=-1;//��������־�����ڲ������ʱ
	//}
	if(m_Radio3==0)
	{
		if(m_Polebegin<=0||m_Poleend>m_Samplenum||m_Polebegin>=m_Poleend-10)
		{
			AfxMessageBox ("��ѡ�Ĵ����㷶Χ����ȷ!",MB_OK);
			return;
		}
	}
	//else
	//{
	//	m_Polebegin=-1;
	//}

	CDialog::OnOK();
}
