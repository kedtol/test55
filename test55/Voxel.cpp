#include "Voxel.h"
void Voxel::draw(Camera* camera)
{
	if (id != 0)
		camera->loadDrawBuffer(getTransform().applyTransform(getMesh()),faces);
}

