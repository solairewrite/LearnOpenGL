#include "pch.h"
#include "5.x-GraphicAttribute.h"
#define _USE_MATH_DEFINES
#include "math.h"
#include <iostream>

using namespace std;

// ���๹�캯�����ø��๹�캯��
GraphicAttribute::GraphicAttribute() :BaseMain(800,1.333)
{

}

void GraphicAttribute::MainFunc(int argc, char * argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB); // ����֡����
	glutInitWindowPosition(InitWindowPosX, InitWindowPosY);
	// glutInitWindowSize: ����ʾ���ڵĴ�С
	// gluOrtho2D: ��ͶӰ����ʾ���ڵ�����,Ӧ������ʾ���ڵĿ�߱���ͬ
	// ���Ƶ�ͼ����gluOrtho2D��ʾ,���ձ���ͶӰ��glutInitWindowSize
	glutInitWindowSize(WindowWidth, WindowHeight);
	glutCreateWindow("��5�� ͼԪ������");

	BaseInit();

	int DrawWhatIndex = 1;
	switch (DrawWhatIndex)
	{
	case 0: glutDisplayFunc(DrawPoint);	break;
	case 1: glutDisplayFunc(DrawLine);	break;
	default:							break;
	}
	
	glutReshapeFunc(WindowReshape);

	glutMainLoop();
}

// ���Ƶ�
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
		glPointSize(PointMinSize + PointMaxSize * SinPositive(Angle)); // ��Ҫ��glBegin�ⲿ������Ч
		glBegin(GL_POINTS);
		glVertex2i(CenterX + Radius * cos(Angle), CenterX + Radius * sin(Angle));
		glEnd();
	}

	glFlush();
}

// ��SinֵͶ�䵽[0,1]
GLfloat GraphicAttribute::SinPositive(GLfloat value)
{
	return sin(value) / 2 + 0.5;
}

// ����ֱ��
void GraphicAttribute::DrawLine()
{
	Point dataPts[5] = {
		Point(WindowWidth * 0.1f,WindowHeight * 0.5f),
		Point(WindowWidth * 0.3f,WindowHeight * 0.7f),
		Point(WindowWidth * 0.5f,WindowHeight * 0.5f),
		Point(WindowWidth * 0.7f,WindowHeight * 0.3f),
		Point(WindowWidth * 0.9f,WindowHeight * 0.5f)
	};

	// ������������
	glEnable(GL_LINE_STIPPLE);
	{
		// ������
		glLineWidth(1.0); // ������glBegin��
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

		// ������ɫ
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
		// ��ֱ����, Stipple: �㻭
		glLineStipple(1, 0x1C47); // �㻮��
		glLineWidth(1.0);
		glColor3f(1, 0, 0); // Ĭ�ϰ�ɫ���°�����Ϊû������
		linePlot(dataPts, 5);

		glLineStipple(1, 0x00FF); // ����
		glLineWidth(2.0);
		dataPts[1].Y = WindowHeight * 0.3f;
		dataPts[3].Y = WindowHeight * 0.7f;
		glColor3f(0, 1, 0);
		linePlot(dataPts, 5);

		glLineStipple(1, 0x0101); // �����
		glLineWidth(10.0);
		dataPts[1].Y = WindowHeight * 0.5f;
		dataPts[3].Y = WindowHeight * 0.5f;
		glColor3f(0, 0, 1);
		linePlot(dataPts, 5);
	}
	glDisable(GL_LINE_STIPPLE);
}

// ���붨������,��������
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

	glFlush(); // ������glEnd����
}

