#include "pch.h"
#include "20.x-Interactive.h"

GLsizei Interactive::winWidth = 400;
GLsizei Interactive::winHeight = 300;

GLint Interactive::endPtCrt = 0;

GLint Interactive::edgeLength = 10;

//std::vector<Point> pts = {};

Interactive::Interactive()
{

}

void Interactive::MainFunc(int argc, char * argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(winWidth, winHeight);
	glutCreateWindow("交互");

	init();
	glutDisplayFunc(displayFcn);
	glutReshapeFunc(winReshapeFcn);

	int DrawIndex = 3;
	switch (DrawIndex)
	{
	case 0:		glutMouseFunc(mousePtPlot);			break;
	case 1:		glutMouseFunc(polyline);			break;
	case 2:		glutKeyboardFunc(curveDrawing);		break;
	case 3:		glutMouseFunc(fillSquare);
				glutKeyboardFunc(enlargeSquare);
				glutSpecialFunc(reduceSquare);		break;
	default:	break;
	}

	glutMainLoop();
}

void Interactive::init()
{
	glClearColor(1.0, 1.0, 1.0, 0.0);

	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(0.0, 200.0, 0.0, 150.0);
}

void Interactive::displayFcn()
{
	glClear(GL_COLOR_BUFFER_BIT);

	glColor3f(1.0, 0.0, 0.0);
	glPointSize(10.0);
}

void Interactive::winReshapeFcn(GLint newWidth, GLint newHeight)
{
	glViewport(0, 0, newWidth, newHeight); // 视口,窗口中的显示区域
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, GLdouble(newWidth), 0.0, GLdouble(newHeight)); // 截取世界坐标系

	winWidth = newWidth;
	winHeight = newHeight;
}

void Interactive::plotPoint(GLint x, GLint y)
{
	glBegin(GL_POINTS);
	{
		glVertex2i(x, y);
	}
	glEnd();
}

void Interactive::mousePtPlot(GLint button, GLint action, GLint xMouse, GLint yMouse)
{
	if (button == GLUT_LEFT_BUTTON && action == GLUT_DOWN)
	{
		// yMouse是到窗口上边界的距离
		plotPoint(xMouse, winHeight - yMouse);

		glFlush();
	}
}

void Interactive::drawLineSegment(Point endPt1, Point endPt2)
{
	glBegin(GL_LINES);
	{
		glVertex2i(endPt1.X, endPt1.Y);
		glVertex2i(endPt2.X, endPt2.Y);
	}
	glEnd();
}

void Interactive::polyline(GLint button, GLint action, GLint xMouse, GLint yMouse)
{
	static Point endPt1, endPt2;
	static std::vector<Point> pts;

	if (endPtCrt == 0)
	{
		if (button == GLUT_LEFT_BUTTON && action == GLUT_DOWN)
		{
			endPt1.X = xMouse;
			endPt1.Y = winHeight - yMouse;

			pts.push_back(endPt1);

			endPtCrt = 1;
		}
		else
		{
			if (button == GLUT_RIGHT_BUTTON)
			{
				// 退出
				exit(0);
			}
		}
	}
	else
	{
		if (button == GLUT_LEFT_BUTTON && action == GLUT_DOWN)
		{
			endPt2.X = xMouse;
			endPt2.Y = winHeight - yMouse;

			pts.push_back(endPt2);

			for (int i = 0; i < pts.size() - 1; i++)
			{
				drawLineSegment(pts[i], pts[i + 1]);
			}

			endPt1 = endPt2;
		}
		else
			if (button == GLUT_RIGHT_BUTTON)
				exit(0);
	}

	glFlush();
}

void Interactive::curveDrawing(GLubyte curvePlotKey, GLint xMouse, GLint yMouse)
{
	GLint x = xMouse;
	GLint y = winHeight - yMouse;
	switch (curvePlotKey) // 检测按键
	{
	case 'c':	plotPoint(x, y);	break;
	default:	break;
	}
	glFlush();
}

void Interactive::fillSquare(GLint button, GLint action, GLint xMouse, GLint yMouse)
{
	GLint x1, y1, x2, y2;

	if (button == GLUT_LEFT_BUTTON && action == GLUT_DOWN)
	{
		x1 = xMouse;
		y1 = winHeight - yMouse;
		x2 = x1 + edgeLength;
		y2 = y1 + edgeLength;
		glRecti(x1, y1, x2, y2);
	}
	else
		if (button == GLUT_RIGHT_BUTTON)
			exit(0);

	glFlush();
}

void Interactive::enlargeSquare(GLubyte sizeFacttor, GLint xMouse, GLint yMouse)
{
	switch (sizeFacttor)
	{
	case '2':	edgeLength *= 2;	break;
	case '3':	edgeLength *= 3;	break;
	case '4':	edgeLength *= 4;	break;
	default:	break;
	}
}

void Interactive::reduceSquare(GLint reductionKey, GLint xMouse, GLint yMouse)
{
	switch (reductionKey)
	{
	case GLUT_KEY_F2:	edgeLength /= 2;	break;
	case GLUT_KEY_F4:	edgeLength /= 4;	break;
	default:	break;
	}
}
