// WavOutPlayDlg.cpp : implementation file
//

#include "stdafx.h"
#include "WavOutPlay.h"
#include "WavOutPlayDlg.h"
#include <Mmsystem.h>   
#pragma   comment(lib,   "Winmm.lib")   

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
// CWavOutPlayDlg dialog

CWavOutPlayDlg::CWavOutPlayDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CWavOutPlayDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CWavOutPlayDlg)
	m_wavfile = _T("");
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CWavOutPlayDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CWavOutPlayDlg)
	DDX_Text(pDX, IDC_EDIT1, m_wavfile);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CWavOutPlayDlg, CDialog)
	//{{AFX_MSG_MAP(CWavOutPlayDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_FILE, OnFile)
	ON_BN_CLICKED(IDC_PLAY, OnPlay)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CWavOutPlayDlg message handlers

BOOL CWavOutPlayDlg::OnInitDialog()
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
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CWavOutPlayDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CWavOutPlayDlg::OnPaint() 
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
HCURSOR CWavOutPlayDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CWavOutPlayDlg::OnFile() 
{
	// TODO: Add your control notification handler code here
	CString szFilters="WAV Files (*.wav)|*.wav|All Files (*.*)|*.*||";		//�����ļ�������
   //�������ļ��Ի������Ĭ�ϵ��ļ���չ��Ϊ ".wav".
   CFileDialog fileDlg (TRUE, "WAV", "*.wav",OFN_FILEMUSTEXIST| OFN_HIDEREADONLY, szFilters, this);
   //����DoModal()������ʾ���ļ��Ի���
   if( fileDlg.DoModal ()==IDOK )
   {
      m_wavfile = fileDlg.GetPathName();//��ȡ�ļ�·��
	  UpdateData(false);//�༭����ʾ
   }
}

void CWavOutPlayDlg::OnPlay() 
{
// TODO: Add your control notification handler code here
	UpdateData(true);
	if(m_wavfile.IsEmpty())
	{
		AfxMessageBox("��ѡ��Ҫ���ŵĲ����ļ���");
		 return;
	}
	HMMIO m_hmmio;	//��Ƶ�ļ����
	DWORD           WaveLong;       
	DWORD           dwFmtSize; //fmt���ݴ�С          
	DWORD           dwDataOffset;//ƫ�Ƶ�ַ           
	DWORD           dwDataSize; //�����С  
	MMCKINFO     mmckinfoParent; //����ṹ          
	MMCKINFO     mmckinfoSubChunk;//�ӿ�ṹ        
	WAVEFORMATEX     *lpFormat; //���νṹ                     
	LONG SoundOffset=0;  //��������ƫ�Ƶ�ַ     
	LONG SoundLong=0;    //�������ݵĴ�С
	HPSTR m_lpData;//��Ƶ����
	HWAVEOUT m_hWaveOut;//HWAVEOUT�ṹ
	//�򿪲����ļ�
	m_hmmio = mmioOpen((LPSTR)(LPCTSTR)m_wavfile,NULL,MMIO_READ);       
	if(!m_hmmio)           
	{             
		mmioClose(m_hmmio,MMIO_FHOPEN); //�ر��ļ�
		return;           
	}           
	//�����ļ��Ƿ�ΪWAV�ļ�           
	mmckinfoParent.fccType =  mmioFOURCC('W','A','V','E');           
	if(mmioDescend(m_hmmio,(LPMMCKINFO)&mmckinfoParent,NULL,MMIO_FINDRIFF))           
	{           
		//����WAV�ļ�,�ر��ļ����˳�
		AfxMessageBox("���ļ�����Wav�ļ���");
		mmioClose(m_hmmio,MMIO_FHOPEN);           
		return;           
	}           
	//����'fmt'��        
	mmckinfoSubChunk.ckid=mmioFOURCC('f','m','t',' ');           
	if(mmioDescend(m_hmmio,&mmckinfoSubChunk,&mmckinfoParent,MMIO_FINDCHUNK))           
	{           
		//�Ҳ���fmt��,�ر��ļ����˳�      
		mmioClose(m_hmmio,MMIO_FHOPEN);       
		return;           
	}             
	//��ȡfmt��Ĵ�С�������ڴ�         
	dwFmtSize= mmckinfoSubChunk.cksize;         
	HLOCAL m_hFormat=LocalAlloc(LMEM_MOVEABLE,LOWORD(dwFmtSize));           
	if(!m_hFormat)      //�����ڴ�ʧ��,�ر��ļ����˳�      
	{             
		mmioClose(m_hmmio,MMIO_FHOPEN);       
		return;           
	}           
	//����fmt���ڴ�  
	lpFormat = (WAVEFORMATEX*)LocalLock(m_hFormat);           
	if(!lpFormat)        //�����ڴ�ʧ��,�ر��ļ����˳�     
	{           
		mmioClose(m_hmmio,MMIO_FHOPEN);       
		LocalUnlock(m_hFormat);           
		LocalFree(m_hFormat);       
		return;           
	}           
	//�������ļ���Fmt�����ݶ���lpFormat 
	if((unsigned long)mmioRead(m_hmmio,(HPSTR)lpFormat,dwFmtSize)!= dwFmtSize)           
	{           
		//������ʧ��,�ر��ļ����˳�       
		mmioClose(m_hmmio,MMIO_FHOPEN);       
		LocalUnlock(m_hFormat);           
		LocalFree(m_hFormat);       
		return;           
	}            
	//�뿪'fmt'��           
	mmioAscend(m_hmmio,&mmckinfoSubChunk,0);            
	//����'data'��         
	mmckinfoSubChunk.ckid   =   mmioFOURCC('d','a','t','a');           
	if(mmioDescend(m_hmmio,&mmckinfoSubChunk,&mmckinfoParent,MMIO_FINDCHUNK))           
	{           
		//�����ҵ�data��, �ر��ļ����˳�         
		mmioClose(m_hmmio,MMIO_FHOPEN);       
		LocalUnlock(m_hFormat);           
		LocalFree(m_hFormat);       
		return;           
	}              
	//��ȡ'data'��Ĵ�С��ƫ�Ƶ�ַ           
	dwDataSize =   mmckinfoSubChunk.cksize;           
	dwDataOffset  =   mmckinfoSubChunk.dwDataOffset;           
	if(dwDataSize== 0L)           
	{           
		//���data����û������,�ر��ļ����˳�      
		mmioClose(m_hmmio,MMIO_FHOPEN);       
		LocalUnlock(m_hFormat);           
		LocalFree(m_hFormat);       
		return;           
	}           
	//Ϊ��Ƶ���ݷ����ڴ�
	m_lpData = new  char[dwDataSize];         
	if(!m_lpData)//����ʧ��           
	{               
		mmioClose(m_hmmio,MMIO_FHOPEN);       
		LocalUnlock(m_hFormat);           
		LocalFree(m_hFormat);           
		if(m_lpData!= NULL)       
		delete[] m_lpData;       
		return;           
	}             
	//�������ļ���λ���������ݴ�
	SoundOffset =   dwDataOffset;   
	if(mmioSeek(m_hmmio,SoundOffset,SEEK_SET) < 0 )           
	{           
		//��λʧ��,�ر��ļ����˳�       
		mmioClose(m_hmmio,MMIO_FHOPEN);       
		LocalUnlock(m_hFormat);           
		LocalFree(m_hFormat);           
		delete[]  m_lpData; 
		return;             
	}           
	//��ȡ������������data  
	SoundLong = dwDataSize;   
	WaveLong=mmioRead(m_hmmio,m_lpData,SoundLong);           
	if(WaveLong <0)           
	{           
		//��ȡdata����ʧ��,�ر��ļ����˳�       
		mmioClose(m_hmmio,MMIO_FHOPEN);       
		LocalUnlock(m_hFormat);           
		LocalFree(m_hFormat);           
		delete[]  m_lpData;    
		return;           
	}       
	//�����Ƶ�豸
	if(waveOutGetNumDevs()==0)
	{
		AfxMessageBox("û�п��õ���Ƶ�豸!");
		return;
	} 

	//�����Ƶ����豸�Ƿ��ܲ���ָ������Ƶ�ļ�           
	if(waveOutOpen (&m_hWaveOut,0,lpFormat,NULL,NULL,CALLBACK_NULL) !=  MMSYSERR_NOERROR)           
	{               
		//������ܲ���, �ر��ļ����ͷ��ڴ沢�˳�    
		mmioClose(m_hmmio,MMIO_FHOPEN);       
		waveOutReset(m_hWaveOut);           
		waveOutClose(m_hWaveOut);           
		LocalUnlock(m_hFormat);           
		LocalFree(m_hFormat);           
		delete [] m_lpData;       
		return;           
	}           
	//׼�������ŵ�����  
	 WAVEHDR m_pWaveOutHdr;
	m_pWaveOutHdr.lpData  =   (HPSTR)m_lpData;//����           
	m_pWaveOutHdr.dwBufferLength =   WaveLong;  //����         
	m_pWaveOutHdr.dwFlags= 0;    
	m_pWaveOutHdr.dwFlags= WHDR_BEGINLOOP|WHDR_ENDLOOP   ;       
	m_pWaveOutHdr.dwLoops= 1;   //ѭ������ 
	//׼��WAV���� 
	if(waveOutPrepareHeader(m_hWaveOut,&m_pWaveOutHdr,sizeof(WAVEHDR)) == MMSYSERR_INVALHANDLE)           
	{           
		//�������WAV�����ڴ�ʧ��, �ر��ļ����ͷ��ڴ沢�˳�      
		mmioClose(m_hmmio,MMIO_FHOPEN);       
		waveOutReset(m_hWaveOut);           
		waveOutClose(m_hWaveOut);           
		LocalUnlock(m_hFormat);           
		LocalFree(m_hFormat);       
		return;           
	}
	//������Ƶ�����ļ�           
	if(waveOutWrite(m_hWaveOut,&m_pWaveOutHdr,sizeof(WAVEHDR))!=0)           
	{           
		//�������ʧ��, �ر��ļ����ͷ��ڴ沢�˳�     
		mmioClose(m_hmmio,MMIO_FHOPEN);       
		waveOutReset(m_hWaveOut);           
		waveOutClose(m_hWaveOut);           
		LocalUnlock(m_hFormat);           
		LocalFree(m_hFormat); 
		return;           
	} 

}
