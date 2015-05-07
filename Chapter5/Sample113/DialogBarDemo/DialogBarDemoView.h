// DialogBarDemoView.h : interface of the CDialogBarDemoView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_DIALOGBARDEMOVIEW_H__2747C279_7D77_4C69_B8C2_C95F48DD282A__INCLUDED_)
#define AFX_DIALOGBARDEMOVIEW_H__2747C279_7D77_4C69_B8C2_C95F48DD282A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CDialogBarDemoView : public CView
{
protected: // create from serialization only
	CDialogBarDemoView();
	DECLARE_DYNCREATE(CDialogBarDemoView)

// Attributes
public:
	CDialogBarDemoDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDialogBarDemoView)
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
	virtual ~CDialogBarDemoView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CDialogBarDemoView)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in DialogBarDemoView.cpp
inline CDialogBarDemoDoc* CDialogBarDemoView::GetDocument()
   { return (CDialogBarDemoDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DIALOGBARDEMOVIEW_H__2747C279_7D77_4C69_B8C2_C95F48DD282A__INCLUDED_)
