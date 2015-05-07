// ADODataBase2.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "ADODataBase2.h"
#include "ADODataBase2Dlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CADODataBase2App

BEGIN_MESSAGE_MAP(CADODataBase2App, CWinApp)
	//{{AFX_MSG_MAP(CADODataBase2App)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CADODataBase2App construction

CADODataBase2App::CADODataBase2App()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CADODataBase2App object

CADODataBase2App theApp;

/////////////////////////////////////////////////////////////////////////////
// CADODataBase2App initialization

BOOL CADODataBase2App::InitInstance()
{
	AfxEnableControlContainer();
	//��ʼ��OLE DLLs
	if (!AfxOleInit())
	{
		AfxMessageBox("��ʼ��OLE DLLʧ�ܣ�");
		return FALSE;
	}
	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.

#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif

	CADODataBase2Dlg dlg;
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
