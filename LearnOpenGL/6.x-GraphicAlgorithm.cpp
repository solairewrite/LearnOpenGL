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

	int FuncIndex = 0;
	switch (FuncIndex)
	{
	case 0:		glutDisplayFunc(LineBresenham);		break;
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

