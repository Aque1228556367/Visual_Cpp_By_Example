#pragma once
#include "afxwin.h"


// CFilePara �Ի���

class CFilePara : public CDialog
{
	DECLARE_DYNAMIC(CFilePara)

public:
	CFilePara(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CFilePara();

// �Ի�������
	enum { IDD = IDD_FILEPARA };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CStatic m_Outshow;
	int m_Radio1;
	int m_Radio3;
	CButton mb_Radio1;
	//CButton mb_Radio2;
	CButton mb_Radio3;
	CEdit mb_Slice;
	int m_Slice;
	CEdit mb_Polebegin;
	int m_Polebegin;
	CEdit mb_Poleend;
	int m_Poleend;

	int m_Timewindow;//ʱ��
	int m_Samplenum;//������
	int m_Sampleslice;//����������
	int m_Samplepole;//ÿ������Ĳ����


	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg void OnBnClickedRadio1();
	afx_msg void OnBnClickedRadio2();
	afx_msg void OnBnClickedRadio5();
	afx_msg void OnBnClickedRadio6();
protected:
	virtual void OnOK();
};
