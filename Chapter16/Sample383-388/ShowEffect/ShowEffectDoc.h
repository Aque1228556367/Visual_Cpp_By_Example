// ShowEffectDoc.h : interface of the CShowEffectDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_SHOWEFFECTDOC_H__E592659D_4D62_4C1F_B391_E6602C31BD0C__INCLUDED_)
#define AFX_SHOWEFFECTDOC_H__E592659D_4D62_4C1F_B391_E6602C31BD0C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "Dib.h"
extern  m_dib;									//����һ�����õ��ⲿ��Ա����


class CShowEffectDoc : public CDocument
{
protected: // create from serialization only
	CShowEffectDoc();
	DECLARE_DYNCREATE(CShowEffectDoc)

// Attributes
public:
	CDib m_dib;								//����һ��Dib����
// Operations
public:
	HGLOBAL GetHObject() const					//��ȡDib����ľ��
		{ return m_hDIB; }
	CPalette* GetDocPal() const						//��ȡ��ɫ��ָ��
		{ return m_palDIB; }
	void UpdateObject(HGLOBAL hDIB);				//����dib����
	void SetDib();								//��ʼ��dib����

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CShowEffectDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	virtual BOOL OnOpenDocument(LPCTSTR lpszPathName);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CShowEffectDoc();

#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	HGLOBAL m_hDIB;							//����ָ��DIB�ľ������
	CPalette* m_palDIB;							//����ָ���߼���ɫ���ָ��
	CSize m_sizeDoc;							//�ĵ���С�ı���


// Generated message map functions
protected:
	//{{AFX_MSG(CShowEffectDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SHOWEFFECTDOC_H__E592659D_4D62_4C1F_B391_E6602C31BD0C__INCLUDED_)
