#include "Chunk.h"

Chunk::Chunk(int worldSize)
{
	for (int i = 0; i < 16; i++)
	{
		for (int j = 0; j < 16; j++)
		{
			for (int k = 0; k < 256; k++)
			{
				int id = 0;
				if (id < 100)
					id = 1;
				voxels[i][j][k] = Voxel(i, j, k, id, worldSize);
			}
		}
	}
}

void Chunk::simulate()
{

}

GameObject* Chunk::get(size_t x, size_t y, size_t z)
{
	return &voxels[x][y][z];
}
