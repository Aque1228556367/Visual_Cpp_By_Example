// AreaVolumnClass.cpp: implementation of the AreaVolumnClass class.
//
//////////////////////////////////////////////////////////////////////

#include "AreaVolumnClass.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

AreaVolumnClass::AreaVolumnClass()
{
	height=lenth=width=0.0;//��ʼ��
}

AreaVolumnClass::~AreaVolumnClass()
{

}
double AreaVolumnClass::GetArea()										//��������
{
	return 2*(height*lenth+height*width+width*lenth);
}
double AreaVolumnClass::GetVolumn()									//�������
{
	return height*lenth*width;
}
void AreaVolumnClass::SetLenth(double a)								//���ó�
{
	lenth=a;
}
void AreaVolumnClass::SetHeight(double c)								//���ø�
{
	height=c;
}
void AreaVolumnClass::SetWidth(double b)								//���ÿ�
{
	width=b;
}
