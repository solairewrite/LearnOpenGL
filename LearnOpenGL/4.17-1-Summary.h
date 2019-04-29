#pragma once
#include "BaseMain.h"
#include <GL/glut.h>

class Summary :public BaseMain
{
public:
	Summary();

private:
	static const GLsizei SingleChartSize = 600;
	GLsizei winWidth, winHeight;	// 窗口尺寸
	static GLint xRaster, yRaster;	// 初始光栅位置

	static GLubyte label[36];		// 月名简写,Jan,Feb...
	static GLint dataValue[12];		// 每个月的数据

public:
	virtual void MainFunc(int argc, char * argv[]) override;

private:
	void init();
	static void lineGraph(GLint MonthSpace); // 折线图
	static void barChart(GLint MonthSpace); // 条形图
	static void DrawChart();
	static void winReshapeFcn2(GLint newWidth, GLint newHeight);

};
