#include "pch.h"
#include "5.x-GraphicAttribute.h"
#define _USE_MATH_DEFINES
#include "math.h"

GraphicAttribute::GraphicAttribute()
{
	winWidth = 600;
	winHeight = 600;
}

void GraphicAttribute::MainFunc(int argc, char * argv[])
{
	GLint winX = 200;
	GLint winY = 200;

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB); // 单个帧缓存
	glutInitWindowPosition(winX, winY);
	glutInitWindowSize(winWidth, winHeight);
	glutCreateWindow("第5章 图元的属性");

	init();
	glutDisplayFunc(DrawPoint);
	//glutReshapeFunc(WindowReshape);

	glutMainLoop();
}

// glutInitWindowSize: 是显示窗口的大小
// gluOrtho2D: 被投影到显示窗口的区域,应该与显示窗口的宽高比相同
// 绘制的图形在gluOrtho2D显示,按照比例投影到glutInitWindowSize
void GraphicAttribute::init()
{
	GLdouble initWidth = 250;
	GLdouble initHeight = 250;

	glClearColor(1.0, 1.0, 1.0, 1.0);
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(0, initWidth, 0, initHeight);
}

void GraphicAttribute::DrawPoint()
{
	glClear(GL_COLOR_BUFFER_BIT);

	GLint PointNum = 80;
	GLfloat theta = M_PI * 2 / PointNum;
	GLfloat Angle;
	GLint PointMinSize = 3;
	GLint PointMaxSize = 30;
	GLint Radius = 100;
	GLint CenterX = Radius + 20;
	GLint CenterY = Radius + 20;
	for (int i = 0; i < PointNum; i++)
	{
		Angle = i * theta;
		glColor3f(SinPositive(Angle), SinPositive(Angle+M_PI_2), SinPositive(Angle+M_PI));
		glPointSize(PointMinSize + PointMaxSize * SinPositive(Angle)); // 需要在glBegin外部才能生效
		glBegin(GL_POINTS);
		glVertex2i(CenterX + Radius * cos(Angle), CenterX + Radius * sin(Angle));
		glEnd();
	}

	glFlush();
}

GLfloat GraphicAttribute::SinPositive(GLfloat value)
{
	return sin(value) / 2 + 0.5;
}

