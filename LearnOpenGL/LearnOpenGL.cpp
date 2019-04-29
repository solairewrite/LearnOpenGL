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

using namespace std;

BaseMain* GetTestClass(string ClassName);

int main(int argc, char * argv[])
{
	cout << "����������" <<endl;

	BaseMain* TestClass = GetTestClass("GraphicAttribute");

	TestClass->MainFunc(argc, argv);
}

BaseMain* GetTestClass(string ClassName)
{
	if (ClassName == "Test")
	{
		return new Test();
	}
	if (ClassName == "Heaxpon")
	{
		return new Heaxpon();
	}
	if (ClassName == "Summary")
	{
		return new Summary();
	}
	if (ClassName == "PieChart")
	{
		return new PieChart();
	}
	if (ClassName == "DrawCurve")
	{
		return new DrawCurve();
	}	
	if (ClassName == "GraphicAttribute")
	{
		return new GraphicAttribute();
	}
	return nullptr;
}