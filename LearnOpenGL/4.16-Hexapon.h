#pragma once
#include "BaseMain.h"
#include <GL/glut.h>

class Heaxpon :public BaseMain
{
private:
	const double TWO_PI = 6.28;
	// 窗口Size
	GLsizei winWidth, winHeigth;
	// 显示表索引
	static GLuint regHex;

public:
	Heaxpon();

	virtual void MainFunc(int argc, char * argv[]) override;

private:
	void init();
	void static regHexagon();
	void static winReshapeFcn(int newWidth, int newHeight);
};

class screenPt
{
private:
	GLint x, y;

public:
	screenPt()
	{
		x = y = 0;
	}

	void setCoords(GLint xCoord, GLint yCoord)
	{
		x = xCoord;
		y = yCoord;
	}

	void setx(GLint inX) { x = inX; }
	void sety(GLint inY) { y = inY; }

	GLint getx() { return x; }

	GLint gety() { return y; }
};