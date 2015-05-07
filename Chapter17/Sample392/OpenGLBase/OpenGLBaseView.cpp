// OpenGLBaseView.cpp : implementation of the COpenGLBaseView class
//

#include "stdafx.h"
#include "OpenGLBase.h"

#include "OpenGLBaseDoc.h"
#include "OpenGLBaseView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// COpenGLBaseView

IMPLEMENT_DYNCREATE(COpenGLBaseView, CView)

BEGIN_MESSAGE_MAP(COpenGLBaseView, CView)
	//{{AFX_MSG_MAP(COpenGLBaseView)
	ON_WM_CREATE()
	ON_WM_DESTROY()
	ON_WM_SIZE()
	ON_WM_ERASEBKGND()
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// COpenGLBaseView construction/destruction

COpenGLBaseView::COpenGLBaseView()
{
	// TODO: add construction code here

}

COpenGLBaseView::~COpenGLBaseView()
{
}

BOOL COpenGLBaseView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs
//	cs.style |= WS_CLIPSIBLINGS | WS_CLIPCHILDREN;//�����Ӵ��ں��ֵܴ���
	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// COpenGLBaseView drawing

void COpenGLBaseView::OnDraw(CDC* pDC)
{
	COpenGLBaseDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
	//ָ���ں�̨�����л���
	glDrawBuffer(GL_BACK);
	//��ʼ���任����
	glLoadIdentity();
	glClearColor(0.0,0.0,0.0,0.0f);//���ñ�����ɫΪ��ɫ
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);//���������ɫ
	gluLookAt(0, 0, 10, 0, 0, 0, 0, 1, 0); // ���ù۲��λ��
	glLoadIdentity(); // ���õ�ǰ����Ϊ��λ���������ź���ת��
	glColor3f(1.0f, 0.0f, 0.0f); // ���û�ͼ��ɫΪ��ɫ
	DrawGLSquare(); // ��������
	glPushMatrix();
		glScalef(2.0f, 0.5f, 0.0f); // x����ĳߴ�Ŵ�һ��, y����ĳߴ���Сһ��
		glColor3f(0.0f, 1.0f, 0.0f); // ���û�ͼ��ɫΪ��ɫ
		DrawGLSquare(); // �������
	glPopMatrix();
	glPushMatrix();
		glRotatef(45.0f, 0.0f, 0.0f, 1.0f); // ��z����ת45��
		glColor3f(0.0f, 0.0f, 1.0f); // ���û�ͼ��ɫΪ��ɫ
		DrawGLSquare(); // ������
		glScalef(0.5f, 0.5f, 0.0f); // x������y����ĳߴ綼��Сһ��
		glColor3f(1.0f, 1.0f, 0.0f); // ���û�ͼ��ɫΪ��ɫ
		DrawGLSquare();// ��С����
	glPopMatrix();
	gluLookAt(3, 2, 6, 0, 0, 0, 0, 1, 0); // ���ù۲��λ��
	glColor3f(1.0f, 1.0f, 0.0f); //���û�ͼ��ɫ
	glPushMatrix();
	glColor3f(0.0,1.0,1.0);
	glTranslatef(-5.0,0.2,0.0);
	auxWireTeapot(1.6);// ���������
	glTranslatef(9.0,3.0,0.0);
	auxSolidTeapot(1.6);//ʵ�Ĳ��
	glPopMatrix();	
	//����ǰ�󻺴�
	SwapBuffers(wglGetCurrentDC());
	//����ǰ��
	glDrawBuffer(GL_FRONT);
}
void COpenGLBaseView::DrawGLSquare() 
{ // X-Yƽ���е�������
	glBegin(GL_LINES); // ��ʱ�뻭���߿�
		// �������
		glVertex3f(-1.0f, 1.0f, 0.0f); // ��MoveTo
		glVertex3f(-1.0f, -1.0f, 0.0f); // ��LineTo
		// ���±���
		glVertex3f(-1.0f, -1.0f, 0.0f);
		glVertex3f(1.0f, -1.0f, 0.0f);
		// ���ұ���
		glVertex3f(1.0f, -1.0f, 0.0f);
		glVertex3f(1.0f, 1.0f, 0.0f);
		// ���ϱ���
		glVertex3f(1.0f, 1.0f, 0.0f);
		glVertex3f(-1.0f, 1.0f, 0.0f);
	glEnd();
}

/////////////////////////////////////////////////////////////////////////////
// COpenGLBaseView printing

BOOL COpenGLBaseView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void COpenGLBaseView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void COpenGLBaseView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// COpenGLBaseView diagnostics

#ifdef _DEBUG
void COpenGLBaseView::AssertValid() const
{
	CView::AssertValid();
}

void COpenGLBaseView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

COpenGLBaseDoc* COpenGLBaseView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(COpenGLBaseDoc)));
	return (COpenGLBaseDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// COpenGLBaseView message handlers

int COpenGLBaseView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
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

void COpenGLBaseView::OnDestroy() 
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

void COpenGLBaseView::OnSize(UINT nType, int cx, int cy) 
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

BOOL COpenGLBaseView::OnEraseBkgnd(CDC* pDC) 
{
	// TODO: Add your message handler code here and/or call default
	return true;
	//return CView::OnEraseBkgnd(pDC);
}
