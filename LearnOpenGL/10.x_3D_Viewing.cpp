#include "pch.h"
#include "10.x_3D_Viewing.h"

GLint Viewing_3D::winWidth = 600;
GLint Viewing_3D::winHeight = 600;

Viewing_3D::Viewing_3D()
{

}

void Viewing_3D::MainFunc(int argc, char * argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowPosition(50, 50);
	glutInitWindowSize(winWidth, winHeight);
	glutCreateWindow("三维观察");

	init();
	glutDisplayFunc(displayFcn);
	glutReshapeFunc(reshapeFcn);

	glutMainLoop();
}

void Viewing_3D::init()
{
	glClearColor(1.0, 1.0, 1.0, 0.0);

	glMatrixMode(GL_MODELVIEW);
	// 观察参数,(相机位置,观察对象位置,相机上方)
	gluLookAt(x0, y0, z0, xref, yref, zref, Vx, Vy, Vz);

	glMatrixMode(GL_PROJECTION);
	// 指定棱台观察体的透视投影
	glFrustum(xwMin, xwMax, ywMin, ywMax, dnear, dfar);
}

void Viewing_3D::displayFcn()
{
	glClear(GL_COLOR_BUFFER_BIT);

	// 方形填充区参数
	glColor3f(0.0, 1.0, 0.0);
	glPolygonMode(GL_FRONT, GL_FILL);
	glPolygonMode(GL_BACK, GL_LINE); // 背面线框模式
	glBegin(GL_QUADS);
	{
		glVertex3f(0.0, 0.0, 0.0);
		glVertex3f(100.0, 0.0, 0.0);
		glVertex3f(100.0, 100.0, 0.0);
		glVertex3f(0.0, 100.0, 0.0);
	}
	glEnd();

	glFlush();
}

void Viewing_3D::reshapeFcn(GLint newWidth, GLint newHeight)
{
	// 视口
	glViewport(0, 0, newWidth, newHeight);

	winWidth = newWidth;
	winHeight = newHeight;
}

