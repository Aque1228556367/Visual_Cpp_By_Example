// BaseListCtrlDlg.h : header file
//

#if !defined(AFX_BASELISTCTRLDLG_H__5D902156_3E5F_4DBA_AFB6_A5B83216413C__INCLUDED_)
#define AFX_BASELISTCTRLDLG_H__5D902156_3E5F_4DBA_AFB6_A5B83216413C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CBaseListCtrlDlg dialog

class CBaseListCtrlDlg : public CDialog
{
// Construction
public:
	CBaseListCtrlDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CBaseListCtrlDlg)
	enum { IDD = IDD_BASELISTCTRL_DIALOG };
	CListCtrl	m_ctlList;
	CString	m_edit;
	int		m_radio;
	CString	m_static;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBaseListCtrlDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;
	CImageList m_pImageList;							//ͼ���б�����

	// Generated message map functions
	//{{AFX_MSG(CBaseListCtrlDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnButton1();
	afx_msg void OnItemchangedList1(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BASELISTCTRLDLG_H__5D902156_3E5F_4DBA_AFB6_A5B83216413C__INCLUDED_)
