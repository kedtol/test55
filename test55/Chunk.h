#include "Voxel.h"

class Chunk
{
	Voxel voxels[16][16][256];

public:
	Chunk(int worldSize);
	void simulate();
	GameObject* get(size_t x, size_t y, size_t z);
	~Chunk();
};