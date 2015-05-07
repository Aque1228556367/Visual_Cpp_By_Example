
#include "stdafx.h"
#include "VideoVoiceTrans.h"
#include "DSocket.h"
#include "VideoVoiceTransDlg.h"
#include "RequestDlg.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// DSocket

// Initialize static members...
char DSocket::remoteaddress[500]="";
char DSocket::remotename[500]="";
unsigned char DSocket::data[2000];
unsigned char DSocket::vdata[30000];
unsigned char DSocket::adata[5000];
unsigned int DSocket::length=2000;
unsigned int DSocket::vlength=30000;
unsigned int DSocket::alength=5000;


DSocket::DSocket()
{

}

DSocket::~DSocket()
{
}


// Do not edit the following lines, which are needed by ClassWizard.
#if 0
BEGIN_MESSAGE_MAP(DSocket, CSocket)
	//{{AFX_MSG_MAP(DSocket)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
#endif	// 0

/////////////////////////////////////////////////////////////////////////////
// DSocket member functions

void DSocket::CreateSocket(int port,int dtype)
{
	this->Create(port,SOCK_DGRAM);//����Socket
	type=dtype;//Socket����
	gethostname(localname,300);//��ȡ�Զ��û���
}


void DSocket::SetParent(CDialog *dlg)
{
	pdlg=dlg;	
}

/**
*    Invoked when any data arrives from the remote host
*
*/
void DSocket::OnReceive(int errcode)
{
	CString address;
	char hname[400],str[1000],mesg[500];
	unsigned int port,retvalue;
	int n,len;
	RequestDlg rdlg(NULL);//�������ӶԻ���
	if(type==TYPE_CONTROL)//SocketΪ������ϢSocket
	{	
		retvalue=this->ReceiveFrom(data,length,address,port);//���նԶ���Ϣ
		if(retvalue==SOCKET_ERROR)
		return;
		for(int i=0;i<data[1];i++)
		hname[i]=data[i+2];
		hname[i]=0;
		strcpy(remotename,hname);//��ȡ�Զ�����
		strcpy(remoteaddress,(LPCTSTR)address);	
		switch(data[0])
		{
			
			case MESG_CONNECT://������Ϣ
			// display the accept , reject dialog box
			rdlg.SetParameter(remotename,remoteaddress,pdlg);
			rdlg.DoModal();//�����������ӶԻ���
			return;	
			case MESG_DISCONNECT://�Ͽ�����
			( (CVideoVoiceTransDlg*)pdlg)->DestroyConference();
			sprintf(str,"�û� %s �Ͽ������ӣ�",hname);
			AfxMessageBox(str);
			return;
			case MESG_ACCEPT://��������
			AfxMessageBox("�û��Ѿ���������������");
			( (CVideoVoiceTransDlg*)pdlg)->StartConference();//��ʼ����
			return;
			case MESG_REJECT://�ܾ�����
			sprintf(str,"�û� %s �ܾ�����������",hname);
			AfxMessageBox(str);
			return;
		}
		return;
	}

	if(type==TYPE_AUDIO)//��ƵSocket
	{
		
		retvalue=this->ReceiveFrom(adata,alength,address,port);//������Ƶ����
		if(retvalue==SOCKET_ERROR)
		return;
		((CVideoVoiceTransDlg *)pdlg)->play->PostThreadMessage(WM_PLAYSOUND_PLAYBLOCK,retvalue,(LPARAM)adata);//��������	
		return;
	}
	if(type==TYPE_VIDEO)//��ƵSocket
	{
		
		retvalue=this->ReceiveFrom(vdata,vlength,address,port);//������Ƶ����
		if(retvalue==SOCKET_ERROR)
		return;
		((CVideoVoiceTransDlg *)pdlg)->DisplayRemoteFrame(vdata,retvalue);//��ʾ�Զ���Ƶ
		return;
	}
	if(type==TYPE_TEXT)//�ı�Socket
	{
		
		retvalue=this->ReceiveFrom(data,length,address,port);//�����ı���Ϣ
		if(retvalue==SOCKET_ERROR)
		return;
		n=data[1];
		for(int i=0;i<n;i++)
		hname[i]=data[i+2];
		hname[i]=0;	
		len=data[n+2] | ( data[n+3]<<8 );
		memcpy(mesg,&data[n+4],len);
		mesg[len]=0;
		sprintf(str,"%s >> %s ",hname,mesg);
		((CVideoVoiceTransDlg *)pdlg)->DisplayMesg(str);//���б����ʾ�ı�
		return;
	}
}


/**
*       Send the control data to remote host
*
*
*/
void DSocket::SendControlMessage(int type,char *address)
{
	char data[1000];
	int n;
	data[0]=type;//��һ���ֽ�Ϊ�������ͱ�ʶ				
	n=strlen(localname);//���˻�����	
	data[1]=n;//�ڶ����ֽ�Ϊ���ֳ���						
	memcpy(&data[2],localname,n);
	if(address==NULL)
	{	
		SendTo(data,n+2,PORT_CONTROL,remoteaddress);
	}
	else
	{
		SendTo(data,n+2,PORT_CONTROL,address);//����������Ϣ����
	}
}


void DSocket::SendAudioData(unsigned char *data,int length)//������Ƶ����
{
	SendTo(data,length,PORT_AUDIO,remoteaddress);	
}

void DSocket::SendVideoData(unsigned char *data,int length)//������Ƶ����
{
	SendTo(data,length,PORT_VIDEO,remoteaddress);	
}


void DSocket::SendTextData(unsigned char *data,short length)//�����ı�����
{
	unsigned char *packet=new unsigned char[length+500];
	int n;	
	packet[0]=TYPE_TEXT;//��һ���ֽڴ洢����
	n=strlen(localname);//�������Ƴ���
	packet[1]=n;	
	// Hostname
	memcpy(&packet[2],localname,n);//���������Ƽ�������
	packet[n+2]=(unsigned char) length;//�ı���Ϣ����
	packet[n+3]=(unsigned char) (length>>8);
	memcpy(&packet[n+4],data,length);	
	SendTo(packet,n+4+length,PORT_TEXT,remoteaddress);//��������	
}


void DSocket::SendRequestCon(unsigned char *data,short length)
{
	
	//static char address[50];
	//address[50]="127.0.0.1";
	SendTo(data,length,PORT_QUEST,"127.0.0.1");
	
}

/**
*    Closes the socket created by the createsocket method
*
*/
void DSocket::CloseSocket()
{
	DSocket::Close();
}
