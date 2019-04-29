#include "pch.h"
#include "4.16-Hexapon.h"
#include "GL/glut.h"
#include "math.h"

// 静态成员需要初始化,在类的外部
GLuint Heaxpon::regHex = 0;

Heaxpon::Heaxpon()
{
	winWidth = 400;
	winHeigth = 400;
}

void Heaxpon::init()
{
	// 六边形顶点,圆心
	screenPt hexgonVertex, circleCenter;
	// 六边形顶点到圆心与x轴的弧度夹角
	GLdouble theta;
	const int CircleRadius = 150;
	GLint k;

	// 设置圆心
	circleCenter.setCoords(winWidth / 2, winHeigth / 2);

	// 窗口颜色
	glClearColor(1.0, 1.0, 1.0, 0.0);

	// 设置display list,正六边形的顶点在圆周上等距分布
	// 获取display list id
	regHex = glGenLists(1);
	glNewList(regHex, GL_COMPILE);
	// 填充颜色
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
	// 使用glClearColor中指定的值设定颜色缓存区的值，即将窗口中的每一个像素设置为背景色
	glClear(GL_COLOR_BUFFER_BIT);
	// 执行显示表
	glCallList(regHex);
	// 清空OpenGL命令缓冲区，强制执行命令缓冲区中所有OpenGL函数
	glFlush();
}

void Heaxpon::winReshapeFcn(int newWidth, int newHeight)
{
	// OpenGL按照三维方式来处理图像，所以需要一个投影变换将三维图形投影到显示器的二维空间中
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	// 将一个x坐标在0~newWidth，y坐标0~newHeight范围内的矩形坐标区域投影到显示器窗口
	gluOrtho2D(0.0, (GLdouble)newWidth, 0.0, (GLdouble)newHeight);
	// 使用glClearColor中指定的值设定颜色缓存区的值，即将窗口中的每一个像素设置为背景色
	glClear(GL_COLOR_BUFFER_BIT);
}


void Heaxpon::MainFunc(int argc, char * argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(winWidth, winHeigth);
	glutCreateWindow("显示表 & 窗口重定型");

	init();
	glutDisplayFunc(regHexagon);
	glutReshapeFunc(winReshapeFcn);

	glutMainLoop();
}
