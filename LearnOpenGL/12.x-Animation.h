#include "BaseMain.h"
#include <GL/glut.h>
#include <math.h>
//#include <stdlib.h>

class Animation : public BaseMain
{
public:
	Animation();

	virtual void MainFunc(int argc, char * argv[]) override;

private:

	GLsizei winWidth = 500;
	GLsizei winHeight = 500;
	// 显示列表的名称
	static GLuint regHex;
	static GLfloat rotTheta;

private:

	void init();

	static void displayHex();

	static void rotateHex();

	static void winReshapeFcn(GLint newWidth, GLint newHeight);

	static void MouseFcn(GLint button, GLint action, GLint x, GLint y);
};