// RWIniFileDemo.h : main header file for the RWIniFileDemo application
//

#if !defined(AFX_RWIniFileDemo_H__4620B7C1_34C6_486E_8DC7_A23EC9F668F9__INCLUDED_)
#define AFX_RWIniFileDemo_H__4620B7C1_34C6_486E_8DC7_A23EC9F668F9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CRWIniFileDemoApp:
// See RWIniFileDemo.cpp for the implementation of this class
//

class CRWIniFileDemoApp : public CWinApp
{
public:
	CRWIniFileDemoApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRWIniFileDemoApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CRWIniFileDemoApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_RWIniFileDemo_H__4620B7C1_34C6_486E_8DC7_A23EC9F668F9__INCLUDED_)
