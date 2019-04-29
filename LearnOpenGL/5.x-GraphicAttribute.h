#pragma once
#include "BaseMain.h"
#include "GL/glut.h"

class GraphicAttribute :public BaseMain
{
public:
	GraphicAttribute();

	virtual void MainFunc(int argc, char * argv[]) override;

private:

	static void DrawPoint();
	static inline GLfloat SinPositive(GLfloat value);

	static void DrawLine();
	static void linePlot(Point points[],GLint ArrayLength); // »æÖÆ
};