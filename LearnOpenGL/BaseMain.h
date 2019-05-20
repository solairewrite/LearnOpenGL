#pragma once
#include "GL/glut.h"

/**
 * 提供绘图接口
 */
class BaseMain
{
public:
	BaseMain();
	BaseMain(GLint windowWidth, GLfloat aspectRatio = 1.0f);

	virtual void MainFunc(int argc, char * argv[]);

protected:
	static GLint WindowWidth;		// 输出窗口宽度
	static GLint WindowHeight;		// 输出窗口高度
	static GLfloat AspectRatio;	// 输出窗口宽高比

	GLint InitWindowPosX;	// 输出窗口初始位置
	GLint InitWindowPosY;	// 输出窗口初始位置

	static const GLdouble PI;
	static const GLdouble TWO_PI;

protected:
	virtual void BaseInit(GLclampf R = 1.0f, GLclampf G = 1.0f, GLclampf B = 1.0f, GLclampf A = 1.0f);

	static void WindowReshape(GLint newWidth, GLint newHeight);

	char* readTextFile(const char* name);

};

typedef struct Point
{
	GLfloat X, Y;

	Point()
	{

	}

	Point(GLfloat x, GLfloat y)
	{
		X = x;
		Y = y;
	}

	void SetXY(GLfloat x, GLfloat y)
	{
		X = x;
		Y = y;
	}
} Point;