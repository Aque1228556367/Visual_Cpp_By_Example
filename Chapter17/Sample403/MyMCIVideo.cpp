// MyMCIVideo.cpp: implementation of the CMyMCIVideo class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "MCIDigitalVideoPlay.h"
#include "MyMCIVideo.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CMyMCIVideo::CMyMCIVideo()
{
	//��ʼ��״̬����
	m_bOpen = FALSE;
	m_bPause = FALSE;
	m_bPlaying = FALSE;
	m_wDeviceID = NULL;
}

CMyMCIVideo::~CMyMCIVideo()
{
	Close();    // �ر���Ƶ�豸
}
int CMyMCIVideo::OpenAvi(CString FileName, CWnd* pWnd, int left, int top, int width, int height)
{
	if (!m_bOpen)      // ���m_bOpen��FALSE��û�д��豸
	{
		//��ʼ�����ݳ�Ա
		m_bOpen = m_bPause = m_bPlaying = FALSE;
		m_wDeviceID = NULL;
		//�ж�������Ƶ�ļ��Ƿ����
		CFileStatus fileStatus;
		if (!CFile::GetStatus(FileName, fileStatus))
				 return 0;
		//���豸���������Ƶ�豸��ID��
		MCI_DGV_OPEN_PARMS mciOpenParms;
		mciOpenParms.lpstrDeviceType = "AviVideo";    //���ò����豸Ϊ��Ƶ�����豸
		mciOpenParms.lpstrElementName = (LPSTR)FileName.GetBuffer(0);  //�����ļ���
		mciOpenParms.wDeviceID = NULL;
		mciOpenParms.hWndParent = pWnd->m_hWnd;  //�ɲ�����Ƶ�ļ�����ָ��
		mciOpenParms.dwStyle = WS_CHILD|WS_VISIBLE;
		if (mciSendCommand(NULL, MCI_OPEN, MCI_WAIT|MCI_OPEN_TYPE|MCI_OPEN_ELEMENT|MCI_DGV_OPEN_PARENT|MCI_DGV_OPEN_WS, (DWORD)(LPVOID)&mciOpenParms))
		{
			return 0;
		}
		m_wDeviceID = mciOpenParms.wDeviceID;
		m_bOpen = TRUE;    //��ʾ��Ƶ�豸�Ѿ�����ȷ���
		// ����Ƶ�豸�Ĳ��Ž��г�ʼ��
		MCI_DGV_SET_PARMS mciSetParms;
		mciSetParms.dwTimeFormat = MCI_FORMAT_FRAMES;// ������Ƶ�ļ����ŵ�λΪ֡
		if (mciSendCommand(m_wDeviceID, MCI_SET, MCI_SET_TIME_FORMAT,(DWORD)(LPVOID)& mciSetParms))
		{
			Close();
			return 0;    //��ʾ���豸ʱ����
		}
		// ����Ƶ�ļ���ǰ��λ����Ϊ��ʼλ��
		mciSendCommand(m_wDeviceID, MCI_SEEK, MCI_SEEK_TO_START, NULL);
		// �����Ż�������pWnd����֮��
		MCI_DGV_PUT_PARMS mciPutParms;
		mciPutParms.rc.left = left;
		mciPutParms.rc.top = top;        //��Ƶ���Ŵ������Ͻǵ�����
		mciPutParms.rc.right = left + width;
		mciPutParms.rc.bottom = top + height;
		if (mciSendCommand(m_wDeviceID, MCI_PUT, MCI_WAIT |MCI_DGV_PUT_CLIENT | MCI_DGV_PUT_WINDOW | MCI_DGV_RECT, (DWORD)(LPVOID)& mciPutParms))
		{
			Close();
			return 0;
		}
	}
	return 1;
}
int CMyMCIVideo::PlayAvi(int Loop, int FullScreen)//����
{
	if (m_bOpen)
	{
		// �������Ƶ��β�������¿�ʼ
		if (GetFrame()>=GetFrames())
			mciSendCommand(m_wDeviceID, MCI_SEEK, MCI_SEEK_TO_START, NULL);//��λ����ʼλ��
		MCI_DGV_PLAY_PARMS mciPlayParms;
		mciPlayParms.dwCallback = NULL;
		mciPlayParms.dwFrom = GetFrame();    // �õ���ǰ����Ƶλ��
		DWORD dwFlags = MCI_FROM;
		if (Loop)
			dwFlags |=MCI_DGV_PLAY_REPEAT;    //ѭ�����ű�־
		if (FullScreen)
			dwFlags |=MCI_MCIAVI_PLAY_FULLSCREEN;    //ȫ��Ļ���ű�־
		if (mciSendCommand(m_wDeviceID,MCI_PLAY,dwFlags,(DWORD)(LPVOID)&mciPlayParms))//��ʼ����
		{
			return 0;
		}
		//����״̬������ֵ
		m_bPause = FALSE;
		m_bPlaying = TRUE;
		return 1;
	}
	return 1;
}
void CMyMCIVideo::Close()
{
	if (m_bOpen)
	{
		mciSendCommand(m_wDeviceID, MCI_STOP, NULL, NULL);    // ����ֹͣ��Ϣ
		mciSendCommand(m_wDeviceID, MCI_CLOSE, NULL, NULL);  // ���͹ر���Ϣ
		m_bOpen = m_bPause = m_bPlaying = FALSE;
	    m_wDeviceID = NULL;
	}
}
void CMyMCIVideo::Stop()
{
	if (m_bOpen && m_bPlaying)
	{
		mciSendCommand(m_wDeviceID, MCI_STOP, NULL, NULL);
		mciSendCommand(m_wDeviceID, MCI_SEEK, MCI_SEEK_TO_START, NULL);
		m_bPause = TRUE;
	    m_bPlaying = FALSE;
	}
}
void CMyMCIVideo::Pause()
{
	if (m_bOpen)
	{
		MCI_DGV_PAUSE_PARMS mciPauseParms;
		if (mciSendCommand(m_wDeviceID, MCI_PAUSE, NULL,
		(DWORD)(LPVOID) & mciPauseParms))
			return;
		m_bPause = TRUE;
	}
}
void CMyMCIVideo::Forward(int nFrames)
{
	if (m_bOpen)
	{
		if (m_bPlaying && !m_bPause)
			Pause();
		MCI_DGV_STEP_PARMS mciStepParms;
		mciStepParms.dwFrames = nFrames;
		mciSendCommand(m_wDeviceID, MCI_STEP, MCI_DGV_STEP_FRAMES, 
		(DWORD)(LPVOID)&mciStepParms);
	}
}
void CMyMCIVideo::Backward(int nFrames)
{
	if (m_bOpen)
	{
		if (m_bPlaying && !m_bPause)
			Pause();
		MCI_DGV_STEP_PARMS mciStepParms;
		mciStepParms.dwFrames = nFrames;
		mciSendCommand(m_wDeviceID, MCI_STEP, MCI_DGV_STEP_REVERSE | 
		MCI_DGV_STEP_FRAMES, (DWORD)(LPVOID)&mciStepParms);
	}
}
void CMyMCIVideo::SetSpeed(int nSpeed)
{
	if (m_bOpen)
	{
		MCI_DGV_SET_PARMS mciSetParms;//�����ṹ
		mciSetParms.dwSpeed = nSpeed;
		//����MCI_SET������ò����ٶ�
		mciSendCommand(m_wDeviceID, MCI_SET, MCI_WAIT | MCI_DGV_SET_SPEED,(DWORD)(LPVOID)&mciSetParms);
	}
}
BOOL CMyMCIVideo::SeekTo(int nFrame)
{
	if (m_bOpen)
	{
		MCI_SEEK_PARMS mciSeekParms;
		mciSeekParms.dwTo = nFrame;
		if (m_bPlaying && !m_bPause)
		    mciSendCommand(m_wDeviceID, MCI_PAUSE, 0, NULL);
	    if (mciSendCommand(m_wDeviceID, MCI_SEEK, MCI_TO | MCI_WAIT,
	      (DWORD)(LPVOID)&mciSeekParms))
        	return FALSE;
		if (m_bPlaying && m_bPause)
			PlayAvi();
		return TRUE;
	}
	return FALSE;
}
int CMyMCIVideo::GetFrames()//��ȡ��Ƶ����֡��
{
	if (m_bOpen)
	{
		MCI_DGV_STATUS_PARMS mciStatusParms;
	    mciStatusParms.dwItem = MCI_STATUS_LENGTH;
		if (mciSendCommand(m_wDeviceID, MCI_STATUS, MCI_WAIT|
		MCI_STATUS_ITEM, (DWORD)(LPVOID)&mciStatusParms))
			return 0;
		return (int)mciStatusParms.dwReturn;
	}
	return 0;
}
int CMyMCIVideo::GetFrame()
{
	if (m_bOpen)
	{
		MCI_DGV_STATUS_PARMS mciStatusParms;
		mciStatusParms.dwItem = MCI_STATUS_POSITION;
		if (mciSendCommand(m_wDeviceID, MCI_STATUS, MCI_WAIT |
		MCI_STATUS_ITEM, (DWORD)(LPVOID)&mciStatusParms))
			return -1;
		return (int)mciStatusParms.dwReturn;
	}
	return -1;
}
int CMyMCIVideo::GetSpeed()
{
	if (m_bOpen)
	{
		MCI_DGV_STATUS_PARMS mciStatusParms;
		mciStatusParms.dwItem = MCI_DGV_STATUS_SPEED;
		if (mciSendCommand(m_wDeviceID, MCI_STATUS, MCI_WAIT |
		MCI_STATUS_ITEM, (DWORD)(LPVOID)&mciStatusParms))
			return -1;
		return (int)mciStatusParms.dwReturn;
	}
	return -1;
}
BOOL CMyMCIVideo::IsPlaying()
{
	if (m_bOpen)
	{
		MCI_DGV_STATUS_PARMS mciStatusParms;
		mciStatusParms.dwItem = MCI_STATUS_MODE;
		if (mciSendCommand(m_wDeviceID, MCI_STATUS, MCI_WAIT |
			MCI_STATUS_ITEM, (DWORD)(LPVOID)&mciStatusParms))
			return FALSE;
		if (mciStatusParms.dwReturn == MCI_MODE_PLAY)
		{
			m_bPlaying = TRUE;
			m_bPause = FALSE;
			return TRUE;
		}
		else if(mciStatusParms.dwReturn == MCI_MODE_PAUSE)
		{
			m_bPlaying = TRUE;
			m_bPause = TRUE;
			return TRUE;
		}
		else
		{
			m_bPlaying = FALSE;
			m_bPause = FALSE;
			return FALSE;
		}
	}
	return FALSE;
}
int CMyMCIVideo::GetWidth()
{
	if (m_bOpen)
	{
		MCI_DGV_WHERE_PARMS mciWhereParms;
		if (mciSendCommand(m_wDeviceID, MCI_WHERE,
			MCI_DGV_WHERE_SOURCE, (DWORD)(LPVOID)&mciWhereParms))
			return 0;
		return (int) mciWhereParms.rc.right;
	}
	return 0;
}
int CMyMCIVideo::GetHeight()
{
	if (m_bOpen)
	{
		MCI_DGV_WHERE_PARMS mciWhereParms;
		if (mciSendCommand(m_wDeviceID, MCI_WHERE,
		MCI_DGV_WHERE_SOURCE, (DWORD)(LPVOID)&mciWhereParms))
			return 0;
		return (int) mciWhereParms.rc.bottom;
	}
	return 0;
}
BOOL CMyMCIVideo::GetPause()
{
	if (m_bOpen)
	{
		MCI_DGV_STATUS_PARMS mciStatusParms;
		mciStatusParms.dwItem = MCI_STATUS_MODE;
		if (mciSendCommand(m_wDeviceID, MCI_STATUS, MCI_WAIT |
			MCI_STATUS_ITEM, (DWORD)(LPVOID)&mciStatusParms))
			return FALSE;
		if(mciStatusParms.dwReturn == MCI_MODE_PAUSE)
		{
			return TRUE;
		}
		else
		{
			return FALSE;
		}
	}
	else
	{
		return FALSE;
	}
}
