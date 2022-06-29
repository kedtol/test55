#pragma once
#include "Vector3D.h"
#include "Color.h"

class Light
{
	Vector3D position;
	double luminosity;
	double reach;
	Color color;

public:
	Light();
	
};