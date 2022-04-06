#include "Surface.h"

Surface::Surface()
{
	normal = Vector3D();
	position = Vector3D();
}

Surface::Surface(Vector3D _position, Vector3D _normal)
{
	normal = _normal;
	position = _position;
}

Vector3D Surface::intersect(Line line,bool* failed) const // only works with try catch
{
	Vector3D intersection = Vector3D();

	double div = normal.dot(line.getDir());
	double t = 0;
	if (div != 0)
	{
		t = normal.dot(position - line.getPos()) / div;
		intersection = line.getDir() * t + line.getPos();
	}
	else
	{
		*failed = true; // todo: exception class
	}

	if (t > -0.99)
		return intersection;
	else
	{
		*failed = true;
		return Vector3D();
	}
}
