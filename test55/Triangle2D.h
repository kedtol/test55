#pragma once
#include <SDL.h>
#include "SDL2_gfxPrimitives.h"
#include "Vector2D.h"
#include "Material.h"

class Triangle2D
{
	Vector2D v1, v2, v3;
	Material m;
	double d; // distance from camera

public:
	Triangle2D(Vector2D _v1, Vector2D _v2, Vector2D _v3,Material _m, double _d);
	void draw(SDL_Renderer* renderer);
	double getD() { return d; }
};