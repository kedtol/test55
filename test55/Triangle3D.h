#pragma once
#include "Vector3D.h"
#include "Material.h"

class Triangle3D
{
	Vector3D v1, v2, v3;
	Material m;

public:
	Triangle3D(Vector3D _v1, Vector3D _v2, Vector3D _v3, Material _m);
	double getDistance(Vector3D v);
	Vector3D getV1() { return v1; }
	Vector3D getV2() { return v2; }
	Vector3D getV3() { return v3; }
	Material getM() { return m; }
};