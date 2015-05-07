// MainFrm.h : interface of the CMainFrame class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MAINFRM_H__D2F2851D_9D4A_4356_BC67_406FDC271B76__INCLUDED_)
#define AFX_MAINFRM_H__D2F2851D_9D4A_4356_BC67_406FDC271B76__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CMainFrame : public CFrameWnd
{
	
protected: // create from serialization only
	CMainFrame();
	DECLARE_DYNCREATE(CMainFrame)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMainFrame)
	public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual BOOL OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // control bar embedded members
	CStatusBar  m_wndStatusBar;
	CToolBar    m_wndToolBar;

// Generated message map functions
protected:
	CSplitterWnd m_wndSplitter;
	//{{AFX_MSG(CMainFrame)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnChangePassword();
	afx_msg void OnChangeUser();
	afx_msg void OnRegisterUser();
	afx_msg void OnUpdateRegisterUser(CCmdUI* pCmdUI);
	afx_msg void OnDeleteUser();
	afx_msg void OnUpdateDeleteUser(CCmdUI* pCmdUI);
	afx_msg void OnSelectUser();
	afx_msg void OnExit();
	afx_msg void OnCleanUp();
	afx_msg void OnUpdateCleanUp(CCmdUI* pCmdUI);
	afx_msg void OnStore();
	afx_msg void OnUpdateStore(CCmdUI* pCmdUI);
	afx_msg void OnSale();
	afx_msg void OnClose();
	afx_msg void OnSeekById();
	afx_msg void OnSeekByName();
	afx_msg void OnSeekByType();
	afx_msg void OnSeekAll();
	afx_msg void OnSeekZeroNumber();
	afx_msg void OnSeekOverdue();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MAINFRM_H__D2F2851D_9D4A_4356_BC67_406FDC271B76__INCLUDED_)
