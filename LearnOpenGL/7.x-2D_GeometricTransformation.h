#pragma once
#include "BaseMain.h"
#include "GL/glut.h"

typedef GLfloat Matrix3x3[3][3];

class GeometricTransformation_2D : public BaseMain
{
public:
	GeometricTransformation_2D();

	virtual void MainFunc(int argc, char * argv[]) override;

private:

	// 初始显示窗口尺寸
	GLsizei winWidth = 600, winHeight = 600;

	// 世界坐标范围
	static GLfloat xwcMin , xwcMax;
	static GLfloat ywcMin , ywcMax;

	static Matrix3x3 matComposite;

	static int DrawIndex;

private:

	void init();

	// 将指定矩阵设为单位矩阵
	static void matrix3x3SetIdentity(Matrix3x3 matIdent3x3);

	// 矩阵乘法,值保存在m2中
	static void matrix3x3Premultiply(Matrix3x3 m1, Matrix3x3 m2);

	// 平移,平移矩阵见7.2.2
	static void translate2D(GLfloat tx, GLfloat ty);

	// 旋转
	static void rotate2D(Point pivotPt, GLfloat theta);

	// 缩放
	static void scale2D(GLfloat sx, GLfloat sy, Point fixedPt);

	// 变换顶点
	static void transformVerts2D(GLint nVerts, Point* verts);

	// 绘制三角形
	static void triangle(Point* verts);

	// 显示回调
	static void displayFcn();

	static void winReshapeFcn(GLint newWidth, GLint newHeight);

	// 使用矩阵
	static void TransformUseMatrix();
};