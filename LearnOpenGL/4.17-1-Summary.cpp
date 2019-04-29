#include "pch.h"
#include "4.17-1-Summary.h"
#include <GL/glut.h>

GLint Summary::xRaster = 25;
GLint Summary::yRaster = 150;

// 静态数组的初始化
GLubyte Summary::label[36] = {
	'J','a','n',	'F','e','b',	'M','a','r',
	'A','p','r',	'M','a','y',	'J','u','n',
	'J','u','l',	'A','u','g',	'S','e','p',
	'O','c','t',	'N','o','v',	'D','e','c'
};
GLint Summary::dataValue[12] = { 420,342,324,310,262,185,
								 190,196,217,240,312,438 };


Summary::Summary()
{
	winWidth = SingleChartSize * 2; // 左边画折线图,右边画条形图
	winHeight = SingleChartSize;
}

void Summary::init()
{
	glClearColor(1, 1, 1, 1); // 白色窗口
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(0.0, SingleChartSize, 0.0, SingleChartSize - 100.0); // 投影到窗口的矩形区域尺寸
}

void Summary::lineGraph(GLint MonthSpace)
{
	GLint month, k;
	GLint x = 30; // 初始点的X位置

	glClear(GL_COLOR_BUFFER_BIT); // 清空窗口
	glColor3f(0.0, 0.0, 1.0); // 设置线的颜色为蓝色

	// 绘制折线
	glBegin(GL_LINE_STRIP);
	for (k = 0; k < 12; k++)
	{
		glVertex2i(x + k * MonthSpace, dataValue[k]);
	}
	glEnd();

	glColor3f(1.0, 0.0, 0.0); // 设置标记的颜色为红色
	// 将数据绘制为*
	for (k = 0; k < 12; k++)
	{
		glRasterPos2i(xRaster + k * MonthSpace, dataValue[k] - 4);
		// 显示字符
		glutBitmapCharacter(GLUT_BITMAP_9_BY_15, '*');
	}

	glColor3f(0.0, 0.0, 0.0); // 设置文字黑色
	for (month = 0; month < 12; month++)
	{
		glRasterPos2i((xRaster - 5) + month * MonthSpace, yRaster);
		for (k = 3 * month; k < 3 * month + 3; k++)
		{
			glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, label[k]); // 'Jan','Feb'...
		}
	}
}

void Summary::barChart(GLint MonthSpace)
{
	GLint month, k;
	GLint RectWidth = 20;
	GLint barChartXRaster = SingleChartSize + RectWidth;

	//glClear(GL_COLOR_BUFFER_BIT); // 清空窗口
	for (k = 0; k < 12; k++)
	{
		glRecti(barChartXRaster + k * MonthSpace, 165, barChartXRaster + RectWidth + k * MonthSpace, dataValue[k]);
	}

	glColor3f(0.0, 0.0, 0.0); // 黑色文字
	for (month = 0; month < 12; month++)
	{
		glRasterPos2i(barChartXRaster + month * MonthSpace, yRaster);
		for (k = 3 * month; k < 3 * month + 3; k++)
		{
			glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, label[k]);
		}
	}
}

void Summary::DrawChart()
{
	GLint MonthSpace = 50; // 两个月份之间的间隔
	// 折线图
	lineGraph(MonthSpace);
	// 柱状图
	barChart(MonthSpace);
	glFlush(); // 清空OpenGL命令缓冲区，强制执行命令缓冲区中所有OpenGL函数
}

void Summary::winReshapeFcn2(GLint newWidth, GLint newHeight)
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, GLdouble(newWidth), 0.0, GLdouble(newHeight));
	glClear(GL_COLOR_BUFFER_BIT);
}

void Summary::MainFunc(int argc, char * argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(winWidth, winHeight);
	glutCreateWindow("线形图");

	init();
	glutDisplayFunc(DrawChart);
	glutReshapeFunc(winReshapeFcn2);

	glutMainLoop();
}