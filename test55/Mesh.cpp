#include "Mesh.h"

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

	for (int i = 0; i < 12; i++)
	{
		if (i % 2 == 0)
		{
			char cr = 255/8*(rand() % 5+2);
			char cg = 255 / 8 *( rand() % 5+2);
			char cb = 255 / 8 *( rand() % 5+2);
			m = Material(cr, cg, cb);
		}
		bakedMaterialArray.push_back(m);
	}

}

Mesh::Mesh(double paneSize, int w, int h)
{
	w;
	h;
	triMode = true;
	materialBuffer = NULL;

	normalIndexBufferSize = w*h*2;
	normalIndexBuffer = new size_t[normalIndexBufferSize];
	for (int i = 0; i < normalIndexBufferSize; i += 1)
	{
		normalIndexBuffer[i] = 1;
	}
	normalArray.push_back(Vector3D(0, 0, -1));

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
			double h = dproduct[(w + 1) * j + i] * 100;
			vertexArray.push_back(Vector3D(i*paneSize + -10 * rand() % 50, j * paneSize+-10*rand() % 50, h));
			if (j * w * i % 3 == 0)
			{
				/*char cr = 255 / 8 * (rand() % 3 + 3);
				char cg = 255 / 8 * (rand() % 3 + 3);
				char cb = 255 / 8 * (rand() % 3 + 3);
				
				if (h < 0)
				{
					cr = 230;
					cg = 235;
					cb = 235;
				}
				//m = Material(cr, cb, cg);

				//bakedMaterialArray.push_back(m);
				//bakedMaterialArray.push_back(m);*/
			}
		}
	}

	for (int i = 0; i < w * h * 2; i++)
	{
		char cr = 255 / 8 * (rand() % 3 + 3);
		char cg = 255 / 8 * (rand() % 3 + 3);
		char cb = 255 / 8 * (rand() % 3 + 3);
		m = Material(cr, cb, cg);

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
