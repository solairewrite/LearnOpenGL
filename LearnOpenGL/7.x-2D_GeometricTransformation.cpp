#include "pch.h"
#include "7.x-2D_GeometricTransformation.h"
#include <math.h>
#include <iostream>

using namespace std;

GLfloat GeometricTransformation_2D::xwcMin = 0.0;
GLfloat GeometricTransformation_2D::xwcMax = 225.0;
GLfloat GeometricTransformation_2D::ywcMin = 0.0;
GLfloat GeometricTransformation_2D::ywcMax = 225.0;
Matrix3x3 GeometricTransformation_2D::matComposite;

int GeometricTransformation_2D::DrawIndex = 1; // 绘制什么

GeometricTransformation_2D::GeometricTransformation_2D()
{

}

void GeometricTransformation_2D::MainFunc(int argc, char * argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowPosition(50, 50);

	switch (DrawIndex)
	{
	case 0:	glutInitWindowSize(winWidth, winHeight);		break;
	case 1:	glutInitWindowSize(winWidth , winWidth * 3 / 5);	break;
	default: break;
	}
	
	glutCreateWindow("2维几何变换");

	init();

	switch (DrawIndex)
	{
	case 0:		glutDisplayFunc(displayFcn);			break;
	case 1:		glutDisplayFunc(TransformUseMatrix);	break;
	default:											break;
	}
	
	glutReshapeFunc(winReshapeFcn);

	glutMainLoop();
}

void GeometricTransformation_2D::init()
{
	glClearColor(1.0, 1.0, 1.0, 0.0);
}

void GeometricTransformation_2D::matrix3x3SetIdentity(Matrix3x3 matIdent3x3)
{
	GLint row, col;

	for (row=0;row<3;row++)
	{
		for (col=0;col<3;col++)
		{
			matIdent3x3[row][col] = (row == col);
		}
	}
}

void GeometricTransformation_2D::matrix3x3Premultiply(Matrix3x3 m1, Matrix3x3 m2)
{
	GLint row, col;
	Matrix3x3 matTemp;

	for (row=0;row<3;row++)
	{
		for (col=0;col<3;col++)
		{
			matTemp[row][col] = m1[row][0] * m2[0][col] + m1[row][1] * m2[1][col] + m1[row][2] * m2[2][col];
		}
	}

	for (row=0;row<3;row++)
	{
		for (col=0;col<3;col++)
		{
			m2[row][col] = matTemp[row][col];
		}
	}
}

void GeometricTransformation_2D::translate2D(GLfloat tx, GLfloat ty)
{
	Matrix3x3 matTrans1;

	// 初始化为单位矩阵
	matrix3x3SetIdentity(matTrans1);

	matTrans1[0][2] = tx;
	matTrans1[1][2] = ty;

	matrix3x3Premultiply(matTrans1, matComposite);
}

void GeometricTransformation_2D::rotate2D(Point pivotPt, GLfloat theta)
{
	Matrix3x3 matRot;

	matrix3x3SetIdentity(matRot);

	matRot[0][0] = cos(theta);
	matRot[0][1] = -sin(theta);
	matRot[0][2] = pivotPt.X*(1 - cos(theta)) + pivotPt.Y*sin(theta);
	matRot[1][0] = sin(theta);
	matRot[1][1] = cos(theta);
	matRot[1][2] = pivotPt.Y*(1 - cos(theta)) - pivotPt.X*sin(theta);

	matrix3x3Premultiply(matRot, matComposite);
}

void GeometricTransformation_2D::scale2D(GLfloat sx, GLfloat sy, Point fixedPt)
{
	Matrix3x3 matScale;
	matrix3x3SetIdentity(matScale);

	matScale[0][0] = sx;
	matScale[0][2] = (1 - sx)*fixedPt.X;
	matScale[1][1] = sy;
	matScale[1][2] = (1 - sy)*fixedPt.Y;

	matrix3x3Premultiply(matScale, matComposite);
}

void GeometricTransformation_2D::transformVerts2D(GLint nVerts, Point* verts)
{
	GLint k;
	GLfloat temp;

	for (k=0;k<nVerts;k++)
	{
		temp = matComposite[0][0] * verts[k].X + matComposite[0][1] * verts[k].Y + matComposite[0][2];
		verts[k].Y = matComposite[1][0] * verts[k].X + matComposite[1][1] * verts[k].Y + matComposite[1][2];
		verts[k].X = temp;
	}
}

void GeometricTransformation_2D::triangle(Point* verts)
{
	GLint k;

	//glColor3f(1.0f, 0.0f, 0.0f);
	glBegin(GL_TRIANGLES);
	{
		for (k=0;k<3;k++)
		{
			glVertex2f(verts[k].X, verts[k].Y);
			cout << k << ": (" << verts[k].X << ", " << verts[k].Y << ")" << endl;
		}
	}
	glEnd();
}

void GeometricTransformation_2D::displayFcn()
{
	// 三角形初始位置
	GLint nVerts = 3;
	Point verts[3] = { Point(50.0,25.0),Point(150.0,25.0),Point(100.0,100.0) };

	// 中心点
	Point centroidPt;

	GLint k, xSum = 0, ySum = 0;
	for (k=0;k<nVerts;k++)
	{
		xSum += verts[k].X;
		ySum += verts[k].Y;
	}
	centroidPt.X = GLfloat(xSum) / GLfloat(nVerts);
	centroidPt.Y = GLfloat(ySum) / GLfloat(nVerts);

	// 几何变换参数
	Point pivPt, fixedPt;
	pivPt = centroidPt; // 旋转
	fixedPt = centroidPt; // 缩放

	GLfloat tx = 0.0, ty = 100.0;
	GLfloat sx = 0.5, sy = 0.5;
	GLdouble theta = PI / 2.0;

	glClear(GL_COLOR_BUFFER_BIT);

	glColor3f(0.0, 0.0, 1.0); // 初始颜色为蓝色
	triangle(verts);

	// 初始化转换矩阵为单位矩阵
	matrix3x3SetIdentity(matComposite);

	// 构建转换矩阵
	scale2D(sx, sy, fixedPt);
	rotate2D(pivPt, theta);
	translate2D(tx, ty);

	transformVerts2D(nVerts, verts);

	glColor3f(1.0, 0.0, 0.0);
	triangle(verts);

	glFlush();
}

void GeometricTransformation_2D::winReshapeFcn(GLint newWidth, GLint newHeight)
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	switch (DrawIndex)
	{
	case 0:		gluOrtho2D(xwcMin, xwcMax, ywcMin, ywcMax);		break;
	case 1:		gluOrtho2D(-200, 250, -10, ywcMax);				break;
	default:													break;
	}

	glClear(GL_COLOR_BUFFER_BIT);
}

void GeometricTransformation_2D::TransformUseMatrix()
{
	glMatrixMode(GL_MODELVIEW);

	glColor3f(1.0, 0.0, 1.0);
	glLineWidth(3.0f);
	glBegin(GL_LINES); // 坐标轴
	{
		glVertex2i(-200, 0);
		glVertex2i(250, 0);
		glVertex2i(0, -10);
		glVertex2i(0, 200);
	}
	glEnd();

	glColor3f(1.0, 0.0, 0.0);
	glRecti(50, 100, 200, 150);

	glColor3f(0.0, 0.0, 1.0);
	glTranslatef(-200.0, -50.0, 0.0); // 变换矩阵是累乘的
	glRecti(50, 100, 200, 150);
	glLoadIdentity(); // 重置变换矩阵为单位矩阵(由于绘制函数会多次调用,而变换矩阵是有记忆的,导致后面的绘制覆盖前面的)

	glColor3f(0.0, 1.0, 1.0);
	glRotatef(90.0, 0.0, 0.0, 1.0); // 绕Z轴旋转90°
	glRecti(50, 100, 200, 150);
	glLoadIdentity();

	glColor3f(1.0, 1.0, 0.0);
	glScalef(-0.3, 0.9, 1.0); // x=-0.5,负值生成反射(镜像)矩阵,y=0.9,基准点是x轴(理解为所有的y*0.9)
	glRecti(50, 100, 200, 150);
	glLoadIdentity();

	glFlush();
}

