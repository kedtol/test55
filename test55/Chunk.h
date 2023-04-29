#include "Voxel.h"

class Chunk
{
	Voxel voxels[16][16][10];
	int x,y;
	size_t xs = 16, ys = 16, zs = 10;
public:
	Chunk(int worldSize, int x, int y);
	Chunk();
	void simulate();
	/*void draw(Camera* camera);*/
	GameObject* get(size_t x, size_t y, size_t z);
	void lightUpdate(std::vector<Light> *lights);
	void optimizeVoxels();
	//~Chunk();
};