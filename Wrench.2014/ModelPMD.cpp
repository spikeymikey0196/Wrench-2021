#include "ModelPMD.h"
#include "Utils.h"
#include <fstream>
#include <string>
#include <cstring>
#include "GLee.h"
#include <GL/gl.h>
#include <GL/glu.h>

using namespace std;

namespace Wrench
{
	ModelPMD::ModelPMD(const char *filename)
	{
		Load(filename);
	};

	bool ModelPMD::Load(const char *filename)
	{
		ifstream pmdFile;
		pmdFile.open(filename, ios::binary);

		if (pmdFile.is_open())
		{
			vertexArray = VertexArray(VA_INDICES);
			bounds = BoundingBox(Vector3(FLT_MAX, FLT_MAX, FLT_MAX), Vector3(FLT_MIN, FLT_MIN, FLT_MIN));

			char magic[4] = { 0 };
			float version = 0;

			char name[21] = { 0 };
			char comment[257] = { 0 };

			int numVertices = 0;
			int numIndices = 0;


			pmdFile.read(magic, 3);
			pmdFile.read((char*)&version, 4);

			pmdFile.read(name, 20);
			pmdFile.read(comment, 256);


			pmdFile.read((char*)&numVertices, 4);

			//temp
			char vertexInfo[39] = { 0 };
			Vector3 min = bounds.Min();
			Vector3 max = bounds.Max();

			for (int a = 0; a < numVertices; a++)
			{
				pmdFile.read(vertexInfo, 38);

				Vertex v;

				memcpy((void*)&v.position.x, &vertexInfo[0], 4);
				memcpy((void*)&v.position.y, &vertexInfo[4], 4);
				memcpy((void*)&v.position.z, &vertexInfo[8], 4);

				memcpy((void*)&v.normal.x, &vertexInfo[12], 4);
				memcpy((void*)&v.normal.y, &vertexInfo[16], 4);
				memcpy((void*)&v.normal.z, &vertexInfo[20], 4);

				memcpy((void*)&v.tex.x, &vertexInfo[24], 4);
				memcpy((void*)&v.tex.y, &vertexInfo[28], 4);

				if (v.position.x < min.x) min.x = v.position.x;
				if (v.position.y < min.y) min.y = v.position.y;
				if (v.position.z < min.z) min.z = v.position.z;

				if (v.position.x > max.x) max.x = v.position.x;
				if (v.position.y > max.y) max.y = v.position.y;
				if (v.position.z > max.z) max.z = v.position.z;

				vertexArray.PushVertex(v);
			}

			bounds.SetMin(min);
			bounds.SetMax(max);

			pmdFile.read((char *)&numIndices, 4);

			unsigned short v1 = 0;
			unsigned short v2 = 0;
			unsigned short v3 = 0;

			for (int a = 0; a < numIndices/3; a++)
			{
				pmdFile.read((char *)&v1, 2);
				pmdFile.read((char *)&v2, 2);
				pmdFile.read((char *)&v3, 2);

				vertexArray.PushTriangleIndices(v1, v2, v3);
			}


			int numMaterials = 0;
			char matBuffer[71] = { 0 };
			pmdFile.read((char*)&numMaterials, 4);

			for (int a = 0; a < numMaterials; a++)
			{
				pmdFile.read(matBuffer, 70);
			}

			return true;
		}

		return false;
	};

	void ModelPMD::Render()
	{
		vertexArray.Render();
	};

	BoundingBox ModelPMD::Bounds()
	{
		return bounds;
	};

}