#pragma once
#include "BaseMain.h"
#include "GL/glut.h"

typedef enum
{
	limacon = 1,// ������
	cardioid,	// ������
	threeLeaf,	// ��Ҷ����
	fourLeaf,	// ��Ҷ����
	spiral		// ������
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