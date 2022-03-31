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

Vector3D Surface::intersect(Line line) const // only works with try catch
{
	Vector3D intersection = Vector3D();

	double div = normal.dot(line.getDir());
	double t = 0;
	//if (div != 0)
	//{
		//t = normal.dot(position - line.getPos()) / div;
		t = (normal.getX() * (position.getX() - line.getPos().getX()) + normal.getY() * (position.getY() - line.getPos().getY()) + normal.getZ() * (position.getZ() - line.getPos().getZ())) / ((normal.getX() * line.getDir().getX()) + (normal.getY() * line.getDir().getY()) + (normal.getZ() * line.getDir().getZ()));

		intersection = line.getDir() * t + line.getPos();
	//}
	//else
	//{
	//	throw "div by zero"; // todo: exception class
	//}

	if (t <= -1)
		throw "intersection fail";
		
	return intersection;
}
