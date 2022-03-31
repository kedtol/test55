#include "Mesh.h"

Mesh::Mesh(double paneSize)
{
	triMode = true;
	vertexArray.push_back(Vector3D(paneSize, paneSize, -paneSize));
	vertexArray.push_back(Vector3D(-paneSize, paneSize, -paneSize));
	vertexArray.push_back(Vector3D(-paneSize, -paneSize, -paneSize));
	vertexArray.push_back(Vector3D(paneSize, -paneSize, -paneSize));
	vertexArray.push_back(Vector3D(paneSize, paneSize, paneSize));
	vertexArray.push_back(Vector3D(-paneSize, paneSize, paneSize));
	vertexArray.push_back(Vector3D(-paneSize, -paneSize, paneSize));
	vertexArray.push_back(Vector3D(paneSize, -paneSize, paneSize));

	indexBufferSize = 36;
	indexBuffer = new size_t[indexBufferSize]{ 2, 1, 5, 2, 6, 5, 1, 4, 8, 1, 5, 8, 2, 6, 7, 2, 3, 7, 3, 7, 8, 3, 4, 8, 6, 5, 8, 6, 7, 8, 2, 3, 4, 2, 1, 4 };

	normalArray.push_back(Vector3D(0, 1, 0));
	normalArray.push_back(Vector3D(0, 1, 0));
	normalArray.push_back(Vector3D(1, 0, 0));
	normalArray.push_back(Vector3D(1, 0, 0));
	normalArray.push_back(Vector3D(-1, 0, 0));
	normalArray.push_back(Vector3D(-1, 0, 0));
	normalArray.push_back(Vector3D(0, -1, 0));
	normalArray.push_back(Vector3D(0, -1, 0));
	normalArray.push_back(Vector3D(0, 0, 1));
	normalArray.push_back(Vector3D(0, 0, 1));
	normalArray.push_back(Vector3D(0, 0, -1));
	normalArray.push_back(Vector3D(0, 0, -1));

	Material m = Material('z',0,0);

	for (int i = 0; i < 12; i++)
	{
		bakedMaterialArray.push_back(m);
	}

}

Mesh::Mesh(Mesh& mesh, Matrix3x3 matrix, Vector3D position)
{
	indexBuffer = mesh.shareIndex();
	indexBufferSize = mesh.getIndexBufferSize();
	triMode = mesh.getTriMode();

	for (size_t i = 0; i < mesh.getVertexCount(); i++)
		vertexArray.push_back(mesh.loadVertex(i).applyMatrix(matrix)+position);

	for (size_t i = 0; i < mesh.getTriCount(); i++)
		normalArray.push_back(mesh.loadNormal(i).applyMatrix(matrix) + position);

	for (size_t i = 0; i < mesh.getTriCount(); i++)
		bakedMaterialArray.push_back(mesh.loadBakedMaterial(i));
}

Vector3D Mesh::loadVertex(size_t i)
{
	return vertexArray[i];
}

Vector3D Mesh::loadNormal(size_t i)
{
	return normalArray[i];
}

Material Mesh::loadBakedMaterial(size_t i)
{
	return bakedMaterialArray[i];
}
