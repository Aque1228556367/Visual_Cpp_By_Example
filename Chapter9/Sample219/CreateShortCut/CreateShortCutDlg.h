// CreateShortCutDlg.h : header file
//

#if !defined(AFX_CREATESHORTCUTDLG_H__F768FF90_F6F4_46B2_B8F5_1107A2CA3608__INCLUDED_)
#define AFX_CREATESHORTCUTDLG_H__F768FF90_F6F4_46B2_B8F5_1107A2CA3608__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


/////////////////////////////////////////////////////////////////////////////
// CCreateShortCutDlg dialog

class CCreateShortCutDlg : public CDialog
{
// Construction
public:
	CCreateShortCutDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CCreateShortCutDlg)
	enum { IDD = IDD_CREATESHORTCUT_DIALOG };
	int		m_radio;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCreateShortCutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;
	
	int nBeginAt;//��ʼ�ļ��е�PIDL	
	BOOL BrowseForFolder(
    LPITEMIDLIST pidlRoot,//�����ʼ����PIDL
    LPITEMIDLIST *ppidlDestination, //�������ʱ��ѡ���PIDL
    LPCSTR lpszTitle);//����Ի����е���ʾ����
	BOOL SelectMenuItem( LPSTR szFileName);//ȡ�ÿ�ݷ�ʽ��Ŀ��Ӧ�ó�����
	BOOL GetShortcutCrt(LPSTR szPath);//ȡ��Ҫ�����Ŀ�ݷ�ʽ������
	//������ݷ�ʽ
	BOOL CreateLink ( 
		LPSTR szPath,//��ݷ�ʽ��Ŀ��Ӧ�ó�����
		LPSTR szLink);//��ݷ�ʽ�������ļ���(*.lnk)
	// ֪ͨshell�йر仯
	void NotifyShell(LONG wEventId,//�¼���־
            LPSTR szPath);//·��
	// Generated message map functions
	//{{AFX_MSG(CCreateShortCutDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnCreate();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CREATESHORTCUTDLG_H__F768FF90_F6F4_46B2_B8F5_1107A2CA3608__INCLUDED_)
