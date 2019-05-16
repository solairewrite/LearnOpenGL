#include "pch.h"
#include "12.x-Animation.h"
#include <iostream>

using namespace std;

GLfloat Animation::rotTheta = 0.0;
GLuint Animation::regHex = 0;

Animation::Animation()
{

}

void Animation::MainFunc(int argc, char * argv[])
{
	glutInit(&argc, argv);
	// 注意这里是双缓存区
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowPosition(150, 150);
	glutInitWindowSize(winWidth, winHeight);
	glutCreateWindow("动画");

	init();
	glutDisplayFunc(displayHex);
	glutReshapeFunc(winReshapeFcn);
	// 鼠标点击事件
	glutMouseFunc(MouseFcn);

	glutMainLoop();
}

void Animation::init()
{
	Point hexVertex;
	GLdouble hexTheta;
	GLint k;

	// 护眼色
	glClearColor(0.78, 0.93, 0.81, 0.0);

	// 设置红色正六边形的显示列表,4.16
	regHex = glGenLists(1);
	glNewList(regHex, GL_COMPILE);
	glColor3f(1.0, 0.0, 0.0);
	glBegin(GL_POLYGON);
	{
		for (k=0;k<6;k++)
		{
			hexTheta = TWO_PI * k / 6.0;
			hexVertex.X = 150 + 100 * cos(hexTheta);
			hexVertex.Y = 150 + 100 * sin(hexTheta);
			glVertex2i(hexVertex.X, hexVertex.Y);
		}
	}
	glEnd();
	glEndList();
}

void Animation::displayHex()
{
	glClear(GL_COLOR_BUFFER_BIT);

	// 旋转
	glPushMatrix();
	glRotatef(rotTheta, 0.0, 0.0, 1.0);
	// 调用绘制列表
	glCallList(regHex);
	glPopMatrix();

	// 交换前后缓冲区
	glutSwapBuffers();

	glFlush();
}

void Animation::rotateHex()
{
	rotTheta += 3.0;
	if (rotTheta>360.0)
	{
		rotTheta -= 360.0;
	}

	glutPostRedisplay();
}

void Animation::winReshapeFcn(GLint newWidth, GLint newHeight)
{
	glViewport(0, 0, newWidth, newHeight);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-320.0, 320.0, -320.0, 320.0);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glClear(GL_COLOR_BUFFER_BIT);
}

void Animation::MouseFcn(GLint button, GLint action, GLint x, GLint y)
{
	switch (button)
	{
	case GLUT_MIDDLE_BUTTON:
		if (action==GLUT_DOWN)
		{
			// 点击鼠标中键开始旋转
			glutIdleFunc(rotateHex);
		}
		break;
	case GLUT_RIGHT_BUTTON:
		if (action==GLUT_DOWN)
		{
			// 点击鼠标右键结束旋转
			glutIdleFunc(NULL);
		}
		break;
	default:
		break;
	}
}

