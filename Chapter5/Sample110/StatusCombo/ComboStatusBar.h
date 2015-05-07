#if !defined(AFX_COMBOSTATUSBAR_H__880A3FCF_DD0A_4E04_9E4A_3EB92C3DF406__INCLUDED_)
#define AFX_COMBOSTATUSBAR_H__880A3FCF_DD0A_4E04_9E4A_3EB92C3DF406__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ComboStatusBar.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CComboStatusBar window

class CComboStatusBar : public CStatusBar
{
// Construction
public:
	CComboStatusBar();

// Attributes
public:

	CComboBox	m_Combo;//��Ͽ�ؼ�
// Operations
public:
	CComboBox &GetCombo();//��ȡ��Ͽ�ؼ�����

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CComboStatusBar)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CComboStatusBar();

	// Generated message map functions
protected:
	//{{AFX_MSG(CComboStatusBar)
		afx_msg void OnComboSelChange();//��Ͽ�ؼ�ѡ��ı亯��
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_COMBOSTATUSBAR_H__880A3FCF_DD0A_4E04_9E4A_3EB92C3DF406__INCLUDED_)
