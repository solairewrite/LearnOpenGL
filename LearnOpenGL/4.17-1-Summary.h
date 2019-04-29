#pragma once
#include "BaseMain.h"
#include <GL/glut.h>

class Summary :public BaseMain
{
public:
	Summary();

private:
	static const GLsizei SingleChartSize = 600;
	GLsizei winWidth, winHeight;	// ���ڳߴ�
	static GLint xRaster, yRaster;	// ��ʼ��դλ��

	static GLubyte label[36];		// ������д,Jan,Feb...
	static GLint dataValue[12];		// ÿ���µ�����

public:
	virtual void MainFunc(int argc, char * argv[]) override;

private:
	void init();
	static void lineGraph(GLint MonthSpace); // ����ͼ
	static void barChart(GLint MonthSpace); // ����ͼ
	static void DrawChart();
	static void winReshapeFcn2(GLint newWidth, GLint newHeight);

};
