// MousehookDll.cpp : Defines the initialization routines for the DLL.
//

#include "stdafx.h"
#include <afxdllx.h>
#include "MousehookDll.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


static AFX_EXTENSION_MODULE MousehookDllDLL = { NULL, NULL };


#pragma data_seg("Titlename")
	HWND glhPrevWnd=NULL; //�ϴ������ָ�Ĵ��ھ�� 
	HWND glhDisplayWnd=NULL; //��ʾĿ�괰�ڱ���༭��ľ�� 
	HHOOK glhHook=NULL; //��װ����깳�Ӿ�� 
	HINSTANCE glhInstance=NULL;//DLLʵ����� 
#pragma data_seg() 


extern "C" int APIENTRY
DllMain(HINSTANCE hInstance, DWORD dwReason, LPVOID lpReserved)
{
	// Remove this if you use lpReserved
	UNREFERENCED_PARAMETER(lpReserved);

	if (dwReason == DLL_PROCESS_ATTACH)
	{
		TRACE0("MOUSEHOOKDLL.DLL Initializing!\n");
		
		// Extension DLL one-time initialization
		if (!AfxInitExtensionModule(MousehookDllDLL, hInstance))
			return 0;

		// Insert this DLL into the resource chain
		// NOTE: If this Extension DLL is being implicitly linked to by
		//  an MFC Regular DLL (such as an ActiveX Control)
		//  instead of an MFC application, then you will want to
		//  remove this line from DllMain and put it in a separate
		//  function exported from this Extension DLL.  The Regular DLL
		//  that uses this Extension DLL should then explicitly call that
		//  function to initialize this Extension DLL.  Otherwise,
		//  the CDynLinkLibrary object will not be attached to the
		//  Regular DLL's resource chain, and serious problems will
		//  result.

		new CDynLinkLibrary(MousehookDllDLL);
		glhInstance=hInstance;//���뱣��DLLʵ����� 
	}
	else if (dwReason == DLL_PROCESS_DETACH)
	{
		TRACE0("MOUSEHOOKDLL.DLL Terminating!\n");
		// Terminate the library before destructors are called
		AfxTermExtensionModule(MousehookDllDLL);
	}
	return 1;   // ok
}
//��깳�Ӻ�����ʵ��
LRESULT CALLBACK MouseProc(int nCode,WPARAM wparam,LPARAM lparam) 
{ 
	LPMOUSEHOOKSTRUCT pMouseHook=(MOUSEHOOKSTRUCT FAR *) lparam; 
	if (nCode>=0) 
	{ 
		HWND glhTargetWnd=pMouseHook->hwnd;//ȡĿ�괰�ھ�� 
		HWND ParentWnd=glhTargetWnd; 
		while (ParentWnd !=NULL) 
		{ 
			glhTargetWnd=ParentWnd; 
			ParentWnd=GetParent(glhTargetWnd); //ȡӦ�ó��������ھ�� 
		} 
		if(glhTargetWnd!=glhPrevWnd) 
		{ 
			char szCaption[100]; 
			GetWindowText(glhTargetWnd,szCaption,100); //ȡĿ�괰�ڱ��� 
			if(IsWindow(glhDisplayWnd)) 
				SendMessage(glhDisplayWnd,WM_SETTEXT,0,(LPARAM)(LPCTSTR)szCaption); 
			glhPrevWnd=glhTargetWnd; //����Ŀ�괰�� 
		} 
	} 
	return CallNextHookEx(glhHook,nCode,wparam,lparam); //����������Ϣ 
} 


CMouseHook::CMouseHook() //�๹�캯�� 
{ 
} 
CMouseHook::~CMouseHook() //���������� 
{ 
	StopHook(); 
} 

BOOL CMouseHook::StartHook(HWND hWnd) //��װ���Ӳ��趨������ʾ���ھ�� 
{ 
	BOOL bResult=FALSE;
	glhHook=SetWindowsHookEx(WH_MOUSE,MouseProc,glhInstance,0); 
	if(glhHook!=NULL) 
	{
		bResult=TRUE;
	}
	glhDisplayWnd=hWnd;//������ʾĿ�괰�ڱ���༭��ľ�� 
	return bResult; 
} 

BOOL CMouseHook::StopHook() //ж�ع��� 
{ 
	BOOL bResult=FALSE; 
	if(glhHook) 
	{ 
		bResult= UnhookWindowsHookEx(glhHook); 
		if(bResult) 
		{ 
			glhPrevWnd=NULL; 
			glhDisplayWnd=NULL;//����� 
			glhHook=NULL; 
		} 
	} 
	return bResult; 
} 



