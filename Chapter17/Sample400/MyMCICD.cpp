// CDAudio.cpp

#include "stdafx.h"

#include "MyMCICD.h"

CMyMCICD::CMyMCICD()
{

	m_bOpened = m_bPaused = m_bPlaying = FALSE;
	m_wDeviceID = 0;

}

CMyMCICD::~CMyMCICD()
{

	Close();

}

//���豸
BOOL CMyMCICD::OpenCD()
{
	if( m_bOpened )
		return( TRUE );
	m_bPaused = m_bPlaying = FALSE;
	m_wDeviceID = 0;
	//���ʹ��豸����
	MCI_OPEN_PARMS OpenParms;
	OpenParms.lpstrDeviceType = (LPCSTR) MCI_DEVTYPE_CD_AUDIO;//�豸����ΪCD
	OpenParms.wDeviceID = 0;
	if(mciSendCommand(NULL,MCI_OPEN,MCI_WAIT|MCI_OPEN_TYPE|MCI_OPEN_TYPE_ID|MCI_OPEN_SHAREABLE,(DWORD)(LPVOID)&OpenParms))
		return( FALSE );
	m_wDeviceID = OpenParms.wDeviceID;//��ȡ�豸ID
	m_bOpened = TRUE;
	MCI_SET_PARMS SetParms;
	SetParms.dwTimeFormat=MCI_FORMAT_TMSF;//����ʱ���ʽΪ�����/��/��/֡������ʽ
	if(mciSendCommand(m_wDeviceID,MCI_SET,MCI_WAIT|MCI_SET_TIME_FORMAT,(DWORD)(LPVOID)&SetParms))
	{
		Close();
		return(FALSE);
	}
	mciSendCommand( m_wDeviceID, MCI_SEEK, MCI_SEEK_TO_START, NULL );//��λ��CD��ʼ��
	return( TRUE );
}
//�ر��豸
void CMyMCICD::Close()
{

	if( !m_bOpened )
		return;

	if( m_bPlaying || m_bPaused )
		mciSendCommand( m_wDeviceID, MCI_STOP, NULL, NULL );

	mciSendCommand( m_wDeviceID, MCI_CLOSE, MCI_WAIT, NULL );

	m_bOpened = m_bPaused = m_bPlaying = FALSE;
	m_wDeviceID = 0;

}
//����
BOOL CMyMCICD::PlayCD ()
{

	if( !OpenCD() )
		return( FALSE );
	if( !IsAudioTrack( GetCurrentTrack() ) )
		return( FALSE );
	MCI_PLAY_PARMS PlayParms;
	PlayParms.dwCallback = NULL;
	PlayParms.dwFrom = MCI_MAKE_TMSF( GetCurrentTrack(), GetMinutes(), GetSeconds(), GetFrames() );
	if( mciSendCommand( m_wDeviceID, MCI_PLAY, MCI_FROM, (DWORD)(LPVOID) &PlayParms ) )
		return( FALSE );
	m_bPaused = FALSE;
	m_bPlaying = TRUE;
	return( TRUE );

}
//ֹͣ
void CMyMCICD::Stop()
{

	if( !m_bOpened || !m_bPlaying )
		return;

	mciSendCommand( m_wDeviceID, MCI_STOP, MCI_WAIT, NULL );
	mciSendCommand( m_wDeviceID, MCI_SEEK, MCI_SEEK_TO_START, NULL );
	m_bPlaying = FALSE;
	m_bPaused = FALSE;

}
//��ͣ
void CMyMCICD::Pause( )
{

	if( !m_bOpened || !m_bPlaying )
		return;

	MCI_PLAY_PARMS PlayParms;

	if( mciSendCommand( m_wDeviceID, MCI_PAUSE, 0, (DWORD)(LPVOID) &PlayParms ) )
		return;

	m_bPaused = TRUE;

}
//�����Ŀ����
int CMyMCICD::GetTotalTracks()
{

	if( !m_bOpened )
		return( -1 );

	MCI_STATUS_PARMS StatusParms;
	StatusParms.dwItem = MCI_STATUS_NUMBER_OF_TRACKS;

	if( mciSendCommand( m_wDeviceID, MCI_STATUS, MCI_STATUS_ITEM, (DWORD)(LPVOID) &StatusParms ) )
		return( -1 );

	return( (int) StatusParms.dwReturn );

}
//���������Ŀ���ܳ��ȣ�ʱ�䣩
void CMyMCICD::GetTotalLength( int *pnMinutes, int *pnSeconds )
{

	*pnMinutes = -1;
	*pnSeconds = -1;

	if( !m_bOpened )
		return;

	MCI_STATUS_PARMS StatusParms;
	StatusParms.dwItem = MCI_STATUS_LENGTH;

	if( mciSendCommand( m_wDeviceID, MCI_STATUS, MCI_WAIT | MCI_STATUS_ITEM, (DWORD)(LPVOID) &StatusParms ) )
		return;

	*pnMinutes = MCI_MSF_MINUTE( StatusParms.dwReturn );
	*pnSeconds = MCI_MSF_SECOND( StatusParms.dwReturn );

}
//���һ����Ŀ�ĳ���
void CMyMCICD::GetTrackLength( int nTrack, int *pnMinutes, int *pnSeconds )
{
	*pnMinutes = -1;
	*pnSeconds = -1;
	if( !m_bOpened )
		return;
	MCI_STATUS_PARMS StatusParms;
	StatusParms.dwItem = MCI_STATUS_LENGTH;
	StatusParms.dwTrack = (DWORD) nTrack;
	if( mciSendCommand( m_wDeviceID, MCI_STATUS, MCI_WAIT | MCI_STATUS_ITEM | MCI_TRACK, (DWORD)(LPVOID) &StatusParms ) )
			return;
	*pnMinutes = MCI_MSF_MINUTE( StatusParms.dwReturn );
	*pnSeconds = MCI_MSF_SECOND( StatusParms.dwReturn );

}
//��õ�ǰ���ŵ���Ŀ
int CMyMCICD::GetCurrentTrack( )
{

	if( !m_bOpened )
		return( -1 );

	MCI_STATUS_PARMS StatusParms;
	StatusParms.dwItem = MCI_STATUS_POSITION;

	if( mciSendCommand( m_wDeviceID, MCI_STATUS, MCI_WAIT | MCI_STATUS_ITEM, (DWORD)(LPVOID) &StatusParms ) )
		return( -1 );

	return( MCI_TMSF_TRACK( StatusParms.dwReturn ) );

}
//��õ�ǰ������Ŀǰ�Ѿ����ŵķ�����
int CMyMCICD::GetMinutes( )
{
	if( !m_bOpened )
		return( -1 );
	MCI_STATUS_PARMS StatusParms;
	StatusParms.dwItem = MCI_STATUS_POSITION;
	if( mciSendCommand( m_wDeviceID, MCI_STATUS, MCI_WAIT | MCI_STATUS_ITEM, (DWORD)(LPVOID) &StatusParms ) )
		return( -1 );
	return(MCI_TMSF_MINUTE(StatusParms.dwReturn));
}
//��õ�ǰ������Ŀǰ�����ŵ�����
int CMyMCICD::GetSeconds( )
{

	if( !m_bOpened )
		return( -1 );

	MCI_STATUS_PARMS StatusParms;
	StatusParms.dwItem = MCI_STATUS_POSITION;

	if( mciSendCommand( m_wDeviceID, MCI_STATUS, MCI_WAIT | MCI_STATUS_ITEM, (DWORD)(LPVOID) &StatusParms ) )
		return( -1 );

	return( MCI_TMSF_SECOND( StatusParms.dwReturn ) );

}
//���֡��
int CMyMCICD::GetFrames()
{

	if( !m_bOpened )
		return( -1 );

	MCI_STATUS_PARMS StatusParms;
	StatusParms.dwItem = MCI_STATUS_POSITION;

	if( mciSendCommand( m_wDeviceID, MCI_STATUS, MCI_WAIT | MCI_STATUS_ITEM, (DWORD)(LPVOID) &StatusParms ) )
		return( -1 );

	return( MCI_TMSF_FRAME( StatusParms.dwReturn ) );

}
//�жϹ������cd�Ƿ�����
BOOL CMyMCICD::IsDriveReady()
{

	if( !m_bOpened )
		return( FALSE );

	MCI_STATUS_PARMS StatusParms;
	StatusParms.dwItem = MCI_STATUS_MODE;
	if( mciSendCommand( m_wDeviceID, MCI_STATUS, MCI_STATUS_ITEM, (DWORD)(LPVOID) &StatusParms ) )
		return( FALSE );
	if( StatusParms.dwReturn == MCI_MODE_NOT_READY || StatusParms.dwReturn == MCI_MODE_OPEN )
		return( FALSE );
	StatusParms.dwItem = MCI_STATUS_MEDIA_PRESENT;
	if( mciSendCommand( m_wDeviceID, MCI_STATUS, MCI_STATUS_ITEM, (DWORD)(LPVOID) &StatusParms ) )
		return( FALSE );
	return( (BOOL) StatusParms.dwReturn );

}
//�ж���Ŀ�Ƿ�������
BOOL CMyMCICD::IsAudioTrack( int nTrack )
{
	if(!m_bOpened)
		return(FALSE);
	MCI_STATUS_PARMS StatusParms;
	StatusParms.dwItem = MCI_CDA_STATUS_TYPE_TRACK;
	StatusParms.dwTrack = nTrack;
	if(mciSendCommand(m_wDeviceID,MCI_STATUS,MCI_STATUS_ITEM|MCI_TRACK,(DWORD)(LPVOID)&StatusParms))
		return(FALSE);
	if(StatusParms.dwReturn == MCI_CDA_TRACK_AUDIO)
		return(TRUE);
	return(FALSE);

}
//�ж��Ƿ����ڲ���
BOOL CMyMCICD::IsPlaying( BOOL *pbPaused )
{

	*pbPaused = m_bPaused;

	return( m_bPlaying );

}
//��Ծ��ĳ����Ŀ��ǡ���ط�
BOOL CMyMCICD::SeekTo( int nTrack, int nMinute, int nSecond, int nFrame )
{

	if( !m_bOpened )
		return( FALSE );
	if( m_bPlaying && !m_bPaused )
		mciSendCommand( m_wDeviceID, MCI_PAUSE, 0, NULL );
	MCI_SEEK_PARMS SeekParms;
	SeekParms.dwTo = MCI_MAKE_TMSF( nTrack, nMinute, nSecond, nFrame );
	if( mciSendCommand( m_wDeviceID, MCI_SEEK, MCI_TO | MCI_WAIT, (DWORD)(LPVOID) &SeekParms ) )
		return( FALSE );

	if( m_bPlaying && !m_bPaused )
		PlayCD();

	return( TRUE );

}
//��ǰ��Ծ����ʱ��
void CMyMCICD::SkipForward( int nSeconds )
{

	if( !m_bOpened )
		return;
	//����ʱ���ʽ
	MCI_SET_PARMS SetParms;
	SetParms.dwTimeFormat = MCI_FORMAT_MILLISECONDS;//ʱ���ʽΪ����
	mciSendCommand( m_wDeviceID, MCI_SET, MCI_WAIT | MCI_SET_TIME_FORMAT, (DWORD)(LPVOID) &SetParms );
	//��õ�ǰ����λ�ã�����Ϊ��λ��
	MCI_STATUS_PARMS StatusParms;
	DWORD dwPos;
	StatusParms.dwItem = MCI_STATUS_POSITION;
	mciSendCommand( m_wDeviceID, MCI_STATUS, MCI_WAIT | MCI_STATUS_ITEM, (DWORD)(LPVOID) &StatusParms );
	//��ǰʱ��������Ծʱ�伴����λ��ʱ��
	dwPos = StatusParms.dwReturn;
	dwPos += (DWORD) nSeconds * 1000;
	MCI_SEEK_PARMS SeekParms;
	SeekParms.dwTo = dwPos;
	if( m_bPlaying && !m_bPaused )
		mciSendCommand( m_wDeviceID, MCI_PAUSE, 0, NULL );//��ͣ����
	//��λ����λ��
	mciSendCommand( m_wDeviceID, MCI_SEEK, MCI_TO | MCI_WAIT, (DWORD)(LPVOID) &SeekParms );
	SetParms.dwTimeFormat = MCI_FORMAT_TMSF;//�ָ�ʱ���ʽ
	mciSendCommand( m_wDeviceID, MCI_SET, MCI_WAIT | MCI_SET_TIME_FORMAT, (DWORD)(LPVOID) &SetParms );

	if( m_bPlaying && !m_bPaused )
		PlayCD();//����λ�ò���
}
//�����Ծ����ʱ��
void CMyMCICD::SkipBack( int nSeconds )
{

	if( !m_bOpened )
		return;

	MCI_SET_PARMS SetParms;
	SetParms.dwTimeFormat = MCI_FORMAT_MILLISECONDS;
	mciSendCommand( m_wDeviceID, MCI_SET, MCI_WAIT | MCI_SET_TIME_FORMAT, (DWORD)(LPVOID) &SetParms );

	MCI_STATUS_PARMS StatusParms;
	DWORD dwPos;
	StatusParms.dwItem = MCI_STATUS_POSITION;

	mciSendCommand( m_wDeviceID, MCI_STATUS, MCI_WAIT | MCI_STATUS_ITEM, (DWORD)(LPVOID) &StatusParms );

	dwPos = StatusParms.dwReturn;
	dwPos -= (DWORD) nSeconds * 1000;
	MCI_SEEK_PARMS SeekParms;
	SeekParms.dwTo = dwPos;

	if( m_bPlaying && !m_bPaused )
		mciSendCommand( m_wDeviceID, MCI_PAUSE, 0, NULL );

	mciSendCommand( m_wDeviceID, MCI_SEEK, MCI_TO | MCI_WAIT, (DWORD)(LPVOID) &SeekParms );
	SetParms.dwTimeFormat = MCI_FORMAT_TMSF;
	mciSendCommand( m_wDeviceID, MCI_SET, MCI_WAIT | MCI_SET_TIME_FORMAT, (DWORD)(LPVOID) &SetParms );

	if( m_bPlaying && !m_bPaused )
		PlayCD();

}
//�򿪹���
void CMyMCICD::OpenDrive( void )
{
	if( m_bOpened )
	{
		Stop();//ֹͣ�豸
		mciSendCommand(m_wDeviceID, MCI_SET, MCI_SET_DOOR_OPEN, NULL );
	}
}
//�رչ���
void CMyMCICD::CloseDrive( void )
{
	if( m_bOpened )
	{
		mciSendCommand(m_wDeviceID, MCI_SET, MCI_SET_DOOR_CLOSED, NULL );
		Stop();//ֹͣ�豸
	}	
}

