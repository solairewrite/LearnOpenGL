#include "pch.h"
#include "13.x-Present.h"

int Present::DrawIndex = 0;

Present::Present()
{

}

void Present::MainFunc(int argc, char * argv[])
{
	//glutInit(&argc, argv);
	//glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	//glutInitWindowPosition(100, 100);
	//glutInitWindowSize(winWidth, winHeight);
	//glutCreateWindow("三位对象的表示");

	//init();
	//gluLookAt(5.0, 5.0, 5.0, // 相机位置
	//	0.0, 0.0, 0.0, // 被观察点
	//	0.0, 1.0, 0.0); // 相机向上方向
	//glutDisplayFunc(displayWirePolyhedra);
	//glutReshapeFunc(winReshapeFcn);

	//glutMainLoop();

	/***********************************/

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(winWidth, winHeight);
	glutCreateWindow("二次曲面");

	init();
	gluLookAt(2.0, 2.0, 2.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0);
	glutDisplayFunc(wireQuadSurfs);
	glutReshapeFunc(winReshapeFcn2);

	glutMainLoop();
}

void Present::init()
{
	glClearColor(1.0, 1.0, 1.0, 0.0);
}

void Present::displayWirePolyhedra()
{
	glClear(GL_COLOR_BUFFER_BIT);

	glColor3f(0.0, 0.0, 1.0);

	//gluLookAt(5.0, 5.0, 5.0, // 相机位置
	//	0.0, 0.0, 0.0, // 被观察点
	//	0.0, 1.0, 0.0); // 相机向上方向

	glScalef(1.5, 2.0, 1.0);
	glutWireCube(1.0);
	glScalef(1 / 1.5, 0.5, 1.0);

	glScalef(0.8, 0.5, 0.8);
	glTranslatef(-6.0, -5.0, 0.0);
	glutWireDodecahedron();
	glTranslatef(6, 5, 0);
	glScalef(1 / 0.8, 2, 1 / 0.8);

	glTranslatef(8.6, 8.6, 2.0);
	glutWireTetrahedron();
	glTranslatef(-8.6, -8.6, -2.0);

	glTranslatef(-3.0, -1.0, 0.0);
	glutWireOctahedron();
	glTranslatef(3.0, 1.0, 0.0);

	glScalef(0.8, 0.8, 1.0);
	glTranslatef(4.3, -2.0, 0.5);
	glutWireIcosahedron();
	glTranslatef(-4.3, 2.0,-0.5);
	glScalef(1/0.8, 1/0.8, 1.0);

	glFlush();
}

void Present::winReshapeFcn(GLint newWidth, GLint newHeight)
{
	glViewport(0, 0, newWidth, newHeight);

	glMatrixMode(GL_PROJECTION);
	// 指定棱台透视体的观察投影
	//glFrustum(xwMin, xwMax, ywMin, ywMax, dnear, dfar);
	glFrustum(-1.0, 1.0, -1.0, 1.0, 2.0, 20.0);

	glMatrixMode(GL_MODELVIEW);

	glClear(GL_COLOR_BUFFER_BIT);
}

void Present::wireQuadSurfs()
{
	glClear(GL_COLOR_BUFFER_BIT);

	glColor3f(0.0, 0.0, 1.0);

	// 球
	glPushMatrix();
	glTranslatef(1.0, 1.0, 0.0);
	glutWireSphere(0.75, 8, 6);
	glPopMatrix();

	// 圆锥
	glPushMatrix();
	glTranslatef(1.0, -0.5, 0.5);
	glutWireCone(0.7, 2.0, 7, 6);
	glPopMatrix();

	// 圆柱
	GLUquadricObj* cylinder;
	glPushMatrix();
	glTranslatef(0.0, 1.2, 0.8);
	cylinder = gluNewQuadric();
	gluQuadricDrawStyle(cylinder, GLU_LINE);
	gluCylinder(cylinder, 0.6, 0.6, 1.5, 6, 4);
	glPopMatrix();

	glFlush();
}

void Present::winReshapeFcn2(GLint newWidth, GLint newHeight)
{
	glViewport(0, 0, newWidth, newHeight);

	glMatrixMode(GL_PROJECTION);
	glOrtho(-2.0, 2.0, -2.0, 2.0, 0.0, 5.0);

	glMatrixMode(GL_MODELVIEW);

	glClear(GL_COLOR_BUFFER_BIT);
}
