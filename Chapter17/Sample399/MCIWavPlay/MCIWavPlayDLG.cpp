// MCIWavPlayDlg.cpp : implementation file
//

#include "stdafx.h"
#include "MCIWavPlay.h"
#include "MCIWavPlayDlg.h"

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
// CMCIWavPlayDlg dialog

CMCIWavPlayDlg::CMCIWavPlayDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CMCIWavPlayDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CMCIWavPlayDlg)
	m_strbits = _T("");
	m_strChannel = _T("");
	m_strname = _T("");
	m_strtime = _T("");
	m_strSample = _T("");
	m_strstatus = _T("");
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMCIWavPlayDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMCIWavPlayDlg)
	DDX_Control(pDX, IDC_LIST1, m_List);
	DDX_Text(pDX, IDC_BITS, m_strbits);
	DDX_Text(pDX, IDC_CHANNEL, m_strChannel);
	DDX_Text(pDX, IDC_FILENAME, m_strname);
	DDX_Text(pDX, IDC_FILETIME, m_strtime);
	DDX_Text(pDX, IDC_SAMPLERATE, m_strSample);
	DDX_Text(pDX, IDC_STATUS, m_strstatus);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CMCIWavPlayDlg, CDialog)
	//{{AFX_MSG_MAP(CMCIWavPlayDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_OPENWAV, OnOpenwav)
	ON_BN_CLICKED(IDC_PLAYWAV, OnPlaywav)
	ON_BN_CLICKED(IDC_RECORDWAV, OnRecordwav)
	ON_BN_CLICKED(IDC_SAVEWAV, OnSavewav)
	ON_BN_CLICKED(IDC_STOPWAV, OnStopwav)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMCIWavPlayDlg message handlers

BOOL CMCIWavPlayDlg::OnInitDialog()
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
	GetDlgItem(IDC_PLAYWAV)->EnableWindow(FALSE);    // ʹ"����"��ť������Ч
	GetDlgItem(IDC_SAVEWAV)->EnableWindow(FALSE);    // ʹ"����"��ť������Ч
	GetDlgItem(IDC_STOPWAV)->EnableWindow(FALSE);    // ʹ"ֹͣ"��ť������Ч
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CMCIWavPlayDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CMCIWavPlayDlg::OnPaint() 
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
HCURSOR CMCIWavPlayDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CMCIWavPlayDlg::OnOpenwav() //�򿪲�����Ƶ�ļ�
{
	// TODO: Add your control notification handler code here
	CString Filter;
	char buf[128];
	DWORD dwFlag;
	Filter = "������Ƶ�ļ�(*.WAV)|*.WAV||";
	CFileDialog fileDlg(TRUE, NULL, NULL, OFN_HIDEREADONLY, Filter);
	if (fileDlg.DoModal() ==IDOK)    // ��ʾ���ļ��ĶԻ���
	{
   		m_strname = fileDlg.GetPathName();       // ��ô򿪵��ļ���
		dwFlag = m_MyMCIWave.OpenWave(m_strname);                    // �򿪲�����Ƶ�ļ�
		if (dwFlag)
		{
			mciGetErrorString(dwFlag, buf, strlen(buf));  // ��ȡ������Ϣ
			AfxMessageBox(buf);                    // ��ʾ������Ϣ
		}
		GetDlgItem(IDC_PLAYWAV)->EnableWindow(TRUE); // ʹ"����"��ť��Ч
		m_strstatus = "���ļ���"+m_strname;  // ������Ϣ�ַ�������ʾ
		CTime m_time;
		m_time=CTime::GetCurrentTime();							//��ȡ��ǰʱ������
		CString str=m_time.Format("%H:%M:%S��");		//��ʽ��
		str=str+m_strstatus;
		m_List.AddString(str);//��ӵ��б��
		m_strSample.Format("%5.3f kHZ", m_MyMCIWave.GetSampleRate()/1000.);//��ȡ����Ƶ��
		switch (m_MyMCIWave.GetChannel())//��ȡ����
		{
		case 1:
			m_strChannel = "������";
			break;
		case 2:
			m_strChannel = "������";
			break;
		}
		m_strbits.Format("%dλ", m_MyMCIWave.GetBitLength());//����λ
		m_strtime.Format("%02.2fs",m_MyMCIWave.GetWaveLength()/1000.);//ʱ��
   		UpdateData(FALSE);//��ʾ��Ϣ
	}
}

void CMCIWavPlayDlg::OnPlaywav() //���Ų����ļ�
{
	if (m_MyMCIWave.PlayWave())
	{
		AfxMessageBox("���ų���");
		return;
	}
	GetDlgItem(IDC_RECORDWAV)->EnableWindow(FALSE);    // ʹ"¼��"��ť������Ч
	GetDlgItem(IDC_OPENWAV)->EnableWindow(FALSE);    // ʹ"��"��ť������Ч
	GetDlgItem(IDC_PLAYWAV)->EnableWindow(FALSE);    // ʹ"����"��ť������Ч
	GetDlgItem(IDC_STOPWAV)->EnableWindow(true);    // ʹ"ֹͣ"��ť������Ч
	m_MyMCIWave.m_bPlaying = TRUE;//���ò��ű�־
	m_strstatus = "���ڲ��š���";//����״̬
	CTime m_time;
	m_time=CTime::GetCurrentTime();		//��ȡ��ǰʱ��
	CString str=m_time.Format("%H:%M:%S��");		//��ʽ��
	str=str+"��ʼ����";
	m_List.AddString(str);//��ӵ��б��
	UpdateData(FALSE);
}

void CMCIWavPlayDlg::OnRecordwav() 
{
	// TODO: Add your control notification handler code here
	GetDlgItem(IDC_PLAYWAV)->EnableWindow(FALSE);    // ʹ"����"��ť������Ч
	GetDlgItem(IDC_OPENWAV)->EnableWindow(FALSE);    // ʹ"��"��ť������Ч
	GetDlgItem(IDC_RECORDWAV)->EnableWindow(FALSE);    // ʹ"¼��"��ť������Ч
	GetDlgItem(IDC_STOPWAV)->EnableWindow(true);    // ʹ"ֹͣ"��ť������Ч
	m_strstatus = "����¼������";        // ������Ϣ�ַ�������ʾ
	CTime m_time;
	m_time=CTime::GetCurrentTime();		
	CString str=m_time.Format("%H:%M:%S��");		//��ʽ��
	str=str+"��ʼ¼��";
	m_List.AddString(str);//��ӵ��б��
	m_strSample=m_strChannel=m_strname=m_strbits=m_strtime="";
	UpdateData(FALSE);
	m_MyMCIWave.RecordWave();                   // ��ʼ¼��
}

void CMCIWavPlayDlg::OnSavewav() //����¼�ƵĲ����ļ�
{
	// TODO: Add your control notification handler code here
	CString Filter;
	char buf[128];
	DWORD dwFlag;
	Filter = "Wave Files(*.WAV)|*.WAV||";//������
	CFileDialog fileDlg(FALSE, NULL, NULL, OFN_OVERWRITEPROMPT, Filter);//�����ļ��Ի���
	fileDlg.m_ofn.lpstrDefExt = "wav";
	if (fileDlg.DoModal() ==IDOK)
	{
		dwFlag =m_MyMCIWave.SaveWave(fileDlg.GetPathName());
		if (dwFlag)
		{
			mciGetErrorString(dwFlag, buf, strlen(buf));//��ȡ������Ϣ
			AfxMessageBox(buf);
			return;
		}
	}
	m_strstatus = "�����������";
	CTime m_time;
	m_time=CTime::GetCurrentTime();		
	CString str=m_time.Format("%H:%M:%S��");		//��ʽ��
	str=str+"����¼���ļ�";
	m_List.AddString(str);//��ӵ��б��
	UpdateData(FALSE);	
}

void CMCIWavPlayDlg::OnStopwav() //ֹͣ���Ż�¼��
{
	// TODO: Add your control notification handler code here
	GetDlgItem(IDC_STOPWAV)->EnableWindow(FALSE);    // ʹ"ֹͣ"��ť������Ч
	GetDlgItem(IDC_PLAYWAV)->EnableWindow(true);    // ʹ"����"��ť������Ч
	GetDlgItem(IDC_OPENWAV)->EnableWindow(true);    // ʹ"��"��ť������Ч
	GetDlgItem(IDC_RECORDWAV)->EnableWindow(true);    // ʹ"¼��"��ť������Ч
	CTime m_time;
	m_time=CTime::GetCurrentTime();		
	CString str=m_time.Format("%H:%M:%S��");		//��ʽ��
	if (m_MyMCIWave.m_bRecord)//����¼��
	{
		GetDlgItem(IDC_SAVEWAV)->EnableWindow(true);    // ʹ"����"��ť������Ч
		m_strstatus = "¼��ֹͣ����";
		str=str+"¼��ֹͣ";
		m_List.AddString(str);//��ӵ��б��
	}
	if (m_MyMCIWave.m_bPlaying)
	{
		m_strstatus = "����ֹͣ����";
		str=str+"����ֹͣ";
		m_List.AddString(str);//��ӵ��б��
	}
	UpdateData(FALSE);
	m_MyMCIWave.StopWave();//ֹͣ	
}
