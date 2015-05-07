// ExcelPrintDlg.h : header file
//

#if !defined(AFX_ExcelPrintDLG_H__E43F62A6_60CE_4BC9_AABF_6D29B86D84A6__INCLUDED_)
#define AFX_ExcelPrintDLG_H__E43F62A6_60CE_4BC9_AABF_6D29B86D84A6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CExcelPrintDlg dialog

class CExcelPrintDlg : public CDialog
{
// Construction
public:
	CExcelPrintDlg(CWnd* pParent = NULL);	// standard constructor
	_ConnectionPtr m_pConnection;									//���Ӷ���ָ��
	_RecordsetPtr m_pRecordset; 									//��¼������
	int count;													//��¼��

// Dialog Data
	//{{AFX_DATA(CExcelPrintDlg)
	enum { IDD = IDD_ExcelPrint_DIALOG };
	CString	m_strTitle;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CExcelPrintDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CExcelPrintDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnExcelPrint();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ExcelPrintDLG_H__E43F62A6_60CE_4BC9_AABF_6D29B86D84A6__INCLUDED_)
