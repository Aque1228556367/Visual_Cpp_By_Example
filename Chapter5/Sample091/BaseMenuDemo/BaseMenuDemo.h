// BaseMenuDemo.h : main header file for the BASEMENUDEMO application
//

#if !defined(AFX_BASEMENUDEMO_H__C6907707_DE7C_4E1F_9E46_85E91A0D6FC8__INCLUDED_)
#define AFX_BASEMENUDEMO_H__C6907707_DE7C_4E1F_9E46_85E91A0D6FC8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CBaseMenuDemoApp:
// See BaseMenuDemo.cpp for the implementation of this class
//

class CBaseMenuDemoApp : public CWinApp
{
public:
	CBaseMenuDemoApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBaseMenuDemoApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CBaseMenuDemoApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BASEMENUDEMO_H__C6907707_DE7C_4E1F_9E46_85E91A0D6FC8__INCLUDED_)
