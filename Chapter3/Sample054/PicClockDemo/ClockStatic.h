#if !defined(AFX_CLOCKSTATIC_H__CD8035CF_D298_4E59_B111_84443FF64462__INCLUDED_)
#define AFX_CLOCKSTATIC_H__CD8035CF_D298_4E59_B111_84443FF64462__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ClockStatic.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CClockStatic window

class CClockStatic : public CStatic
{
// Construction
public:
	CClockStatic();

// Attributes
public:

// Operations
public:
//	static COLORREF origin;
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CClockStatic)
	protected:
	/*框架调用这个成员函数以允许在窗口被子类化之前进行其它必要的子类化。重载这个函数以允许控件的动态子类化。这是个高级可重载函数*/
	virtual void PreSubclassWindow();
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CClockStatic();

	// Generated message map functions
protected:
	//{{AFX_MSG(CClockStatic)
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnDestroy();
	afx_msg void OnPaint();
	//}}AFX_MSG
private:
	UINT m_Width;//静态框的宽度
	UINT m_Height;//静态框的高度
	BITMAP m_bm;//位图
	HBITMAP m_hBitmap[11];//位图句柄数组
	UINT m_nTimer;
	void ShowPic(UINT digit,UINT pos);//显示位图
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CLOCKSTATIC_H__CD8035CF_D298_4E59_B111_84443FF64462__INCLUDED_)