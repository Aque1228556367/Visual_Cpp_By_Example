// FloatEdit.cpp : implementation file
//

#include "stdafx.h"
#include "FloatEditDemo.h"
#include "FloatEdit.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CFloatEdit

CFloatEdit::CFloatEdit()
{
}

CFloatEdit::~CFloatEdit()
{
}


BEGIN_MESSAGE_MAP(CFloatEdit, CEdit)
	//{{AFX_MSG_MAP(CFloatEdit)
	ON_CONTROL_REFLECT(EN_CHANGE, OnChange)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFloatEdit message handlers

int CFloatEdit::GetStringNum(CString str)//����ַ����м�.�ŵĸ���
{
	int nNum=0; 
	while(1)
	{ 
		int nCount=str.Find('.');//����.��
		if(nCount==-1)
		break; 
		str=str.Right(str.GetLength()-nCount-1); //��ȡ.���ұߵ��ַ���
		nNum++;
	} 
	return nNum;
}


void CFloatEdit::OnChange() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CEdit::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	CString m_estr,szTemp;
	GetWindowText(m_estr);//��ȡ�༭���ı�
	int nLen=m_estr.GetLength();//��ȡ�ı�����
	if(!m_estr.IsEmpty())
	{
		szTemp=m_estr.Right(1);
		BOOL bNum=TRUE;
		CString strtemp=szTemp.SpanIncluding("0123456789");
		if(!strtemp.IsEmpty()) //����ַ���Ϊ����
		bNum=TRUE;
		else 
			bNum=FALSE;
		int nPoint=GetStringNum(m_estr);//����.�ŵĸ���
		if(strcmp(szTemp,".")==0 || bNum)
		{
			if(nPoint>1)//.�Ŷ���1��
			{
				nPoint--;
				::AfxMessageBox(".���Ѿ�����!");
				m_estr=m_estr.Left(m_estr.GetLength()-1); //ȥ����ǰ����
				SetWindowText(m_estr); 
				nLen--;
				SendMessage(EM_SETSEL,nLen,nLen);//��������λ��
				return;
			}
		}
		else//�����ַ���Ϊ����
		{
			::AfxMessageBox("���������ֻ�.��");
			m_estr=m_estr.Left(m_estr.GetLength()-1);//ȥ����ǰ����
			SetWindowText(m_estr);
			nLen--;
			SendMessage(EM_SETSEL,nLen,nLen);//��������λ��
			return; 
		}
	} 
}
