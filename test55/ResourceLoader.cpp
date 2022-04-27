#include "ResourceLoader.h"


void ResourceLoader::loadMeshes() // reuse of my (old c98) file loading system 
{
    
    /*/DIR* d;
    struct dirent* dir;
    d = opendir(".\\obj\\");

    if (d)
    {
        while ((dir = readdir(d)) != NULL)
        {
            if (strendw(dir->d_name, ".obj"))
            {
               // char* fname = (char*) malloc(sizeof(char) * (dir->d_namlen + 1));
                //strcpy(fname, dir->d_name);
                
                char* fullPath = strAppend(".\\stages\\", dir->d_name);
                FILE* file;
                fopen_s(&file, fullPath, "r");
                char* line = NULL; // current line
                bool eof = false; // end of file
                Mesh mesh = Mesh();
                bool firstTime = true;
                int faces = 0;
                int iter = 0;
                size_t* ib = NULL;
                size_t* nib = NULL;

                while (eof || firstTime)
                {             
                    line = readLine(file, &eof); // read a new line
                    if (line != NULL)
                    {
                        if (strstartw(line, "mtllib ") && firstTime) // load mtl
                        {
                            //loadMaterials(line+7);
                        }

                        if (strstartw(line, "usemtl ") && firstTime) // use mtl
                        {
                           //set loading material
                        }

                        if (line[0] == 'v' && firstTime)
                        {
                            if (line[1] == 'n') // load vertex normal
                            {
                                double x, y, z;
                                sscanf_s(line, "vn %lf  %lf  %lf", &x, &y, &z);
                                mesh.addNormal(Vector3D(x, y, z));
                            }
                            else // load vertex
                            {
                                double x, y, z;
                                sscanf_s(line, "v %lf  %lf  %lf",&x,&y,&z);
                                mesh.addVertex(Vector3D(x, y, z));
                            }
                        }

                        if (line[0] == 'f') // construct vertex index buffer
                        {
                            if (firstTime) // count 
                            {
                                faces++;
                            }
                            else // construct index buffers
                            {
                                if (ib == NULL)
                                {
                                    ib = new size_t[faces*3]; // 3 vertex per face
                                    nib = new size_t[faces]; // only one normal vector per face
                                    iter = 0;
                                }
                                else
                                {
                                    double vti1 = 0; // vertex texture index i guess
                                    double vti2 = 0; 
                                    double vti3 = 0; 
                                    sscanf_s(line, "f %lf/ %lf/ %lf/ %lf/ %lf/ %lf/ %lf/ %lf/ %lf", ib+iter, &vti1, nib+iter, ib + iter+1, &vti2, nib + iter, ib + iter+2, &vti3, nib + iter );
                                    iter += 3;
                                }
                            }

                        }
                    }
                    if (eof)
                    {
                        firstTime = false;
                        eof = false;
                    }
                }
                mesh.setIndex(ib);
                mesh.setNormalIndex(nib);
                meshes.push_back(mesh); // one mesh per file
            }
        }
        closedir(d);
    }

    */
}

void ResourceLoader::loadMaterials(char* name)
{
}
