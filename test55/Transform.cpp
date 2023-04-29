#include "Transform.h"

Transform::Transform()
{
	position = Vector3D();
	rotCenter = Vector3D();
	rotation = Matrix3x3();
	yaw = 0;
	pitch = 0;
	updateRotation();
}


Transform::Transform(Vector3D v)
{
	position = v;
	rotCenter = Vector3D();
	rotation = Matrix3x3();
	yaw = 0;
	pitch = 0;
	updateRotation();
}

Mesh Transform::applyTransform(Mesh& mesh) const
{
	return Mesh(mesh,rotation,position, rotCenter);
}

Mesh Transform::applyTransform(Mesh* mesh) const
{
	return Mesh(*mesh, rotation, position, rotCenter);
}

void Transform::rotateSurface(Surface& surface,double focaldistance,Vector3D focuspoint) const
{
	Vector3D surfPos = rotation.getI() * focaldistance + focuspoint;
	Vector3D surfNormal = rotation.getI();
	surface = Surface(rotation.getI() * focaldistance + focuspoint, rotation.getI());
}



void Transform::updateRotation()
{
    Vector3D i = Vector3D(cos(yaw) * cos(pitch), sin(yaw) * cos(pitch), sin(pitch));
    Vector3D j = Vector3D(-sin(yaw), cos(yaw) ,0);
    Vector3D k = Vector3D(-cos(yaw) * sin(pitch),  -sin(yaw) * sin(pitch), cos(pitch));

	rotation = Matrix3x3(i, j, k);

}
