#include "ModelObj.h"
#include "Utils.h"
#include <fstream>
#include <string>
#include <cstring>

using namespace std;

namespace Wrench
{
	ModelObj::ModelObj()
	{
		texture = NULL;
		bounds = BoundingBox();
		int vboID = 0;
		indexVBOID = 0;
		numFaces = 0;
	};

	ModelObj::ModelObj(const char *filename)
		: ModelObj()
	{
		Load(filename);
	};

	ModelObj::ModelObj(const char *filename, Texture *t)
		: ModelObj()
	{
		texture = t;
		Load(filename);
	};

	bool ModelObj::Load(const char *filename)
	{
		bounds = BoundingBox(Vector3(FLT_MAX, FLT_MAX, FLT_MAX), Vector3(FLT_MIN, FLT_MIN, FLT_MIN));

		ifstream MDLFILE(filename);

		if (MDLFILE.is_open())
		{
			int numVerts = 0;
			int numNormals = 0;
			int numTexs = 0;

			Vector3 *vertices = NULL;
			Vector3 *normals = NULL;
			Vector3 *tex = NULL;
			GLuint *indices = NULL;

			while (!MDLFILE.eof())
			{
				string line = "";
				getline(MDLFILE, line);

				switch (line[0])
				{
				case 'v':
				{
					switch (line[1])
					{
					case ' ':
						{
							numVerts++;
							vertices = (Vector3*)realloc(vertices, sizeof(Vector3) * numVerts);
							sscanf(line.c_str(), "%*s %f %f %f", &vertices[numVerts - 1].x, &vertices[numVerts - 1].y, &vertices[numVerts - 1].z);

							Vector3 min = bounds.Min();
							Vector3 max = bounds.Max();

							if (vertices[numVerts - 1].x < min.x) min.x = vertices[numVerts - 1].x;
							if (vertices[numVerts - 1].y < min.y) min.y = vertices[numVerts - 1].y;
							if (vertices[numVerts - 1].z < min.z) min.z = vertices[numVerts - 1].z;

							if (vertices[numVerts - 1].x > max.x) max.x = vertices[numVerts - 1].x;
							if (vertices[numVerts - 1].y > max.y) max.y = vertices[numVerts - 1].y;
							if (vertices[numVerts - 1].z > max.z) max.z = vertices[numVerts - 1].z;

							bounds.SetMin(min);
							bounds.SetMax(max);
						}
						break;

					case 't':
						numTexs++;
						tex = (Vector3*)realloc(tex, sizeof(Vector3) * numTexs);
						sscanf(line.c_str(), "%*s %f %f", &tex[numTexs - 1].x, &tex[numTexs - 1].y);
						tex[numTexs - 1].z = 0.0;
						break;

					case 'n':
						numNormals++;
						normals = (Vector3*)realloc(normals, sizeof(Vector3) * numNormals);
						sscanf(line.c_str(), "%*s %f %f %f", &normals[numNormals - 1].x, &normals[numNormals - 1].y, &normals[numNormals - 1].z);
						break;

					default: break;
					}
				}
					break;

				case 'f':
					numFaces++;
					break;

				default: break;
				}
			}

			Vertex *verts = new Vertex[numFaces * 3];
			indices = new GLuint[numFaces * 3];

			MDLFILE.clear();
			MDLFILE.seekg(0, ios::beg);

			int currentIndex = 0;

			while (!MDLFILE.eof())
			{
				string line = "";
				getline(MDLFILE, line);

				switch (line[0])
				{
				case 'f':
				{
					char *lineBuffer = (char*)line.c_str();
					char *token = strtok(lineBuffer, "f ");

					for (int a = 0; a < 3; a++)
					{
						int vertIndex = -1;
						int texIndex = -1;
						int normalIndex = -1;

						if (sscanf(token, "%d/%d/%d", &vertIndex, &texIndex, &normalIndex) != 3)
						{
							if (sscanf(token, "%d/%d", &vertIndex, &texIndex) != 2)
							{
								sscanf(token, "%d", &vertIndex);
							}
						}

						if (vertIndex > 0)
						{
							verts[currentIndex].position.x = vertices[vertIndex - 1].x;
							verts[currentIndex].position.y = vertices[vertIndex - 1].y;
							verts[currentIndex].position.z = vertices[vertIndex - 1].z;
						}

						if (texIndex > 0)
						{
							verts[currentIndex].tex.x = tex[texIndex - 1].x;
							verts[currentIndex].tex.y = tex[texIndex - 1].y;
						}

						if (normalIndex > 0)
						{
							verts[currentIndex].normal.x = normals[normalIndex - 1].x;
							verts[currentIndex].normal.y = normals[normalIndex - 1].y;
							verts[currentIndex].normal.z = normals[normalIndex - 1].z;
						}

						verts[currentIndex].color.r = 1.0;
						verts[currentIndex].color.g = 1.0;
						verts[currentIndex].color.b = 1.0;
						verts[currentIndex].color.a = 1.0;

						indices[currentIndex] = currentIndex;
						currentIndex++;

						token = strtok(NULL, "f ");
					}
				}
					break;

				default: break;
				}
			}

			glGenBuffers(1, &vboID);
			glBindBuffer(GL_ARRAY_BUFFER, vboID);

			glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * (numFaces * 3), NULL, GL_STATIC_DRAW);
			glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(Vertex) * (numFaces * 3), verts);

			glTexCoordPointer(2, GL_FLOAT, sizeof(Vertex), BUFFER_OFFSET(12));
			glNormalPointer(GL_FLOAT, sizeof(Vertex), BUFFER_OFFSET(20));
			glColorPointer(4, GL_FLOAT, sizeof(Vertex), BUFFER_OFFSET(32));
			glVertexPointer(3, GL_FLOAT, sizeof(Vertex), BUFFER_OFFSET(0));

			glGenBuffers(1, &indexVBOID);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexVBOID);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, (numFaces * 3) * sizeof(GLuint), indices, GL_STATIC_DRAW);

			if (indices) delete[] indices;
			if (vertices) delete[] vertices;
			if (normals) delete[] normals;
			if (tex) delete[] tex;
			if (verts) delete[] verts;

			return true;
		}

		return false;
	}

	void ModelObj::Render()
	{
		if (texture)
			texture->Bind();

		glBindBuffer(GL_ARRAY_BUFFER, vboID);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexVBOID);

		glEnableClientState(GL_TEXTURE_COORD_ARRAY);
		glEnableClientState(GL_COLOR_ARRAY);
		glEnableClientState(GL_NORMAL_ARRAY);
		glEnableClientState(GL_VERTEX_ARRAY);

		glTexCoordPointer(2, GL_FLOAT, sizeof(Vertex), BUFFER_OFFSET(12));
		glNormalPointer(GL_FLOAT, sizeof(Vertex), BUFFER_OFFSET(20));
		glColorPointer(4, GL_FLOAT, sizeof(Vertex), BUFFER_OFFSET(32));
		glVertexPointer(3, GL_FLOAT, sizeof(Vertex), BUFFER_OFFSET(0));

		glDrawElements(GL_TRIANGLES, numFaces * 3, GL_UNSIGNED_INT, BUFFER_OFFSET(0));

		glDisableClientState(GL_COLOR_ARRAY);
		glDisableClientState(GL_VERTEX_ARRAY);
		glDisableClientState(GL_TEXTURE_COORD_ARRAY);
		glDisableClientState(GL_NORMAL_ARRAY);

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

		if (texture)
			texture->Unbind();
	};

	BoundingBox ModelObj::Bounds()
	{
		return bounds;
	};
}
