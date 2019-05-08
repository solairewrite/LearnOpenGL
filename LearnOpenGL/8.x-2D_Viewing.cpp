#include "pch.h"
#include "8.x-2D_Viewing.h"

Viewing_2D::Viewing_2D()
{

}

void Viewing_2D::MainFunc(int argc, char * argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowPosition(50, 50);
	glutInitWindowSize(600, 300);
	glutCreateWindow("分屏");

	init();

	int DrawIndex = 0;
	switch (DrawIndex)
	{
	case 0:	glutDisplayFunc(displayFcn);	break;
	default: break;
	}

	//glutReshapeFunc(WindowReshape);

	glutMainLoop();
}

void Viewing_2D::init()
{
	// 设置窗口颜色
	glClearColor(1.0, 1.0, 1.0, 0.0);

	// 设置世界坐标裁剪窗口
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(-100.0, 100.0, -100.0, 100.0);

	// 设置构建几何变换矩阵模式
	glMatrixMode(GL_MODELVIEW);
}

void Viewing_2D::triangle(Point *verts)
{
	GLint k;

	glBegin(GL_TRIANGLES);
	{
		for (k=0;k<3;k++)
		{
			glVertex2f(verts[k].X, verts[k].Y);
		}
	}
	glEnd();
}

void Viewing_2D::displayFcn()
{
	Point verts[3] = { Point(-50.0,-25.0),Point(50.0,-25.0),Point(0.0,50.0) };

	// 清除显示窗口
	glClear(GL_COLOR_BUFFER_BIT);

	// 绘制颜色
	glColor3f(0.0, 0.0, 1.0);

	// 左边视口
	glViewport(0, 0, 300, 300);
	triangle(verts);

	// 旋转三角形,在右边窗口显示
	glColor3f(1.0, 0.0, 0.0);
	glViewport(300, 0, 300, 300);
	// 绕Z轴旋转
	glRotatef(90.0, 0.0, 0.0, 1.0);
	triangle(verts);
	glLoadIdentity();

	glFlush();
}

