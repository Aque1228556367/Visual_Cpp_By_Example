// MappingDemo.h : main header file for the MAPPINGDEMO application
//

#if !defined(AFX_MAPPINGDEMO_H__4C213D9A_CD00_4C03_9A42_51C5764C14F5__INCLUDED_)
#define AFX_MAPPINGDEMO_H__4C213D9A_CD00_4C03_9A42_51C5764C14F5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CMappingDemoApp:
// See MappingDemo.cpp for the implementation of this class
//

class CMappingDemoApp : public CWinApp
{
public:
	CMappingDemoApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMappingDemoApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CMappingDemoApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MAPPINGDEMO_H__4C213D9A_CD00_4C03_9A42_51C5764C14F5__INCLUDED_)
