#include <iostream.h>
class CComplex												//���帴����
{	
	double m_fReal, m_fImag;//��Ա����
public:
	CComplex(double r = 0, double i = 0): m_fReal(r), m_fImag(i){}			//���캯��
	double GetReal(){return m_fReal;}//��Ա���������ظ�����ʵ��
	double GetImag(){return m_fImag;}//��Ա���������ظ������鲿
	CComplex operator +(CComplex&);							//�����������
	CComplex operator +(double);								//�����������
}; 
CComplex CComplex::operator + (CComplex &c)				//�������������ʵ�����������ļӷ�
{	
	CComplex temp;
	temp.m_fReal = m_fReal+c.m_fReal;
	temp.m_fImag = m_fImag+c.m_fImag;
	return temp;
}
CComplex CComplex::operator + (double d)				//�������������ʵ�ָ�����ʵ���ļӷ�
{	
	CComplex temp;
	temp.m_fReal = m_fReal+d;
	temp.m_fImag = m_fImag;
	return temp;
}

void main()//������
{
	CComplex c1(2.3,5.5),c2(3.6,6.8),c3;//���������
	cout << "ʹ�����ص�+�����ʵ�ָ����븴�������" << endl;
	cout << "C1 = " << c1.GetReal() << "+j" << c1.GetImag() << endl;
	cout << "C2 = " << c2.GetReal() << "+j" << c2.GetImag() << endl;
	c3 = c1+c2;
	cout << "C3 = C1 + C2 =" << c3.GetReal() << "+j" << c3.GetImag() << endl;
	cout << "ʹ�����ص�+�����ʵ�ָ�����ʵ�������" << endl;
	c3 = c3+6.5;
	cout << "C3 + 6.5 = " << c3.GetReal() << "+j" << c3.GetImag() << endl;
}
