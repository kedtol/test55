#pragma once
#include "Vector3D.h"
#include "Matrix3x3.h"
#include "Surface.h"
#include "Mesh.h"


class Transform
{
	Vector3D position, rotCenter;
	Matrix3x3 rotation, scale;
	double yaw, pitch, xScale, yScale, zScale;

public:
	Transform();
	Transform(Vector3D v);

	Vector3D getPos() const { return position; };
	Matrix3x3 getRot() const { return rotation; };

	double getPitch() const { return pitch; }
	double getYaw() const { return yaw; }
	
	void addPos(Vector3D v) { position += v; }
	void setPos(Vector3D v) { position = v; } // haha  nem oo, nem �rdekel
	void setRotCenter(Vector3D v) { rotCenter = v; } // haha  nem oo, nem �rdekel
	void addYaw(double _yaw) { yaw += _yaw; }
	void addPitch(double _pitch) { pitch += _pitch; }

	Mesh applyTransform(Mesh& mesh) const;	
	Mesh applyTransform(Mesh* mesh) const;
	void rotateSurface(Surface& surface,double focaldistance, Vector3D focuspoint) const;
	void updateRotation();
	void updateScale();

};