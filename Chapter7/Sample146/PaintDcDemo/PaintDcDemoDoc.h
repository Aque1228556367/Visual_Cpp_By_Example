// PaintDcDemoDoc.h : interface of the CPaintDcDemoDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_PAINTDCDEMODOC_H__92064E5B_4588_44AC_BC0D_6E6208E63693__INCLUDED_)
#define AFX_PAINTDCDEMODOC_H__92064E5B_4588_44AC_BC0D_6E6208E63693__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CPaintDcDemoDoc : public CDocument
{
protected: // create from serialization only
	CPaintDcDemoDoc();
	DECLARE_DYNCREATE(CPaintDcDemoDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPaintDcDemoDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CPaintDcDemoDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CPaintDcDemoDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PAINTDCDEMODOC_H__92064E5B_4588_44AC_BC0D_6E6208E63693__INCLUDED_)
