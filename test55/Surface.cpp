#include "Surface.h"

Surface::Surface()
{
	normal = Vector3D();
	position = Vector3D();
}

Surface::Surface(Vector3D _normal, Vector3D _position)
{
	normal = _normal;
	position = _position;
}

Vector3D Surface::intersect(Line line) const // only works with try catch
{
	Vector3D intersection = Vector3D();

	double div = normal.dot(line.getDir());
	double t = 0;
	if (div != 0)
	{
		t = normal.dot(position - line.getPos()) / div;
		intersection = line.getPos() + (line.getDir() * t);
	}
	else
	{
		throw "div by zero"; // todo: exception class
	}

	if (t <= -0.99)
		throw "intersection fail";
	else
		return intersection;
}
