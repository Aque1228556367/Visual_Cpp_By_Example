// RullerSplliterWnd.cpp : implementation file
//

#include "stdafx.h"
#include "RadarDataShow.h"
#include "RullerSplliterWnd.h"

#include "RulerView.h"
#include "CornerView.h"
#include "AscanView.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRullerSplliterWnd
IMPLEMENT_DYNCREATE(CRullerSplliterWnd, CMDIChildWnd)
CRullerSplliterWnd::CRullerSplliterWnd()
{
	m_cxSplitter     = 0;
	m_cySplitter     = 0;
	m_cxBorderShare  = 0;
	m_cyBorderShare  = 0;
	m_cxSplitterGap  = 1;
	m_cySplitterGap  = 1;

}

CRullerSplliterWnd::~CRullerSplliterWnd()
{
}


BEGIN_MESSAGE_MAP(CRullerSplliterWnd, CSplitterWnd)
	//{{AFX_MSG_MAP(CRullerSplliterWnd)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CRullerSplliterWnd message handlers
BOOL CRullerSplliterWnd::CreateRulers(CFrameWnd *pParent, CCreateContext *pContext)
{
	if (!CreateStatic(pParent, 2, 3))	//��������			
		return FALSE;																																	
	if (!CreateView(0, 0, RUNTIME_CLASS(CCornerView), CSize(0,0), pContext))//���Ͻ���ͼ				
		return FALSE;
	if (!CreateView(0, 2, RUNTIME_CLASS(CCornerView), CSize(0,0), pContext))//���Ͻ���ͼ				
		return FALSE;
	if (!CreateView(0, 1, RUNTIME_CLASS(CRulerView), CSize(0,0), pContext))	//ˮƽ�����ͼ				
		return FALSE;														
	if (!CreateView(1, 0, RUNTIME_CLASS(CRulerView), CSize(0,0), pContext))//��ֱ�����ͼ					
		return FALSE;														
	if (!CreateView(1, 1, pContext->m_pNewViewClass, CSize(0,0),pContext))	//ͼ����ͼ				
		return FALSE;														
	if (!CreateView(1, 2, RUNTIME_CLASS(CAscanView), CSize(0,0), pContext))	//������ͼ				
		return FALSE;																		
	SetColumnInfo(0, 0, 0);	
	SetColumnInfo(1, 0, 0);	
	SetRowInfo(0, 0, 0);																							
	((CRulerView*)GetPane(0, 1))->SetRulerType(RT_HORIZONTAL);//ָ��ˮƽ���										
	((CRulerView*)GetPane(1, 0))->SetRulerType(RT_VERTICAL);//ָ����ֱ���   
    SetActivePane(1, 1);	 //��ͼ�񴰸�����Ϊ���ͼ  
    return TRUE;
}

void CRullerSplliterWnd::ShowRulers()
{
	int nSize       = 16;//��ߴ���ĳߴ�
    int nSizeBorder = 3;//�ָ����ߴ�

    SetRowInfo(0, nSize, 0);//ˮƽ��ߴ���߶�
    SetColumnInfo(0, nSize, 0);//��ֱ��ߴ�����
	SetColumnInfo(1,(GetSystemMetrics(SM_CXSCREEN)-128), 0);//����ͼ����ʾ���ڳߴ�	
    m_cxSplitterGap  = nSizeBorder;//�ָ����ߴ�
	m_cySplitterGap  = nSizeBorder;
    RecalcLayout();//�������д���
}

void CRullerSplliterWnd::UpdateRulersInfo(stRULER_INFO stRulerInfo)
{

	((CRulerView*)GetPane(0, 1))->UpdateRulersInfo(stRulerInfo);//����ˮƽ���
	((CRulerView*)GetPane(1, 0))->UpdateRulersInfo(stRulerInfo);//���´�ֱ���
}
