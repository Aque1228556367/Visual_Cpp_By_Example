// DrawLine.cpp: implementation of the CDrawLine class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "BaseDocViewDemo3.h"
#include "DrawLine.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CDrawLine::CDrawLine(CPoint pStar,CPoint pEnd)
{
	m_Star=pStar;
	m_End=pEnd;
}

CDrawLine::~CDrawLine()
{

}
void CDrawLine::Draw(CDC *pDC)
{
	pDC->MoveTo(m_Star.x,m_Star.y);							//��������
	pDC->LineTo(m_End.x,m_End.y);
}

IMPLEMENT_SERIAL(CDrawLine,CObject,1)
CDrawLine::CDrawLine()									//���������Ĺ��캯����ʵ��
{
}

void CDrawLine::Serialize(CArchive &ar)//���л�������ʵ��
{
	 if (ar.IsStoring())										//���д浵����
	{
		// TODO: add storing code here
		ar<<m_Star<<m_End;
	}
	else												//���ж�������
	{
		// TODO: add loading code here
		ar>>m_Star>>m_End;
	}
}
