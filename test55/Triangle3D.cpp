#include "Triangle3D.h"

Triangle3D::Triangle3D(Vector3D _v1, Vector3D _v2, Vector3D _v3,Material _m)
{
	v1 = _v1;
	v2 = _v2;
	v3 = _v3;
	m = _m;
}

double Triangle3D::getDistance(Vector3D v)
{
	double l1 = (v1 - v).getLength();
	double l2 = (v2 - v).getLength();
	double l3 = (v3 - v).getLength();

	if (l1 > l2 && l1 > l3)
		return l1;

	if (l2 > l1 && l2 > l3)
		return l2;

	if (l3 > l2 && l3 > l1)
		return l3;

	return 0;
}
