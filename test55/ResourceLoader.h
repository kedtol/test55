#ifndef __RESOURCELOADER_H__
#define __RESOURCELOADER_H__
#include <vector>
//#include <string>
#include <iostream>
#include <fstream>
//#include <stdio.h>
//#include "dirent.h"
#include "Mesh.h"
//#include "load.h"
//#include <string_view>
//#include <string>

class ResourceLoader 
{
	std::vector<Mesh> meshes;
	std::vector<Material> materials;
	void loadMaterials(char* name);
public:
	void loadMeshes();
	
};


#endif