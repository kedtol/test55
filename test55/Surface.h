#pragma once
#include "Vector3D.h"
#include "Line.h"

class Surface
{
	Vector3D normal, position;

public:
	Surface();
	Surface(Vector3D _normal, Vector3D _position);

	Vector3D getNormal() const { return normal; }
	Vector3D getPos() const { return position; }

	Vector3D intersect(Line line) const;

};