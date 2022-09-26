#include "GameObject.h"

class Voxel : public GameObject
{
	int id;
	bool* faces;

public:
	Voxel(size_t x, size_t y, size_t z, int id, int cubeSize) : GameObject(Transform(Vector3D(x*cubeSize, y* cubeSize, z* cubeSize)), cubeSize), id(id) { faces = NULL; }
	Voxel() :GameObject(Transform(),0) {}
};
