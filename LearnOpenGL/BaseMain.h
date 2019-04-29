#pragma once
#include "GL/glut.h"

/**
 * 提供绘图接口
 */
class BaseMain
{
public:
	virtual void MainFunc(int argc, char * argv[]);

protected:
	static void WindowReshape(GLint newWidth, GLint newHeight);
};