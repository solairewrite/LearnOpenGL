#include "BaseMain.h"
#include <GL/glut.h>

class Present :public BaseMain
{
public:

	Present();

	virtual void MainFunc(int argc, char * argv[]) override;

private:

	GLsizei winWidth = 500;
	GLsizei winHeight = 500;

	static int DrawIndex;

private:

	void init();

	static void displayWirePolyhedra();

	static void winReshapeFcn(GLint newWidth, GLint newHeight);

	static void wireQuadSurfs();

	static void winReshapeFcn2(GLint newWidth, GLint newHeight);

};