#pragma once
#include "BaseMain.h"
#include "4.16-Hexapon.h"
#include "GL/glut.h"

class PieChart :public BaseMain
{
public:
	PieChart();

private:
	static const GLdouble twoPi;
	static GLsizei winWidth, winHeight; // ´°¿Ú³ß´ç

public:
	virtual void MainFunc(int argc, char * argv[]) override;

private:
	void init();
	static void circleMidpoint(screenPt CircleCenter, GLfloat radius, GLint SegmentsNum = 128);
	static void pieChart();
	static void displayFcn();
	static void winReshapeFcn(GLint newWidth, GLint newHeight);
};