#include "BaseMain.h"
#include <GL/glut.h>

class TextureAndSurface : public BaseMain
{
public:
	TextureAndSurface();

	virtual void MainFunc(int argc, char * argv[])override;

private:

	static void DrawTexture1D();

	static void DrawTexture2D();

};