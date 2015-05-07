// BaseDocViewDemo3View.h : interface of the CBaseDocViewDemo3View class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_BaseDocViewDemo3VIEW_H__87EB8DEC_3B19_404C_8AB9_E5DF802CAB56__INCLUDED_)
#define AFX_BaseDocViewDemo3VIEW_H__87EB8DEC_3B19_404C_8AB9_E5DF802CAB56__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CBaseDocViewDemo3View : public CView
{
protected: // create from serialization only
	CBaseDocViewDemo3View();
	DECLARE_DYNCREATE(CBaseDocViewDemo3View)

// Attributes
public:
	CBaseDocViewDemo3Doc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBaseDocViewDemo3View)
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
	virtual ~CBaseDocViewDemo3View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	bool m_bDraw;											//��ͼ��ʶ
	HCURSOR m_Hcursor;									//������
	CPoint m_pOld;											//��¼���λ��

// Generated message map functions
protected:
	//{{AFX_MSG(CBaseDocViewDemo3View)
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in BaseDocViewDemo3View.cpp
inline CBaseDocViewDemo3Doc* CBaseDocViewDemo3View::GetDocument()
   { return (CBaseDocViewDemo3Doc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BaseDocViewDemo3VIEW_H__87EB8DEC_3B19_404C_8AB9_E5DF802CAB56__INCLUDED_)
