class AFX_EXT_CLASS CMouseHook:public CObject //AFX_EXT_CLASS��������Ϊ������
{ 
public: 
	CMouseHook();//������Ĺ��캯��
	~CMouseHook();//��������������� 
	BOOL StartHook(HWND hWnd);//��װ���Ӻ��� 
	BOOL StopHook();//ж�ع��Ӻ��� 
}; 
