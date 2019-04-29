#include "pch.h"
#include "4.17-3-DrawCurve.h"
#include "math.h"
#include <iostream>

DrawCurve::DrawCurve()
{
	winWidth = 600;
	winHeight = 500;
}

void DrawCurve::MainFunc(int argc, char * argv[])
{
	GLint winX = 200;
	GLint winY = 200;
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowPosition(winX, winY);
	glutInitWindowSize(winWidth, winHeight);
	glutCreateWindow("绘制曲线");

	init();
	glutDisplayFunc(displayFcn);
	glutReshapeFunc(winReshape);

	glutMainLoop();
}

void DrawCurve::init()
{
	GLdouble initWidth = 200;
	GLdouble initHeight = 150;

	glClearColor(1, 1, 1, 1);
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(0, initWidth, 0, initHeight);
}

void DrawCurve::lineSegment(screenPt pt1, screenPt pt2)
{
	glBegin(GL_LINES);
	glVertex2i(pt1.x, pt1.y);
	glVertex2i(pt2.x, pt2.y);
	glEnd();
}

void DrawCurve::drawCurve(GLint curveNum)
{
	const GLdouble twoPi = 6.28;
	const GLint a = 175, b = 60;

	GLfloat r, theta, dtheta = 1.0f / float(a); // 一个很小的角度
	GLint x0 = 200, y0 = 250; // 初始屏幕位置
	screenPt curvePt[2];

	glColor3f(0, 0, 0); // 黑色曲线

	curvePt[0].x = x0; // 初始曲线位置
	curvePt[0].y = y0;

	switch (curveNum)
	{
	case limacon:	curvePt[0].x += a + b;	break;
	case cardioid:	curvePt[0].x += a + a;	break;
	case threeLeaf:	curvePt[0].x += a;		break;
	case fourLeaf:	curvePt[0].x += a;		break;
	case spiral:	break;
	default:		break;
	}

	theta = dtheta;
	while (theta < twoPi)
	{
		switch (curveNum)
		{
		case limacon:	r = a * cos(theta) + b;		break;
		case cardioid:	r = a * cos(theta) + a;		break;
		case threeLeaf:	r = a * cos(3 * theta);		break;
		case fourLeaf:	r = a * cos(2 * theta);		break;
		case spiral:	r = (a / 4.0)*theta;		break;
		default:	break;
		}

		curvePt[1].x = x0 + r * cos(theta);
		curvePt[1].y = y0 + r * sin(theta);
		lineSegment(curvePt[0], curvePt[1]);

		curvePt[0].x = curvePt[1].x;
		curvePt[0].y = curvePt[1].y;
		theta += dtheta;
	}
}

void DrawCurve::displayFcn()
{
	GLint curveNum;
	glClear(GL_COLOR_BUFFER_BIT);

	using namespace std;
	// ...
	cout << "输入曲线序号: " << endl;
	cout << "1-蜗形线, 2-心形线, 3-三叶曲线, 4-四叶曲线, 5-螺旋线" << endl;
	cin >> curveNum;

	if (curveNum >= 1 && curveNum <= 5)
	{
		drawCurve(curveNum);
	}
	else
	{
		exit(0);
	}

	glFlush();
}

void DrawCurve::winReshape(GLint newWidth, GLint newHeight)
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, newWidth, 0, newHeight);
	glClear(GL_COLOR_BUFFER_BIT);
}
