// ReadEdit.cpp : implementation file
//

#include "stdafx.h"
#include "ReadEditDemo.h"
#include "ReadEdit.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CReadEdit

CReadEdit::CReadEdit()
{
}

CReadEdit::~CReadEdit()
{
}


BEGIN_MESSAGE_MAP(CReadEdit, CEdit)
	//{{AFX_MSG_MAP(CReadEdit)
	ON_WM_SETFOCUS()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CReadEdit message handlers

void CReadEdit::OnSetFocus(CWnd* pOldWnd) 
{
	pOldWnd->SetFocus();//�����뽹�㷵��ԭ����	
//	CEdit::OnSetFocus(pOldWnd);//��ִ��Ĭ�ϵĴ�����	
}
void CReadEdit::AppendString(CString str)

{
	CString   strBuffer;    // current contents of edit control
  GetWindowText (strBuffer);//��ȡ�༭��ԭ���ı�
  if (!strBuffer.IsEmpty())
     strBuffer += "\r\n";//����
  strBuffer += str;
  SetWindowText (strBuffer);//��ʾ�ı�
  LineScroll (GetLineCount(), 0);//�����༭��
}
