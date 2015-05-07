// FullScreenDemoView.h : interface of the CFullScreenDemoView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_FULLSCREENDEMOVIEW_H__4B3B7008_B57F_4165_A36A_22C84AD516B1__INCLUDED_)
#define AFX_FULLSCREENDEMOVIEW_H__4B3B7008_B57F_4165_A36A_22C84AD516B1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CFullScreenDemoView : public CView
{
protected: // create from serialization only
	CFullScreenDemoView();
	DECLARE_DYNCREATE(CFullScreenDemoView)

// Attributes
public:
	CFullScreenDemoDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFullScreenDemoView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CFullScreenDemoView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CFullScreenDemoView)
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in FullScreenDemoView.cpp
inline CFullScreenDemoDoc* CFullScreenDemoView::GetDocument()
   { return (CFullScreenDemoDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FULLSCREENDEMOVIEW_H__4B3B7008_B57F_4165_A36A_22C84AD516B1__INCLUDED_)
