#include "GameObject.h"

GameObject::GameObject(Transform _transform, double panesize)
{
	transform = _transform;
	mesh = Mesh(panesize);
}

GameObject::GameObject(Transform _transform, Mesh _mesh)
{
	transform = _transform;
	mesh = _mesh;
}

void GameObject::action()
{
	//transform.addPitch((rand() % 10) / 100.);
	//transform.addYaw((rand() % 10) / 100.);
	transform.updateRotation();
}

void GameObject::draw(Camera* camera)
{
	camera->loadDrawBuffer(transform.applyTransform(mesh));
}
