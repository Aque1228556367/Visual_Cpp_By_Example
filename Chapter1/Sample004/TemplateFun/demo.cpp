#include <iostream>
#include <string>
using namespace std;
template <class T>											//���庯��ģ��
T Min(T a, T b,T c)
{
	if(a<b)													
		b=a;
	return b<c?b:c;											//����b��c�е�Сֵ
}
int main()													//������
{	
	cout<<"ʹ��ģ�庯����ͬ�������ݵ���Сֵ"<<endl<<endl;
	int i1 = 2, i2 = 6, i3 = 4;
	double d1 = 3.4, d2 = 7.2, d3 = 3.39;
	string  str1("one"), str2("two"),str3("three");
	cout << " int���ͣ�"<<i1<<", "<<i2<<", "<<i3  <<"    ��Сֵ: " << Min(i1, i2, i3) << endl<<endl;					//int�͵����ֵ
	cout << " double���ͣ�" <<d1<<", "<<d2<<", "<<d3 <<"    ��Сֵ:" << Min(d1, d2, d3) << endl<<endl;				//double�͵����ֵ
	cout << " string���ͣ�" <<str1<<", "<<str2<<", "<<str3 <<"    ��Сֵ:"<< Min(str1, str2, str3) << endl<<endl;			//string�͵����ֵ
	return 0;
}
