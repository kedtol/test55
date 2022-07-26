#include "Light.h"

Light::Light(Vector3D pos, Color c, double r, double l)
{
	position = pos;
	color = c;
	reach = r;
	luminosity = l;
}

Vector3D Light::getPos() const
{
	return position;
}