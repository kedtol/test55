#include "GameObject.h"

class Voxel : public GameObject
{
	bool* faces = NULL;
	int id;
	Mesh* cutdownMesh;

public:
	Voxel(size_t x, size_t y, size_t z, int id, int cubeSize, Mesh* _mesh) 
		: GameObject(Transform(Vector3D(x*cubeSize*2, y* cubeSize*2, z* cubeSize*2)), cubeSize), id(id), cutdownMesh(_mesh)
	{ faces = NULL; }
	
	Voxel() :GameObject(Transform(),0) {}
	
	/*void draw(Camera* camera);*/
	
	void setFaces(bool* faces) 
	{
		if (this->faces != NULL)
			delete this->faces;
		this->faces = faces; 
	}

	int getId() { return id; }
};
