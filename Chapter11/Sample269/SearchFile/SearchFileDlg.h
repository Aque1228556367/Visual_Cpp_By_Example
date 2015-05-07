// SearchFileDlg.h : header file
//

#if !defined(AFX_SearchFileDLG_H__9D9022A8_A0F3_4116_9949_B36DF0269578__INCLUDED_)
#define AFX_SearchFileDLG_H__9D9022A8_A0F3_4116_9949_B36DF0269578__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CSearchFileDlg dialog
extern UINT SearchFileThread(LPVOID pParam);//�����߳���ں���
typedef struct THREADPARAM //�̲߳����ṹ��
{
	CString strPath;							//·����
	CString strFileName;						//�ļ���
	CListBox *m_pListInfo;						//�б�����
	HWND	hwnd;											//���ھ��
}MyTHREADPARAM;

class CSearchFileDlg : public CDialog
{
// Construction
public:
	CSearchFileDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CSearchFileDlg)
	enum { IDD = IDD_SearchFile_DIALOG };
	CListBox	m_ctrList;
	CString	m_FileName;
	CString	m_strPath;
	CString	m_status;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSearchFileDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CSearchFileDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnButtonFind();
	afx_msg void OnButtonView();
	afx_msg void OnMsg();//��Ϣ��Ӧ����
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SearchFileDLG_H__9D9022A8_A0F3_4116_9949_B36DF0269578__INCLUDED_)
