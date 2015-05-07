// CreateThreadDlg.h : header file
//

#if !defined(AFX_CreateThreadDLG_H__C5BF7543_D37A_4A78_BEBE_C65E8DC1E67A__INCLUDED_)
#define AFX_CreateThreadDLG_H__C5BF7543_D37A_4A78_BEBE_C65E8DC1E67A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CCreateThreadDlg dialog
typedef struct Threadinfo{
	CProgressCtrl *progress;								//����������
	int speed;												//�������ٶ�
	int pos;												//������λ��
} thread,*lpthread;

class CCreateThreadDlg : public CDialog
{
// Construction
public:
	CCreateThreadDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CCreateThreadDlg)
	enum { IDD = IDD_CreateThread_DIALOG };
	CProgressCtrl	m_progress3;
	CProgressCtrl	m_progress2;
	CProgressCtrl	m_progress1;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCreateThreadDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;
	thread thread1;												//�߳�1�Ľṹ
	thread thread2;												//�߳�2�Ľṹ
	thread thread3;												//�߳�3�Ľṹ
	HANDLE hThread1;										//�߳�1�߳̾��
	HANDLE hThread2;											//�߳�2�߳̾��
	HANDLE hThread3;											//�߳�3�߳̾��


	// Generated message map functions
	//{{AFX_MSG(CCreateThreadDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnStar1();
	afx_msg void OnStar2();
	afx_msg void OnStar3();
	afx_msg void OnPause1();
	afx_msg void OnPause2();
	afx_msg void OnPause3();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CreateThreadDLG_H__C5BF7543_D37A_4A78_BEBE_C65E8DC1E67A__INCLUDED_)
