#include "Triangle2D.h"

Triangle2D::Triangle2D(Vector2D _v1, Vector2D _v2, Vector2D _v3, Material _m, double _d)
{
	v1 = _v1;
	v2 = _v2;
	v3 = _v3;
	m = _m;
	d = _d;
}

void Triangle2D::draw(SDL_Renderer* renderer)
{
	filledTrigonRGBA(renderer, v1.getX(), v1.getY(), v2.getX(), v2.getY(), v3.getX(), v3.getY(), m.getR(), m.getG(), m.getB(), 255);
	
}
