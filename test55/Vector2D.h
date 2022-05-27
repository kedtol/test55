#ifndef __VECTOR2D_H__
#define __VECTOR2D_H__
#include <math.h>
#include <iostream>

class Vector2D
{
	double x, y;

public:
	Vector2D(double x = 0, double y = 0);
	Vector2D(const Vector2D& v);

	double getX() const { return x; }
	double getY() const { return y; }

	void randomGradient();
	double getLength() const;
	Vector2D getNormal() const { return Vector2D(-y, x); }
	double dot(Vector2D v) const;
	bool insideRect(const Vector2D&, const Vector2D&) const;
	Vector2D castGL(Vector2D v);

	void operator+=(Vector2D v);
	Vector2D& operator=(const Vector2D& v);
};

Vector2D operator+(Vector2D v1, Vector2D v2);
Vector2D operator-(Vector2D v1, Vector2D v2);
Vector2D operator*(Vector2D v, double n);
#endif