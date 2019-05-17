#include "BaseMain.h"
#include <GL/glut.h>
#include <vector>

class Interactive :public BaseMain
{
public:

	Interactive();

	virtual void MainFunc(int argc, char * argv[]) override;

private:

	static GLsizei winWidth;
	static GLsizei winHeight;

	// 初始线段端点
	static GLint endPtCrt;

	// 方形边长
	static GLint edgeLength;

	// 标准库动态数组
	// static std::vector<Point> pts;

private:

	void init();

	static void displayFcn();

	static void winReshapeFcn(GLint newWidth, GLint newHeight);

	// 画点
	static void plotPoint(GLint x, GLint y);

	// 左键画点
	static void mousePtPlot(GLint button, GLint action, GLint xMouse, GLint yMouse);

	// 画线段
	static void drawLineSegment(Point endPt1, Point endPt2);

	// 画折线
	static void polyline(GLint button, GLint action, GLint xMouse, GLint yMouse);

	// 按下c,移动鼠标画曲线
	static void curveDrawing(GLubyte curvePlotKey, GLint xMouse, GLint yMouse);

	// 绘制方形
	static void fillSquare(GLint button, GLint action, GLint xMouse, GLint yMouse);

	// 按下2,3,4增大方形
	static void enlargeSquare(GLubyte sizeFacttor, GLint xMouse, GLint yMouse);

	// 按下F2,F4减小方形
	static void reduceSquare(GLint reductionKey, GLint xMouse, GLint yMouse);

};