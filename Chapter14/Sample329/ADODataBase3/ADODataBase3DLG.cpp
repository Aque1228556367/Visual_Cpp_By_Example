// ADODataBase3Dlg.cpp : implementation file
//

#include "stdafx.h"
#include "ADODataBase3.h"
#include "ADODataBase3Dlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CADODataBase3Dlg dialog

CADODataBase3Dlg::CADODataBase3Dlg(CWnd* pParent /*=NULL*/)
	: CDialog(CADODataBase3Dlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CADODataBase3Dlg)
	m_strNumber = _T("");
	m_strName = _T("");
	m_strSex = _T("");
	m_strAddress = _T("");
	m_radio = 0;
	m_Status = _T("");
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CADODataBase3Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CADODataBase3Dlg)
	DDX_Text(pDX, IDC_EDIT1, m_strNumber);
	DDX_Text(pDX, IDC_EDIT2, m_strName);
	DDX_Text(pDX, IDC_EDIT3, m_strSex);
	DDX_Text(pDX, IDC_EDIT4, m_strAddress);
	DDX_Radio(pDX, IDC_RADIO1, m_radio);
	DDX_Text(pDX, IDC_EDIT5, m_Status);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CADODataBase3Dlg, CDialog)
	//{{AFX_MSG_MAP(CADODataBase3Dlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_ADD, OnAdd)
	ON_BN_CLICKED(IDC_RADIO1, OnRadio1)
	ON_BN_CLICKED(IDC_RADIO2, OnRadio2)
	ON_BN_CLICKED(IDC_RADIO3, OnRadio3)
	ON_BN_CLICKED(IDC_FIRST, OnFirst)
	ON_BN_CLICKED(IDC_LAST, OnLast)
	ON_BN_CLICKED(IDC_NEXT, OnNext)
	ON_BN_CLICKED(IDC_PREV, OnPrev)
	ON_BN_CLICKED(IDC_CHECKIN, OnCheckin)
	ON_BN_CLICKED(IDC_REMOVE, OnRemove)
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CADODataBase3Dlg message handlers

BOOL CADODataBase3Dlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	// TODO: Add extra initialization here
	AfxEnableControlContainer();
	GetDlgItem(IDC_REMOVE)->EnableWindow(false);//����ɾ����ť
	GetDlgItem(IDC_CHECKIN)->EnableWindow(false);//�����ύ��ť
	//���õ�����ť�ؼ�
	GetDlgItem(IDC_FIRST)->EnableWindow(false);//���õ�һ����ť
	GetDlgItem(IDC_NEXT)->EnableWindow(false);//������һ����ť
	GetDlgItem(IDC_PREV)->EnableWindow(false);//������һ����ť
	GetDlgItem(IDC_LAST)->EnableWindow(false);//�������һ����ť
	HRESULT hr; 
	try 
	{ 
		hr = m_pConnection.CreateInstance("ADODB.Connection");			//����Connection���� 
		if(SUCCEEDED(hr)) 
		{ 
			hr = m_pConnection->Open("student","","",adModeUnknown);//�������ݿ� 
		}
	}
	catch(_com_error e)										//��׽�쳣 
	{ 
		CString errormessage; 
		errormessage.Format("�������ݿ�ʧ��!\r\n������Ϣ:%s",e.ErrorMessage()); 
		AfxMessageBox(errormessage);								//��ʾ������Ϣ 
	} 
	
	_variant_t RecordsAffected; 
//	m_pConnection->Execute("CREATE TABLE studentinfo(stuNo TEXT,stuName TEXT,stuSex TEXT,stuAddress TEXT)",&RecordsAffected,adCmdText); 						//������
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CADODataBase3Dlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CADODataBase3Dlg::OnPaint() 
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
HCURSOR CADODataBase3Dlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CADODataBase3Dlg::OnAdd() 
{
	// TODO: Add your control notification handler code here
	_variant_t RecordsAffected; 
	UpdateData(true);
	if(m_strNumber.IsEmpty())
	{
		AfxMessageBox("ѧ�Ų���Ϊ�գ�");
		return;
	}
	CString strSQL; 
	strSQL.Format("INSERT INTO studentinfo(stuNo,stuName,stuSex,stuAddress)VALUES ('%s', '%s','%s','%s')",m_strNumber,m_strName,m_strSex,m_strAddress); 
	m_pConnection->Execute((_bstr_t)strSQL,&RecordsAffected,adCmdText); //��Ӽ�¼
	m_strNumber=m_strName=m_strSex=m_strAddress="";
	UpdateData(false);		
}

void CADODataBase3Dlg::OnRadio1() //��Ӳ���
{
	// TODO: Add your control notification handler code here
	m_radio=0;
	GetDlgItem(IDC_ADD)->EnableWindow(true);//������Ӱ�ť
	GetDlgItem(IDC_REMOVE)->EnableWindow(false);//����ɾ����ť
	GetDlgItem(IDC_CHECKIN)->EnableWindow(false);//�����ύ��ť
	//���õ�����ť�ؼ�
	GetDlgItem(IDC_FIRST)->EnableWindow(false);//���õ�һ����ť
	GetDlgItem(IDC_NEXT)->EnableWindow(false);//������һ����ť
	GetDlgItem(IDC_PREV)->EnableWindow(false);//������һ����ť
	GetDlgItem(IDC_LAST)->EnableWindow(false);//�������һ����ť
	m_strNumber=m_strName=m_strSex=m_strAddress="";
	UpdateData(false);	
}

void CADODataBase3Dlg::OnRadio2()//�༭���� 
{
	// TODO: Add your control notification handler code here
	m_radio=1;
	GetDlgItem(IDC_ADD)->EnableWindow(false);//������Ӱ�ť
	GetDlgItem(IDC_REMOVE)->EnableWindow(false);//����ɾ����ť
	GetDlgItem(IDC_CHECKIN)->EnableWindow(true);//�����ύ��ť
	//�������ť�ؼ�
	GetDlgItem(IDC_FIRST)->EnableWindow(true);//�����һ����ť
	GetDlgItem(IDC_NEXT)->EnableWindow(true);//������һ����ť
	GetDlgItem(IDC_PREV)->EnableWindow(true);//������һ����ť
	GetDlgItem(IDC_LAST)->EnableWindow(true);//�������һ����ť
	_variant_t RecordsAffected; 
	m_pRecordset =m_pConnection->Execute("SELECT COUNT(*) FROM studentinfo",&RecordsAffected,adCmdText); 
	_variant_t vIndex = (long)0; 
	_variant_t vCount = m_pRecordset->GetCollect(vIndex); //ȡ�õ�һ���ֶε�ֵ����vCount���� 
	count=vCount.lVal;//��ȡ��¼���ļ�¼��
	m_pRecordset->Close();///�رռ�¼�� 
	if(count==0)//��¼Ϊ0
	{
		GetDlgItem(IDC_REMOVE)->EnableWindow(false);//����ɾ����ť
		//���õ�����ť�ؼ�
		GetDlgItem(IDC_FIRST)->EnableWindow(false);//���õ�һ����ť
		GetDlgItem(IDC_NEXT)->EnableWindow(false);//������һ����ť
		GetDlgItem(IDC_PREV)->EnableWindow(false);//������һ����ť
		GetDlgItem(IDC_LAST)->EnableWindow(false);//�������һ����ť
		AfxMessageBox("����û�����ݣ�");
		return;
	}
	m_pRecordset.CreateInstance(__uuidof(Recordset));//������¼������
	CString strSQL="SELECT * FROM studentinfo";
	try
	{
		//�����ݿ��д򿪱�
		m_pRecordset->Open(_bstr_t(strSQL), m_pConnection.GetInterfacePtr(),adOpenDynamic,adLockOptimistic,adCmdText);
	}
	catch (_com_error e)
	{
		CString strError;
		strError.Format("���棺�����ݱ�ʱ�����쳣��������Ϣ��%s",e.ErrorMessage());
		AfxMessageBox(strError);
		return;
	}
	m_pRecordset->MoveFirst();//�Ƶ���һ����¼
	curNo=1;
	m_Status.Format("����%d����¼����ǰ��%d��",count,curNo);
	UpdateData(false);
	ShowRecord();//��ʾ��¼
	
}

void CADODataBase3Dlg::OnRadio3() //ɾ����¼
{
	// TODO: Add your control notification handler code here
	OnRadio2();
	m_radio=2;
	GetDlgItem(IDC_REMOVE)->EnableWindow(true);//����ɾ����ť
	GetDlgItem(IDC_CHECKIN)->EnableWindow(false);//�����ύ��ť
	UpdateData(false);

}

void CADODataBase3Dlg::OnFirst() //��һ��
{
	// TODO: Add your control notification handler code here
	if(count==0)//��¼Ϊ0
	{
		m_strNumber=m_strName=m_strSex=m_strAddress="";
		UpdateData(false);	
		GetDlgItem(IDC_REMOVE)->EnableWindow(false);//����ɾ����ť
		//���õ�����ť�ؼ�
		GetDlgItem(IDC_FIRST)->EnableWindow(false);//���õ�һ����ť
		GetDlgItem(IDC_NEXT)->EnableWindow(false);//������һ����ť
		GetDlgItem(IDC_PREV)->EnableWindow(false);//������һ����ť
		GetDlgItem(IDC_LAST)->EnableWindow(false);//�������һ����ť
		return;
	}
	m_pRecordset->MoveFirst();//�Ƶ���һ����¼
	curNo=1;
	m_Status.Format("����%d����¼����ǰ��%d��",count,curNo);
	UpdateData(false);
	ShowRecord();//��ʾ��¼	
}

void CADODataBase3Dlg::OnLast() //���һ��
{
	// TODO: Add your control notification handler code here
	m_pRecordset->MoveLast();//�Ƶ����һ����¼
	curNo=count;
	m_Status.Format("����%d����¼����ǰ��%d��",count,curNo);
	UpdateData(false);
	ShowRecord();//��ʾ��¼	
}

void CADODataBase3Dlg::OnNext() //��һ��
{
	// TODO: Add your control notification handler code here
	if(curNo<count)
	{
		m_pRecordset->MoveNext();//�Ƶ���һ����¼
		curNo++;
		if(m_pRecordset->adoEOF)
		{
			m_pRecordset->MoveLast();
		}
		m_Status.Format("����%d����¼����ǰ��%d��",count,curNo);
		UpdateData(false);
		ShowRecord();//��ʾ��¼
	}	
}
void CADODataBase3Dlg::OnPrev() //��һ��
{
	// TODO: Add your control notification handler code here
		if(curNo>1)
	{
		m_pRecordset->MovePrevious();//�Ƶ���һ����¼
		curNo--;
		if(m_pRecordset->BOF)
		{
			m_pRecordset->MoveFirst();
		}
		m_Status.Format("����%d����¼����ǰ��%d��",count,curNo);
		UpdateData(false);
		ShowRecord();//��ʾ��¼
	}	
}

void CADODataBase3Dlg::OnCheckin() 
{
	// TODO: Add your control notification handler code here
	UpdateData();
	m_pRecordset->PutCollect("stuNo",_variant_t(m_strNumber));
	m_pRecordset->PutCollect("stuName",_variant_t(m_strName));
	m_pRecordset->PutCollect("stuSex",_variant_t(m_strSex));
	m_pRecordset->PutCollect("stuAddress",_variant_t(m_strAddress));
	m_pRecordset->Update();//�ύ��¼
	m_Status="�ɹ��޸���һ����¼��";
	UpdateData(false);
}

void CADODataBase3Dlg::OnRemove() 
{
	// TODO: Add your control notification handler code here
	m_pRecordset->Delete(adAffectCurrent);//ɾ����ǰ��¼
	OnRadio3();	//ɾ������
}
void CADODataBase3Dlg::ShowRecord()//�ڱ༭������ʾ��¼
{
	m_strNumber=(char*)_bstr_t(m_pRecordset->GetCollect("stuNo"));
	m_strName=(char*)_bstr_t(m_pRecordset->GetCollect("stuName"));
	m_strSex=(char*)_bstr_t(m_pRecordset->GetCollect("stuSex"));
	m_strAddress=(char*)_bstr_t(m_pRecordset->GetCollect("stuAddress"));
	UpdateData(false);
}

void CADODataBase3Dlg::OnDestroy() 
{
	if(m_pRecordset!=NULL)
	{
		m_pRecordset->Close();//�رռ�¼������
		m_pRecordset=NULL;
	}
	if(m_pConnection->State)
	{
		m_pConnection->Close();//�ر����Ӷ���
		m_pConnection=NULL;
	}	
	CDialog::OnDestroy();
}
