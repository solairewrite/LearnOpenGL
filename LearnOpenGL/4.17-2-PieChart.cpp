#include "pch.h"
#include "4.17-2-PieChart.h"
#include "4.16-Hexapon.h"
#include <GL/glut.h>
#include "math.h"

GLsizei PieChart::winWidth = 800;
GLsizei PieChart::winHeight = 600;
const GLdouble PieChart::twoPi = 6.28;

PieChart::PieChart()
{

}

void PieChart::MainFunc(int argc, char * argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(winWidth, winHeight);
	glutCreateWindow("±ýÍ¼");

	init();
	glutDisplayFunc(displayFcn);
	glutReshapeFunc(winReshapeFcn);

	glutMainLoop();
}

void PieChart::init()
{
	GLdouble w = 400, h = 300;
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(0.0, w, 0, h);
}

void PieChart::circleMidpoint(screenPt CircleCenter, GLfloat radius, GLint SegmentsNum /*= 128*/)
{
	GLdouble theta = twoPi / SegmentsNum;
	GLdouble angle;
	GLfloat x, y;

	glBegin(GL_LINE_LOOP);
	for (GLint i = 0; i < SegmentsNum; i++)
	{
		angle = theta * i;
		x = CircleCenter.getx() + radius * cos(angle);
		y = CircleCenter.gety() + radius * sin(angle);
		glVertex2f(x, y);
	}
	glEnd();
}

void PieChart::pieChart()
{
	screenPt CircleCenter, piePt;
	GLint radius = winWidth / 4;

	GLdouble sliceAngle, previousSliceAngle = 0.0;

	GLint k, nSlices = 12;
	GLfloat dataValues[12] = { 10,	7,	13,	5,	13,	14,
								3,	16,	5,	3,	17,	8 };
	GLfloat dataSum = 0;

	CircleCenter.setx(winWidth / 2);
	CircleCenter.sety(winHeight / 2);
	circleMidpoint(CircleCenter, radius);

	for (k = 0; k < nSlices; k++)
	{
		if (k == 0)
		{
			dataSum = 0;
		}
		dataSum += dataValues[k];
	}

	glColor3f(0, 1, 0);
	glBegin(GL_LINES);
	for (k = 0; k < nSlices; k++)
	{
		sliceAngle = twoPi * dataValues[k] / dataSum + previousSliceAngle;
		piePt.setx(CircleCenter.getx() + radius * cos(sliceAngle));
		piePt.sety(CircleCenter.gety() + radius * sin(sliceAngle));
		//glBegin(GL_LINES);
		glVertex2f(CircleCenter.getx(), CircleCenter.gety());
		glVertex2f(piePt.getx(), piePt.gety());
		//glEnd();
		previousSliceAngle = sliceAngle;
	}
	glEnd();
}

void PieChart::displayFcn()
{
	glClear(GL_COLOR_BUFFER_BIT); // Çå¿Õ´°¿Ú
	glColor3f(0, 0, 1); // Ô²À¶É«
	pieChart();
	glFlush();
}

void PieChart::winReshapeFcn(GLint newWidth, GLint newHeight)
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, GLdouble(newWidth), 0, GLdouble(newHeight));

	glClear(GL_COLOR_BUFFER_BIT);

	winWidth = newWidth;
	winHeight = newHeight;
}
