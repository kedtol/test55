#include "Triangle3D.h"
#include <iostream>

Triangle3D::Triangle3D(Vector3D _v1, Vector3D _v2, Vector3D _v3,Material _m1, Material _m2, Material _m3)
{
	v1 = _v1;
	v2 = _v2;
	v3 = _v3;
	m1 = _m1;
	m2 = _m2;
	m3 = _m3;

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

Vector3D Triangle3D::getWpoint() const 
{
	Vector3D v = Vector3D((v1 + v2 + v3) * (1. / 3.));
	return v;
}

void Triangle3D::render(SDL_GLContext* gcontext)
{
	double screenw = 1024. / 2.;
	double screenh = 768. / 2.;
	
	v1 = v1 * 0.001;
	v2 = v2 * 0.001;
	v3 = v3 * 0.001;

	glBegin(GL_TRIANGLES);

	
	//if (rand()%3 == 0)
	glColor4b(m1.getR() - 128, m1.getG() - 128, m1.getB() - 128, 128);
		
	//else
	/*	if (rand() % 3 == 1)
			glColor4b(m3.getR() - 128, m3.getG() - 128, m3.getB() - 128, 128);
		else
			glColor4b(m2.getR() - 128, m2.getG() - 128, m2.getB() - 128, 128);*/
	
	glVertex3d(v1.getX(), v1.getY(), v1.getZ());
	glColor4b(m2.getR() - 128, m2.getG() - 128, m2.getB() - 128, 128);

	glVertex3d(v2.getX(), v2.getY(), v2.getZ());
	glColor4b(m3.getR() - 128, m3.getG() - 128, m3.getB() - 128, 128);

	glVertex3d(v3.getX(), v3.getY(),v3.getZ());
	glEnd();
}