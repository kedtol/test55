#pragma once
#include "Mesh.h"
#include "Camera.h"
#include "Matrix3x3.h"



class GameObject
{
	Transform transform;
	Mesh mesh;
	double pspeed;
	double yspeed;
	double mspeed;
	bool hasPhysics;
	Vector3D gravForce;
	//void updatePhysics(GameObject* solid);

public:
	GameObject(Transform _transform); // tri
	GameObject(Transform _transform,double panesize); // cube
	GameObject(Transform _transform, double panesize, int w, int h); // terrain
	GameObject(Transform _transform, Mesh _mesh);
	void action();
	void draw(Camera* camera);
	
	Mesh* getMeshp() { return &mesh; }
	Mesh& getMesh() { return mesh; }
	Transform getTransform() { return transform; }
};

bool forceStabsObject(Vector3D p, Vector3D f, GameObject o);