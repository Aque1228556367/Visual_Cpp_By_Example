#include<iostream>
using namespace std;
class CTimeType//����ʱ����
{
	int hour,minute,second;              							//��Ա����
public:
	CTimeType(int h=12,int m=0,int s=0)								//���캯��
	{
		hour=h;
		minute=m;
		second=s;
	}
	void display()												//��Ա���������ʱ��
	{
		cout<<hour<<":"<<minute<<":"<<second<<endl;
	}
	void SetTime(int h,int m,int s)								//��Ա����������ʱ��
	{
		hour=h;
		minute=m;
		second=s;
	}
};
class CDateType//������
{
	int month,day,year;                							//��Ա����
public:
	CDateType(int mon=1,int d=1,int y=2008)							//���캯��
	{
		month=mon;
		day=d;
		year=y;
	}
	void display()											//��Ա�������������
	{
		cout<<month<<"/"<<day<<"/"<<year<<endl;
	}
	void SetDate(int mon,int d,int y)								//��Ա��������������
	{
		month=mon;
		day=d;
		year=y;
	}
};
class CDateTimeType:public CDateType,public CTimeType//ʱ��������
{
public:
	CDateTimeType(int mon=1,int d=1,int y=2000,int h=0,int m=0,int s=0):CDateType(mon,d,y),CTimeType(h,m,s){}								//���캯��
	void display()//��Ա��������ʾʱ�䡢����
	{
		CDateType::display();						//����CDateType���display����
		CTimeType::display();						//����CTimeType���display����
	}
}; 

int main()
{
	cout<<"��Ķ��ؼ̳���ʾ"<<endl;
	CDateTimeType dt(1,1,2008,11,12,12);		//ֱ��ʹ��DateTimeType���캯����������ʱ��
	cout<<"����CDateTimeType�๹�캯���趨�ĳ�ʼ���ڡ�ʱ��Ϊ��"<<endl;
	dt.display();//��ʾʱ������
	dt.SetDate(8,8,2008);						//���û���ĳ�Ա�����޸�����
	dt.SetTime(20,8,8);						//���û���ĳ�Ա�����޸�ʱ��
	cout<<"���û����Ա�����޸ĺ�����ڡ�ʱ��Ϊ��"<<endl;
	dt.display();
	return 0;
}
