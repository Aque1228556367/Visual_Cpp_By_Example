// calculate.cpp: implementation of the calculate class.
//
//////////////////////////////////////////////////////////////////////

#include "calculate.h"
float floatcalculate(float x,float y, int type)
{
	switch (type)
	{
	case 0:											//�ӷ�����
		{return x+y;}
	case 1:											//��������
		{return x-y;}
	case 2:											//�˷�����
		{return x*y;}
	case 3:											//��������
		{return x/y;}			
	}
}

