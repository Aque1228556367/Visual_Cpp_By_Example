// OpenGLShowMovieView.cpp : implementation of the COpenGLShowMovieView class
//

#include "stdafx.h"
#include "OpenGLShowMovie.h"

#include "OpenGLShowMovieDoc.h"
#include "OpenGLShowMovieView.h"
#include "math.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// COpenGLShowMovieView
#define RAD  (3.14159265358979 / 180)
IMPLEMENT_DYNCREATE(COpenGLShowMovieView, CView)

BEGIN_MESSAGE_MAP(COpenGLShowMovieView, CView)
	//{{AFX_MSG_MAP(COpenGLShowMovieView)
	ON_WM_CREATE()
	ON_WM_DESTROY()
	ON_WM_SIZE()
	ON_WM_ERASEBKGND()
	ON_WM_KEYDOWN()
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// COpenGLShowMovieView construction/destruction

COpenGLShowMovieView::COpenGLShowMovieView()
{
	// TODO: add construction code here
	ctrl=false;
	r=10.0;
	hDegree=vDegree=10;

}

COpenGLShowMovieView::~COpenGLShowMovieView()
{
}

BOOL COpenGLShowMovieView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs
//	cs.style |= WS_CLIPSIBLINGS | WS_CLIPCHILDREN;//�����Ӵ��ں��ֵܴ���
	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// COpenGLShowMovieView drawing

void COpenGLShowMovieView::OnDraw(CDC* pDC)
{
	COpenGLShowMovieDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
	//ָ���ں�̨�����л���
	glDrawBuffer(GL_BACK);
	//��ʼ���任����
	glLoadIdentity();
	glClearColor(0.0,0.0,0.0,0.0f);//���ñ�����ɫΪ��ɫ
	glClear(GL_COLOR_BUFFER_BIT );//���������ɫ
	GetEye(r, hDegree, vDegree, ex, ey, ez);
	gluLookAt(ex, ey, ez, 0, 0, 0, 0, r, 0);
	glColor3f(1.0f, 1.0f, 0.0f); // ���û�ͼ��ɫ
	auxWireTeapot(3.5);//���Ʋ������
	char buf[40];
	sprintf(buf, "r = %.4g, hDegree = %d, vDegree = %d", r, hDegree, vDegree);
	//����ǰ�󻺴�
	SwapBuffers(wglGetCurrentDC());
	//����ǰ��
	glDrawBuffer(GL_FRONT);
	pDC->TextOut(10, 10, "ͨ��ʹ���ϡ��¡����Ҽ�ͷ�ͼӼ����������۲�λ��");
	pDC->TextOut(10, 30, buf);
}

/////////////////////////////////////////////////////////////////////////////
// COpenGLShowMovieView printing

BOOL COpenGLShowMovieView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void COpenGLShowMovieView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void COpenGLShowMovieView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// COpenGLShowMovieView diagnostics

#ifdef _DEBUG
void COpenGLShowMovieView::AssertValid() const
{
	CView::AssertValid();
}

void COpenGLShowMovieView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

COpenGLShowMovieDoc* COpenGLShowMovieView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(COpenGLShowMovieDoc)));
	return (COpenGLShowMovieDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// COpenGLShowMovieView message handlers

int COpenGLShowMovieView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
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
	return 0;
}

void COpenGLShowMovieView::OnDestroy() 
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

void COpenGLShowMovieView::OnSize(UINT nType, int cx, int cy) 
{
	CView::OnSize(nType, cx, cy);	
	// TODO: Add your message handler code here
	if(m_hglrc)
		wglMakeCurrent(m_pDC->GetSafeHdc(), m_hglrc);//��ȡ��ǰ��ͼ����
	else
		return;
	glViewport(0,0,cx,cy);//�����ӿڴ�С
	glMatrixMode(GL_PROJECTION);//���ñ任ģʽΪͶӰ�任
	glLoadIdentity();//��ʼ��ͶӰ�任����
	//���ݴ��ڴ�С���õ�������ͶӰ����
	if(cx<=cy)
		glOrtho(-5.0,5.0,-5.0*(GLfloat)cy/(GLfloat)cx,
			5.0*(GLfloat)cy/(GLfloat)cx,-12.0,12.0);
	else
		glOrtho(-5.0*(GLfloat)cx/(GLfloat)cy,
			5.0*(GLfloat)cx/(GLfloat)cy,-5.0,5.0,-12.0,12.0);
	//	���ñ任ģʽΪģ�ͱ任
	glMatrixMode(GL_MODELVIEW);
	//	��ʼ��ģ�ͱ任����Ϊ��λ����
	glLoadIdentity();	
}

BOOL COpenGLShowMovieView::OnEraseBkgnd(CDC* pDC) 
{
	// TODO: Add your message handler code here and/or call default
	return true;
	//return CView::OnEraseBkgnd(pDC);
}

void COpenGLShowMovieView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	// TODO: Add your message handler code here and/or call default
	int hDegree0 = hDegree,	vDegree0 = vDegree, times;
	double r0=r,dr=0.01;
	if (ctrl) 
		times = 10; 
	else 
		times = 1;
	switch (nChar) 	{
	 // change view degree and distance
	 case 187: // +
		 r += times * dr; 
		 break;
	 case 189: // - 
		 r -= times * dr; 
		 break;
	 case VK_UP: 
		 vDegree -= times; 
		 break;
	 case VK_DOWN: 
		 vDegree += times; 
		 break;
	 case VK_LEFT: 
		 hDegree += times; 
		 break;
	 case VK_RIGHT: 
		 hDegree -= times; 
		 break;
	 case VK_CONTROL: 
		 ctrl = TRUE;
		 break;
	case VK_SHIFT: 
		ctrl = FALSE;
	}
	if (hDegree < 0) 
		hDegree += 360; 
	else if (hDegree > 360) 
		hDegree -= 360;
	if (vDegree < -180) 
		vDegree += 360; 
	else if (vDegree > 180) 
		vDegree -= 360;
	if (r != r0 || hDegree != hDegree0 || vDegree0 != vDegree) 
		Invalidate();//������ͼ
	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}
void COpenGLShowMovieView::GetEye(double r, int hd, int vd, GLdouble &ex, GLdouble &ey, GLdouble &ez)
 {
	ex = r * sin(vd * RAD) * cos(hd * RAD);
	ey = r * sin(vd * RAD) * sin(hd * RAD);
	ez = r * cos(vd * RAD);
}
