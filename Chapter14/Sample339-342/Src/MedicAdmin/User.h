// User.h: interface for the CUser class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_USER_H__BA485565_5FF5_4E8E_A6EF_21BADF0E3D2F__INCLUDED_)
#define AFX_USER_H__BA485565_5FF5_4E8E_A6EF_21BADF0E3D2F__INCLUDED_

#include "userSet.h"

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CUser  
{
public:
	void ModifyPassword(CUserSet* theSet);//�޸��û����룬����CUserSet��ĳ�Ա�����ͳ�Ա����
	CString GetPassword();								//�õ��û�����
	CString GetAccount();									//�õ��û��˺�
	void SetPassword(CString password);						//�����û�����
	CString GetType();									//�õ��û����
	void SeekUserInfo(int typeRadio,CString str,CUserSet* theSet);	//��ѯ�û���Ϣ
	void SetAccount(CString account);						//�����û��˺�
	void DeleteUser(CUser* user,CUserSet* userSet);				//ɾ��ָ���û�
	BOOL AddNewUser(CUser* newUser,CUserSet* theSet);		//�����û�
	void SetAllMember(CString account,CString password,CString type,CString name);//��ʼ���û�
	BOOL LogIn(CUserSet*);	//�û���¼�����������Ϣ�����ݿ��е���Ϣ�Ƚϣ���һ������������ϵͳ�������ܽ����ϵͳ
	CUser();
	virtual ~CUser();
protected:
	CString m_userAccount;								//�û��ʺ�
	CString m_userPassword;								//�û�����
	CString m_userName;									//�û�����
	CString m_userType;									//�û����
};


#endif // !defined(AFX_USER_H__BA485565_5FF5_4E8E_A6EF_21BADF0E3D2F__INCLUDED_)
