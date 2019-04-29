#pragma once
#include "BaseMain.h"
#include "GL/glut.h"

typedef enum
{
	limacon = 1,// 蜗形线
	cardioid,	// 心形线
	threeLeaf,	// 三叶曲线
	fourLeaf,	// 四叶曲线
	spiral		// 螺旋线
} curveName;

class DrawCurve :public BaseMain
{
	struct screenPt
	{
		GLint x;
		GLint y;
	};

public:
	DrawCurve();

	virtual void MainFunc(int argc, char * argv[]) override;

private:
	GLsizei winWidth;
	GLsizei winHeight;

private:

	void init();

	static void lineSegment(screenPt pt1, screenPt pt2);

	static void drawCurve(GLint curveNum);

	static void displayFcn();

	static void winReshape(GLint newWidth, GLint newHeight);

};