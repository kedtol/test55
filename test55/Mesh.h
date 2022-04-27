#pragma once
#include <iostream>
#include <vector>
#include "Vector3D.h"
#include "Triangle3D.h"
#include "Vector2D.h"
#include "Material.h"
#include "Line.h"
#include "Matrix3x3.h"

class Mesh
{
	bool triMode;
	std::vector<Vector3D> vertexArray;
	std::vector<Vector3D> normalArray;
	std::vector<Material> materialArray; // used materials //unused now
	std::vector<Material> bakedMaterialArray; // for baked lights
	size_t* materialBuffer; // original material colors //unused now
	size_t* indexBuffer = NULL;
	size_t* normalIndexBuffer = NULL;
	size_t normalIndexBufferSize;
	size_t indexBufferSize;
public:
	Mesh() { triMode = true;};
	Mesh(double paneSize); //cube
	Mesh(double paneSize,int w, int h); //terrain
	Mesh(Mesh& mesh, Matrix3x3 matrix, Vector3D position);

	Vector3D loadVertex(size_t i);
	Vector3D loadNormal(size_t i);
	Material loadBakedMaterial(size_t i);
	size_t* shareIndex() const { return indexBuffer; }
	size_t* shareNormalIndex() const { return normalIndexBuffer; }
	void setIndex(size_t* ib) { indexBuffer = ib; }
	void setNormalIndex(size_t* ib) { normalIndexBuffer = ib; }
	size_t getVertexCount() const { return vertexArray.size(); }
	size_t getNormalCount() const { return normalArray.size(); }
	size_t getTriCount() const {return indexBufferSize / 3;}
	size_t getIndexBufferSize() const { return indexBufferSize; }
	size_t getNormalIndexBufferSize() const { return normalIndexBufferSize; }
	
	void addVertex(Vector3D v) { vertexArray.push_back(v); }
	void addNormal(Vector3D n) { normalArray.push_back(n); }
	void addBakedMaterial(Material m) { bakedMaterialArray.push_back(m); }
	
	bool getTriMode() const { return triMode; }
};
