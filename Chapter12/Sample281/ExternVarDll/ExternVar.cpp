// ExternVar.cpp: implementation of the ExternVar class.
//
//////////////////////////////////////////////////////////////////////

#include "ExternVar.h"
#include "Windows.h"
char* myVar;									//�������
//DLLMain��������DLL����ں���
BOOL WINAPI DllMain(HANDLE hInst,ULONG ul_reason_for_call,LPVOID lpReserved)
{
	switch( ul_reason_for_call ) 
	{
	case DLL_PROCESS_ATTACH:						//�µĽ���Ҫ����DLL
		//��ʼ��ʼ��DLL
		myVar="�µĽ��̷�����DLL�ĵ�������";
		break;
	case DLL_THREAD_ATTACH:						//�µ��߳�Ҫ����DLL
	case DLL_THREAD_DETACH:						//һ���̲߳���ʹ��DLL
	case DLL_PROCESS_DETACH:						//һ�����̲���ʹ��DLL
		myVar="";
		break;
	}
	return TRUE;
}
