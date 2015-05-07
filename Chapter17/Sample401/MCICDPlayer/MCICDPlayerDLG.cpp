// MCICDPlayerDlg.cpp : implementation file
//

#include "stdafx.h"
#include "MCICDPlayer.h"
#include "MCICDPlayerDlg.h"

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
// CMCICDPlayerDlg dialog

CMCICDPlayerDlg::CMCICDPlayerDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CMCICDPlayerDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CMCICDPlayerDlg)
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMCICDPlayerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMCICDPlayerDlg)
	DDX_Control(pDX, IDC_MUSIC_LIST, m_ctlCombo);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CMCICDPlayerDlg, CDialog)
	//{{AFX_MSG_MAP(CMCICDPlayerDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_PLAY, OnPlay)
	ON_BN_CLICKED(IDC_STOP, OnStop)
	ON_BN_CLICKED(IDC_PAUSE, OnPause)
	ON_BN_CLICKED(IDC_FORWARD, OnForward)
	ON_BN_CLICKED(IDC_BACK, OnBack)
	ON_BN_CLICKED(IDC_SKIPBACK, OnSkipback)
	ON_BN_CLICKED(IDC_SKIPFORWARD, OnSkipforward)
	ON_CBN_SELCHANGE(IDC_MUSIC_LIST, OnSelchangeMusicList)
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMCICDPlayerDlg message handlers

BOOL CMCICDPlayerDlg::OnInitDialog()
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
	m_CDAudio.OpenCD();//���豸
	SetTimer( 1, 1000, NULL );//����һ����ʱ��
	for(int i=0;i<m_CDAudio.GetTotalTracks();i++)//����Ŀ�ӵ�CComboBox�ؼ���
	{
		CString str;
		str.Format("��Ŀ%d",i+1);
		m_ctlCombo.AddString(str);
	}
	m_ctlCombo.SetCurSel(0);
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CMCICDPlayerDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CMCICDPlayerDlg::OnPaint() 
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
HCURSOR CMCICDPlayerDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}
void CMCICDPlayerDlg::OnDestroy() 
{
	//ɱ����ʱ��
	KillTimer(1);
	CDialog::OnDestroy();	
}
void CMCICDPlayerDlg::OnTimer(UINT nIDEvent) 
{	
	BOOL bDriveReady = TRUE;
	//��õ�ǰ��Ŀ�Ѿ����ŵ�ʱ�䣬����ʾ
	CString strStatus;
	strStatus.Format( "[%d] %02d:%02d",m_CDAudio.GetCurrentTrack(),m_CDAudio.GetMinutes(),m_CDAudio.GetSeconds() );
	//û��CD
	if( m_CDAudio.GetCurrentTrack() == -1 )
	{
		strStatus = "û��CD";
		bDriveReady = FALSE;
	}
	SetDlgItemText(IDC_TRACKINFO, strStatus );
	//���CD���ܹ����ȣ�����ʾ
	CString strLength;
	int nMinutes, nSeconds;
	m_CDAudio.GetTotalLength( &nMinutes,&nSeconds );
	strLength.Format( "�ܹ�����(m:s): %02d:%02d",nMinutes, nSeconds );
	if( nMinutes == -1 )
		strLength = "�ܹ�����(��:��): 00:00";
	SetDlgItemText( IDC_TOTALTIME, strLength );
	//��õ�ǰ����Ŀ���ȣ�����ʾ
	m_CDAudio.GetTrackLength(m_CDAudio.GetCurrentTrack(),&nMinutes, &nSeconds );
	strLength.Format( "��Ŀ����(��:��): %02d:%02d",nMinutes, nSeconds);
	if( nMinutes == -1 )
		strLength = "��Ŀ����(��:��): 00:00";
	SetDlgItemText( IDC_TRACKTIME, strLength );
	//���ݲ���״̬�ı䰴ť�Ŀ����벻����״̬
	GetDlgItem(IDC_BACK)->EnableWindow(bDriveReady);//���˰�ť
	GetDlgItem(IDC_FORWARD)->EnableWindow(bDriveReady);//ǰ����ť
	GetDlgItem(IDC_SKIPBACK)->EnableWindow(bDriveReady);//��һ��Ŀ
	GetDlgItem(IDC_SKIPFORWARD)->EnableWindow(bDriveReady);//��һ��Ŀ
	BOOL bPaused;
	if( m_CDAudio.IsPlaying(&bPaused))
	{
		GetDlgItem(IDC_PLAY)->EnableWindow(bPaused);//���Ű�ť
		GetDlgItem(IDC_STOP)->EnableWindow(bDriveReady);//ֹͣ��ť
		GetDlgItem(IDC_PAUSE)->EnableWindow(bDriveReady && !bPaused);//��ͣ��ť	
	}
	else
	{
		GetDlgItem(IDC_PLAY)->EnableWindow(bDriveReady);
		GetDlgItem(IDC_STOP)->EnableWindow(FALSE);
		GetDlgItem(IDC_PAUSE)->EnableWindow(FALSE);	
	}
	CDialog::OnTimer(nIDEvent);
}

void CMCICDPlayerDlg::OnPlay() //����
{
	// ��������е�CD�Ѿ�׼���þͲ���
	if(m_CDAudio.IsDriveReady())
		m_CDAudio.PlayCD();
}

void CMCICDPlayerDlg::OnStop() // ֹͣ����
{	
	m_CDAudio.Stop();
}

void CMCICDPlayerDlg::OnPause() // ��ͣ����
{
	m_CDAudio.Pause();
}

void CMCICDPlayerDlg::OnForward() //����
{
	
	// ��õ�ǰ��Ŀ�Ĳ��ų���
	int nMinutes = m_CDAudio.GetMinutes();
	int nSeconds = m_CDAudio.GetSeconds();
	int nTrack = m_CDAudio.GetCurrentTrack();
	if( nMinutes == -1 )
		return;
	//��ǰ��Ծ5�룬��֤û�г���
	nSeconds += 5;
	if( nSeconds > 59 )
	{
		nMinutes++;
		nSeconds -= 60;
	}
	int nTrackMinutes, nTrackSeconds;
	m_CDAudio.GetTrackLength(nTrack,&nTrackMinutes, &nTrackSeconds);
	if(nMinutes*60+nSeconds >nTrackMinutes*60+nTrackSeconds)
	{
		nMinutes = nTrackMinutes;
		nSeconds = nTrackSeconds;
	}
	//��λ���µ�λ��
	m_CDAudio.SeekTo(nTrack,nMinutes, nSeconds,0);
}

void CMCICDPlayerDlg::OnBack() //����
{
	// ��õ�ǰ��Ŀ�Ĳ��ų���
	int nMinutes = m_CDAudio.GetMinutes();
	int nSeconds = m_CDAudio.GetSeconds();
	int nTrack = m_CDAudio.GetCurrentTrack();
	if( nMinutes == -1 )
		return;
	//��ǰ��Ծ5�룬��֤û�г���
	nSeconds -= 5;
	if( nSeconds < 0 )
	{
		nMinutes--;
		nSeconds += 60;
		if(nMinutes<0)
			nMinutes=0;
	}
	//��λ���µ�λ��
	m_CDAudio.SeekTo( nTrack,nMinutes, nSeconds, 0 );
}

void CMCICDPlayerDlg::OnSkipback() //��һ��Ŀ
{
	//�����Ծһ����Ŀ
	int nTrack = m_CDAudio.GetCurrentTrack() - 1;
	if( nTrack < 1 )
		nTrack = m_CDAudio.GetTotalTracks();
	m_CDAudio.SeekTo(nTrack, 0, 0, 0 );
	m_ctlCombo.SetCurSel(nTrack-1);
}

void CMCICDPlayerDlg::OnSkipforward() //��һ��Ŀ
{
	//��ǰ��Ծһ����Ŀ
	int nTrack = m_CDAudio.GetCurrentTrack() + 1;
	if(nTrack > m_CDAudio.GetTotalTracks())
		nTrack = 1;
	m_CDAudio.SeekTo( nTrack, 0, 0, 0 );
	m_ctlCombo.SetCurSel(nTrack-1);
}

void CMCICDPlayerDlg::OnSelchangeMusicList() 
{
	//��CComboBox����Ŀѡ��ı�ʱ�����ű�ѡ����Ŀ
	int nSelTrack = m_ctlCombo.GetCurSel();
	m_CDAudio.SeekTo(nSelTrack+1,0,0,0);
}


