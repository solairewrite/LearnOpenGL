#pragma once
#include "pch.h"
#include "BaseMain.h"

void BaseMain::MainFunc(int argc, char * argv[])
{

}

void BaseMain::WindowReshape(GLint newWidth, GLint newHeight)
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0,newWidth, 0, newHeight);
	glClear(GL_COLOR_BUFFER_BIT);
}
