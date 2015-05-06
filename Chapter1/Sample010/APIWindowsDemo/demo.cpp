#include <windows.h>										//ͷ�ļ�
LRESULT CALLBACK WndProc(HWND,UINT,WPARAM,LPARAM);		//���ں�������
char szClassName[]="windowclass";								//���ڽṹ�������
char szAppTitle[]="ʹ��API��������";							//���ڵı���
int PASCAL WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdParam , INT nCmdShow)													//WinMain()�����Ķ���
{
	HWND hMainWnd;										//���ھ��
	MSG msg;												//��Ϣ�ṹ��
	WNDCLASS winclass;									//���ڽṹ��
if(!hPrevInstance)
//�ж��Ƿ�����Ӧ�ó����ʵ�������У������ڽṹ������ݳ�Ա��ֵ���涨��Ҫ�����Ĵ��ڵ�����
	{
		winclass.style=CS_HREDRAW|CS_VREDRAW;				//���ڷ��
		winclass.lpfnWndProc=WndProc;							//���ڵ���Ϣ������
		winclass.cbClsExtra=0; 								//����������չ
		winclass.cbWndExtra=0; 								//����ʵ������չ
		winclass.hInstance=hInstance;							//��ǰӦ�ó���ʵ�����
		winclass.hIcon=LoadIcon(NULL,IDI_APPLICATION);	//���ڵ���С��ͼ��Ϊȱʡͼ��
		winclass.hCursor=LoadCursor(NULL,IDC_ARROW);			//���ڲ��ü�ͷ���
		winclass.hbrBackground=(HBRUSH)GetStockObject(WHITE_BRUSH);//���ڱ���ɫΪ��ɫ
		winclass.lpszMenuName=NULL;//�޴��ڲ˵�
		winclass.lpszClassName=szClassName; 					//�����ڽṹ������	
		RegisterClass(&winclass);								//ע�ᴰ��
	}
//������CreateWindow()�������������ڣ����������������ڵľ��
	hMainWnd=CreateWindow(
		szClassName,										//���ڽṹ�������
		 szAppTitle,										//���ڵı���
		 WS_OVERLAPPEDWINDOW,							//���ڷ��Ϊ���ص�����
//�����ĸ��������������Ͻ�x��y����ʹ��ڵĿ����߶ȣ���ʹ��ȱʡֵ
CW_USEDEFAULT,CW_USEDEFAULT,CW_USEDEFAULT,CW_USEDEFAULT,
//��������ֱ�Ϊ�����ھ�������ڲ˵������Ӧ�ó���ʵ������͸��Ӳ���
NULL,NULL,hInstance,NULL);
	ShowWindow(hMainWnd,SW_SHOWNORMAL);						//��ʾ����
	UpdateWindow(hMainWnd);									//���´���
//������While()ѭ����������Ϣѭ��
	while(GetMessage(&msg,NULL,0,0))						//��ȡ��Ϣ�����msg�ṹ��
	{
		TranslateMessage(&msg);							//���������Ϣ
		DispatchMessage(&msg);					//�򴰿ں���������Ϣ���ô��ں�������
	}
	return msg.wParam;
}
LRESULT CALLBACK WndProc(HWND hMainwnd, UINT message, WPARAM wParam, LPARAM lParam)  															//���ں����Ķ���
{
	HDC hdc;													//�豸������
	PAINTSTRUCT ps;											//ˢ������
	RECT rect;													//���νṹ
	char messageleft[]="��������������";		//��������������Ϣ����ʾ����ʾ����
	   switch(message)											//�ж���Ϣ��ʶ��
	   {
	   case WM_PAINT:											//�����ػ�
		   {
		   hdc=BeginPaint(hMainwnd,&ps);
		   GetClientRect(hMainwnd,&rect);							//��ȡ�ͻ�������
		   rect.bottom=rect.top+50;
		   DrawText(hdc,TEXT("ʹ��Windows API����Windows���ڳ���"),-1,&rect,DT_SINGLELINE| DT_CENTER|DT_VCENTER);										//�ڿͻ��������������
		   EndPaint(hMainwnd,&ps);
		   break;
		   }
	   case WM_LBUTTONDOWN:
		{
			MessageBox(GetFocus(),messageleft,"ʹ��API��������",MB_OK|MB_ICONINFORMATION);
			break;
		}
	   case WM_DESTROY://�ر�Ӧ�ó��򴰿�ʱ��������Ϣ
		{
		PostQuitMessage(0);						//����WM_QUIT��Ϣ������Ӧ�ó���
		return 0;
		}
	   default :
		break;
	}
return DefWindowProc(hMainwnd,message,wParam,lParam);		//������Ϣ����Windows��Ĭ�ϴ���
}
