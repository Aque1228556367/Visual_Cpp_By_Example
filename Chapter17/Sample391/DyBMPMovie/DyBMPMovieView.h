// DyBMPMovieView.h : interface of the CDyBMPMovieView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_DYBMPMOVIEVIEW_H__81FB2EB3_7C3F_405E_98E5_1A20C9579C30__INCLUDED_)
#define AFX_DYBMPMOVIEVIEW_H__81FB2EB3_7C3F_405E_98E5_1A20C9579C30__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CDyBMPMovieView : public CView
{
protected: // create from serialization only
	CDyBMPMovieView();
	DECLARE_DYNCREATE(CDyBMPMovieView)

// Attributes
public:
	CDyBMPMovieDoc* GetDocument();

// Operations
public:
private:
	CBitmap		m_Bitmap[6];    //װ��Ҫ��ʾλͼ����
	int			m_nFrameWidth;          //ͼ����
	int			m_nFrameHeight;         //ͼ��߶�
	CPoint		m_ptCurPos;				//��ǰ�Ĺ���λ��	
	int			m_nCurFrameNo;          //��ǰ��ʾ��ͼ����
	int			m_nStepX;				//ˮƽ�����ϵĲ�����
	int			m_nStepY;               //��ֱ�����ϵĲ�����
	CBrush      m_BKBrush;				//������������ı���ˢ��
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDyBMPMovieView)
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
	virtual ~CDyBMPMovieView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CDyBMPMovieView)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnDestroy();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in DyBMPMovieView.cpp
inline CDyBMPMovieDoc* CDyBMPMovieView::GetDocument()
   { return (CDyBMPMovieDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DYBMPMOVIEVIEW_H__81FB2EB3_7C3F_405E_98E5_1A20C9579C30__INCLUDED_)
