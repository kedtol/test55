#include "Line2D.h"

Vector2D Line2D::getDir() const
{
	return direction;
}

Vector2D Line2D::getPos() const
{
	return position;
}

Vector2D Line2D::lineIntersection(Line2D l, bool* failed)
{
    *failed = false;
    Vector2D v1 = position+direction;
    Vector2D v2 = position + (direction * 2);
    Vector2D u1 = l.getPos() + l.getDir();
    Vector2D u2 = l.getPos() + (l.getDir() * 2);
    double denominator = (v1.getX() - v2.getX()) * (u1.getY() - u2.getY()) - (v1.getY() - v2.getY()) * (u1.getX() - u2.getX());
    if (denominator != 0)
    {
        double x = ((v1.getX() * v2.getY() - v1.getY() * v2.getX()) * (u1.getX() - u2.getX()) - (u1.getX() * u2.getY() - u1.getY() * u2.getX()) * (v1.getX() - v2.getX())) / denominator;
        double y = ((v1.getX() * v2.getY() - v1.getY() * v2.getX()) * (u1.getY() - u2.getY()) - (u1.getX() * u2.getY() - u1.getY() * u2.getX()) * (v1.getY() - v2.getY())) / denominator;
        Vector2D it = Vector2D(x, y);
        if ((limit1- it).dot(limit2-limit1) < -0.99 && (limit1 - it).getLength() < direction.getLength())
            return it;
        else
            *failed = true;
    }
    else
    {
        *failed = true;
    }
        
    return -1;
}

double Line2D::getYIntersection(double y, bool* failed)
{
    *failed = false;
    if (direction.getX() * y != 0)
        return (direction.getY()*position.getX()-direction.getX()*position.getY()) / (-1*(direction.getX()*y));
    else
        *failed = true;
    return -1;
}

double Line2D::getXIntersection(double x, bool* failed)
{
    *failed = false;
    if (direction.getY() * x != 0)
        return (direction.getY() * position.getX() - direction.getX() * position.getY()) / (direction.getY() * x);
    else
        *failed = true;
    return -1;
}

void Line2D::rectIntersection(Vector2D p1, Vector2D p2, Vector2D** it1, Vector2D** it2)
{
    bool failed = false;
    int amount = 0;

    Vector2D intersection = lineIntersection(Line2D(p1,p1-Vector2D(p2.getX(),p1.getY())), &failed);
    if (!failed && amount < 2)
    {
        if (intersection.getX() > p1.getX() && intersection.getX() < p2.getX())
        {
            if (amount == 0)
                *it1 = new Vector2D(intersection);
            amount++;
        }
    }

    intersection = lineIntersection(Line2D(p2, Vector2D(p1.getX(), p2.getY())-p2), &failed);
    if (!failed && amount < 2)
    {
        if (intersection.getX() > p1.getX() && intersection.getX() < p2.getX())
        {
            if (amount == 0)
                *it1 = new Vector2D(intersection);
            if (amount == 1)
                *it2 = new Vector2D(intersection);
            amount++;
        }
    }

    intersection = lineIntersection(Line2D(p1, p1-Vector2D(p1.getX(), p2.getY())), &failed);
    if (!failed && amount < 2)
    {
        if (intersection.getY() > p1.getY() && intersection.getY() < p2.getY())
        {
            if (amount == 0)
                *it1 = new Vector2D(intersection);
            if (amount == 1)
                *it2 = new Vector2D(intersection);
            amount++;
        }
    }

    intersection = lineIntersection(Line2D(p2, p2 - Vector2D(p2.getX(), p1.getY())), &failed);
    if (!failed && amount < 2)
    {
        if (intersection.getY() > p1.getY() && intersection.getY() < p2.getY())
        {
            if (amount == 0)
                *it1 = new Vector2D(intersection);
            if (amount == 1)
                *it2 = new Vector2D(intersection);
            amount++;
        }
    }
}
