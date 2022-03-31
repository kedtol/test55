#pragma once
#include "Transform.h"
#include "Mesh.h"
#include "Material.h"
#include "Camera.h"

class GameObject
{
	Transform transform;
	Mesh mesh;

public:
	GameObject(Transform _transform);
	GameObject(Transform _transform, Mesh _mesh);
	void action();
	void draw(Camera* camera);
};