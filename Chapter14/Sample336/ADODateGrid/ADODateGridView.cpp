// ADODateGridView.cpp : implementation of the CADODateGridView class
//

#include "stdafx.h"
#include "ADODateGrid.h"
#include "column.h"
#include "columns.h"
#include "ADODateGridDoc.h"
#include "ADODateGridView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CADODateGridView

IMPLEMENT_DYNCREATE(CADODateGridView, CFormView)

BEGIN_MESSAGE_MAP(CADODateGridView, CFormView)
	//{{AFX_MSG_MAP(CADODateGridView)
	ON_BN_CLICKED(IDC_SOURCE, OnSource)
	ON_BN_CLICKED(IDC_CONNECT, OnConnect)
	ON_BN_CLICKED(IDC_EXECUTE, OnExecute)
	ON_BN_CLICKED(IDC_DISCONNECT, OnDisconnect)
	ON_BN_CLICKED(IDC_QUIT, OnQuit)
	ON_LBN_SELCHANGE(IDC_LIST1, OnSelchangeList1)
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CFormView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CFormView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CFormView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CADODateGridView construction/destruction

CADODateGridView::CADODateGridView()
	: CFormView(CADODateGridView::IDD)
{
	//{{AFX_DATA_INIT(CADODateGridView)
	m_strConnection = _T("");
	m_strSQL = _T("");
	//}}AFX_DATA_INIT
	// TODO: add construction code here
	isDesc=true;

}

CADODateGridView::~CADODateGridView()
{
}

void CADODateGridView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CADODateGridView)
	DDX_Control(pDX, IDC_LIST1, m_ctlList);
	DDX_Text(pDX, IDC_EDIT1, m_strConnection);
	DDX_Text(pDX, IDC_EDIT2, m_strSQL);
	DDX_Control(pDX, IDC_DATAGRID1, m_ctlDataGrid);
	//}}AFX_DATA_MAP
}

BOOL CADODateGridView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CFormView::PreCreateWindow(cs);
}

void CADODateGridView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();
	GetParentFrame()->RecalcLayout();
	ResizeParentToFit();

}

/////////////////////////////////////////////////////////////////////////////
// CADODateGridView printing

BOOL CADODateGridView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CADODateGridView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CADODateGridView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

void CADODateGridView::OnPrint(CDC* pDC, CPrintInfo* /*pInfo*/)
{
	// TODO: add customized printing code here
}

/////////////////////////////////////////////////////////////////////////////
// CADODateGridView diagnostics

#ifdef _DEBUG
void CADODateGridView::AssertValid() const
{
	CFormView::AssertValid();
}

void CADODateGridView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}

CADODateGridDoc* CADODateGridView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CADODateGridDoc)));
	return (CADODateGridDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CADODateGridView message handlers

void CADODateGridView::OnSource() //ѡ������Դ
{
	// TODO: Add your control notification handler code here
	HRESULT hr;
	IDataSourceLocatorPtr m_slocator=NULL;//DataSourceLocator����ָ��
	_ConnectionPtr m_Conn=NULL;
	::CoInitialize(NULL); 										//��ʼ��COM����
	hr=m_slocator.CreateInstance(_uuidof(DataLinks));//����ʵ��
	m_Conn=m_slocator->PromptNew();//������������Դ�Ի���
	if(m_Conn!=NULL)
	{
		m_strConnection.Format("%s",(char*)m_Conn->ConnectionString);
		UpdateData(false);
	}	
}

void CADODateGridView::OnConnect() //��������Դ
{
	// TODO: Add your control notification handler code here
	UpdateData(true);
	try
	{
		m_Connection.CreateInstance("ADODB.Connection");			//����Connection����
		m_Connection->Open(_bstr_t(m_strConnection.GetBuffer(0)),"","",-1);
	}
	catch(_com_error e)										//��׽�쳣 
	{ 
		CString errormessage; 
		errormessage.Format("�������ݿ�ʧ��!\r\n������Ϣ:%s",e.ErrorMessage()); 
		AfxMessageBox(errormessage);						//��ʾ������Ϣ 
		return;
	}  
	m_ctlList.ResetContent();//����б��
	//����ʵ�ֻ�ȡ����Դ�а��������б�ı���������ӵ��б����
	_bstr_t tablenames;
	CString  str;
	try
	{
		m_Recordset.CreateInstance(_uuidof(Recordset));//������¼��ʵ��
		//��ֻ���ķ�ʽ�򿪽��������ñ���
		m_Recordset=m_Connection->OpenSchema(adSchemaTables,vtMissing,vtMissing);
		while(!m_Recordset->adoEOF)
		{
			tablenames=m_Recordset->GetCollect("TABLE_NAME");//��ȡ���������
			str=(char*)tablenames;
			if(str.Left(4)!="MSys")//����Ǳ���
				m_ctlList.AddString(str);//��ӵ��б��
			m_Recordset->MoveNext();
		}
	}
	catch(_com_error e)										//��׽�쳣 
	{ 
		CString errormessage; 
		errormessage.Format("����ʧ��!\r\n������Ϣ:%s",e.ErrorMessage()); 
		AfxMessageBox(errormessage);						//��ʾ������Ϣ 
		return;
	}  
	m_Recordset=NULL;
}



void CADODateGridView::OnExecute() //ִ��SQL���
{
	// TODO: Add your control notification handler code here
	try
	{
		m_Recordset.CreateInstance(_uuidof(Recordset));//������¼��ʵ��
		UpdateData(true);
		m_Recordset->CursorLocation=adUseClient;//�趨�α����
		m_Recordset->Open(m_strSQL.GetBuffer(0),m_Connection.GetInterfacePtr(),adOpenDynamic,adLockOptimistic,adCmdText);
	}
	catch(_com_error e)										//��׽�쳣 
	{ 
		CString errormessage; 
		errormessage.Format("����ʧ��!\r\n������Ϣ:%s",e.ErrorMessage()); 
		AfxMessageBox(errormessage);						//��ʾ������Ϣ 
		return;
	}  
	//��ִ��SQL���õ��Ľ������DataGrid�ؼ�����ʾ
	m_ctlDataGrid.SetRefDataSource((LPUNKNOWN)m_Recordset);
	m_ctlDataGrid.Refresh();//ˢ�¿ؼ�
	UpdateData(false);
	m_Recordset=NULL;
}

void CADODateGridView::OnDisconnect() //�Ͽ�����
{
	// TODO: Add your control notification handler code here
	try
	{
		m_Connection->Close();//�Ͽ�����
		m_Connection=NULL;

	}
	catch(_com_error e)										//��׽�쳣 
	{ 
		CString errormessage; 
		errormessage.Format("����ʧ��!\r\n������Ϣ:%s",e.ErrorMessage()); 
		AfxMessageBox(errormessage);						//��ʾ������Ϣ 
		return;
	}  
	//ʹ�ø��ؼ��ָ�����ʼ״̬
	m_ctlList.ResetContent();//����б��
	m_ctlDataGrid.SetRefDataSource(NULL);//���DataGrid
	m_ctlDataGrid.ClearFields();
	m_ctlDataGrid.Refresh();
	m_strSQL="";
	UpdateData(false);	
}

void CADODateGridView::OnQuit() //�˳�����
{
	// TODO: Add your control notification handler code here
	if(m_Recordset!=NULL)
		m_Recordset->Close();//�رռ�¼��
	if(m_Connection!=NULL)
		m_Connection->Close();//�Ͽ�����
	PostMessage(WM_QUIT);//�˳�����
}

void CADODateGridView::OnSelchangeList1() 
{
	// TODO: Add your control notification handler code here
	int index=m_ctlList.GetCurSel();
	m_ctlList.GetText(index,m_strTable);//��ȡ�б����ѡ�еı���
	m_strSQL="Select * from ["+m_strTable+"]";
	UpdateData(false);
	OnExecute();//ִ��SQL���
}

BEGIN_EVENTSINK_MAP(CADODateGridView, CFormView)
    //{{AFX_EVENTSINK_MAP(CADODateGridView)
	ON_EVENT(CADODateGridView, IDC_DATAGRID1, 216 /* HeadClick */, OnHeadClickDatagrid1, VTS_I2)
	//}}AFX_EVENTSINK_MAP
END_EVENTSINK_MAP()

void CADODateGridView::OnHeadClickDatagrid1(short ColIndex) 
{
	// TODO: Add your control notification handler code here
	CColumns cols=m_ctlDataGrid.GetColumns();//��ȡ�ؼ��ĸ���
	VARIANT index;
	index.intVal=ColIndex;
	index.vt=VT_I4;//����
	CColumn col=cols.GetItem(index);//�õ���������
	CString strCol;//����
	strCol=col.GetCaption();
	CString strSQL;
	int len;//��¼SQL���ĳ���
	if(m_Connection!=NULL)
	{
		if(strCol.GetLength()!=0)
		{
			len=m_strSQL.GetLength();
			strSQL="Order by ["+strCol+"]";
			if(isDesc)//��������
			{
				strSQL+="desc";
				isDesc=false;
			}
			else//��������
				isDesc=true;
		}
		m_strSQL+=strSQL;
		UpdateData(false);
		OnExecute();//ִ��SQL���
		m_strSQL.Delete(len,strSQL.GetLength());//�ָ�����ǰ��SQL���
	}
}
