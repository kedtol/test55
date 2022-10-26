#include "GameObject.h"


GameObject::GameObject(Transform _transform)
{
	transform = _transform;
	mesh = Mesh();
}

GameObject::GameObject(Transform _transform, double panesize)
{
	transform = _transform;
	hasPhysics = true;
	gravForce = Vector3D(0, 0, 0.05*panesize);
	//yspeed = (double)((rand() % 30)) / 1000.;
	//pspeed = (double)((rand() % 30)) / 1000.;
	//mspeed = (double)((rand() % 30))+10;
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
	yspeed = (double)((rand() % 30)) / 1000.;
	//pspeed = (double)((rand() % 30)) / 1000.;
	//mspeed = (double)((rand() % 30)) + 10;
}

void GameObject::action()
{
	transform.addPitch(pspeed);
	transform.addYaw(yspeed);
	transform.updateRotation();
	//transform.addPos(transform.getRot().getJ()*mspeed);
	//if (hasPhysics)
	//	updatePhysics(solid);
}

/*void GameObject::updatePhysics(GameObject* solid)
{
	if (!forceStabsObject(transform.getPos(),gravForce,*solid))
		transform.addPos(gravForce);
}*/


void GameObject::draw(Camera* camera)
{
	camera->loadDrawBuffer(transform.applyTransform(mesh),NULL);
}

bool forceStabsObject(Vector3D p, Vector3D f, GameObject o)
{
	Mesh m = o.getTransform().applyTransform(o.getMesh());


	for (size_t i = 0; i < m.getIndexBufferSize() - 2; i += 3)
	{
		// -READING-
		int iterator = static_cast<int>(i);
		int sol = iterator / 3;
		size_t vo = 0; // every third vertex
		if (sol < m.getTriCount())
			vo = sol; //size_t scam 

		int normalIndex = m.shareNormalIndex()[vo]; // get the normal buffer index

		Triangle3D tri = Triangle3D(m.loadVertex(m.shareIndex()[i] - 1), m.loadVertex(m.shareIndex()[i + 1] - 1), m.loadVertex(m.shareIndex()[i + 2] - 1), Material());
		//--

		// -GETTING THE NORMAL-
		Vector3D normal = m.loadNormal(normalIndex - 1); // normalbuffer stores normal vectors/face
		//--

		// -CONSTRUCT THE SURFACE AND THE LINE-
		Surface s = Surface(tri.getV1(), normal);
		Line l = Line(p, f);

		// -INTERSECTING THEM-
		bool failed = false;
		Vector3D intersection = s.intersect(l, &failed);
		if (!failed)
			if (intersection.insideTriangle(tri.getV1(), tri.getV2(), tri.getV3()))
				return true;
	}

	return false;
}
