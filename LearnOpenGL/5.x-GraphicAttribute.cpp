#include "pch.h"
#include "5.x-GraphicAttribute.h"
#define _USE_MATH_DEFINES
#include "math.h"
#include <iostream>

using namespace std;

// 子类构造函数调用父类构造函数
GraphicAttribute::GraphicAttribute() :BaseMain(800,1.333)
{

}

void GraphicAttribute::MainFunc(int argc, char * argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB); // 单个帧缓存
	glutInitWindowPosition(InitWindowPosX, InitWindowPosY);
	// glutInitWindowSize: 是显示窗口的大小
	// gluOrtho2D: 被投影到显示窗口的区域,应该与显示窗口的宽高比相同
	// 绘制的图形在gluOrtho2D显示,按照比例投影到glutInitWindowSize
	glutInitWindowSize(WindowWidth, WindowHeight);
	glutCreateWindow("第5章 图元的属性");

	BaseInit();

	int DrawWhatIndex = 3;
	switch (DrawWhatIndex)
	{
	case 0: glutDisplayFunc(DrawPoint);			break;
	case 1: glutDisplayFunc(DrawLine);			break;
	case 2: glutDisplayFunc(DrawInterpTexture);	break;
	case 3: glutDisplayFunc(DrawBorder);		break;
	default:									break;
	}
	
	glutReshapeFunc(WindowReshape);

	glutMainLoop();
}

// 绘制点
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

// 将Sin值投射到[0,1]
GLfloat GraphicAttribute::SinPositive(GLfloat value)
{
	return sin(value) / 2 + 0.5;
}

// 绘制直线
void GraphicAttribute::DrawLine()
{
	Point dataPts[5] = {
		Point(WindowWidth * 0.1f,WindowHeight * 0.5f),
		Point(WindowWidth * 0.3f,WindowHeight * 0.7f),
		Point(WindowWidth * 0.5f,WindowHeight * 0.5f),
		Point(WindowWidth * 0.7f,WindowHeight * 0.3f),
		Point(WindowWidth * 0.9f,WindowHeight * 0.5f)
	};

	// 激活线型特性
	glEnable(GL_LINE_STIPPLE);
	{
		// 坐标轴
		glLineWidth(1.0); // 必须在glBegin外
		glBegin(GL_LINES);
		{
			glColor3f(0, 1, 0);
			glVertex2f(WindowWidth * 0.1f, WindowHeight * 0.1f);
			glVertex2f(WindowWidth * 0.9f, WindowHeight * 0.1f);
			glColor3f(0, 0, 1);
			glVertex2f(WindowWidth * 0.1f, WindowHeight * 0.1f);
			glVertex2f(WindowWidth * 0.1f, WindowHeight * 0.9f);
		}
		glEnd();

		// 渐变颜色
		glShadeModel(GL_SMOOTH);
		glLineWidth(5.0);
		glBegin(GL_LINES);
		{
			glColor3f(1, 0, 0);
			glVertex2i(WindowWidth * 0.1f, WindowHeight * 0.2f);

			glColor3f(0, 0.5, 0.5);
			glVertex2i(WindowWidth * 0.9f, WindowHeight * 0.2f);
		}
		glEnd();
		// 设直线型, Stipple: 点画
		glLineStipple(1, 0x1C47); // 点划线
		glLineWidth(1.0);
		glColor3f(1, 0, 0); // 默认白色导致半天以为没画出来
		linePlot(dataPts, 5);

		glLineStipple(1, 0x00FF); // 虚线
		glLineWidth(2.0);
		dataPts[1].Y = WindowHeight * 0.3f;
		dataPts[3].Y = WindowHeight * 0.7f;
		glColor3f(0, 1, 0);
		linePlot(dataPts, 5);

		glLineStipple(1, 0x0101); // 点点线
		glLineWidth(10.0);
		dataPts[1].Y = WindowHeight * 0.5f;
		dataPts[3].Y = WindowHeight * 0.5f;
		glColor3f(0, 0, 1);
		linePlot(dataPts, 5);
	}
	glDisable(GL_LINE_STIPPLE);
}

// 传入定点数组,绘制折线
void GraphicAttribute::linePlot(Point points[], GLint ArrayLength)
{
	glBegin(GL_LINE_STRIP);
	{
		for (int i = 0; i < ArrayLength; i++)
		{
			glVertex2f(points[i].X, points[i].Y);
		}
	}
	glEnd();

	glFlush(); // 必须在glEnd后面
}

// 绘制三角形,使用纹理和差值填充
void GraphicAttribute::DrawInterpTexture()
{
	glShadeModel(GL_SMOOTH);

	glBegin(GL_TRIANGLES); 
	{
		glColor3f(0, 0, 1);
		glVertex2i(50, 50);
		glColor3f(1, 0, 0);
		glVertex2i(750, 50);
		glColor3f(0, 1, 0);
		glVertex2i(75, 550);
	}
	glEnd();

	// 仅绘制边框,绘制边框要单独设置
	glPolygonMode(GL_FRONT, GL_LINE); // 要放在glBegin外面
	glBegin(GL_TRIANGLES);
	{
		glColor3f(0, 0, 0);
		glVertex2i(50, 50);
		glVertex2i(750, 50);
		glVertex2i(75, 550);
	}
	glEnd();

	glFlush();
}

void GraphicAttribute::DrawBorder()
{
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	glColor3f(1, 0, 0);
	// 绘制指定边,GL_TRUE为默认值
	// GL_FALSE后面的点(A),以A为起点的边不绘制
	// 直到重新设为GL_TRUE后面的点(B),以B为起点,再次开始绘制
	glBegin(GL_POLYGON);
	{
		glVertex2i(50, 50);
		glVertex2i(250, 50);
		glEdgeFlag(GL_FALSE);
		glVertex2i(250, 250); // 点(A)
		glEdgeFlag(GL_TRUE);
		glVertex2i(50, 250); // 点(B)
	}
	glEnd();

	glFlush();
}

