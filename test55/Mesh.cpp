#include "Mesh.h"

Mesh::Mesh()
{
	triMode = true;
	/*materialBuffer = NULL;
	vertexArray.push_back(Vector3D(-5000, 0, 0));
	vertexArray.push_back(Vector3D(5000, 0, 0));
	vertexArray.push_back(Vector3D(0, 5000, 0));

	indexBufferSize = 3;
	indexBuffer = new size_t[indexBufferSize]{ 1,2,3 };

	normalArray.push_back(Vector3D(0, 0, 1));

	normalIndexBufferSize = 1;
	normalIndexBuffer = new size_t[normalIndexBufferSize]{ 1 };

	bakedMaterialArray.push_back(Material(255, 0, 0));
	bakedMaterialArray.push_back(Material(0, 255, 0));
	bakedMaterialArray.push_back(Material(0, 0, 255));

	*/
}

Mesh::Mesh(double paneSize)
{
	triMode = true;
	materialBuffer = NULL;
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
	normalArray.push_back(Vector3D(1, 0, 0));
	normalArray.push_back(Vector3D(-1, 0, 0));
	normalArray.push_back(Vector3D(0, -1, 0));
	normalArray.push_back(Vector3D(0, 0, 1));
	normalArray.push_back(Vector3D(0, 0, -1));

	normalIndexBufferSize = 12;
	normalIndexBuffer = new size_t[normalIndexBufferSize]{ 1,1,2,2,3,3,4,4,5,5,6,6 };

	Material m;
	char cr = 255;
	char cg = 255;
	char cb = 255;

	for (int i = 0; i < 8; i++)
	{

		char cr = 255/8*(rand() % 5+20);
		char cg = 255 / 8 *( rand() % 5+20);
		char cb = 255 / 8 *( rand() % 5+20);
		m = Material(Color(cr, cg, cb));

		bakedMaterialArray.push_back(m);
	}

	
	

}

Mesh::Mesh(double paneSize, int w, int h)
{
	w;
	h;
	triMode = true;
	materialBuffer = NULL;

	indexBufferSize = w*h*6; // every square has 2 triangles
	indexBuffer = new size_t[indexBufferSize];
	int vindex = 1;
	for (int i = 0; i < indexBufferSize; i += 3)
	{

		indexBuffer[i] = vindex;
		indexBuffer[i + 1] = vindex + 1;
		indexBuffer[i + 2] = vindex + (w+1);
		i += 3;
		indexBuffer[i] = vindex + 1 + (w+1);
		indexBuffer[i + 1] = vindex + (w+1);
		indexBuffer[i + 2] = vindex + 1;

		if ((vindex) % (w+1) == w)
			vindex += 2;
		else
			vindex++;
	}
	
	Vector2D* perlin = new Vector2D[w * h];

	for (int i = 0; i < w; i += 1)
	{
		for (int j = 0; j < h; j += 1)
		{
			perlin[i * j] = Vector2D();
			perlin[i * j].randomGradient();
		}
	}
	double* dproduct = new double[(w + 1) * (h + 1)];

	for (int i = 0; i < w; i += 1)
	{
		for (int j = 0; j < h; j += 1)
		{
			for (int k = -1; k <= 1;k++)
			{
				for (int l = -1; l <= 1;l++)
				{
					int dpx = i * 2 + k;
					int dpy = j * 2 + l;
					if (dpx >= 0 && dpx < w+1 && dpy >= 0 && dpy < h+1)
					{
						dproduct[w* dpy+dpx] = (Vector2D(i+k, j+l) - perlin[i * j]).dot(perlin[i * j]);
					}
				}
			}
		}
	}

	Material m;
	char cr = 255;
	char cg = 255;
	char cb = 255;

	for (int i = 0; i <= w; i += 1)
	{
		for (int j = 0; j <= h; j += 1)
		{
			double h = dproduct[(w + 1) * j + i] * 160;

			vertexArray.push_back(Vector3D(i*paneSize + -5 * rand() % 50, j * paneSize+ -5*rand() % 50, h));
			
			char cr = (rand() % 20)+120;
			char cg = (rand() % 40) + 170;
			char cb = (rand() % 20)+120;
				
			if (h < -200)
			{
				cr = 240;
				cg = 240;
				cb = 240;
			}
			m = Material(Color(cr,cg,cb));

			bakedMaterialArray.push_back(m);
		}
	}

	normalIndexBufferSize = w * h * 2;
	normalIndexBuffer = new size_t[normalIndexBufferSize];
	for (int i = 0; i < normalIndexBufferSize; i += 1)
	{
		normalIndexBuffer[i] = i+1;
	}
	
	for (int i = 0; i < indexBufferSize; i += 3)
	{
		if (i + 2 < indexBufferSize)
		{
			Vector3D a = vertexArray[indexBuffer[i]-1] - vertexArray[indexBuffer[i + 1]-1];
			Vector3D b = vertexArray[indexBuffer[i]-1] - vertexArray[indexBuffer[i + 2]-1];

			normalArray.push_back(a.cross(b));
		}
		
	}

	for (int i = 0; i < w * h * 2; i++)
	{
		char cr = 255 / 8 * (rand() % 3 + 3);
		char cg = 255 / 8 * (rand() % 3 + 3);
		char cb = 255 / 8 * (rand() % 3 + 3);
		m = Material(Color(cr, cg, cb));

		bakedMaterialArray.push_back(m);
	}
}

Mesh::Mesh(Mesh& mesh, Matrix3x3 matrix, Vector3D position)
{
	indexBuffer = mesh.shareIndex();
	indexBufferSize = mesh.getIndexBufferSize();
	normalIndexBuffer = mesh.shareNormalIndex();
	normalIndexBufferSize = mesh.getNormalIndexBufferSize();
	triMode = mesh.getTriMode();

	for (size_t i = 0; i < mesh.getVertexCount(); i++)
		vertexArray.push_back(mesh.loadVertex(i).applyMatrix(matrix)+position);

	for (size_t i = 0; i < mesh.getNormalCount(); i++)
		normalArray.push_back(mesh.loadNormal(i).applyMatrix(matrix));

	for (size_t i = 0; i < mesh.getVertexCount(); i++)
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
