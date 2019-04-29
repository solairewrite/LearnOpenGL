#pragma once
#include "GL/glut.h"

/**
 * �ṩ��ͼ�ӿ�
 */
class BaseMain
{
public:
	BaseMain();
	BaseMain(GLint windowWidth, GLfloat aspectRatio = 1.0f);

	virtual void MainFunc(int argc, char * argv[]);

protected:
	static GLint WindowWidth;		// ������ڿ��
	static GLint WindowHeight;		// ������ڸ߶�
	static GLfloat AspectRatio;	// ������ڿ�߱�

	GLint InitWindowPosX;	// ������ڳ�ʼλ��
	GLint InitWindowPosY;	// ������ڳ�ʼλ��

protected:
	virtual void BaseInit(GLclampf R = 1.0f, GLclampf G = 1.0f, GLclampf B = 1.0f, GLclampf A = 1.0f);

	static void WindowReshape(GLint newWidth, GLint newHeight);

};

typedef struct Point
{
	GLfloat X, Y;
	Point(GLfloat x, GLfloat y)
	{
		X = x;
		Y = y;
	}
} Point;