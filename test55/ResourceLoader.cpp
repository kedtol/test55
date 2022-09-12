#include "ResourceLoader.h"

bool strendw(char* str, const char* end)
{
    int i = strlen(str) - strlen(end);
    int j = 0;

    if (i < 0)
        return false;

    while (str[i] != 0)
    {
        if (str[i] != end[j])
            return false;
        i++;
        j++;
    }

    return true;
}

bool strstartw(char* str, const char* start)
{
    int i = 0;

    if (strlen(str) < strlen(start))
        return false;

    while (i < strlen(start))
    {
        if (str[i] != start[i])
            return false;
        i++;
    }

    return true;
}

char* strAppend(const char* o, char* a)
{
    int sizeO = strlen(o)+1;
    int sizeA = strlen(a)+1;

    char* out =  (char*)malloc((sizeO + sizeA - 1) * sizeof(char));

    for (int i = 0; i < sizeO - 1; i++)
    {
        out[i] = o[i];
    }

    for (int i = 0; i < sizeA; i++)
    {
        out[i + sizeO - 1] = a[i];
    }

    return out;
}


char* readLine(FILE* stream, bool* eof)
{
    char* out = (char*)malloc(sizeof(char));
    int bufferSize = 1;

    char readC = fgetc(stream);

    while (readC != '\n')
    {
        out[bufferSize - 1] = readC;
        bufferSize++;
        out = (char*)realloc(out, sizeof(char) * bufferSize);

        if (readC == EOF)
        {
            out[bufferSize - 1] = 0;
            *eof = true;
            return out;
        }

        readC = fgetc(stream);
    }
    out[bufferSize - 1] = 0;
    return out;
}



void ResourceLoader::loadMeshes() // reuse of my (old c98) file loading system 
{
    
    DIR* d;
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
                
                char* fullPath = strAppend(".\\obj\\", dir->d_name);
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
                size_t nibs = 0;
                size_t ibs = 0;
                FILE* fback = file;
                bool exit = false;
                while (!exit)
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
                                mesh.addNormal(Vector3D(x*100, y*100, -1*z*100));
                            }
                            else // load vertex
                            {
                                double x, y, z;
                                sscanf_s(line, "v %lf  %lf  %lf",&x,&y,&z);
                                mesh.addVertex(Vector3D(x*100, y*100, -1*z*100));
                                char cr = 255 / 8 * (rand() % 5 + 20);
                                char cg = 255 / 8 * (rand() % 5 + 20);
                                char cb = 255 / 8 * (rand() % 5 + 20);
                                Material m = Material(Color(255, 255, 255));
                                mesh.addMaterial(m);
                               
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
                                int vti1 = 0; // vertex texture index i guess
                                int vti2 = 0; 
                                int vti3 = 0; 
                                int ibit1 = 0;
                                int ibit2 = 0;
                                int ibit3 = 0;
                                int nibit1 = 0;
                                int nibit2 = 0;
                                int nibit3 = 0;
                                sscanf_s(line, "f %d/%d/%d %d/%d/%d %d/%d/%d", &ibit1, &vti1, &nibit1, &ibit2, &vti2, &nibit2, &ibit3, &vti3, &nibit3);
                                ib[iter] = ibit1;
                                ib[iter+1] = ibit2;
                                ib[iter+2] = ibit3;

                                nib[iter/3] = nibit1;
                                //nib[(iter / 3)+1] = nibit2;
                                //nib[(iter / 3)+2] = nibit3;
                                ibs += 3;
                                nibs++;
                                iter += 3;
                            }

                        }
                    }

                    if (eof)
                    {
                        if (firstTime)
                        {
                            firstTime = false;
                            ib = new size_t[faces * 3]; // 3 vertex per face
                            nib = new size_t[faces]; // only one normal vector per face
                            iter = 0;
                            rewind(file);
                            eof = false;
                        }
                        else
                        {
                            exit = true;
                        }
                    }
            
                }
                mesh.setIndexSize(ibs);
                mesh.setNormalIndexSize(nibs);
                mesh.setIndex(ib);
                mesh.setNormalIndex(nib);
                mesh.resetBakedMaterial();
                meshes.push_back(mesh); // one mesh per file
                fclose(file);
            }
           
        }
       
        closedir(d);
    }

}

void ResourceLoader::loadMaterials(char* name)
{
}
