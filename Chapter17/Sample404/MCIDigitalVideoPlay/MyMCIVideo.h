// MyMCIVideo.h: interface for the CMyMCIVideo class.
#include		<Mmsystem.h>   
#pragma   comment(lib,   "Winmm.lib")   
#include "Digitalv.h"
#include "mciavi.h"
class CMyMCIVideo  
{
public:
	CMyMCIVideo();
	virtual ~CMyMCIVideo();
	int OpenAvi(CString ,CWnd *pWnd, int left=0, int top=0, int width=20,int height=20);// ��pWnd�����д���Ƶ�豸
	int PlayAvi(int Loop=0, int FullScreen=0);    // ������Ƶ�豸
	void Close(void);                     // �ر���Ƶ�ļ�
	void Stop();                         // ֹͣ����
	void Pause();                        // ��ͣ����
	void Forward(int frame);              // ǰ�� frame֡
	void Backward(int frame);             // ����frame֡
	int GetWidth();                    // �õ���Ƶ���
	int GetHeight();                   // �õ���Ƶ�߶�
	int GetFrame();                   // �õ���ǰ֡��
	int GetFrames();                  // �õ���Ƶ��֡��
	int IsPlaying();                   // ��ѯ����״̬
	int GetSpeed();                   // ��ѯ�����ٶ�
	BOOL GetPause();                   // ��ѯ�Ƿ���ͣ��״̬
	void SetSpeed(int speed);          // ���ò����ٶ�
	BOOL SeekTo(int position);        // ����λ��position����
private :
	BOOL m_bOpen;                // �Ƿ���ý�岥�ţ�1��ʾ���ļ����򿪣�����Ϊ0
	BOOL m_bPause;               // �Ƿ���ͣ��1 ��ʾ��ͣ������0
	BOOL m_bPlaying;              // �Ƿ����ڲ���
	WORD m_wDeviceID;           // �����豸ID
};

