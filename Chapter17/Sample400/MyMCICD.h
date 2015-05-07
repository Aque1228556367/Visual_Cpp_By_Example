// CMyMCICD.h
#include	<Mmsystem.h>   
#pragma   comment(lib,   "Winmm.lib")   
class CMyMCICD
{
public:
	CMyMCICD();
	~CMyMCICD();
	BOOL OpenCD();//���豸
	void Close();//�ر��豸
	BOOL PlayCD();//����CD
	void Stop();//ֹͣ
	void Pause();//��ͣ
	void CloseDrive();//�رչ���
	void OpenDrive();//�򿪹���
	int GetTotalTracks();//�����Ŀ����
	int GetCurrentTrack();//��õ�ǰ���ŵ���Ŀ
	void GetTotalLength(int *pnMinutes, int *pnSeconds );//���������Ŀ���ܳ��ȣ�ʱ�䣩
	void GetTrackLength(int nTrack, int *pnMinutes, int *pnSeconds);//���һ����Ŀ�ĳ���
	int GetMinutes();//��õ�ǰ������Ŀǰ�Ѿ����ŵķ�����
	int GetSeconds();//��õ�ǰ������Ŀǰ�����ŵ�����
	int GetFrames();//���֡��
	BOOL IsDriveReady();//�жϹ������cd�Ƿ�����
	BOOL IsPlaying(BOOL *pbPaused);//�ж��Ƿ����ڲ���
	BOOL IsAudioTrack(int nTrack );//�ж���Ŀ�Ƿ�������
	BOOL SeekTo(int nTrack, int nMinute, int nSecond, int nFrame);//��Ծ��ĳ����Ŀ
	void SkipForward(int nSeconds);//��ǰ��Ծ����ʱ��
	void SkipBack(int nSeconds);//�����Ծ����ʱ��
private:
	BOOL m_bOpened, m_bPaused, m_bPlaying;//����״̬����
	WORD m_wDeviceID;//�����豸ID
};

