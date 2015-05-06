#include<iostream>
using namespace std;
class CFigure												//����-ͼ����
{
protected:
	double x,y;												//��Ա����
public:
	void SetDim(double i,double j=0.0)						//����ͼ�β���
	{
		x=i;
		y=j;
	}
	virtual void GetShowArea()								//�麯��������ʾ���
	{
		cout<<"�޷��������\n";
	}
};
class CTriangle:public CFigure									//��������
{
public:
	void GetShowArea()												//�����麯��
	{
		cout<<"�����Σ��ױ߳���"<<x<<" �ߣ�"<<y<<" �����"<<x*0.5*y<<endl;
	}
};
class CRect:public CFigure											//������
{
public:
	void GetShowArea()												//�����麯��
	{
		cout<<"���Σ����� "<<x<<" �� "<<y<<" �����"<<x*y<<endl;
	}
};
class CCircle:public CFigure											//Բ����
{
public:
	void GetShowArea()												//�����麯��
	{
		cout<<"Բ�Σ��뾶��"<<x<<" �����"<<3.14159*x*x<<endl;
	}
};

int main()
{
	cout<<"ʹ���麯��ʵ������ʱ��̬"<<endl;
	CFigure *figure;
	CTriangle triangle;													//�����������
	CRect rect;													//���������
	CCircle circle;													//Բ�������
	figure=&triangle;
	figure->SetDim(8.0,5.0);											//���������εĲ���
	figure->GetShowArea();												//������ʾ�����ε����
	figure=&rect;
	figure->SetDim(10.0,5.0);											//���þ��εĲ���
	figure->GetShowArea();												//������ʾ���ε����
	figure=&circle;
	figure->SetDim(10.0);											//����Բ�εĲ���
	figure->GetShowArea();												//������ʾԲ�ε����
	return 0;
}
