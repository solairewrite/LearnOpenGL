#pragma once
#include "pch.h"
#include "BaseMain.h"
#include <stdio.h>

GLint BaseMain::WindowWidth = 800;
GLfloat BaseMain::AspectRatio = 1.0f;
GLint BaseMain::WindowHeight = BaseMain::WindowWidth / BaseMain::AspectRatio;

// 静态常量初始化
const GLdouble BaseMain::PI = 3.14159;
const GLdouble BaseMain::TWO_PI = 6.2831853;

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
	gluOrtho2D(0, newWidth, 0, newHeight);
	glClear(GL_COLOR_BUFFER_BIT);
}

/**
 * 读取文件内容,并将其写入动态分配的字符串缓存区
 * 打开文件,并确定包含的字符总数.然后为字符串分配储存空间,再将文件内容存入该字符串
 * 返回指向字符串缓冲区地址的指针
 */
char* BaseMain::readTextFile(const char* name)
{
	FILE* fp;
	char* content = NULL;
	int count = 0;

	if (name = NULL)
		return NULL;

	// 尝试打开文件
	fopen_s(&fp, name, "rt");
	if (fp = NULL)
		return NULL;

	// 确定字符总数
	fseek(fp, 0, SEEK_END);
	count = ftell(fp);
	rewind(fp);

	// 分配缓存,写入文件
	if (count > 0)
	{
		content = (char*)malloc(sizeof(char) * (count + 1));
		if (count != NULL)
		{
			count = fread(content, sizeof(char), count, fp);
			content[count] = '\0';
		}
	}

	fclose(fp);

	return content;
}
