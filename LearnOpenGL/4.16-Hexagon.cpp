#include "pch.h"
#include "4.16-Hexapon.h"
#include "GL/glut.h"
#include "math.h"

// ��̬��Ա��Ҫ��ʼ��,������ⲿ
GLuint Heaxpon::regHex = 0;

Heaxpon::Heaxpon()
{
	winWidth = 400;
	winHeigth = 400;
}

void Heaxpon::init()
{
	// �����ζ���,Բ��
	screenPt hexgonVertex, circleCenter;
	// �����ζ��㵽Բ����x��Ļ��ȼн�
	GLdouble theta;
	const int CircleRadius = 150;
	GLint k;

	// ����Բ��
	circleCenter.setCoords(winWidth / 2, winHeigth / 2);

	// ������ɫ
	glClearColor(1.0, 1.0, 1.0, 0.0);

	// ����display list,�������εĶ�����Բ���ϵȾ�ֲ�
	// ��ȡdisplay list id
	regHex = glGenLists(1);
	glNewList(regHex, GL_COMPILE);
	// �����ɫ
	glColor3f(1.0, 0.0, 0.0);
	glBegin(GL_POLYGON);
	for (k = 0; k < 6; k++)
	{
		theta = TWO_PI * k / 6.0;
		hexgonVertex.setCoords(circleCenter.getx() + CircleRadius * cos(theta), circleCenter.gety() + CircleRadius * sin(theta));
		glVertex2i(hexgonVertex.getx(), hexgonVertex.gety());
	}
	glEnd();
	glEndList();

}

void Heaxpon::regHexagon()
{
	// ʹ��glClearColor��ָ����ֵ�趨��ɫ��������ֵ�����������е�ÿһ����������Ϊ����ɫ
	glClear(GL_COLOR_BUFFER_BIT);
	// ִ����ʾ��
	glCallList(regHex);
	// ���OpenGL���������ǿ��ִ���������������OpenGL����
	glFlush();
}

void Heaxpon::winReshapeFcn(int newWidth, int newHeight)
{
	// OpenGL������ά��ʽ������ͼ��������Ҫһ��ͶӰ�任����άͼ��ͶӰ����ʾ���Ķ�ά�ռ���
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	// ��һ��x������0~newWidth��y����0~newHeight��Χ�ڵľ�����������ͶӰ����ʾ������
	gluOrtho2D(0.0, (GLdouble)newWidth, 0.0, (GLdouble)newHeight);
	// ʹ��glClearColor��ָ����ֵ�趨��ɫ��������ֵ�����������е�ÿһ����������Ϊ����ɫ
	glClear(GL_COLOR_BUFFER_BIT);
}


void Heaxpon::MainFunc(int argc, char * argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(winWidth, winHeigth);
	glutCreateWindow("��ʾ�� & �����ض���");

	init();
	glutDisplayFunc(regHexagon);
	glutReshapeFunc(winReshapeFcn);

	glutMainLoop();
}
