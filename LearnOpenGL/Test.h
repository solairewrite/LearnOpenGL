#pragma once
#include "BaseMain.h"

class Test :public BaseMain
{
public:
	virtual void MainFunc(int argc, char * argv[]) override;

private:
	static void myDisplay();
	void Initial();
};