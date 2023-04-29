#ifndef __VECTOR3D_H__
#define __VECTOR3D_H__
#include <math.h>

class Matrix3x3;

class Vector3D 
{
	double x, y, z;

public:
	Vector3D(const Vector3D& v);
	Vector3D(double _x = 0, double _y = 0, double _z = 0);

	double getX() const { return x; }
	double getY() const { return y; }
	double getZ() const { return z; }

	void setX(double x) { this->x = x; }
	void setY(double y) { this->y = y; }
	void setZ(double z)  { this->z = z; }

	double getLength() const;
	double dot(Vector3D v) const;
	Vector3D normalize() const;
	Vector3D cross(Vector3D v) const;
	bool insideTriangle(Vector3D v1, Vector3D v2, Vector3D v3);

	Vector3D applyMatrix(Matrix3x3& matrix);
	void operator+=(Vector3D v);
	Vector3D& operator=(const Vector3D& v);
};

Vector3D operator+(Vector3D v1, Vector3D v2);
Vector3D operator-(Vector3D v1, Vector3D v2);
Vector3D operator*(Vector3D v, double n);

class Matrix3x3
{
	Vector3D i, j, k;

public:
	Matrix3x3(Vector3D _i, Vector3D _j, Vector3D _k);

	Matrix3x3() { i = Vector3D(); j = Vector3D(); k = Vector3D(); }

	Vector3D getI() const;
	Vector3D getJ() const;
	Vector3D getK() const;

	//Vector3D applyMatrix(Vector3D v);

};



#endif