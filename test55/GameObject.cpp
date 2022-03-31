#include "GameObject.h"

GameObject::GameObject(Transform _transform)
{
	transform = _transform;
	mesh = Mesh(100.);
}

GameObject::GameObject(Transform _transform, Mesh _mesh)
{
	transform = _transform;
	mesh = _mesh;
}

void GameObject::action()
{

}

void GameObject::draw(Camera* camera)
{
	camera->loadDrawBuffer(transform.applyTransform(mesh));
}
