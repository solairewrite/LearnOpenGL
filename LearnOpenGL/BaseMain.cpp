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

}

// glutInitWindowSize: ����ʾ���ڵĴ�С
// gluOrtho2D: ��ͶӰ����ʾ���ڵ�����,Ӧ������ʾ���ڵĿ�߱���ͬ
// ���Ƶ�ͼ����gluOrtho2D��ʾ,���ձ���ͶӰ��glutInitWindowSize
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
