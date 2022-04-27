#include "Vector2D.h"

Vector2D::Vector2D(const Vector2D& v)
{
	x = v.getX();
	y = v.getY();
}

Vector2D::Vector2D(double _x, double _y)
{
	x = _x;
	y = _y;
}

double Vector2D::getLength() const
{
	return sqrt(x * x + y * y);
}

void Vector2D::randomGradient()
{
	double angle = double(rand() % 6283) / 1000;
	x = cos(angle);
	y = sin(angle);
}

void Vector2D::operator+=(Vector2D v)
{
	x += v.getX();
	y += v.getY();
}

Vector2D& Vector2D::operator=(const Vector2D& v)
{
	x = v.getX();
	y = v.getY();
	return *this;
}

double Vector2D::dot(Vector2D v) const
{
	return x * v.getX() + y * v.getY();
}

Vector2D operator+(Vector2D v1, Vector2D v2)
{
	return Vector2D(v1.getX() + v2.getX(), v1.getY() + v2.getY());
}

Vector2D operator-(Vector2D v1, Vector2D v2)
{
	return Vector2D(v1.getX() - v2.getX(), v1.getY() - v2.getY());
}

Vector2D operator*(Vector2D v, double n)
{
	return Vector2D(v.getX() * n, v.getY() * n);
}