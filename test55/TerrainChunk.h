#include "GameObject.h"
#include "PerlinMap.h"
class TerrainChunk : public GameObject
{
	PerlinMap* pmap;
	Mesh* finalMesh = NULL;

public:
	TerrainChunk(size_t x, size_t y, size_t z, int id, int chunkSize, int xPCount, int yPCount, PerlinMap* _pmap)
		: GameObject(Transform(Vector3D(x* chunkSize * 2, y* chunkSize * 2, z)),chunkSize, xPCount, yPCount), pmap(_pmap) {}

	TerrainChunk() :GameObject(Transform(), 0) {}
	
	/*void draw(Camera* camera);
	void buildFinalMesh(Camera* camera);*/
};
