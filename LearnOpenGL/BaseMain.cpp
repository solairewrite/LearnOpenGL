#pragma once
#include "pch.h"
#include "BaseMain.h"

GLint BaseMain::WindowWidth = 800;
GLfloat BaseMain::AspectRatio = 1.0f;
GLint BaseMain::WindowHeight = BaseMain::WindowWidth / BaseMain::AspectRatio;

BaseMain::BaseMain()
{

}

BaseMain::BaseMain(GLint windowWidth, GLfloat aspectRatio)
{
	WindowWidth = windowWidth;
	AspectRatio = aspectRatio;
	WindowHeight = WindowWidth / AspectRatio;

	InitWindowPosX = 300;
	InitWindowPosY = 300;
}

void BaseMain::MainFunc(int argc, char * argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowPosition(InitWindowPosX, InitWindowPosY);
	glutInitWindowSize(WindowWidth, WindowHeight);
}

// glutInitWindowSize: 是显示窗口的大小
// gluOrtho2D: 被投影到显示窗口的区域,应该与显示窗口的宽高比相同
// 绘制的图形在gluOrtho2D显示,按照比例投影到glutInitWindowSize
void BaseMain::BaseInit(GLclampf R /*= 1.0f*/, GLclampf G /*= 1.0f*/, GLclampf B /*= 1.0f*/, GLclampf A /*= 1.0f*/)
{
	glClearColor(R, G, B, A);
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(0, WindowWidth, 0, WindowHeight);
}

void BaseMain::WindowReshape(GLint newWidth, GLint newHeight)
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0,newWidth, 0, newHeight);
	glClear(GL_COLOR_BUFFER_BIT);
}
