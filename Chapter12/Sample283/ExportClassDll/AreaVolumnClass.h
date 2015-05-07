// AreaVolumnClass.h: interface for the AreaVolumnClass class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_AREAVOLUMNCLASS_H__753A6037_F26C_4720_9876_7F43A1A19E87__INCLUDED_)
#define AFX_AREAVOLUMNCLASS_H__753A6037_F26C_4720_9876_7F43A1A19E87__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class _declspec(dllexport) AreaVolumnClass  //����������
{
public:
	AreaVolumnClass();
	virtual ~AreaVolumnClass();
	double GetArea();										//���㳤����ı����
	double GetVolumn();										//���㳤��������
	void SetLenth(double a);									//���ó�����ĳ�
	void SetWidth(double b);									//���ó�����Ŀ�
	void SetHeight(double c);									//���ó�����ĸ�
private:
	double lenth;											//�洢������ĳ�
	double width;											//�洢������Ŀ�
	double height;											//�洢������ĸ�

};

#endif // !defined(AFX_AREAVOLUMNCLASS_H__753A6037_F26C_4720_9876_7F43A1A19E87__INCLUDED_)
