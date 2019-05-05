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

	// 中点画圆算法
	static void circleMidpoint(GLint xc, GLint yc, GLint radius);
	// 示例
	static void DrawCircle();

	// 绘制一个点
	static void setPixel(GLint xCoord, GLint yCoord);

	// 根据对称性,绘制八分圆上的点
	static void circlePlotPoints(GLint xc, GLint yc, Point circPt);

};