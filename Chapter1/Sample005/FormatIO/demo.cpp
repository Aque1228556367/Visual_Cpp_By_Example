#include <iostream>
#include <iomanip>
using namespace std;
void main()
{
	char bookname[100];double price;int counts;
	cout << "����������:"<< endl;
	cin>>bookname;
	cout << "�����뵥��:"<< endl;
	cin>>price;
	cout << "��������������:"<< endl;
	cin>>counts;
	cout<<"ʹ��״̬��־�ͳ�Ա�������и�ʽ�����"<<endl;
	cout<<"��"<<bookname<<"����";
	cout.width(5);        								//������ʾ���Ϊ5���ַ�
	cout.fill('*');          								//��Ȳ�����*�ַ����
	cout<<price<<"(����)  ";  									//��������ĸ�ʽ�������
	cout.setf(ios::scientific);   								//�ÿ�ѧ������������۶�
	cout.precision(3);   									//����3λ����
	cout<<price*counts<<"(���۶�)  ";  
	//��ʾ�������������������š������
	cout.setf(ios::showpos|ios::left);
	cout<<counts<<"(��������)"<<endl;


/*cout<<"ʹ�������������и�ʽ���"<<endl;
	cout<<"��"<<bookname<<"����"
	<<setw(5)<<setfill('*')<<price<<"(����)  " 
	<<scientific<<setprecision(3)<<price*counts<<"(���۶�)  "
	<<showpos<<left<<counts<<"(��������)"<<endl;*/
}
