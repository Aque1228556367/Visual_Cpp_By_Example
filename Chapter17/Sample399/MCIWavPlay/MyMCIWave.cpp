// MCIWave.cpp: implementation of the CMyMCIWave class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "MCIWavPlay.h"
#include "MyMCIWave.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CMyMCIWave::CMyMCIWave()
{
	//����״ָ̬ʾ�����ĳ�ʼ��
	m_bPlaying = FALSE;
    m_bRecord = FALSE;
    m_bOpen = FALSE;
    m_wDeviceID = 0;
}

CMyMCIWave::~CMyMCIWave()
{
	CloseWave();//�ر�WAV�ļ�
}
DWORD CMyMCIWave::OpenWave(CString strFileName)//�򿪲����ļ�
{
	if (m_bOpen)//����ļ��Ѿ���
	{
		CloseWave();//�رո��ļ�
	}
	DWORD dwOpenFlag;//�򿪱��
	MCI_OPEN_PARMS mciOpenParam;//MCI_OPEN_PARMS�ṹ
	mciOpenParam.lpstrDeviceType = "WaveAudio";//MCI�豸����
	mciOpenParam.lpstrElementName = strFileName;//���ļ���
	//��ʼ��MCI�豸
	dwOpenFlag = mciSendCommand(NULL, MCI_OPEN, MCI_OPEN_ELEMENT|MCI_OPEN_TYPE, (DWORD)(LPVOID)&mciOpenParam);
	if (dwOpenFlag)//��ʼ��ʧ��
		return dwOpenFlag;//���ش������
	m_wDeviceID = mciOpenParam.wDeviceID;//�豸ID
	m_bOpen = TRUE;
	dwOpenFlag = 0;
	MCI_SET_PARMS mciSetParam;
	mciSetParam.dwTimeFormat = MCI_FORMAT_MILLISECONDS;//ʱ���������Ϊ����
	//�ı�ʱ���������
	dwOpenFlag = mciSendCommand(m_wDeviceID,MCI_SET,MCI_SET_TIME_FORMAT,(DWORD)(LPVOID)&mciSetParam);
	if (dwOpenFlag)//����ʧ��
		return dwOpenFlag;//���ش������
	return 0;
}

DWORD CMyMCIWave::PlayWave()//���Ų����ļ�
{
	MCI_PLAY_PARMS mciPlayParam;
	DWORD dwPlayFlag;
	dwPlayFlag = mciSendCommand(m_wDeviceID, MCI_PLAY, NULL, (DWORD)(LPVOID)&mciPlayParam);//��ʼ��������
	if (dwPlayFlag)//����ʧ��
		return dwPlayFlag;//���ش������
	else
	{
		m_bPlaying = TRUE;
		return 0;
	}
}
void CMyMCIWave::StopWave()//ֹͣ���Ų����ļ�
{
	mciSendCommand(m_wDeviceID, MCI_STOP, NULL, NULL);//ֹͣ����
}
DWORD CMyMCIWave::RecordWave()
{
	if (m_bOpen)//������ļ���
		CloseWave();//�ر��ļ�
	DWORD dwRecordFlag;
	MCI_OPEN_PARMS mciOpenParam;
	mciOpenParam.lpstrDeviceType = " waveAudio ";
	mciOpenParam.lpstrElementName = NULL;
	//��ʼ��MCI�豸
	dwRecordFlag = mciSendCommand(NULL, MCI_OPEN,MCI_OPEN_ELEMENT | MCI_OPEN_TYPE | MCI_WAIT, (DWORD)(LPVOID)&mciOpenParam);
	if (dwRecordFlag)//��ʼ��ʧ��
		return dwRecordFlag;//���ش������
	m_wDeviceID = mciOpenParam.wDeviceID;
	MCI_RECORD_PARMS mciRecordParam;
	//��ʼ��¼����
	dwRecordFlag = mciSendCommand(m_wDeviceID, MCI_RECORD,MCI_RECORD_OVERWRITE, (DWORD)(LPVOID)&mciRecordParam);
	if (dwRecordFlag)//��¼����ʧ��
		return dwRecordFlag;//���ش������
	m_bRecord = TRUE;
	m_bOpen = TRUE;
	return 0;
}
DWORD CMyMCIWave::SaveWave(CString strFileName)//���沨���ļ�
{
    if (m_bRecord)//����¼��
        return 0;//����
	StopWave();//ֹͣ¼��
	MCI_SAVE_PARMS mciSaveParam;
	mciSaveParam.lpfilename = strFileName;//���ñ�����ļ�
	//����WAV���ݵ��ļ�
	DWORD dwSaveFlag = mciSendCommand(m_wDeviceID, MCI_SAVE,MCI_SAVE_FILE | MCI_WAIT, (DWORD)(LPVOID)&mciSaveParam);
	if (dwSaveFlag)//����ʧ��
		return dwSaveFlag;//���ش������
	m_bRecord = FALSE;
	return 0;
}
DWORD CMyMCIWave::CloseWave()
{
	if (m_wDeviceID)//��MCI�豸�ڹ���
	{
		DWORD dwCloseFlag;
		mciSendCommand(m_wDeviceID, MCI_STOP, MCI_WAIT, NULL);//ֹͣ����
		dwCloseFlag = mciSendCommand(m_wDeviceID, MCI_CLOSE, NULL, NULL);//�ر��豸
		if (dwCloseFlag)
		{
			AfxMessageBox("�ر�ʱ���ִ���");
			return dwCloseFlag;
		}
	}
	//����״̬����
	m_bRecord = FALSE;
	m_bOpen = FALSE;
	m_bPlaying = FALSE;
	m_wDeviceID = NULL;
	return 0;
}
DWORD CMyMCIWave::GetSampleRate()//��ȡ������
{
	MCI_STATUS_PARMS mciStatusParam;
	mciStatusParam.dwItem = MCI_WAVE_STATUS_SAMPLESPERSEC;//����Ƶ��
	//MCI�豸��״̬��Ϣ������Ƶ�ʣ�
	DWORD dwStatusFlag = mciSendCommand(m_wDeviceID, MCI_STATUS,MCI_WAIT | MCI_STATUS_ITEM, (DWORD)(LPVOID)&mciStatusParam);
	if (dwStatusFlag)
		return dwStatusFlag;//���ش������
	else
		return mciStatusParam.dwReturn;//���ز���Ƶ��
}
DWORD CMyMCIWave::GetChannel()//��ȡ������
{
	MCI_STATUS_PARMS mciStatusParam;
	mciStatusParam.dwItem = MCI_WAVE_STATUS_CHANNELS;//������
	//MCI�豸��״̬��Ϣ����������
	DWORD dwStatusFlag = mciSendCommand(m_wDeviceID, MCI_STATUS,MCI_WAIT | MCI_STATUS_ITEM, (DWORD)(LPVOID)&mciStatusParam);
	if (dwStatusFlag)
		return dwStatusFlag;
	else
		return mciStatusParam.dwReturn;//����������
}
DWORD CMyMCIWave::GetBitLength()//��ȡ����λ��
{
	MCI_STATUS_PARMS mciStatusParam;
	mciStatusParam.dwItem = MCI_WAVE_STATUS_BITSPERSAMPLE;//����λ��
	//MCI�豸��״̬��Ϣ������λ����
	DWORD dwStatusFlag = mciSendCommand(m_wDeviceID, MCI_STATUS,MCI_WAIT|MCI_STATUS_ITEM, (DWORD)(LPVOID)&mciStatusParam);
	if (dwStatusFlag)
		return dwStatusFlag;
	else
		return mciStatusParam.dwReturn;//����λ��
}
DWORD CMyMCIWave::GetWaveLength()//��ȡ�����ļ���ʱ��
{
	MCI_STATUS_PARMS mciStatusParam;
	mciStatusParam.dwItem = MCI_STATUS_LENGTH;//��Ƶ����
	//����MCI�豸��״̬��Ϣ����Ƶ���ȣ�
	DWORD dwStatusFlag = mciSendCommand(m_wDeviceID, MCI_STATUS,MCI_WAIT | MCI_STATUS_ITEM, (DWORD)(LPVOID)&mciStatusParam);
	if (dwStatusFlag)
		return dwStatusFlag;
	else
		return mciStatusParam.dwReturn;//������Ƶ����
}