// WordPrintDlg.cpp : implementation file
//

#include "stdafx.h"
#include "WordPrint.h"
#include "WordPrintDlg.h"
#include "msword.h"
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
// CWordPrintDlg dialog

CWordPrintDlg::CWordPrintDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CWordPrintDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CWordPrintDlg)
	m_strTitle = _T("");
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CWordPrintDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CWordPrintDlg)
	DDX_Text(pDX, IDC_TITLE, m_strTitle);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CWordPrintDlg, CDialog)
	//{{AFX_MSG_MAP(CWordPrintDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_WORDPRINT, OnWordprint)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CWordPrintDlg message handlers

BOOL CWordPrintDlg::OnInitDialog()
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
	::CoInitialize(NULL); 										//��ʼ��COM����
	// TODO: Add extra initialization here
	HRESULT hr; 
	try 
	{ 
		hr = m_pConnection.CreateInstance("ADODB.Connection");			//����Connection���� 
		if(SUCCEEDED(hr)) 
		{ 
			hr = m_pConnection->Open("studb","","",NULL);		//�������ݿ� 
		}
	}
	catch(_com_error e)										//��׽�쳣 
	{ 
		CString errormessage; 
		errormessage.Format("�������ݿ�ʧ��!\r\n������Ϣ:%s",e.ErrorMessage()); 
		AfxMessageBox(errormessage);								//��ʾ������Ϣ 
	} 
	_variant_t RecordsAffected; 
	m_pRecordset =m_pConnection->Execute("SELECT COUNT(*) FROM stuinfo",&RecordsAffected,adCmdText); 
	_variant_t vIndex = (long)0; 
	_variant_t vCount = m_pRecordset->GetCollect(vIndex); //ȡ�õ�һ���ֶε�ֵ����vCount���� 
	count=vCount.lVal;										//��ȡ��¼���ļ�¼��
	m_pRecordset->Close();										//�رռ�¼�� 

	m_pRecordset.CreateInstance(__uuidof(Recordset));					//������¼������
	CString strSQL="SELECT * FROM stuinfo";
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
		return false;
	}

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CWordPrintDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CWordPrintDlg::OnPaint() 
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
HCURSOR CWordPrintDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CWordPrintDlg::OnWordprint() 
{
	// TODO: Add your control notification handler code here
	UpdateData(true);
	CString Field[4]={"ѧ��","����","�Ա�","���"};//�еı���
	m_pRecordset->MoveFirst();
	//����wordӦ�ö���
	_Application sapp;
	if(!sapp.CreateDispatch(_T("word.Application"))) 
	{
		AfxMessageBox(_T(" Word failed to start!"));
		return;
	}
	//��word������ȡ���ĵ����󼯺�,ģ��*.dot
	_Document sDoc;//�ĵ�����
	Documents sDocs;//�ĵ����϶���
	sDocs.AttachDispatch(sapp.GetDocuments(),true);//�õ��ĵ����϶���
	VARIANT varUnit,varOptional;
	VariantInit(&varUnit);
	varUnit.vt=VT_I4;//������Ӧ����������Ϊlong
	varUnit.lVal=5;
	VariantInit(&varOptional);
	varOptional.vt=VT_ERROR;
	varOptional.scode=DISP_E_PARAMNOTFOUND;
	//������ĵ�����
	LPDISPATCH pDoc=sDocs.Add(&varOptional,&varOptional,&varOptional,&varOptional);
	sDoc.AttachDispatch(pDoc);
	long nRows,nCols;//�������к���
	nCols=4;
	nRows=count;
	//Range��������Ϊ����Word�ĵ�
	Range wordRange=sDoc.Range(&varOptional,&varOptional);
	//����ѡ��������
	Selection wordSelect=sapp.GetSelection();
	_Font oFont;//�����������
	_ParagraphFormat wordFormat;
	//���ñ���ı���
	wordSelect.HomeKey(&varUnit,&varOptional);//���������λ
	oFont=wordSelect.GetFont();//��ȡ����
	oFont.SetSize(15);//���������С
	oFont.SetName("����");//������������
	wordFormat=wordSelect.GetParagraphFormat();
	wordFormat.SetAlignment(1);//�ı����ж���
	wordSelect.InsertAfter(m_strTitle);//д���ı�
	wordSelect.EndKey(&varUnit,&varOptional);//��굽��β
	//���ñ��
	wordRange=wordSelect.GetRange();
	oFont=wordSelect.GetFont();
	oFont.SetSize(12);//���������С
	oFont.SetName("����");//������������
	wordFormat=wordSelect.GetParagraphFormat();
	wordFormat.SetAlignment(1);//�ı����ж���

	VARIANT varTable;//������ӱ��
	VariantInit(&varTable);
	varTable.vt=VT_I4;//������Ӧ����������Ϊlong
	varTable.lVal=0;

	Tables wordTables=wordSelect.GetTables();
	Table wordTable=wordTables.Add(wordRange,nRows,nCols,&varOptional,&varTable);
	Borders tblBorders;//�߿����
	tblBorders=wordTable.GetBorders();
	tblBorders.SetInsideLineStyle(1);
	tblBorders.SetOutsideLineStyle(7);

	Columns tblColumns;
	tblColumns=wordTable.GetColumns();
	tblColumns.SetPreferredWidthType(1);//�Զ��п�
	//�����д������
	long i,j,n;
	CString strValue;
	Cell tblCell;
	for(i=1;i<=nRows;i++)
	{
		if(i==1)//��һ��
		{
			for(j=1;j<=nCols;j++)
			{
				tblCell=wordTable.Cell(i,j);
				wordRange=tblCell.GetRange();
				oFont=wordRange.GetFont();
				oFont.SetName("����");
				wordRange.InsertAfter(Field[j-1]);
			}
		}
		else
		{
			for(j=1;j<=nCols;j++)
			{
				tblCell=wordTable.Cell(i,j);
				wordRange=tblCell.GetRange();
				switch (j)
				{
				case 1:
					wordRange.InsertAfter((char*)_bstr_t(m_pRecordset->GetCollect("id")));
					break;
				case 2:
					wordRange.InsertAfter((char*)_bstr_t(m_pRecordset->GetCollect("name")));
					break;
				case 3:
					wordRange.InsertAfter((char*)_bstr_t(m_pRecordset->GetCollect("sex")));
					break;
				case 4:
					wordRange.InsertAfter((char*)_bstr_t(m_pRecordset->GetCollect("home")));
					break;
				}
			}
			m_pRecordset->MoveNext();
		}
	}
	//��ʾ�ĵ��������ĵ�
	sapp.SetVisible(true);
	sDoc.Activate();	
}
