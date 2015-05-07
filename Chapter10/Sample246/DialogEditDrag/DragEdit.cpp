// DragEdit.cpp : implementation file
//

#include "stdafx.h"
#include "DialogEditDrag.h"
#include "DragEdit.h"

//#include <sys/types.h>
//#include <sys/stat.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDragEdit

CDragEdit::CDragEdit()
{
}

CDragEdit::~CDragEdit()
{
}


BEGIN_MESSAGE_MAP(CDragEdit, CEdit)
	//{{AFX_MSG_MAP(CDragEdit)
	ON_WM_CREATE()
	ON_WM_DROPFILES()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDragEdit message handlers

int CDragEdit::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CEdit::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// TODO: Add your specialized creation code here
	DragAcceptFiles(TRUE);//�����Ϸ��ļ�����
	return 0;
}

void CDragEdit::OnDropFiles(HDROP hDropInfo) 
{
	// TODO: Add your message handler code here and/or call default
	WORD wNumFilesDropped = DragQueryFile(hDropInfo, -1, NULL, 0);//ͬʱ�Ϸ��ļ�����Ŀ
	CString firstFile="";
	for (WORD x = 0 ; x < wNumFilesDropped; x++) //ֻ��¼��һ���϶����ļ�
	{
		WORD wPathnameSize = DragQueryFile(hDropInfo, x, NULL, 0);
		char * npszFile = (char *) LocalAlloc(LPTR, wPathnameSize += 1);//�����ڴ�
		if (npszFile == NULL) 
			continue;
		DragQueryFile(hDropInfo, x, npszFile, wPathnameSize);//��ȡ�Ϸŵ��ļ���
		if (firstFile=="")
			firstFile=npszFile;//��¼�ļ���
		LocalFree(npszFile);//�ͷ��ڴ�
	}
	DragFinish(hDropInfo);//�ϷŽ���
	SetWindowText(firstFile);//�༭����ʾ
//	CEdit::OnDropFiles(hDropInfo);
}
