// MessageThreadDlg.h : header file
//

#if !defined(AFX_MessageThreadDLG_H__2C8C8BD8_7479_4288_A470_F2315D2E744B__INCLUDED_)
#define AFX_MessageThreadDLG_H__2C8C8BD8_7479_4288_A470_F2315D2E744B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CMessageThreadDlg dialog
struct NumInfo		
{
  CEdit* pedit;									//�༭�����ָ��
  HWND	hwnd;									//���ھ��
};



class CMessageThreadDlg : public CDialog
{
// Construction
public:
	CMessageThreadDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CMessageThreadDlg)
	enum { IDD = IDD_MessageThread_DIALOG };
	CEdit	m_Num;
	int		m_radio;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMessageThreadDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL
	NumInfo numinfo;
// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CMessageThreadDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnStar();
	afx_msg void OnRadio1();
	afx_msg void OnRadio2();
	afx_msg void OnRadio3();
	afx_msg void OnMsg();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MessageThreadDLG_H__2C8C8BD8_7479_4288_A470_F2315D2E744B__INCLUDED_)