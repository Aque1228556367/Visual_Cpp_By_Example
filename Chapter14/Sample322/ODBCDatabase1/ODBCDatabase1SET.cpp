// ODBCDatabase1Set.cpp : implementation of the CODBCDatabase1Set class
//

#include "stdafx.h"
#include "ODBCDatabase1.h"
#include "ODBCDatabase1Set.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CODBCDatabase1Set implementation

IMPLEMENT_DYNAMIC(CODBCDatabase1Set, CRecordset)

CODBCDatabase1Set::CODBCDatabase1Set(CDatabase* pdb)
	: CRecordset(pdb)
{
	//{{AFX_FIELD_INIT(CODBCDatabase1Set)
	m_Age = _T("");
	m_name = _T("");
	m_sex = _T("");
	m_stuno = _T("");
	m_nFields = 4;
	//}}AFX_FIELD_INIT
	m_nDefaultType = snapshot;
}

CString CODBCDatabase1Set::GetDefaultConnect()
{
	return _T("ODBC;DSN=student");//���ݿ����ڵ�����Դ
}

CString CODBCDatabase1Set::GetDefaultSQL()
{
	return _T("[STUDENT]");//���ݿ��
}

void CODBCDatabase1Set::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CODBCDatabase1Set)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Text(pFX, _T("[����]"), m_Age);
	RFX_Text(pFX, _T("[����]"), m_name);
	RFX_Text(pFX, _T("[�Ա�]"), m_sex);
	RFX_Text(pFX, _T("[ѧ��]"), m_stuno);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// CODBCDatabase1Set diagnostics

#ifdef _DEBUG
void CODBCDatabase1Set::AssertValid() const
{
	CRecordset::AssertValid();
}

void CODBCDatabase1Set::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG
