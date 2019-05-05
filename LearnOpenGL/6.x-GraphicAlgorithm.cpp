#include "pch.h"
#include "6.x-GraphicAlgorithm.h"


GraphicAlgorithm::GraphicAlgorithm() :BaseMain(800, 1.333)
{

}

void GraphicAlgorithm::MainFunc(int argc, char * argv[])
{
	BaseMain::MainFunc(argc, argv);

	glutCreateWindow("第6章 图元算法");

	BaseInit();

	int FuncIndex = 1;
	switch (FuncIndex)
	{
	case 0:		glutDisplayFunc(LineBresenham);		break;
	case 1:		glutDisplayFunc(DrawCircle);		break;
	default:										break;
	}

	glutReshapeFunc(WindowReshape);

	glutMainLoop();
}

// 直线算法,斜率<1的情况
void GraphicAlgorithm::LineBresenham()
{
	GLint x0 = 20, y0 = 10, xEnd = 780, yEnd = 500;
	GLint dx = xEnd - x0, dy = yEnd - y0;
	GLint p = 2 * dy - dx;
	GLint twoDy = 2 * dy, twoDyMinusDx = 2 * (dy - dx);
	GLint x=x0, y=y0;

	glColor3f(1, 0.5, 0);
	glPointSize(10);
	glBegin(GL_POINTS);
	{
		glVertex2i(x0, y0);
		glVertex2i(xEnd, yEnd);
	}
	glEnd();

	glColor3f(1, 0, 0);
	glPointSize(2); // 放在glBegin外面
	glBegin(GL_POINTS);
	{
		glVertex2i(x, y);
		while (x < xEnd)
		{
			x++;
			if (p < 0)
			{
				p += twoDy;
			}
			else
			{
				y++;
				p += twoDyMinusDx;
			}
			glVertex2i(x, y);
		}
	}
	glEnd();
	glFlush();
}

void GraphicAlgorithm::circleMidpoint(GLint xc, GLint yc, GLint radius)
{
	Point circPt;

	GLint p = 1 - radius; // 决策参数的初始值

	circPt.SetXY(0, radius); // 初始坐标设为圆最上面的点

	// 绘制第一个点
	circlePlotPoints(xc, yc, circPt);

	while (circPt.X<circPt.Y)
	{
		circPt.X += 1; // TODO
		// 决策参数判定,推导过程见6.4.2
		if (p<0)
		{
			p += 2 * circPt.X + 1;
		}
		else
		{
			circPt.Y -= 1;
			p += 2 * (circPt.X - circPt.Y) + 1;
		}
		circlePlotPoints(xc, yc, circPt);
	}

	glFlush(); // 注意!不加这行代码不绘制
}

void GraphicAlgorithm::DrawCircle()
{
	glColor3f(1, 0, 0);
	circleMidpoint(300, 300, 100);
}

void GraphicAlgorithm::setPixel(GLint xCoord, GLint yCoord)
{
	glBegin(GL_POINTS);
	{
		glVertex2i(xCoord, yCoord);
	}
	glEnd();
}

void GraphicAlgorithm::circlePlotPoints(GLint xc, GLint yc, Point circPt)
{
	setPixel(xc + circPt.X, yc + circPt.Y);
	setPixel(xc - circPt.X, yc + circPt.Y);
	setPixel(xc + circPt.X, yc - circPt.Y);
	setPixel(xc - circPt.X, yc - circPt.Y);
	setPixel(xc + circPt.Y, yc + circPt.X);
	setPixel(xc - circPt.Y, yc + circPt.X);
	setPixel(xc + circPt.Y, yc - circPt.X);
	setPixel(xc - circPt.Y, yc - circPt.X);
}
