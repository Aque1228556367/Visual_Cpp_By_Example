// OpenGLTextureView.cpp : implementation of the COpenGLTextureView class
//

#include "stdafx.h"
#include "OpenGLTexture.h"

#include "OpenGLTextureDoc.h"
#include "OpenGLTextureView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


/////////////////////////////////////////////////////////////////////////////
// COpenGLTextureView

IMPLEMENT_DYNCREATE(COpenGLTextureView, CView)

BEGIN_MESSAGE_MAP(COpenGLTextureView, CView)
	//{{AFX_MSG_MAP(COpenGLTextureView)
	ON_WM_CREATE()
	ON_WM_DESTROY()
	ON_WM_SIZE()
	ON_WM_ERASEBKGND()
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// COpenGLTextureView construction/destruction

COpenGLTextureView::COpenGLTextureView()
{
	// TODO: add construction code here

}

COpenGLTextureView::~COpenGLTextureView()
{
}

BOOL COpenGLTextureView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs
//	cs.style |= WS_CLIPSIBLINGS | WS_CLIPCHILDREN;//�����Ӵ��ں��ֵܴ���
	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// COpenGLTextureView drawing

void COpenGLTextureView::OnDraw(CDC* pDC)
{
	COpenGLTextureDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

}
void COpenGLTextureView::DrawGLSquare(float x1,float y1,float x2,float y2) 
{ //��ʼ��ʾ����,ע�ⶥ���˳��
    glBegin(GL_QUADS);
        //�ֱ����þ��ε�4������,ע��Ҫ���趨��������
        glTexCoord2f(0,0);
        glVertex3f(x1,y1,0); //���ж����ZֵΪ0
        glTexCoord2f(0,1);
        glVertex3f(x1,y2,0); 
        glTexCoord2f(1,1);
        glVertex3f(x2,y2,0); 
        glTexCoord2f(1,0);
        glVertex3f(x2,y1,0); 
    glEnd();

}

/////////////////////////////////////////////////////////////////////////////
// COpenGLTextureView printing

BOOL COpenGLTextureView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void COpenGLTextureView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void COpenGLTextureView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// COpenGLTextureView diagnostics

#ifdef _DEBUG
void COpenGLTextureView::AssertValid() const
{
	CView::AssertValid();
}

void COpenGLTextureView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

COpenGLTextureDoc* COpenGLTextureView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(COpenGLTextureDoc)));
	return (COpenGLTextureDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// COpenGLTextureView message handlers

int COpenGLTextureView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// TODO: Add your specialized creation code here
    m_pDC = new CClientDC(this);
    ASSERT(m_pDC != NULL);
	//	��ʼ�����ظ�ʽ
    static PIXELFORMATDESCRIPTOR pfd = 
	{
        sizeof(PIXELFORMATDESCRIPTOR),   // �ṹ��С
        1,                               // �汾
        PFD_DRAW_TO_WINDOW   |          // ֧��Windows
          PFD_SUPPORT_OPENGL |          // ֧�� OpenGL
          PFD_DOUBLEBUFFER,             // ˫����
        PFD_TYPE_RGBA,		            // ��������
        24,                             // 24-bit��ɫλ��
        0, 0, 0, 0, 0, 0,               // ����R��G��Bλ��
        0,                              // ��ֵλ��
        0,                              // ��ֵƫ��
        0,                              // ��դ����λ��
        0, 0, 0, 0,                     // ��դ����������λ��
        32,                             // ��Ȼ���λ��
        0,                              // ͼ������λ��
        0,                              // ��������λ��
        PFD_MAIN_PLANE,                 // ������
        0,                              // ����
        0, 0, 0                         // ��������
    };
	//	ѡ�����ظ�ʽ
    int pixelformat;
    if ( (pixelformat = ChoosePixelFormat(m_pDC->GetSafeHdc(), &pfd)) == 0 )
    {
        AfxMessageBox("ѡ�����ظ�ʽʧ�ܣ�");
        return -1;
    }
	//	�������ظ�ʽ
    if (SetPixelFormat(m_pDC->GetSafeHdc(), pixelformat, &pfd) == FALSE)
    {
        AfxMessageBox("�������ظ�ʽʧ�ܣ�");
        return -1;
    }	
	//	���������龰����
    m_hglrc = wglCreateContext(m_pDC->GetSafeHdc());

	SetTimer(1,200,NULL);//���ö�ʱ��

	return 0;
}

void COpenGLTextureView::OnDestroy() 
{
	CView::OnDestroy();	
	// TODO: Add your message handler code here
	::wglMakeCurrent(NULL,  NULL);
	//	ɾ����ǰ��ͼ�龰�����ͷ���ռ�ڴ�
    if (m_hglrc)
	{
        ::wglDeleteContext(m_hglrc);
		m_hglrc = NULL;
	}
    if (m_pDC)
        delete m_pDC;
}

void COpenGLTextureView::OnSize(UINT nType, int cx, int cy) 
{
	CView::OnSize(nType, cx, cy);	
	// TODO: Add your message handler code here
	if(m_hglrc)
		wglMakeCurrent(m_pDC->GetSafeHdc(), m_hglrc);//��ȡ��ǰ��ͼ����
	else
		return;
	//�趨����
  glViewport(0, 0, cx,cy);
	//�趨͸�ӷ�ʽ
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(220.0, 1.0*(GLfloat)cx/(GLfloat)cy, 1.0, 110.0);
  glMatrixMode(GL_MODELVIEW);
//	��ʼ��ģ�ͱ任����Ϊ��λ����
	glLoadIdentity();	
}

BOOL COpenGLTextureView::OnEraseBkgnd(CDC* pDC) 
{
	// TODO: Add your message handler code here and/or call default
	return true;
	//return CView::OnEraseBkgnd(pDC);
}


void COpenGLTextureView::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	//ÿ��ı���ɫ,ʹ��͸��Ч��������
 	int i,j;
    GLubyte color1,alpha;
    //��ʼ������
    for(i=0;i<IMAGEWIDTH;i++)
        for(j=0;j<IMAGEHEIGHT;j++)
        {
            color1 = (i&0x4)?255:0;
            alpha = (j&0x4)?255:128;
           // ��ɫ���������
            Image[i][j][0] = color1;
            Image[i][j][1] = color1;
            Image[i][j][2] = 255;
           // ͸���Ͱ�͸�����
            Image[i][j][3] = (GLubyte) alpha;
        }
        //���ò���
        //���ʰ���RGBA�ĸ�����,û�б߽�
    glTexImage2D(GL_TEXTURE_2D, 0, 4,IMAGEWIDTH,IMAGEHEIGHT, 0,
            GL_RGBA, GL_UNSIGNED_BYTE, &Image[0][0][0]);
    //�������ʱ߽����չ�߽���ɫ
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
    //���˲���
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    //�������а�͸����ɫ,��Ҫ����alpha���,
    glEnable (GL_BLEND);
    glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	static float color = 0.0f;
	color+=0.01f;
  if(color>1.0f)color=0.0f;
//���������Ļ����ɫ���������Ļ����Ȼ���
  glClearColor(0.0f,0.0f,0.0f,0.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//���ó�ģ�;���ģʽ
  glMatrixMode(GL_MODELVIEW);
//���뵥λ������
  glLoadIdentity();
//�趨�����λ�úͷ���
  gluLookAt (0.0, 0.0, 1.02, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0); 
//��ʾһ���޲��ʵľ���
  glDisable(GL_TEXTURE_2D);
  glColor3f(color,0.5f,color);
  glRectf(-1.5f,-1.5f,1.5f,1.5f);
//��ʾһ���в��ʵĲ��
  glEnable(GL_TEXTURE_2D);
  gluLookAt(-0.4, 1.0, 4, 0, 0, 0, 0, -1, 0);	 						//���ù۲��λ��; 
  glColor3f(1.0f,1.0f,1.0f); //ע���������ɫ���ڲ��ʵ���ɫ����Ӱ���
  auxSolidTeapot(4.0);
//�ȴ����е�OPENGL����ִ�����
  glFlush();
//����ǰ�󻺳���
  auxSwapBuffers();
  //����ǰ��
glDrawBuffer(GL_FRONT);
CView::OnTimer(nIDEvent);
}
