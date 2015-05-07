// CircleWaveDoc.h : interface of the CCircleWaveDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_CIRCLEWAVEDOC_H__AF0357BB_C1CD_42D0_B7FA_1081871BD906__INCLUDED_)
#define AFX_CIRCLEWAVEDOC_H__AF0357BB_C1CD_42D0_B7FA_1081871BD906__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CCircleWaveDoc : public CDocument
{
protected: // create from serialization only
	CCircleWaveDoc();
	DECLARE_DYNCREATE(CCircleWaveDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCircleWaveDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CCircleWaveDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CCircleWaveDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CIRCLEWAVEDOC_H__AF0357BB_C1CD_42D0_B7FA_1081871BD906__INCLUDED_)
