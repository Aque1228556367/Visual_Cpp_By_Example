// MCIWave.h: interface for the CMCIWave class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MCIWAVE_H__4D73F398_C689_46D2_AD2A_446EC8C3137F__INCLUDED_)
#define AFX_MCIWAVE_H__4D73F398_C689_46D2_AD2A_446EC8C3137F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include	<Mmsystem.h>   
#pragma   comment(lib,   "Winmm.lib")   
class CMyMCIWave  
{
public:
	CMyMCIWave();//���캯��
	virtual ~CMyMCIWave();//��������
	DWORD OpenWave(CString strFileName);                  //���ļ�
	DWORD CloseWave();                  //�ر��ļ�
	DWORD PlayWave();                   //����
	void  StopWave();                   //ֹͣ����
	DWORD RecordWave();                 //¼��
	DWORD SaveWave(CString strFileName);  //����
	DWORD  GetBitLength();          //�õ�λ��
	DWORD GetSampleRate();          //�õ�������
	DWORD  GetChannel();             //�õ���ǰ����
	DWORD GetWaveLength();         //�õ���Ƶ����
public:
	BOOL m_bPlaying;               //�Ƿ����ڲ���
	BOOL m_bRecord;                //�Ƿ���¼��
	BOOL m_bOpen;                 //�ļ��Ƿ��
	WORD m_wDeviceID;            //�����豸ID
};

#endif // !defined(AFX_MCIWAVE_H__4D73F398_C689_46D2_AD2A_446EC8C3137F__INCLUDED_)
