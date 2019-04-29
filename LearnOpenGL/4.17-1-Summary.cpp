#include "pch.h"
#include "4.17-1-Summary.h"
#include <GL/glut.h>

GLint Summary::xRaster = 25;
GLint Summary::yRaster = 150;

// ��̬����ĳ�ʼ��
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
	winWidth = SingleChartSize * 2; // ��߻�����ͼ,�ұ߻�����ͼ
	winHeight = SingleChartSize;
}

void Summary::init()
{
	glClearColor(1, 1, 1, 1); // ��ɫ����
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(0.0, SingleChartSize, 0.0, SingleChartSize - 100.0); // ͶӰ�����ڵľ�������ߴ�
}

void Summary::lineGraph(GLint MonthSpace)
{
	GLint month, k;
	GLint x = 30; // ��ʼ���Xλ��

	glClear(GL_COLOR_BUFFER_BIT); // ��մ���
	glColor3f(0.0, 0.0, 1.0); // �����ߵ���ɫΪ��ɫ

	// ��������
	glBegin(GL_LINE_STRIP);
	for (k = 0; k < 12; k++)
	{
		glVertex2i(x + k * MonthSpace, dataValue[k]);
	}
	glEnd();

	glColor3f(1.0, 0.0, 0.0); // ���ñ�ǵ���ɫΪ��ɫ
	// �����ݻ���Ϊ*
	for (k = 0; k < 12; k++)
	{
		glRasterPos2i(xRaster + k * MonthSpace, dataValue[k] - 4);
		// ��ʾ�ַ�
		glutBitmapCharacter(GLUT_BITMAP_9_BY_15, '*');
	}

	glColor3f(0.0, 0.0, 0.0); // �������ֺ�ɫ
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

	//glClear(GL_COLOR_BUFFER_BIT); // ��մ���
	for (k = 0; k < 12; k++)
	{
		glRecti(barChartXRaster + k * MonthSpace, 165, barChartXRaster + RectWidth + k * MonthSpace, dataValue[k]);
	}

	glColor3f(0.0, 0.0, 0.0); // ��ɫ����
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
	GLint MonthSpace = 50; // �����·�֮��ļ��
	// ����ͼ
	lineGraph(MonthSpace);
	// ��״ͼ
	barChart(MonthSpace);
	glFlush(); // ���OpenGL���������ǿ��ִ���������������OpenGL����
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
	glutCreateWindow("����ͼ");

	init();
	glutDisplayFunc(DrawChart);
	glutReshapeFunc(winReshapeFcn2);

	glutMainLoop();
}