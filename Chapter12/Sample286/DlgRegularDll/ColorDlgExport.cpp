#include "StdAfx.h"
#include "DlgRegularDll.h"
#include "ColoarDlg.h"
extern "C" _declspec(dllexport)ShowDlg(int m_r,int m_g,int m_b)	//��������
{  
	AFX_MANAGE_STATE(AfxGetStaticModuleState());				//��ȡDLLģ��״̬
	CColoarDlg dlg;											//�����Ի������
	dlg.m_Red=m_r;										//���Ի���ؼ�������ֵ
	dlg.m_Green=m_g;										//���Ի���ؼ�������ֵ
	dlg.m_Blue=m_b;										//���Ի���ؼ�������ֵ
	dlg.DoModal();						//����ģ̬�Ի���
}
