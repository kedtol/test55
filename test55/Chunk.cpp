#include "Chunk.h"

Chunk::Chunk(int worldSize, int x, int y)
{
	this->x = x;
	this->y = y;

	for (int i = 0; i < xs; i++)
	{
		for (int j = 0; j < ys; j++)
		{
			for (int k = 0; k < zs; k++)
			{
				int id = 0;
				if (rand()%100 < 99)
					id = 1;
				voxels[i][j][k] = Voxel(i+xs*x, j+ys*y, k, id, worldSize);
			}
		}
	}
	optimizeVoxels();
}

Chunk::Chunk()
{
}

void Chunk::optimizeVoxels()
{
	for (int i = 0; i < xs; i++)
	{
		for (int j = 0; j < ys; j++)
		{
			for (int k = 0; k < zs; k++)
			{
				if (voxels[i][j][k].getId() != 0)
				{
					bool* faces = new bool[6];
					faces[0] = k == 0 || voxels[i][j][k - 1].getId() == 0;
					faces[1] = k == zs - 1 || voxels[i][j][k + 1].getId() == 0;
					faces[2] = j == 0 || voxels[i][j - 1][k].getId() == 0;
					faces[3] = j == ys - 1 || voxels[i][j + 1][k].getId() == 0;
					faces[4] = i == 0 || voxels[i - 1][j][k].getId() == 0;
					faces[5] = i == xs - 1 || voxels[i + 1][j][k].getId() == 0;

					voxels[i][j][k].setFaces(faces);
				}
			}
		}
	}
}

void Chunk::simulate()
{
	for (int i = 0; i < xs; i++)
	{
		for (int j = 0; j < ys; j++)
		{
			for (int k = 0; k < zs; k++)
			{
				voxels[i][j][k].action();
			}
		}
	}
}

void Chunk::draw(Camera* camera)
{
	for (int i = 0; i < xs; i++)
	{
		for (int j = 0; j < ys; j++)
		{
			for (int k = 0; k < zs; k++)
			{
				voxels[i][j][k].draw(camera);
			}
		}
	}
}

void Chunk::lightUpdate(std::vector<Light>* lights)
{
	for (int i = 0; i < xs; i++)
	{
		for (int j = 0; j < ys; j++)
		{
			for (int k = 0; k < zs; k++)
			{
				voxels[i][j][k].getMeshp()->resetBakedMaterial();
				for (size_t l = 0;l < lights->size(); l++)
				{
					voxels[i][j][k].getMeshp()->bakeLightSource(lights->at(l), voxels[i][j][k].getTransform().applyTransform(voxels[i][j][k].getMesh()));
				}
			}
		}
	}
	
}

GameObject* Chunk::get(size_t x, size_t y, size_t z)
{
	return &voxels[x][y][z];
}
