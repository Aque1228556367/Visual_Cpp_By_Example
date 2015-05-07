// TextButtonToolView.h : interface of the CTextButtonToolView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_TextButtonToolVIEW_H__1F261D4D_ABCB_11D5_8C1B_CC1A6D330B6E__INCLUDED_)
#define AFX_TextButtonToolVIEW_H__1F261D4D_ABCB_11D5_8C1B_CC1A6D330B6E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CTextButtonToolView : public CView
{
protected: // create from serialization only
	CTextButtonToolView();
	DECLARE_DYNCREATE(CTextButtonToolView)

// Attributes
public:
	CTextButtonToolDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTextButtonToolView)
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
	virtual ~CTextButtonToolView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CTextButtonToolView)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in TextButtonToolView.cpp
inline CTextButtonToolDoc* CTextButtonToolView::GetDocument()
   { return (CTextButtonToolDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TextButtonToolVIEW_H__1F261D4D_ABCB_11D5_8C1B_CC1A6D330B6E__INCLUDED_)
