#include <iostream.h>
void binary(int number) //ת��Ϊ���������
{
   int remainder;//����
   if(number <= 1) 
   {
      cout << number;
      return;
   }
   remainder = number%2;//������
   binary(number >> 1);    //�ݹ����
   cout << remainder;
}
void main(void) //������
{
   int number;
   cout << "������һ��������: ";
   cin >> number;
   if (number < 0) 
      cout << "�������\n";
   else 
   {
      cout << number << "ת��Ϊ������Ϊ: ";
      binary(number);//ת��Ϊ���������
      cout << endl;
   }
}

