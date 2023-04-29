#pragma once
#include <GL/glew.h>
#include <SDL.h>
#include <SDL_opengl.h>
#include <GL/glut.h>
#include "Vector3D.h"
#include "Material.h"

class Triangle3D
{
	Vector3D v1, v2, v3;
	Material m1, m2, m3;

public:
	Triangle3D(Vector3D _v1, Vector3D _v2, Vector3D _v3, Material _m1, Material _m2, Material _m3);
	double getDistance(Vector3D v);
	Vector3D getV1() { return v1; }
	Vector3D getV2() { return v2; }
	Vector3D getV3() { return v3; }
	Vector3D getWpoint() const;
	
	
	Material getM() { return m1; }
	Material getM1() { return m1; }
	Material getM2() { return m2; }
	Material getM3() { return m3; }
	void render(SDL_GLContext* gcontext);
};