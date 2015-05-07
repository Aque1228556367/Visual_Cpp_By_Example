// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "TrayIcon.h"
#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMainFrame
#define IDI_NOTIFYICON 100	//����ͼ���ʶ
#define WM_ADDTRAYICON WM_USER+101//�Զ�����Ϣ

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	//{{AFX_MSG_MAP(CMainFrame)
	ON_WM_CREATE()
	ON_WM_CLOSE()
	//}}AFX_MSG_MAP
	ON_MESSAGE(WM_ADDTRAYICON, OnAddTrayIcon)//�����Ϣӳ��
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // status line indicator
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

/////////////////////////////////////////////////////////////////////////////
// CMainFrame construction/destruction

CMainFrame::CMainFrame()
{
	// TODO: add member initialization code here
	flag=false;
	
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP
		| CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}

	if (!m_wndStatusBar.Create(this) ||
		!m_wndStatusBar.SetIndicators(indicators,
		  sizeof(indicators)/sizeof(UINT)))
	{
		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
	}

	// TODO: Delete these three lines if you don't want the toolbar to
	//  be dockable
	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndToolBar);

	NOTIFYICONDATA notifyicondata;//NOTIFYICONDATA�ṹ
	notifyicondata.cbSize = sizeof(NOTIFYICONDATA);//Ϊnotifyicondata�ṹ�����ռ�
	//Ϊnotifyicondata�ṹ�����������ֵ
	notifyicondata.hWnd = m_hWnd;
	notifyicondata.uID = IDI_NOTIFYICON; //ID��ʶ
	notifyicondata.uFlags = NIF_MESSAGE|NIF_ICON|NIF_TIP;
	notifyicondata.uCallbackMessage = WM_ADDTRAYICON;
	notifyicondata.hIcon=AfxGetApp()->LoadIcon(IDI_ICON1);//����ͼ��
    strcpy(notifyicondata.szTip, "Ϊ���򴴽�����ͼ��");
	//װ������ͼ��
	Shell_NotifyIcon(NIM_ADD, &notifyicondata);
	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMainFrame message handlers

LRESULT CMainFrame::OnAddTrayIcon(WPARAM wParam,LPARAM lParam)
{
	
	if (wParam == IDI_NOTIFYICON)//Ϊ����������ͼ��
	{
		switch(lParam)
		{
		case WM_LBUTTONDOWN://�������
			{
				flag = !flag;
				if(flag)
				{
					AfxGetApp()->m_pMainWnd->ShowWindow(SW_HIDE);//���ش���
				}
				else
				{
					AfxGetApp()->m_pMainWnd->ShowWindow(SW_SHOW);//��ʾ����
				}
			break;
			}
		case WM_RBUTTONDBLCLK://˫���Ҽ�
			{
				AfxGetApp()->m_pMainWnd->DestroyWindow();//�رմ���
				break;
			}
		}
	}
	return 1;
}
void CMainFrame::OnClose() 
{
	// TODO: Add your message handler code here and/or call default
	NOTIFYICONDATA notifyicondata;
	notifyicondata.cbSize = sizeof(NOTIFYICONDATA);
	notifyicondata.uFlags = 0;
	notifyicondata.hWnd = m_hWnd;
	notifyicondata.uID = IDI_NOTIFYICON;
	Shell_NotifyIcon(NIM_DELETE, &notifyicondata);//ж������ͼ��
	CFrameWnd::OnClose();
}
