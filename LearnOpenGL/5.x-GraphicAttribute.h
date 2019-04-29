#pragma once
#include "BaseMain.h"
#include "GL/glut.h"

class GraphicAttribute :public BaseMain
{
public:
	GraphicAttribute();

	virtual void MainFunc(int argc, char * argv[]) override;

private:
	GLsizei winWidth;
	GLsizei winHeight;

private:
	void init();
	static void DrawPoint();
	static inline GLfloat SinPositive(GLfloat value);
};