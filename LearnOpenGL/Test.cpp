#include "pch.h"
#include "Test.h"
#include<gl/GLUT.H>

// 显示回调函数
void Test::myDisplay()
{
	// 使用glClearColor中指定的值设定颜色缓存区的值，即将窗口中的每一个像素设置为背景色
	glClear(GL_COLOR_BUFFER_BIT);
	// 绘图颜色
	glColor3f(0.0f, 0.0f, 0.0f);
	// 图形的坐标，绘制一个左下角在（50，100），右上角在（150，50）的矩形
	glRectf(0.0f, 10.0f, 100.0f, 120.0f);
	// 清空OpenGL命令缓冲区，强制执行命令缓冲区中所有OpenGL函数
	glFlush();
}

void Test::Initial()
{
	// 白色背景
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	// OpenGL按照三维方式来处理图像，所以需要一个投影变换将三维图形投影到显示器的二维空间中
	glMatrixMode(GL_PROJECTION);
	// 将一个x坐标在0~200，y坐标0~150范围内的矩形坐标区域投影到显示器窗口
	// 用于控制缩放
	// glRectf()的宽度/gluOrtho2D()的宽度 -> 在窗口glutInitWindowSize()中,所占宽度的比例
	gluOrtho2D(0.0, 200, 0.0, 300.0);
}

void Test::MainFunc(int argc, char * argv[])
{
	// 使用glut库需要进行初始化
	glutInit(&argc, argv);
	// 设定窗口显示模式，颜色模型和缓存，这里是RGB颜色模型和单缓存
	glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
	// 设定窗口的初始位置，屏幕左上角为原点，单位为像素
	glutInitWindowPosition(100, 300);
	// 设定窗口的大小
	glutInitWindowSize(500, 400);
	// 创建一个窗口，参数是窗口标题名
	glutCreateWindow("第一个OpenGL程序——搭建环境");
	// 将myDisplay指定为当前窗口的显示内容函数
	glutDisplayFunc(&Test::myDisplay);
	Initial();
	// 使窗口框架运行起来，使显示回调函数开始工作
	glutMainLoop();
}
