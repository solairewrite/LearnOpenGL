#include "BaseMain.h"
#include <GL/glut.h>

class Viewing_2D : public BaseMain
{
public:

	Viewing_2D();

	virtual void MainFunc(int argc, char * argv[]) override;

private:

	void init();

	static void triangle(Point *verts);

	static void displayFcn();
};