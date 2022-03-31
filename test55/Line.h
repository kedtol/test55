#ifndef __LINE_H__
#define __LINE_H__
#include "Vector3D.h"

class Line
{
	Vector3D position, direction;

public:
	Line(Vector3D position, Vector3D direction);

	Vector3D getDir() const;
	Vector3D getPos() const;
};

#endif