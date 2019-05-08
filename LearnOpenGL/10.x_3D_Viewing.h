#include "BaseMain.h"
#include <GL/glut.h>

class Viewing_3D : public BaseMain
{
public:

	Viewing_3D();

	virtual void MainFunc(int argc, char * argv[]) override;

private:

	// 显示窗口尺寸
	static GLint winWidth , winHeight;

	// 观察坐标原点
	GLfloat x0 = 100.0, y0 = 50.0, z0 = 50.0;
	// 观察对象
	GLfloat xref = 50.0, yref = 50.0, zref = 0.0;
	// 相机向上方向
	GLfloat Vx = 0.0, Vy = 1.0, Vz = 0.0;

	// 裁剪窗口
	GLfloat xwMin = -40.0, ywMin = -60.0, xwMax = 40.0, ywMax = 60.0;

	// 近平面,远平面
	GLfloat dnear = 25.0, dfar = 125.0;

protected:

	void init();

	static void displayFcn();

	static void reshapeFcn(GLint newWidth, GLint newHeight);
};