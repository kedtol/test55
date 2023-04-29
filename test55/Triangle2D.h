#pragma once
#include <GL/glew.h>
#include <SDL.h>
#include <SDL_opengl.h>
#include <GL/glut.h>
#include <vector>
//#include "SDL2_gfxPrimitives.h"
#include "Vector2D.h"
#include "Material.h"
#include "Line2D.h"

class Triangle2D
{
	Vector2D v1, v2, v3;
	Material m,m1,m2;
	
	double d; // distance from camera
public:
	Triangle2D(Vector2D _v1, Vector2D _v2, Vector2D _v3,Material _m, Material _m1, Material _m2, double _d);
	void draw(SDL_Renderer* renderer);
	void render(SDL_GLContext* gcontext);
	double getD() const { return d; }
};