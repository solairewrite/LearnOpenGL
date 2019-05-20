#include "pch.h"
#include <GL/glew.h>
#include "22.x-GL_Shader.h"
#include <stdio.h>

GLShader::GLShader()
{

}

void GLShader::MainFunc(int argc, char * argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(WindowWidth, WindowHeight);
	glutCreateWindow("可编程着色器");

	init();

	//UseShader();

	glutDisplayFunc(displayFunc);
	glutReshapeFunc(WindowReshape);

	glutMainLoop();
}

void GLShader::init()
{
	glClearColor(0.78, 0.93, 0.81, 1.0);
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(0, WindowWidth, 0, WindowHeight);
}

void GLShader::displayFunc()
{
	GLint padding = 80;

	glColor3f(1.0, 0.6, 0.1);

	glBegin(GL_POLYGON);
	{
		glVertex2i(padding, padding);
		glVertex2i(WindowWidth - padding, padding);
		glVertex2i(WindowWidth - padding, WindowHeight - padding);
		glVertex2i(padding, WindowHeight - padding);
	}
	glEnd();

	glFlush();
}

void GLShader::UseShader()
{
	GLuint vertShader; // 顶点着色器句柄
	GLuint fragShader; // 片元着色器句柄
	// 创建着色器对象
	// 程序这里崩溃
	vertShader = glCreateShader(GL_VERTEX_SHADER);
	fragShader = glCreateShader(GL_FRAGMENT_SHADER);

	char* vertSource; // 顶点着色器源码
	char* fragSource; // 片元着色器源码
	// 为着色器读入源代码
	vertSource = readTextFile("simpleShader.vert");
	if (vertSource == NULL)
	{
		fputs("Failed to read vertex shader\n", stderr);
		exit(EXIT_FAILURE);
	}
	fragSource = readTextFile("simpleShader.frag");
	if (fragSource == NULL)
	{
		fputs("Failed to read fragment shader\n", stderr);
		exit(EXIT_FAILURE);
	}

	// 将源字符串关联到着色器上
	glShaderSource(vertShader, 1, (const char**)&vertSource, NULL);
	glShaderSource(fragShader, 1, (const char**)&fragSource, NULL);
	
	// 释放字符串空间
	free(vertSource);
	free(fragSource);

	// 编译着色器
	glCompileShader(vertShader);
	glCompileShader(fragShader);

	// 查询是否编译成功
	GLint status;

	glGetShaderiv(vertShader, GL_COMPILE_STATUS, &status);
	if (status != GL_TRUE)
	{
		fputs("Error in vertex shader compilation\n", stderr);
		exit(EXIT_FAILURE);
	}
	glGetShaderiv(fragShader, GL_COMPILE_STATUS, &status);
	if (status != GL_TRUE)
	{
		fputs("Error in fragment shader compilation\n", stderr);
		exit(EXIT_FAILURE);
	}

	// 编译好后,创建程序对象,并将着色器对象与之关联,最后链接整个程序
	GLuint program;
	// 创建程序对象,返回句柄
	program = glCreateProgram();
	// 关联着色器与程序
	glAttachShader(program, vertShader);
	glAttachShader(program, fragShader);
	// 链接程序
	glLinkProgram(program);

	// 粗略检查:确认是够链接成功
	glGetProgramiv(vertShader, GL_LINK_STATUS, &status);
	if (status != GL_TRUE)
	{
		fputs("Error when linking shader program\n", stderr);
		exit(EXIT_FAILURE);
	}

	// 查询着色器/程序信息日志
	// 先查询日志的长度,然后将日志读入一个字符缓冲区再输出
	GLint length;
	GLsizei num;
	char* log;

	glGetShaderiv(vertShader, GL_INFO_LOG_LENGTH, &length);
	if (length > 0)
	{
		log = (char*)malloc(sizeof(char) * length);
		// length:缓冲区的尺寸, num:写入缓冲区的字节数
		glGetShaderInfoLog(vertShader, length, &num, log);
		fprintf(stderr, "%s\n", log);
	}

	glGetProgramiv(program, GL_INFO_LOG_LENGTH, &length);
	if (length > 0)
	{
		log = (char*)malloc(sizeof(char) * length);
		glGetProgramInfoLog(program, length, &num, log);

		fprintf(stderr, "%s\n", log);
	}

	// 激活着色器
	glUseProgram(program);

	// 冻结着色器
	glUseProgram(0);
}
