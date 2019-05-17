#include "pch.h"
#include "18.x-TextureAndSurface.h"

TextureAndSurface::TextureAndSurface()
{

}

void TextureAndSurface::MainFunc(int argc, char * argv[])
{
	BaseMain::MainFunc(argc, argv);

	glutCreateWindow("第18章 纹理与表面细节添加方法");

	BaseInit();

	int DrawIndex = 1;
	switch (DrawIndex)
	{
	case 0:		glutDisplayFunc(DrawTexture1D);		break;
	case 1:		glutDisplayFunc(DrawTexture2D);		break;
	default:	break;
	}

	glutReshapeFunc(WindowReshape);

	glutMainLoop();
}

void TextureAndSurface::DrawTexture1D()
{
	GLint k;
	GLubyte texLine[16]; // 4个点*每个点RGBA 4个值
	Point p1(20, 20);
	Point p2(780,580);

	// 1,3点采用(0,255,0,255)
	for (k = 0; k <= 2; k += 2)
	{
		texLine[4 * k] = 0;
		texLine[4 * k + 1] = 255;
		texLine[4 * k + 2] = 0;
		texLine[4 * k + 3] = 255;
	}

	for (k = 1; k <= 3; k += 2)
	{
		texLine[4 * k] = 255;
		texLine[4 * k + 1] = 0;
		texLine[4 * k + 2] = 0;
		texLine[4 * k + 3] = 255;
	}

	// MAG: 放大
	glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	glTexImage1D(
		GL_TEXTURE_1D,	// 为直线定义纹理数组
		0,				// 该数组不是某个大纹理数组的所见
		GL_RGBA,		// 纹理图案的每一个颜色用RGBA四个值指定
		4,				// 线性纹理图案的数量
		0,				// 不希望在纹理周围有边界
		GL_RGBA,		// 纹理图案怎样指定颜色值 
		GL_UNSIGNED_BYTE, // 数据类型
		texLine			// 纹理颜色和边界颜色
	);

	// 顶点
	glColor3f(1.0f, 0.5f, 0.0f);
	glPointSize(10.0f);
	glBegin(GL_POINTS);
	{
		glVertex2i(p1.X, p1.Y);
		glVertex2i(p2.X, p2.Y);
	}
	glEnd();

	// 采用纹理
	glEnable(GL_TEXTURE_1D);
	{
		glBegin(GL_LINES);
		{
			glTexCoord1f(0.0); // 纹理的起始位置
			glVertex2f(p1.X, p1.Y); // 顶点的起始位置
			glTexCoord1f(1.0);
			glVertex2f(p2.X, p2.Y);
		}
		glEnd();
	}

	int Offset = 30;
	glColor3f(1.0f, 0.5f, 0.0f);
	glPointSize(10.0f);
	glBegin(GL_POINTS);
	{
		glVertex2i(p1.X, p1.Y + Offset);
		glVertex2i(p2.X, p2.Y + Offset);
	}
	glEnd();

	glEnable(GL_TEXTURE_1D);
	{
		glLineWidth(3.0f);
		glBegin(GL_LINES);
		{
			glTexCoord1f(0.25); // 纹理的起始位置
			glVertex2f(p1.X, p1.Y + Offset); // 顶点的起始位置
			glTexCoord1f(0.75);
			glVertex2f(p2.X, p2.Y + Offset);
		}
		glEnd();
	}
	glDisable(GL_TEXTURE_1D);

	glFlush();
}

void TextureAndSurface::DrawTexture2D()
{
	// 可以看出,256很平滑,64开始看出明显的锯齿
	const GLint texSize = 256;
	GLubyte texArray[texSize][texSize][4];
	Point p1(20.0f, 20.0f);
	Point p2(780.0f, 20.0f);
	Point p3(780.0f, 580.0f);
	Point p4(20.0f, 580.0f);

	// 将颜色值赋给数组
	for (int i = 0; i < texSize; i++)
	{
		for (int j = 0; j < texSize; j++)
		{
			texArray[i][j][0] = i * (256 / texSize);
			texArray[i][j][1] = j * (256 / texSize);
			texArray[i][j][2] = 0;
			texArray[i][j][3] = 255;
		}
	}

	// 选择最近的颜色
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexImage2D(
		GL_TEXTURE_2D,
		0,
		GL_RGBA,
		texSize, // 贴图宽度
		texSize, // 贴图高度
		0,
		GL_RGBA,
		GL_UNSIGNED_BYTE,
		texArray
	);

	// 二维纹理图案,自下而上
	glEnable(GL_TEXTURE_2D);
	{
		glBegin(GL_QUADS); 
		{
			glTexCoord2f(0.0, 0.0);		glVertex2f(p1.X, p1.Y);
			glTexCoord2f(1.0, 0.0);		glVertex2f(p2.X, p2.Y);
			glTexCoord2f(1.0, 1.0);		glVertex2f(p3.X, p3.Y);
			glTexCoord2f(0.0, 1.0);		glVertex2f(p4.X, p4.Y);
		}
		glEnd();
	}
	glDisable(GL_TEXTURE_2D);

	glFlush();
}
