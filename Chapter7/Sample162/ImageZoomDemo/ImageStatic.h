#if !defined(AFX_IMAGESTATIC_H__E0AFA2DD_2E70_4C80_965F_3D9C30422C68__INCLUDED_)
#define AFX_IMAGESTATIC_H__E0AFA2DD_2E70_4C80_965F_3D9C30422C68__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ImageStatic.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CImageStatic window

class CImageStatic : public CStatic
{
// Construction
public:
	CImageStatic();
	void SetImage(UINT resID);//����λͼ
	void SetType(int nType);//������������
protected:
	CBitmap m_bmp;//λͼ����
	int m_Type;//��������
// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CImageStatic)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CImageStatic();

	// Generated message map functions
protected:
	//{{AFX_MSG(CImageStatic)
	afx_msg void OnPaint();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_IMAGESTATIC_H__E0AFA2DD_2E70_4C80_965F_3D9C30422C68__INCLUDED_)
