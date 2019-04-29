#include "pch.h"
#include "Test.h"
#include<gl/GLUT.H>

// ��ʾ�ص�����
void Test::myDisplay()
{
	// ʹ��glClearColor��ָ����ֵ�趨��ɫ��������ֵ�����������е�ÿһ����������Ϊ����ɫ
	glClear(GL_COLOR_BUFFER_BIT);
	// ��ͼ��ɫ
	glColor3f(0.0f, 0.0f, 0.0f);
	// ͼ�ε����꣬����һ�����½��ڣ�50��100�������Ͻ��ڣ�150��50���ľ���
	glRectf(0.0f, 10.0f, 100.0f, 120.0f);
	// ���OpenGL���������ǿ��ִ���������������OpenGL����
	glFlush();
}

void Test::Initial()
{
	// ��ɫ����
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	// OpenGL������ά��ʽ������ͼ��������Ҫһ��ͶӰ�任����άͼ��ͶӰ����ʾ���Ķ�ά�ռ���
	glMatrixMode(GL_PROJECTION);
	// ��һ��x������0~200��y����0~150��Χ�ڵľ�����������ͶӰ����ʾ������
	// ���ڿ�������
	// glRectf()�Ŀ��/gluOrtho2D()�Ŀ�� -> �ڴ���glutInitWindowSize()��,��ռ��ȵı���
	gluOrtho2D(0.0, 200, 0.0, 300.0);
}

void Test::MainFunc(int argc, char * argv[])
{
	// ʹ��glut����Ҫ���г�ʼ��
	glutInit(&argc, argv);
	// �趨������ʾģʽ����ɫģ�ͺͻ��棬������RGB��ɫģ�ͺ͵�����
	glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
	// �趨���ڵĳ�ʼλ�ã���Ļ���Ͻ�Ϊԭ�㣬��λΪ����
	glutInitWindowPosition(100, 300);
	// �趨���ڵĴ�С
	glutInitWindowSize(500, 400);
	// ����һ�����ڣ������Ǵ��ڱ�����
	glutCreateWindow("��һ��OpenGL���򡪡������");
	// ��myDisplayָ��Ϊ��ǰ���ڵ���ʾ���ݺ���
	glutDisplayFunc(&Test::myDisplay);
	Initial();
	// ʹ���ڿ������������ʹ��ʾ�ص�������ʼ����
	glutMainLoop();
}
