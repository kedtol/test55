#pragma once
#include <iostream>
#include <vector>
#include "Triangle3D.h"
#include "Vector2D.h"
#include "Material.h"
#include "Line.h"
#include "Light.h"

class Mesh
{
	bool triMode;
	std::vector<Vector3D> vertexArray; // all known vertexes
	std::vector<Vector3D> normalArray; // all known normal vectors
	std::vector<Material> materialArray; // used materials 
	std::vector<Material> bakedMaterialArray; // for baked lights // the camera is looking for this
	//size_t* materialIndexBuffer; // material index buffer // im not gonna index the materials 
	size_t* indexBuffer = NULL; // vertex indexes
	size_t* normalIndexBuffer = NULL; // normal vector indexes
	size_t normalIndexBufferSize;
	size_t indexBufferSize;
public:
	Mesh();
	Mesh(double paneSize); //cube
	Mesh(double paneSize,int w, int h); //terrain
	Mesh(Mesh& mesh, Matrix3x3 matrix, Vector3D position);

	Vector3D loadVertex(size_t i);
	Vector3D loadNormal(size_t i);
	Material loadBakedMaterial(size_t i);
	Material loadMaterial(size_t i);
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
	void addMaterial(Material m) { materialArray.push_back(m); }

	void setIndexSize(size_t ibs) { indexBufferSize = ibs; }
	void setNormalIndexSize(size_t nibs) { normalIndexBufferSize = nibs; }
	
	void bakeLightSource(Light l,Mesh t);
	void resetBakedMaterial();

	void deleteFaces(bool* faces,size_t faceNumber);

	bool getTriMode() const { return triMode; }
};
