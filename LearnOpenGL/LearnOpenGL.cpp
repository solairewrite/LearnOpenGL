// LearnOpenGL.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <string>
#include "BaseMain.h"
#include "Test.h"
#include "4.16-Hexapon.h"
#include "4.17-1-Summary.h"
#include "4.17-2-PieChart.h"
#include "4.17-3-DrawCurve.h"
#include "5.x-GraphicAttribute.h"
#include "6.x-GraphicAlgorithm.h"
#include "7.x-2D_GeometricTransformation.h"
#include "8.x-2D_Viewing.h"
#include "10.x_3D_Viewing.h"
#include "12.x-Animation.h"
#include "13.x-Present.h"
#include "18.x-TextureAndSurface.h"

enum TestClass
{
	Class_Test,
	Class_Heaxpon,
	Class_Summary,
	Class_PieChart,
	Class_DrawCurve,
	Class_GraphicAttribute,
	Class_GraphicAlgorithm,
	Class_GeometricTransformation_2D,
	Class_Viewing_2D,
	Class_Viewing_3D,
	Class_Animation,
	Class_Present,
	Class_TextureAndSurface,
};

BaseMain* GetTestClass(TestClass inClass)
{
	switch (inClass)
	{
	case Class_Test:						return new Test();							break;
	case Class_Heaxpon:						return new Heaxpon();						break;
	case Class_Summary:						return new Summary();						break;
	case Class_PieChart:					return new PieChart();						break;
	case Class_DrawCurve:					return new DrawCurve();						break;
	case Class_GraphicAttribute:			return new GraphicAttribute();				break;
	case Class_GraphicAlgorithm:			return new GraphicAlgorithm();				break;
	case Class_GeometricTransformation_2D:	return new GeometricTransformation_2D();	break;
	case Class_Viewing_2D:					return new Viewing_2D();					break;
	case Class_Viewing_3D:					return new Viewing_3D();					break;
	case Class_Animation:					return new Animation();						break;
	case Class_Present:						return new Present();						break;
	case Class_TextureAndSurface:			return new TextureAndSurface();				break;
	default:								return nullptr;								break;
	}
}

int main(int argc, char * argv[])
{
	using namespace std;
	cout << "程序运行中" <<endl;

	BaseMain* TestClass = GetTestClass(Class_TextureAndSurface);

	TestClass->MainFunc(argc, argv);
}
