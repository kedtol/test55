#include "GameObject.h"

GameObject::GameObject(Transform _transform)
{
	transform = _transform;
	mesh = Mesh();
}

GameObject::GameObject(Transform _transform, double panesize)
{
	transform = _transform;
	yspeed = (double)((rand() % 30)) / 1000.;
	pspeed = (double)((rand() % 30)) / 1000.;
	mspeed = (double)((rand() % 30))+10;
	mesh = Mesh(panesize);
}

GameObject::GameObject(Transform _transform, double panesize, int w, int h)
{
	transform = _transform;
	yspeed = 0;
	pspeed = 0;
	mspeed = 0;
	mesh = Mesh(panesize,w,h);
}

GameObject::GameObject(Transform _transform, Mesh _mesh)
{
	transform = _transform;
	mesh = _mesh;
	//yspeed = (double)((rand() % 30)) / 1000.;
	//pspeed = (double)((rand() % 30)) / 1000.;
	//mspeed = (double)((rand() % 30)) + 10;
}

void GameObject::action()
{
	transform.addPitch(pspeed);
	transform.addYaw(yspeed);
	transform.updateRotation();
	transform.addPos(transform.getRot().getJ()*mspeed);
}

void GameObject::draw(Camera* camera)
{
	camera->loadDrawBuffer(transform.applyTransform(mesh));
}
