#pragma once
#include "Vector3D.h"
#include "Triangle3D.h"
#include "Material.h"
#include "Line.h"
#include <vector>
#include "Matrix3x3.h"

class Mesh
{
	bool triMode;
	std::vector<Vector3D> vertexArray;
	std::vector<Vector3D> normalArray;
	std::vector<Material> materialArray; // used materials //unused now
	std::vector<Material> bakedMaterialArray; // for baked lights
	size_t* materialBuffer; // original material colors //unused now
	size_t* indexBuffer;
	size_t indexBufferSize;
public:
	Mesh() {};
	Mesh(double paneSize);
	Mesh(Mesh& mesh, Matrix3x3 matrix, Vector3D position);

	Vector3D loadVertex(size_t i);
	size_t getVertexCount(){return vertexArray.size();}
	Vector3D loadNormal(size_t i);
	Material loadBakedMaterial(size_t i);
	size_t getTriCount() { return normalArray.size(); }
	size_t* shareIndex() { return indexBuffer; }
	size_t getIndexBufferSize() { return indexBufferSize; }
	bool getTriMode() { return triMode; }
};
