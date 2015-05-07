// CBaseButtonDlg.cpp : implementation file
//

#include "stdafx.h"
#include "CBaseButton.h"
#include "CBaseButtonDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCBaseButtonDlg dialog

CCBaseButtonDlg::CCBaseButtonDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CCBaseButtonDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CCBaseButtonDlg)
	m_radio = 1;							//Ĭ��ѡ��Ϊ1G
	m_show = _T("");
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CCBaseButtonDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCBaseButtonDlg)
	DDX_Control(pDX, IDC_CHECK4, m_check4);
	DDX_Control(pDX, IDC_CHECK3, m_check3);
	DDX_Control(pDX, IDC_CHECK2, m_check2);
	DDX_Control(pDX, IDC_CHECK1, m_check1);
	DDX_Radio(pDX, IDC_RADIO1, m_radio);
	DDX_Text(pDX, IDC_STATICSHOW, m_show);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CCBaseButtonDlg, CDialog)
	//{{AFX_MSG_MAP(CCBaseButtonDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(ID_CHECKIN, OnCheckin)
	ON_BN_CLICKED(ID_RESET, OnReset)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCBaseButtonDlg message handlers

BOOL CCBaseButtonDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	GetDlgItem(ID_RESET)->EnableWindow(false);				//����ѡ��ť��Ч
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CCBaseButtonDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CCBaseButtonDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CCBaseButtonDlg::OnCheckin() 
{
	// TODO: Add your control notification handler code here
	GetDlgItem(ID_RESET)->EnableWindow(true);				//����ѡ����Ч
	GetDlgItem(ID_CHECKIN)->EnableWindow(false);				//�ύ��ť��Ч
	UpdateData(true);
	m_show="�ڴ�: "; 								//���������Ϣ�ַ���
	CString str;
	switch(m_radio)
	{
		case 0:											//�����һ����ѡ�ѡ��
			GetDlgItemText(IDC_RADIO1,str);
			m_show=m_show+str;
			break;
		case 1:											//����ڶ�����ѡ�ѡ��
			GetDlgItemText(IDC_RADIO2,str);
			m_show=m_show+str;
			break;
		case 2:											//�����������ѡ�ѡ��
			GetDlgItemText(IDC_RADIO3,str);
			m_show=m_show+str;
			break;
		
	}
	if(m_check1.GetCheck()==1)							//��ѡ��1��ѡ��
	{
		GetDlgItemText(IDC_CHECK1,str);
		m_show=m_show+str;

	}

	if(m_check2.GetCheck()==1)							//��ѡ��2��ѡ��
	{
		GetDlgItemText(IDC_CHECK2,str);
		m_show=m_show+str;
	}
	if(m_check3.GetCheck()==1)							//��ѡ��3��ѡ��
	{
		GetDlgItemText(IDC_CHECK3,str);
		m_show=m_show+str;
	}
	if(m_check4.GetCheck()==1)							//��ѡ��4��ѡ��
	{
		GetDlgItemText(IDC_CHECK4,str);
		m_show=m_show+str;
	}
	UpdateData(false);

	
}

void CCBaseButtonDlg::OnReset() 
{
	// TODO: Add your control notification handler code here
	GetDlgItem(ID_RESET)->EnableWindow(false);				//����ѡ��ť��Ч
	GetDlgItem(ID_CHECKIN)->EnableWindow(true);				//�ύѡ��ť��Ч
	m_radio=1;											//��ѡ���Ĭ��ֵ
	m_check1.SetCheck(0);								//��ѡ��1��ѡ��
	m_check2.SetCheck(0);								//��ѡ��2��ѡ��
	m_check3.SetCheck(0);								//��ѡ��3��ѡ��
	m_check4.SetCheck(0);								//��ѡ��4��ѡ��
	m_show="";
	UpdateData(false);

	
}
