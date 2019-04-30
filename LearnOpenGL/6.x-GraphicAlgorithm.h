#pragma once
#include "BaseMain.h"
#include "GL/glut.h"

class GraphicAlgorithm :public BaseMain
{
public:
	GraphicAlgorithm();

	virtual void MainFunc(int argc, char * argv[]) override;

private:

	static void LineBresenham();
};