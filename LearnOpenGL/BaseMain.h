#pragma once
#include "GL/glut.h"

/**
 * �ṩ��ͼ�ӿ�
 */
class BaseMain
{
public:
	virtual void MainFunc(int argc, char * argv[]);

protected:
	static void WindowReshape(GLint newWidth, GLint newHeight);
};