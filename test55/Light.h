#pragma once
#include "Vector3D.h"
#include "Color.h"

class Light
{
	Vector3D position;
	double luminosity;
	double reach;
	Color color;

public:
	Light(Vector3D pos, Color color, double r, double l);
	Vector3D getPos() const;
	Color getColor() const { return color; }
	void setPos(Vector3D& pos) { position = pos; }
	double getReach() const { return reach; }
	double getLuminosity() const { return luminosity; }
};