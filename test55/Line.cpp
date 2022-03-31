#include "Line.h"

Line::Line(Vector3D _position, Vector3D _direction)
{
    position = _position;
    direction = _direction;
}

Vector3D Line::getDir() const { return direction; }

Vector3D Line::getPos() const { return position; }
