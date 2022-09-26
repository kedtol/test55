#include "Vector3D.h"
//#include "Matrix3x3.h"

Matrix3x3::Matrix3x3(Vector3D _i, Vector3D _j, Vector3D _k)
{
	i = _i;
	j = _j;
	k = _k;
}
Vector3D Matrix3x3::getI() const { return i; }
Vector3D Matrix3x3::getJ() const { return j; }
Vector3D Matrix3x3::getK() const { return k; }

Vector3D::Vector3D(const Vector3D& v)
{
	x = v.getX();
	y = v.getY();
	z = v.getZ();
}

Vector3D::Vector3D(double _x, double _y, double _z)
{
	x = _x;
	y = _y;
	z = _z;
}

double Vector3D::getLength() const
{
	return sqrt(x * x + y * y + z * z);
}

double Vector3D::dot(Vector3D v) const
{
	return x * v.getX() + y * v.getY() + z * v.getZ();
}

Vector3D Vector3D::cross(Vector3D v) const
{
	return Vector3D(y * v.getZ() - z * v.getY(), z * v.getX() - x * v.getZ(), x * v.getY() - y * v.getX());
}

bool Vector3D::insideTriangle(Vector3D v1, Vector3D v2, Vector3D v3)
{
	double area = (v1-v2).cross(v1-v3).getLength(); // (area times two)
	double alpha = (*this-v2).cross(*this-v3).getLength() / area;
	double beta = (*this-v3).cross(*this-v1).getLength() / area;
	double gamma = 1 - alpha - beta;

	if (alpha + beta + gamma == 1 && alpha >= 0 && alpha <= 1 && beta >= 0 && beta <= 1 && gamma >= 0 && gamma <= 1)
		return true;
	else
		return false;
}

Vector3D Vector3D::applyMatrix(Matrix3x3& matrix)
{
	double x_ = getX() * matrix.getI().getX() + getY() * matrix.getJ().getX() + getZ() * matrix.getK().getX();
	double y_ = getX() * matrix.getI().getY() + getY() * matrix.getJ().getY() + getZ() * matrix.getK().getY();
	double z_ = getX() * matrix.getI().getZ() + getY() * matrix.getJ().getZ() + getZ() * matrix.getK().getZ();
	return Vector3D(x_, y_, z_);
}

void Vector3D::operator+=(Vector3D v)
{
	x += v.getX();
	y += v.getY();
	z += v.getZ();
}

Vector3D& Vector3D::operator=(const Vector3D& v)
{
	x = v.getX();
	y = v.getY();
	z = v.getZ();
	return *this;
}

Vector3D operator+(Vector3D v1, Vector3D v2)
{
	return Vector3D(v1.getX() + v2.getX(), v1.getY() + v2.getY(), v1.getZ() + v2.getZ());
}

Vector3D operator-(Vector3D v1, Vector3D v2)
{
	return Vector3D(v1.getX() - v2.getX(), v1.getY() - v2.getY(), v1.getZ() - v2.getZ());
}

Vector3D operator*(Vector3D v, double n)
{
	return Vector3D(v.getX()*n, v.getY()*n, v.getZ()*n);
}

