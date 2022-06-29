#pragma once
#include "Light.h"

class Material
{
	Color color;
	Color baseColor;
	// i cant really write more... the engine only knows the 3 points of a tri and a color now
public:
	Material() { color = Color(); }
	Material(Color c) { color = c; }
	
	char getR() { return color.getR(); }
	char getG() { return color.getG(); }
	char getB() { return color.getB(); }
	void bakeLight(Light l,Vector3D pos);
};