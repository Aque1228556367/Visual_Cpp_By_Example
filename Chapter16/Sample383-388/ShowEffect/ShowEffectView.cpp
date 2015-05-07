// ShowEffectView.cpp : implementation of the CShowEffectView class
//

#include "stdafx.h"
#include "ShowEffect.h"

#include "ShowEffectDoc.h"
#include "ShowEffectView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CShowEffectView

IMPLEMENT_DYNCREATE(CShowEffectView, CView)

BEGIN_MESSAGE_MAP(CShowEffectView, CView)
	//{{AFX_MSG_MAP(CShowEffectView)
	ON_COMMAND(ID_BLOCK, OnBlock)
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
	ON_COMMAND_RANGE(ID_LTOR, ID_BTOT, OnImageScan)//��Ϣӳ���
	ON_COMMAND_RANGE(ID_LEFT, ID_BOTTOM, OnImageMove)//��Ϣӳ���
	ON_COMMAND_RANGE(ID_HOR, ID_VER, OnImageJalousie)//��Ϣӳ���
	ON_COMMAND_RANGE(ID_GRID_HOR, ID_GRID_VER, OnImageGrid)//��Ϣӳ���
	ON_COMMAND_RANGE(ID_EXTEND_VER, ID_SHRINK_HOR, OnImageStunt)//��Ϣӳ���
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CShowEffectView construction/destruction

CShowEffectView::CShowEffectView()
{
	// TODO: add construction code here

}

CShowEffectView::~CShowEffectView()
{
}

BOOL CShowEffectView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CShowEffectView drawing

void CShowEffectView::OnDraw(CDC* pDC)
{
	CShowEffectDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
	HGLOBAL hDIB = pDoc->GetHObject();	
	if (hDIB != NULL)							   		// �ж�DIB�Ƿ�Ϊ��
	{
		LPSTR lpDibSection = (LPSTR) ::GlobalLock(hDIB);				
		int cxDIB = (int) pDoc->m_dib.GetWidth(lpDibSection);			// ��ȡDIB���	
		int cyDIB = (int) pDoc->m_dib.GetHeight(lpDibSection);			// ��ȡDIB�߶�
		::GlobalUnlock(hDIB);		
		CRect rcDIB;
		rcDIB.top = rcDIB.left = 0;
		rcDIB.right = cxDIB;
		rcDIB.bottom = cyDIB;		
		CRect rcDest= rcDIB;	
		// �ػ�DIB
		pDoc->m_dib.DrawDib(pDC->m_hDC, &rcDest, pDoc->GetHObject(),&rcDIB, pDoc->GetDocPal());                                               
	}
	else
	{
		pDC->TextOut(20,20,"ͨ���ļ��˵��ȴ�BMPͼ�񣬶���Ϳ���ͨ��ɨ����Ч�˵����������Ч��ʾ");
	}

}

/////////////////////////////////////////////////////////////////////////////
// CShowEffectView printing

BOOL CShowEffectView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CShowEffectView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CShowEffectView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CShowEffectView diagnostics

#ifdef _DEBUG
void CShowEffectView::AssertValid() const
{
	CView::AssertValid();
}

void CShowEffectView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CShowEffectDoc* CShowEffectView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CShowEffectDoc)));
	return (CShowEffectDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CShowEffectView message handlers
void CShowEffectView::OnImageScan(UINT nID)
{
	CShowEffectDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	SetCursor(LoadCursor(NULL, IDC_WAIT));			//�����ʾΪ����״̬
	long	lSrcWidth;								//ͼ��Ŀ�Ⱥ͸߶�
	long	lSrcHeight;
	LPSTR	lpSrcDib;							//ָ��Դͼ���ָ��	
	LPSTR   lpDstDib;
	LPSTR lpSrcStartBits;
	lpSrcDib= (LPSTR) ::GlobalLock((HGLOBAL) pDoc->GetHObject());// ����DIB
	lSrcWidth= pDoc->m_dib.GetWidth(lpSrcDib);		// ��ȡͼ��Ŀ��		
	lSrcHeight= pDoc->m_dib.GetHeight(lpSrcDib);		// ��ȡͼ��ĸ߶�
	lpSrcStartBits=pDoc->m_dib.GetBits(lpSrcDib);		// �ҵ�DIBͼ��������ʼλ��
	LPBITMAPINFO lpbmi;						// ָ��BITMAPINFO�ṹ��ָ��
	// �����ڴ�
	HGLOBAL hDIB = (HGLOBAL) ::GlobalAlloc(GHND, lSrcWidth*lSrcHeight);
	if (hDIB == NULL)							// �ж��Ƿ�����Ч��DIB����
	{		
		return;								// ���ǣ��򷵻�
	}		
	lpDstDib=  (char * )::GlobalLock((HGLOBAL) hDIB);// �����ڴ�
	memcpy(lpDstDib, lpSrcDib, lSrcWidth*lSrcHeight);	// ����DIB����
	lpbmi = (LPBITMAPINFO)lpDstDib;				// ��ȡָ��
	CDC *pDC=GetDC();							//��ȡ�ӵĿͻ���
	CRect rect(0,0,lSrcWidth,lSrcHeight);
	CBrush brush(RGB(200,200,200));				//������ˢ
	pDC->FillRect(&rect,&brush);					//�ؼ���ʾǰ�����ͻ�������
	CPalette * pPal=new CPalette;					// �����µ�ɫ��
	pDoc->m_dib.ConstructPalette(pDoc->m_dib.m_hDib,pPal);
    CPalette * pOldPal=pDC->SelectPalette(pPal, TRUE);	//���߼���ɫ��ѡΪ��ǰ��ɫ��
    pDC->RealizePalette();							//ʵ�ֵ�ɫ��
	int i=0,j=0,k=0;								//����һЩѭ������
	int nScanLine=2;								//�趨դ���ؼ�ʱ�Ķ�λ��
	switch(nID)								//�жϵ�ǰ�Ĳ˵�����
	{
		case ID_TTOB:					//���϶���
			for(j=0;j<=lSrcHeight;j++)
			{
				for(i=0;i<=lSrcWidth;i++)
				{
					::StretchDIBits(pDC->GetSafeHdc(),i,0,1,j,
						i,lSrcHeight-j,1,j,
						lpSrcStartBits, lpbmi,
						DIB_RGB_COLORS, SRCCOPY); 	 
				}
				//ÿ��ʾһ����ͣ2����
				Sleep(2);				
			}
		pDC->SelectPalette(pOldPal, TRUE);			//�ָ�ԭ��ɫ��
        ::DeleteObject(pPal);						//ɾ���½��ĵ�ɫ�����
		break;
		
		case ID_BTOT:					//���¶���
			for(j=0;j<=lSrcHeight;j++)
			{
				for(i=0;i<=lSrcWidth;i++)
				{
					::StretchDIBits(pDC->GetSafeHdc(),i,lSrcHeight-j,1,j,
						i,0,1,j,
						lpSrcStartBits, lpbmi,
						DIB_RGB_COLORS, SRCCOPY); 	 
				}
		//ÿ��ʾһ����ͣ2����
				Sleep(2);				
			}
		pDC->SelectPalette(pOldPal, TRUE);			//�ָ�ԭ��ɫ��
        ::DeleteObject(pPal);						//ɾ���½��ĵ�ɫ�����
		break;
	
		case ID_LTOR:						//��������
			for(i=0;i<lSrcWidth;i++)
			{
				::StretchDIBits(pDC->GetSafeHdc(),   i, 0, 1, lSrcHeight,
					i,  0, 1, lSrcHeight,
					lpSrcStartBits, lpbmi,
					DIB_RGB_COLORS, SRCCOPY);
				//ÿ��ʾһ����ͣ3����
			Sleep(3); 					
			}
            pDC->SelectPalette(pOldPal, TRUE);		//�ָ�ԭ��ɫ��
           ::DeleteObject(pPal);					//ɾ���½��ĵ�ɫ�����
			break;
		case ID_RTOL:				 		//��������
			for(i=0;i<lSrcWidth;i++)
			{
				::StretchDIBits(pDC->GetSafeHdc(),  lSrcWidth-i, 0, 1, lSrcHeight,
					lSrcWidth-i,  0, 1, lSrcHeight,
					lpSrcStartBits, lpbmi,
					DIB_RGB_COLORS, SRCCOPY);
				//ÿ��ʾһ����ͣ3����
					Sleep(3); 					
			}
			pDC->SelectPalette(pOldPal, TRUE);
			::DeleteObject(pPal);
			break;
		default :							//û�д������Ϣ����
			AfxMessageBox("��ɨ��Ч����");//������ʾ
			break;
	}
	Invalidate();								//ˢ�¿ͻ���
	SetCursor(LoadCursor(NULL, IDC_ARROW));		//�ָ����ԭʼ״̬
}

void CShowEffectView::OnImageMove(UINT nID)
{
	CShowEffectDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	SetCursor(LoadCursor(NULL, IDC_WAIT));					//�����ʾΪ����״̬
	long	lSrcWidth;										//ͼ��Ŀ�Ⱥ͸߶�
	long	lSrcHeight;
	LPSTR	lpSrcDib;							//ָ��Դͼ���ָ��	
	LPSTR   lpDstDib;
	LPSTR lpSrcStartBits;
	lpSrcDib= (LPSTR) ::GlobalLock((HGLOBAL) pDoc->GetHObject());// ����DIB
	lSrcWidth= pDoc->m_dib.GetWidth(lpSrcDib);		// ��ȡͼ��Ŀ��		
	lSrcHeight= pDoc->m_dib.GetHeight(lpSrcDib);		// ��ȡͼ��ĸ߶�
	lpSrcStartBits=pDoc->m_dib.GetBits(lpSrcDib);		// �ҵ�DIBͼ��������ʼλ��
	LPBITMAPINFO lpbmi;						// ָ��BITMAPINFO�ṹ��ָ��
	// �����ڴ�
	HGLOBAL hDIB = (HGLOBAL) ::GlobalAlloc(GHND, lSrcWidth*lSrcHeight);
	if (hDIB == NULL)							// �ж��Ƿ�����Ч��DIB����
	{		
		return;
	}		
	lpDstDib=  (char * )::GlobalLock((HGLOBAL) hDIB);// �����ڴ�
	memcpy(lpDstDib, lpSrcDib, lSrcWidth*lSrcHeight);	// ����DIB����
	lpbmi = (LPBITMAPINFO)lpDstDib;				// ��ȡָ��
	CDC *pDC=GetDC();							//��ȡ�ӵĿͻ���
	CRect rect(0,0,lSrcWidth,lSrcHeight);
	CBrush brush(RGB(200,200,200));				//������ˢ
	pDC->FillRect(&rect,&brush);					//�ؼ���ʾǰ�����ͻ�������
	CPalette * pPal=new CPalette;					// �����µ�ɫ��
	pDoc->m_dib.ConstructPalette(pDoc->m_dib.m_hDib,pPal);
    CPalette * pOldPal=pDC->SelectPalette(pPal, TRUE);	//���߼���ɫ��ѡΪ��ǰ��ɫ��
    pDC->RealizePalette();							//ʵ�ֵ�ɫ��
	int i=0,j=0,k=0;								//����һЩѭ������
	int nScanLine=2;								//�趨դ���ؼ�ʱ�Ķ�λ��
	switch(nID)								//�жϵ�ǰ�Ĳ˵�����
	{
		case ID_LEFT:					//������ƶ�����
			for(i=0;i<=lSrcWidth;i++)
			{
				for(j=0;j<=lSrcHeight;j=j+8)
				{
					::StretchDIBits(pDC->GetSafeHdc(),0,  j-8 ,  i+1, 8,
						lSrcWidth-i, lSrcHeight-j, i+1, 8,
						lpSrcStartBits, lpbmi,
						DIB_RGB_COLORS, SRCCOPY); 	 
				}
				Sleep(2); 					
			}
            pDC->SelectPalette(pOldPal, TRUE);		//�ָ�ԭ��ɫ��
        	::DeleteObject(pPal);					//ɾ���½��ĵ�ɫ�����
			break;
		case ID_BOTTOM:						//�ӵײ��ƶ�����
			for(i=0;i<=lSrcHeight;i++)
			{
				for(j=0;j<=lSrcWidth;j=j++)
				{
					::StretchDIBits(pDC->GetSafeHdc(), j ,  lSrcHeight-i , 1, i  ,
						j , lSrcHeight-i , 1, i ,
						lpSrcStartBits, lpbmi,
						DIB_RGB_COLORS, SRCCOPY); 
				}		
				Sleep(2); 					
			}
			pDC->SelectPalette(pOldPal, TRUE);		//�ָ�ԭ��ɫ��
        	::DeleteObject(pPal);					//ɾ���½��ĵ�ɫ�����
			break;
		case ID_RIGHT:					//ˮƽ�������
			for(i=0;i<=lSrcWidth;i++)
			{
				for(j=0;j<=lSrcHeight;j++)
				{
					::StretchDIBits(pDC->GetSafeHdc(),lSrcWidth-i,j,i,1,
						0,lSrcHeight-j,i,1,
						lpSrcStartBits, lpbmi,
						DIB_RGB_COLORS, SRCCOPY); 	 
				}
				Sleep(2); 					
			}
			pDC->SelectPalette(pOldPal, TRUE);		//�ָ�ԭ��ɫ��
        	::DeleteObject(pPal);					//ɾ���½��ĵ�ɫ�����
			break;
		case ID_TOP:					//�Ӷ����ƶ�����
			for(i=0;i<=lSrcHeight;i++)
			{
				{
					::StretchDIBits(pDC->GetSafeHdc(),0,0,lSrcWidth,i,
						0,0,lSrcWidth,i,
						lpSrcStartBits,lpbmi,
						DIB_RGB_COLORS,SRCCOPY); 
				}
				Sleep(2); 					
			}
			pDC->SelectPalette(pOldPal, TRUE);		//�ָ�ԭ��ɫ��
        	  	::DeleteObject(pPal);					//ɾ���½��ĵ�ɫ�����
			break;
	}
	Invalidate();								//ˢ�¿ͻ���
	SetCursor(LoadCursor(NULL, IDC_ARROW));		//�ָ����ԭʼ״̬
}

void CShowEffectView::OnBlock() 
{
	// TODO: Add your command handler code here
	CShowEffectDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	SetCursor(LoadCursor(NULL, IDC_WAIT));					//�����ʾΪ����״̬
	long	lSrcWidth;										//ͼ��Ŀ�Ⱥ͸߶�
	long	lSrcHeight;
	LPSTR	lpSrcDib;									//ָ��Դͼ���ָ��	
	LPSTR   lpDstDib;
	LPSTR lpSrcStartBits;
	lpSrcDib= (LPSTR) ::GlobalLock((HGLOBAL) pDoc->GetHObject());// ����DIB
	lSrcWidth= pDoc->m_dib.GetWidth(lpSrcDib);		// ��ȡͼ��Ŀ��		
	lSrcHeight= pDoc->m_dib.GetHeight(lpSrcDib);		// ��ȡͼ��ĸ߶�
	lpSrcStartBits=pDoc->m_dib.GetBits(lpSrcDib);		// �ҵ�DIBͼ��������ʼλ��
	LPBITMAPINFO lpbmi;						// ָ��BITMAPINFO�ṹ��ָ��
	// �����ڴ�
	HGLOBAL hDIB = (HGLOBAL) ::GlobalAlloc(GHND, lSrcWidth*lSrcHeight);
	if (hDIB == NULL)							// �ж��Ƿ�����Ч��DIB����
	{		
		return;
	}		
	lpDstDib=  (char * )::GlobalLock((HGLOBAL) hDIB);// �����ڴ�
	memcpy(lpDstDib, lpSrcDib, lSrcWidth*lSrcHeight);	// ����DIB����
	lpbmi = (LPBITMAPINFO)lpDstDib;				// ��ȡָ��
	CDC *pDC=GetDC();							//��ȡ�ӵĿͻ���
	CRect rect(0,0,lSrcWidth,lSrcHeight);
	CBrush brush(RGB(200,200,200));				//������ˢ
	pDC->FillRect(&rect,&brush);					//�ؼ���ʾǰ�����ͻ�������
	CPalette * pPal=new CPalette;					// �����µ�ɫ��
	pDoc->m_dib.ConstructPalette(pDoc->m_dib.m_hDib,pPal);
    CPalette * pOldPal=pDC->SelectPalette(pPal, TRUE);	//���߼���ɫ��ѡΪ��ǰ��ɫ��
    pDC->RealizePalette();							//ʵ�ֵ�ɫ��
	int i=0,j=0,k=0;								//����һЩѭ������
	long lBlockX,lBlockY;					//������
	int nrw,nrh,nBlockNum; 				//�����������
	lBlockX=lBlockY=nrw=nrh=nBlockNum=0;
	//���С40�������ܷ�Ϊ������ʱ�������µ���Ϊһ��
	if((lSrcWidth%40)!=0)	
	{
		nrw=1;
	}
	if((lSrcHeight%40)!=0)
	{
		nrh=1;
	}
	long lBlockNum;						//�ܿ���
	lBlockNum=(lSrcWidth/20+nrw)*(lSrcHeight/20+nrh);
	POINT* pPoint;						//������¼ÿ����׵�ַ
	pPoint=new POINT[lBlockNum];
	for(nBlockNum=0;nBlockNum<lBlockNum;nBlockNum++)
	{								//��ɿ��׵�ַ����ĸ�ֵ
		pPoint[nBlockNum].x=lBlockX;
		pPoint[nBlockNum].y=lBlockY;
		lBlockX=lBlockX+40;
		if(lBlockX>lSrcWidth)
		{
			lBlockX=0;
			lBlockY=lBlockY+40;
		}
	}
	for(i=0;i<=1;i++)//ѭ������
	{
		for(nBlockNum=lBlockNum-1;nBlockNum>=0;nBlockNum--)
		{	//�����ʾ��kΪ�����������ָʾ�����ʾ���ؿ��˳��
			k=(int)((double)lBlockNum*rand()/RAND_MAX);
			lBlockX=pPoint[k].x;			//��ȡ������
			lBlockY=pPoint[k].y;
			::StretchDIBits(pDC->GetSafeHdc(),lBlockX, lBlockY, 40,40,
						lBlockX,lSrcHeight-lBlockY-40, 40,40,
						lpSrcStartBits, lpbmi,
						DIB_RGB_COLORS, SRCCOPY);
			pPoint[k].x=pPoint[nBlockNum].x;
			pPoint[k].y=pPoint[nBlockNum].y;
			Sleep(5);								
		}
	
	}
	pDC->SelectPalette(pOldPal, TRUE);		//�ָ�ԭ��ɫ��
    ::DeleteObject(pPal);					//ɾ���½��ĵ�ɫ�����
	delete[] pPoint;						//ɾ����ʱ���� 
	Invalidate();								//ˢ�¿ͻ���
	SetCursor(LoadCursor(NULL, IDC_ARROW));		//�ָ����ԭʼ״̬
}


void CShowEffectView::OnImageJalousie(UINT nID)//��Ҷ����Ч
{
	CShowEffectDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	SetCursor(LoadCursor(NULL, IDC_WAIT));					//�����ʾΪ����״̬
	long	lSrcWidth;										//ͼ��Ŀ�Ⱥ͸߶�
	long	lSrcHeight;
	LPSTR	lpSrcDib;							//ָ��Դͼ���ָ��	
	LPSTR   lpDstDib;
	LPSTR lpSrcStartBits;
	lpSrcDib= (LPSTR) ::GlobalLock((HGLOBAL) pDoc->GetHObject());// ����DIB
	lSrcWidth= pDoc->m_dib.GetWidth(lpSrcDib);		// ��ȡͼ��Ŀ��		
	lSrcHeight= pDoc->m_dib.GetHeight(lpSrcDib);		// ��ȡͼ��ĸ߶�
	lpSrcStartBits=pDoc->m_dib.GetBits(lpSrcDib);		// �ҵ�DIBͼ��������ʼλ��
	LPBITMAPINFO lpbmi;						// ָ��BITMAPINFO�ṹ��ָ��
	// �����ڴ�
	HGLOBAL hDIB = (HGLOBAL) ::GlobalAlloc(GHND, lSrcWidth*lSrcHeight);
	if (hDIB == NULL)							// �ж��Ƿ�����Ч��DIB����
	{		
		return;
	}		
	lpDstDib=  (char * )::GlobalLock((HGLOBAL) hDIB);// �����ڴ�
	memcpy(lpDstDib, lpSrcDib, lSrcWidth*lSrcHeight);	// ����DIB����
	lpbmi = (LPBITMAPINFO)lpDstDib;				// ��ȡָ��
	CDC *pDC=GetDC();							//��ȡ�ӵĿͻ���
	CRect rect(0,0,lSrcWidth,lSrcHeight);
	CBrush brush(RGB(200,200,200));				//������ˢ
	pDC->FillRect(&rect,&brush);					//�ؼ���ʾǰ�����ͻ�������
	CPalette * pPal=new CPalette;					// �����µ�ɫ��
	pDoc->m_dib.ConstructPalette(pDoc->m_dib.m_hDib,pPal);
    CPalette * pOldPal=pDC->SelectPalette(pPal, TRUE);	//���߼���ɫ��ѡΪ��ǰ��ɫ��
    pDC->RealizePalette();							//ʵ�ֵ�ɫ��
	int i=0,j=0,k=0;								//����һЩѭ������
	switch(nID)								//�жϵ�ǰ�Ĳ˵�����
	{
		case ID_VER:					//��ֱ����
		for(i=0;i<=lSrcWidth/15;i++)//�ֳ�15��
		{
			for(j=0;j<=15;j++)
			{
				::StretchDIBits(pDC->GetSafeHdc(),j*lSrcWidth/15, 0, i, lSrcHeight,
					j*lSrcWidth/15, 0, i, lSrcHeight,
					lpSrcStartBits, lpbmi,
					DIB_RGB_COLORS, SRCCOPY);
				Sleep(2);				 
			}
		}
		pDC->SelectPalette(pOldPal, TRUE);		//�ָ�ԭ��ɫ��
        ::DeleteObject(pPal);					//ɾ���½��ĵ�ɫ�����
		break;
	case ID_HOR:						//ˮƽ����
		for(j=0;j<=lSrcHeight/15;j++)
		{
			for(i=0;i<=15;i++)
			{
				::StretchDIBits(pDC->GetSafeHdc(),0, i*lSrcHeight/15, lSrcWidth,j,
					0, (14-i)*lSrcHeight/15, lSrcWidth,j,
					lpSrcStartBits, lpbmi,
					DIB_RGB_COLORS, SRCCOPY);
				Sleep(2); 				
			}
		}
		pDC->SelectPalette(pOldPal, TRUE);		//�ָ�ԭ��ɫ��
        ::DeleteObject(pPal);					//ɾ���½��ĵ�ɫ�����
		break;

	}
	Invalidate();								//ˢ�¿ͻ���
	SetCursor(LoadCursor(NULL, IDC_ARROW));		//�ָ����ԭʼ״̬
}

void CShowEffectView::OnImageGrid(UINT nID)//դ�񽻴���Ч
{
	CShowEffectDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	SetCursor(LoadCursor(NULL, IDC_WAIT));					//�����ʾΪ����״̬
	long	lSrcWidth;										//ͼ��Ŀ�Ⱥ͸߶�
	long	lSrcHeight;
	LPSTR	lpSrcDib;							//ָ��Դͼ���ָ��	
	LPSTR   lpDstDib;
	LPSTR lpSrcStartBits;
	lpSrcDib= (LPSTR) ::GlobalLock((HGLOBAL) pDoc->GetHObject());// ����DIB
	lSrcWidth= pDoc->m_dib.GetWidth(lpSrcDib);		// ��ȡͼ��Ŀ��		
	lSrcHeight= pDoc->m_dib.GetHeight(lpSrcDib);		// ��ȡͼ��ĸ߶�
	lpSrcStartBits=pDoc->m_dib.GetBits(lpSrcDib);		// �ҵ�DIBͼ��������ʼλ��
	LPBITMAPINFO lpbmi;						// ָ��BITMAPINFO�ṹ��ָ��
	// �����ڴ�
	HGLOBAL hDIB = (HGLOBAL) ::GlobalAlloc(GHND, lSrcWidth*lSrcHeight);
	if (hDIB == NULL)							// �ж��Ƿ�����Ч��DIB����
	{		
		return;
	}		
	lpDstDib=  (char * )::GlobalLock((HGLOBAL) hDIB);// �����ڴ�
	memcpy(lpDstDib, lpSrcDib, lSrcWidth*lSrcHeight);	// ����DIB����
	lpbmi = (LPBITMAPINFO)lpDstDib;				// ��ȡָ��
	CDC *pDC=GetDC();							//��ȡ�ӵĿͻ���
	CRect rect(0,0,lSrcWidth,lSrcHeight);
	CBrush brush(RGB(200,200,200));				//������ˢ
	pDC->FillRect(&rect,&brush);					//�ؼ���ʾǰ�����ͻ�������
	CPalette * pPal=new CPalette;					// �����µ�ɫ��
	pDoc->m_dib.ConstructPalette(pDoc->m_dib.m_hDib,pPal);
    CPalette * pOldPal=pDC->SelectPalette(pPal, TRUE);	//���߼���ɫ��ѡΪ��ǰ��ɫ��
    pDC->RealizePalette();							//ʵ�ֵ�ɫ��
	int i=0,j=0,k=0;								//����һЩѭ������
	int nScanLine=2;								//�趨դ��Ŀ��
	switch(nID)								//�жϵ�ǰ�Ĳ˵�����
	{
		case ID_GRID_HOR:						//ˮƽդ�񽻴�
			for(i=0;i<=lSrcWidth;i++)
			{
				for(j=0;j<=lSrcHeight;j=j+2*nScanLine)
				{
					::StretchDIBits(pDC->GetSafeHdc(),0,j,i+1,nScanLine,
						lSrcWidth-i,lSrcHeight-j,i+1,nScanLine,lpSrcStartBits,lpbmi,
						DIB_RGB_COLORS,SRCCOPY);
					k=j+nScanLine;				//ż�����ӵ���ʼ��ַ
					::StretchDIBits(pDC->GetSafeHdc(),lSrcWidth-i,k,i+1,nScanLine,
						0,lSrcHeight-k,i+1,nScanLine,
						lpSrcStartBits,lpbmi,
						DIB_RGB_COLORS,SRCCOPY);
				}
			}
            pDC->SelectPalette(pOldPal, TRUE);		//�ָ�ԭ��ɫ��
        	  ::DeleteObject(pPal);					//ɾ���½��ĵ�ɫ�����
			break;
		case ID_GRID_VER:						//��ֱդ�񽻴�
			for(j=0;j<=lSrcHeight;j++)
			{
				for(i=0;i<=lSrcWidth;i=i+2*nScanLine)
				{
					::StretchDIBits(pDC->GetSafeHdc(),i,  0 ,  nScanLine, j+1,
						i, 0, nScanLine, j+1,
						lpSrcStartBits, lpbmi,
						DIB_RGB_COLORS, SRCCOPY);
					k=i+nScanLine;				//ż������(���Ұ벿��)����ʼ��ַ
					::StretchDIBits(pDC->GetSafeHdc(), k, lSrcHeight-j ,  nScanLine,  j+1,
						k,lSrcHeight-j, nScanLine, j+1,
						lpSrcStartBits, lpbmi,
						DIB_RGB_COLORS, SRCCOPY);
					
				}
			}
            pDC->SelectPalette(pOldPal, TRUE);		//�ָ�ԭ��ɫ��
        	::DeleteObject(pPal);					//ɾ���½��ĵ�ɫ�����
			break;
	}
	Invalidate();								//ˢ�¿ͻ���
	SetCursor(LoadCursor(NULL, IDC_ARROW));		//�ָ����ԭʼ״̬
}

void CShowEffectView::OnImageStunt(UINT nID)//������Ч��ʾ
{
	CShowEffectDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	SetCursor(LoadCursor(NULL, IDC_WAIT));			//�����ʾΪ����״̬
	long	lSrcWidth;								//ͼ��Ŀ�Ⱥ͸߶�
	long	lSrcHeight;
	LPSTR	lpSrcDib;							//ָ��Դͼ���ָ��	
	LPSTR   lpDstDib;
	LPSTR lpSrcStartBits;
	lpSrcDib= (LPSTR) ::GlobalLock((HGLOBAL) pDoc->GetHObject());// ����DIB
	lSrcWidth= pDoc->m_dib.GetWidth(lpSrcDib);		// ��ȡͼ��Ŀ��		
	lSrcHeight= pDoc->m_dib.GetHeight(lpSrcDib);		// ��ȡͼ��ĸ߶�
	lpSrcStartBits=pDoc->m_dib.GetBits(lpSrcDib);		// �ҵ�DIBͼ��������ʼλ��
	LPBITMAPINFO lpbmi;						// ָ��BITMAPINFO�ṹ��ָ��
	// �����ڴ�
	HGLOBAL hDIB = (HGLOBAL) ::GlobalAlloc(GHND, lSrcWidth*lSrcHeight);
	if (hDIB == NULL)							// �ж��Ƿ�����Ч��DIB����
	{		
		return;								// ���ǣ��򷵻�
	}		
	lpDstDib=  (char * )::GlobalLock((HGLOBAL) hDIB);// �����ڴ�
	memcpy(lpDstDib, lpSrcDib, lSrcWidth*lSrcHeight);	// ����DIB����
	lpbmi = (LPBITMAPINFO)lpDstDib;				// ��ȡָ��
	CDC *pDC=GetDC();							//��ȡ�ӵĿͻ���
	CRect rect(0,0,lSrcWidth,lSrcHeight);
	CBrush brush(RGB(200,200,200));				//������ˢ
	pDC->FillRect(&rect,&brush);					//�ؼ���ʾǰ�����ͻ�������
	CPalette * pPal=new CPalette;					// �����µ�ɫ��
	pDoc->m_dib.ConstructPalette(pDoc->m_dib.m_hDib,pPal);
    CPalette * pOldPal=pDC->SelectPalette(pPal, TRUE);	//���߼���ɫ��ѡΪ��ǰ��ɫ��
    pDC->RealizePalette();							//ʵ�ֵ�ɫ��
	int i=0,j=0,k=0;								//����һЩѭ������
	switch(nID)								//�жϵ�ǰ�Ĳ˵�����
	{
		case ID_EXTEND_VER:					//����չ��
			for(i=0;i<=lSrcWidth/2;i++)
			{		
				::StretchDIBits(pDC->GetSafeHdc(),0 ,  lSrcHeight/2+i  , lSrcWidth, 1 ,
					0  , lSrcHeight/2-i , lSrcWidth,1 ,
					lpSrcStartBits, lpbmi,
					DIB_RGB_COLORS, SRCCOPY); 
				::StretchDIBits(pDC->GetSafeHdc(),0 ,  lSrcHeight/2-i  , lSrcWidth, 1 ,
					0  , lSrcHeight/2+i , lSrcWidth,1 ,
					lpSrcStartBits, lpbmi,
					DIB_RGB_COLORS, SRCCOPY); 
				Sleep(2); 					
			}
            pDC->SelectPalette(pOldPal, TRUE);		//�ָ�ԭ��ɫ��
        	::DeleteObject(pPal);					//ɾ���½��ĵ�ɫ�����
			break;
		case ID_SHRINK_VER:					//��������
			for(j=0;j<lSrcHeight/2;j++)
			{
				::StretchDIBits(pDC->GetSafeHdc(),0, j, lSrcWidth, 1,
					0, lSrcHeight-j, lSrcWidth, 1,
					lpSrcStartBits, lpbmi,
					DIB_RGB_COLORS, SRCCOPY);
				::StretchDIBits(pDC->GetSafeHdc(),0, lSrcHeight-j, lSrcWidth, 1,
					0,  j, lSrcWidth, 1,
					lpSrcStartBits, lpbmi,
					DIB_RGB_COLORS, SRCCOPY);
				Sleep(2); 	
			}
            pDC->SelectPalette(pOldPal, TRUE);		//�ָ�ԭ��ɫ��
        	::DeleteObject(pPal);					//ɾ���½��ĵ�ɫ�����
		break;
		case ID_EXTEND_HOR:					//����չ��
			for(j=0;j<=lSrcWidth/2;j++)
			{		
				::StretchDIBits(pDC->GetSafeHdc(),lSrcWidth/2+j,0,1,lSrcHeight,
					lSrcWidth/2+j,0,1,lSrcHeight,
					lpSrcStartBits, lpbmi,
					DIB_RGB_COLORS, SRCCOPY); 
				::StretchDIBits(pDC->GetSafeHdc(),lSrcWidth/2-j,0,1,lSrcHeight,
					lSrcWidth/2-j,0,1,lSrcHeight,
					lpSrcStartBits, lpbmi,
					DIB_RGB_COLORS, SRCCOPY); 
				Sleep(2);								
			}
            pDC->SelectPalette(pOldPal, TRUE);		//�ָ�ԭ��ɫ��
        	::DeleteObject(pPal);					//ɾ���½��ĵ�ɫ�����
		   break;
		case ID_SHRINK_HOR:					//��������
			for(j=0;j<lSrcWidth/2;j++)
			{
				::StretchDIBits(pDC->GetSafeHdc(),j, 0, 1, lSrcHeight,
					j, 0, 1, lSrcHeight,
					lpSrcStartBits, lpbmi,
					DIB_RGB_COLORS, SRCCOPY);
				::StretchDIBits(pDC->GetSafeHdc(),lSrcWidth-j,0,1,lSrcHeight,
					lSrcWidth-j,0,1,lSrcHeight,
					lpSrcStartBits, lpbmi,
					DIB_RGB_COLORS, SRCCOPY);
				Sleep(2);					
			}
            pDC->SelectPalette(pOldPal, TRUE);		//�ָ�ԭ��ɫ��
        	  ::DeleteObject(pPal);					//ɾ���½��ĵ�ɫ�����
		   break;
	}
	Invalidate();								//ˢ�¿ͻ���
	SetCursor(LoadCursor(NULL, IDC_ARROW));		//�ָ����ԭʼ״̬
}