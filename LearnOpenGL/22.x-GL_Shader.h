#include "BaseMain.h"

class GLShader : public BaseMain
{
public:

	GLShader();

	virtual void MainFunc(int argc, char * argv[]) override;

private:

	void init();

	static void displayFunc();

	void UseShader();
};