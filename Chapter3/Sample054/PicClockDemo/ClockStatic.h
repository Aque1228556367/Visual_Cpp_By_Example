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
	/*��ܵ��������Ա�����������ڴ��ڱ����໯֮ǰ����������Ҫ�����໯�������������������ؼ��Ķ�̬���໯�����Ǹ��߼������غ���*/
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
	UINT m_Width;//��̬��Ŀ��
	UINT m_Height;//��̬��ĸ߶�
	BITMAP m_bm;//λͼ
	HBITMAP m_hBitmap[11];//λͼ�������
	UINT m_nTimer;
	void ShowPic(UINT digit,UINT pos);//��ʾλͼ
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CLOCKSTATIC_H__CD8035CF_D298_4E59_B111_84443FF64462__INCLUDED_)