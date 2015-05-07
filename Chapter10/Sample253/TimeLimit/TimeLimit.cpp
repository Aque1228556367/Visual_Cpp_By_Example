// TimeLimit.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "TimeLimit.h"
#include "TimeLimitDlg.h"
#include "RegKey.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTimeLimitApp

BEGIN_MESSAGE_MAP(CTimeLimitApp, CWinApp)
	//{{AFX_MSG_MAP(CTimeLimitApp)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTimeLimitApp construction

CTimeLimitApp::CTimeLimitApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CTimeLimitApp object

CTimeLimitApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CTimeLimitApp initialization

BOOL CTimeLimitApp::InitInstance()
{
	
	CTime CurTime = CTime::GetCurrentTime();//�Ȼ�õ�ǰ��ϵͳʱ��
	if (!IsInstalled())//�������Ƿ��һ�����У���������趨����ʱ��
	{
		CTime t = CurTime + CTimeSpan(0,0,5,0); //ʹ��ʱ��Ϊ5����  
		SetLimitTime(t.GetYear(),t.GetMonth(),t.GetDay(),
			         t.GetHour(),t.GetMinute(),t.GetSecond());
	}
	else
	{
		//���������ǵ�һ�����У���ȡע����е�ʱ��ֵ���뵱ǰʱ��Ƚ�
		CTime LimitTime;
		GetLimitTime(LimitTime);
		if (CurTime>LimitTime)//������ʹ������
		{
			AfxMessageBox("���ð��ѵ��ڣ�����ϵ����һ������ʹ��",MB_OK);
			return FALSE;//�˳�
		}
	}
   
	AfxEnableControlContainer();

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.

#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif

	CTimeLimitDlg dlg;
	m_pMainWnd = &dlg;
	int nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with OK
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with Cancel
	}

	// Since the dialog has been closed, return FALSE so that we exit the
	//  application, rather than start the application's message pump.
	return FALSE;
}


BOOL CTimeLimitApp::IsInstalled()//�ж�����Ƿ�Ϊ��һ������
{
	BOOL bInstalled = FALSE;
	DWORD dwDisposition;
	HKEY m_hKey;
	//��ע���
	LONG ret = RegCreateKeyEx (HKEY_LOCAL_MACHINE, "SOFTWARE\\TimeLimit", 0L, NULL,
		REG_OPTION_VOLATILE, KEY_ALL_ACCESS, NULL, &m_hKey, &dwDisposition);
    if (ret != ERROR_SUCCESS)    //��ע���ʧ��
		return FALSE;
	//��ע����ж�������ֵ
	DWORD dwVal,dwType,dwLen;
	ret = RegQueryValueEx(m_hKey, "Installed", NULL, &dwType,(unsigned char*)&dwVal,&dwLen);
    if (ret != ERROR_SUCCESS)      //��ȡ����ʧ��
		return FALSE;                        
	//������������ֵ�Ƿ�Ϊ1������ǣ�����������ǰ�����й�
	bInstalled = (dwVal == 1);	
	RegCloseKey(m_hKey);//�ر�ע���
	return bInstalled;
}


BOOL CTimeLimitApp::GetLimitTime(CTime&t)
{
	DWORD dwDisposition;
	HKEY m_hKey;
	//��ע���
	LONG ret = RegCreateKeyEx (HKEY_LOCAL_MACHINE, "SOFTWARE\\TimeLimit", 0L, NULL,
		REG_OPTION_VOLATILE, KEY_ALL_ACCESS, NULL, &m_hKey, &dwDisposition);
    if (ret != ERROR_SUCCESS)    //��ע���ʧ��
		return FALSE;	
	//��ע����ж���������������
	DWORD nYear,nMonth,nDay,nHour,nMinute,nSecond;
	DWORD dwType;
	DWORD dwLen;
	ret = RegQueryValueEx (m_hKey, "Year", NULL,    //��ȡ���
		&dwType,(unsigned char*)&nYear,&dwLen);
    if (ret != ERROR_SUCCESS)      //��ȡ����ʧ��
		return FALSE;                        
	ret = RegQueryValueEx (m_hKey, "Month", NULL,    //��ȡ�·�
		&dwType,(unsigned char*)&nMonth,&dwLen);
    if (ret != ERROR_SUCCESS)      //��ȡ����ʧ��
		return FALSE;                        
	ret = RegQueryValueEx (m_hKey, "Day", NULL,    //��ȡ��
		&dwType,(unsigned char*)&nDay,&dwLen);
    if (ret != ERROR_SUCCESS)      //��ȡ����ʧ��
		return FALSE;                        
	ret = RegQueryValueEx (m_hKey, "Hour", NULL,    //��ȡСʱ
		&dwType,(unsigned char*)&nHour,&dwLen);
    if (ret != ERROR_SUCCESS)      //��ȡ����ʧ��
		return FALSE;                        
	ret = RegQueryValueEx (m_hKey, "Minute", NULL,    //��ȡ����
		&dwType,(unsigned char*)&nMinute,&dwLen);
    if (ret != ERROR_SUCCESS)      //��ȡ����ʧ��
		return FALSE;                        
	ret = RegQueryValueEx (m_hKey, "Second", NULL,    //��ȡ��
		&dwType,(unsigned char*)&nSecond,&dwLen);
    if (ret != ERROR_SUCCESS)                         //��ȡ����ʧ��
		return FALSE;                        	
	//�ر�ע���
	RegCloseKey(m_hKey);
	t = CTime(nYear,nMonth,nDay,nHour,nMinute,nSecond);
	return TRUE;
}

BOOL CTimeLimitApp::SetLimitTime(DWORD nYear,DWORD nMonth,DWORD nDay,
		              DWORD nHour,DWORD nMinute,DWORD nSecond)
{
    DWORD dwDisposition;
	HKEY m_hKey;
	//��ע���
	LONG ret = RegCreateKeyEx (HKEY_LOCAL_MACHINE, "SOFTWARE\\TimeLimit", 0L, NULL,
		REG_OPTION_VOLATILE, KEY_ALL_ACCESS, NULL, &m_hKey, &dwDisposition);
    if (ret != ERROR_SUCCESS)    //��ע���ʧ��
		return FALSE;	
	//��ע�����д��������������
	ret = RegSetValueEx (m_hKey, "Year", NULL,      //д����
		REG_DWORD,(CONST BYTE*)&nYear,sizeof(DWORD));
    if (ret != ERROR_SUCCESS)                       //д������ʧ��       
		return FALSE;                        
	ret = RegSetValueEx (m_hKey, "Month", NULL,     //д���·�
		REG_DWORD,(CONST BYTE*)&nMonth,sizeof(DWORD));
    if (ret != ERROR_SUCCESS)                       //д������ʧ��
		return FALSE;                        
	ret = RegSetValueEx (m_hKey, "Day", NULL,       //д����
		REG_DWORD,(CONST BYTE*)&nDay,sizeof(DWORD));
    if (ret != ERROR_SUCCESS)                       //д������ʧ��
		return FALSE;                        
	ret = RegSetValueEx (m_hKey, "Hour", NULL,      //д��Сʱ
		REG_DWORD,(CONST BYTE*)&nHour,sizeof(DWORD));
    if (ret != ERROR_SUCCESS)                       //д������ʧ��
		return FALSE;                        
	ret = RegSetValueEx (m_hKey, "Minute", NULL,    //��ȡ��������
		REG_DWORD,(CONST BYTE*)&nMinute,sizeof(DWORD));
    if (ret != ERROR_SUCCESS)                       //д������ʧ��
		return FALSE;                        
	ret = RegSetValueEx (m_hKey, "Second", NULL,    //д����
		REG_DWORD,(CONST BYTE*)&nSecond,sizeof(DWORD));
    if (ret != ERROR_SUCCESS)                       //д������ʧ��
		return FALSE;    	
	//д���������ݣ��������ǵ�һ��ʹ��
	DWORD dwVal = 1;
	ret = RegSetValueEx (m_hKey, "Installed", NULL,    //д������ֵ
		REG_DWORD,(CONST BYTE*)&dwVal,sizeof(DWORD));
    if (ret != ERROR_SUCCESS)				//д������ʧ��
		return FALSE;                 	
	RegCloseKey(m_hKey);	//�ر�ע���
	return TRUE;  
}
