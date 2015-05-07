#if !defined(AFX_TEXTPROGRESSBAR_H__C35FF1DC_7CF2_4F00_8E34_6AC35B093C7C__INCLUDED_)
#define AFX_TEXTPROGRESSBAR_H__C35FF1DC_7CF2_4F00_8E34_6AC35B093C7C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// TextProgressBar.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CTextProgressBar window

class CTextProgressBar : public CProgressCtrl
{
// Construction
public:
	CTextProgressBar();
	void SetRange(int nLower, int nUpper);//���ý������ķ�Χ
	int SetPos(int nPos);//���õ�ǰ��������λ��

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTextProgressBar)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CTextProgressBar();

	// Generated message map functions
protected:
	int m_nLower;//����������Сֵ
	int m_nUpper; //�����������ֵ
	int m_nCurrentPosition;//�������ĵ�ǰλ��
	//{{AFX_MSG(CTextProgressBar)
	afx_msg void OnPaint();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TEXTPROGRESSBAR_H__C35FF1DC_7CF2_4F00_8E34_6AC35B093C7C__INCLUDED_)
