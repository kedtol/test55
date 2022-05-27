#ifndef __LINE2D_H__
#define __LINE2D_H__
#include "Vector2D.h"

class Line2D
{
	Vector2D position, direction;
	Vector2D limit1, limit2;

public:
	Line2D(Vector2D position, Vector2D direction, Vector2D limit1 = Vector2D(), Vector2D limit2 = Vector2D()) : direction(direction), position(position), limit1(limit1), limit2(limit2){}

	Vector2D getDir() const;
	Vector2D getPos() const;

	double getXIntersection(double x, bool*);
	double getYIntersection(double y, bool*);
	Vector2D lineIntersection(Line2D l, bool* failed);
	void rectIntersection(Vector2D p1, Vector2D p2, Vector2D** it1, Vector2D** it2);
};

#endif