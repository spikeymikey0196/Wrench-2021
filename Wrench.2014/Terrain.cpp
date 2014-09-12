#include "Terrain.h"
#include "WMath.h"
#include "SOIL.h"

namespace Wrench
{
	Terrain::Terrain()
	{
		width = 0;
		length = 0;

		vertexArray = VertexArray(VA_INDICES);

		shader = Shader::DefaultTerrain();

		shader->Bind();
		tex0 = shader->GetUniform("tex0");
		tex1 = shader->GetUniform("tex1");
		tex2 = shader->GetUniform("tex2");
		tex3 = shader->GetUniform("tex3");
		tex4 = shader->GetUniform("tex4");
		
		glUniform1i(tex0, 0);
		glUniform1i(tex1, 1);
		glUniform1i(tex2, 2);
		glUniform1i(tex3, 3);
		glUniform1i(tex4, 4);
		shader->Unbind();
	};

	Terrain::Terrain(int nWidth, int nLength)
		: Terrain()
	{
		CreateBlank(nWidth, nLength);
	};

	Terrain::Terrain(int nWidth, int nLength, Texture *nController, Texture *tex0, Texture *tex1, Texture *tex2, Texture *tex3)
		: Terrain()
	{
		CreateBlank(nWidth, nLength);

		controller = nController;
		textures[0] = tex0;
		textures[1] = tex1;
		textures[2] = tex2;
		textures[3] = tex3;
	};

	Terrain::Terrain(const string &heightmap, Texture *nController, Texture *tex0, Texture *tex1, Texture *tex2, Texture *tex3)
		: Terrain()
	{
		int w, l, channels;
		unsigned char *ht_map = SOIL_load_image
			(
			heightmap.c_str(),
			&w, &l, &channels,
			SOIL_LOAD_RGB
			);

		CreateBlank(w, l);

		//load heightmap data
		for (int z = 0; z < l; z++)
		{
			for (int x = 0; x < w; x++)
			{
				Vertex v = vertexArray.GetVertex(z * w + x);

				v.position.y += 0.1f * ht_map[3 * z * w + (x * channels)];

				vertexArray.SetVertex(z * w + x, v);
				waypoints[z][x] = new Waypoint(v.position);
			}
		}

		CalculateNormals();

		controller = nController;
		textures[0] = tex0;
		textures[1] = tex1;
		textures[2] = tex2;
		textures[3] = tex3;

		delete[] ht_map;
	};

	void Terrain::CreateBlank(int nWidth, int nLength)
	{
		width = nWidth;
		length = nLength;

		float w = 1.0f / (float)width;
		float l = 1.0f / (float)length;

		waypoints = new Waypoint**[length];

		for (int z = 0; z < nLength; z++)
		{
			waypoints[z] = new Waypoint*[width];
			for (int x = 0; x < nWidth; x++)
			{
				vertexArray.PushVertex({ { (float)x, 0, (float)z }, { w * (float)x, 1.0f - l * (float)z }, { 1, 1, 1 }, { 1, 1, 1, 1 } });
				waypoints[z][x] = new Waypoint(Vector3((float)x, 0, (float)z));
			}
		}

		for (int z = 0; z < nLength-1; z++)
		{
			for (int x = 0; x < nWidth-1; x++)
			{
				vertexArray.PushTriangleIndices(z * nWidth + x, (z + 1) * nWidth + x, z * nWidth + x + 1);
				vertexArray.PushTriangleIndices((z + 1) * nWidth + x, (z + 1) * nWidth + x+1, z * nWidth + x + 1);
			}
		}

		for (int z = 0; z < length; z++)
		{
			for (int x = 0; x < width; x++)
			{
				if (z > 0) waypoints[z][x]->AddAdjacent(waypoints[z - 1][x]);
				if (x > 0) waypoints[z][x]->AddAdjacent(waypoints[z][x - 1]);

				if (z < length - 1) waypoints[z][x]->AddAdjacent(waypoints[z + 1][x]);
				if (x < width - 1) waypoints[z][x]->AddAdjacent(waypoints[z][x + 1]);
			}
		}
	};

	void Terrain::SetHeight(int x, int z, float vertexHeight)
	{
		Vertex v = vertexArray.GetVertex(x + (z * width));
		v.position.y = vertexHeight;

		vertexArray.SetVertex(x + (z * width), v);
		waypoints[z][x]->SetPosition(v.position);
	};

	void Terrain::CalculateNormals()
	{
		//normal calc (edges incomplete)
		for (int a = 0; a < length; a++)
		{
			for (int b = 0; b < width; b++)
			{
				//middle ones
				if ((a > 0 && b > 0) && (a < length - 1 && b < width - 1))
				{
					Vector3 quadNormals[6];
					Vector3 sum;
					Vector3 normal;

					quadNormals[0] = Vector3::TriangleNormal(
						Vector3(vertexArray.GetVertex(((a)* width + (b))).position.x, vertexArray.GetVertex(((a)* width + (b))).position.y, vertexArray.GetVertex(((a)* width + (b))).position.z),
						Vector3(vertexArray.GetVertex(((a)* width + (b - 1))).position.x, vertexArray.GetVertex(((a)* width + (b - 1))).position.y, vertexArray.GetVertex(((a)* width + (b - 1))).position.z),
						Vector3(vertexArray.GetVertex(((a - 1) * width + (b))).position.x, vertexArray.GetVertex(((a - 1) * width + (b))).position.y, vertexArray.GetVertex(((a - 1) * width + (b))).position.z)
						);

					quadNormals[1] = Vector3::TriangleNormal(
						Vector3(vertexArray.GetVertex(((a)* width + (b))).position.x, vertexArray.GetVertex(((a)* width + (b))).position.y, vertexArray.GetVertex(((a)* width + (b))).position.z),
						Vector3(vertexArray.GetVertex(((a + 1) * width + (b - 1))).position.x, vertexArray.GetVertex(((a + 1) * width + (b - 1))).position.y, vertexArray.GetVertex(((a + 1) * width + (b - 1))).position.z),
						Vector3(vertexArray.GetVertex(((a)* width + (b - 1))).position.x, vertexArray.GetVertex(((a)* width + (b - 1))).position.y, vertexArray.GetVertex(((a)* width + (b - 1))).position.z)
						);

					quadNormals[2] = Vector3::TriangleNormal(
						Vector3(vertexArray.GetVertex(((a)* width + (b))).position.x, vertexArray.GetVertex(((a)* width + (b))).position.y, vertexArray.GetVertex(((a)* width + (b))).position.z),
						Vector3(vertexArray.GetVertex(((a + 1) * width + (b))).position.x, vertexArray.GetVertex(((a + 1) * width + (b))).position.y, vertexArray.GetVertex(((a + 1) * width + (b))).position.z),
						Vector3(vertexArray.GetVertex(((a + 1) * width + (b - 1))).position.x, vertexArray.GetVertex(((a + 1) * width + (b - 1))).position.y, vertexArray.GetVertex(((a + 1) * width + (b - 1))).position.z)
						);

					quadNormals[3] = Vector3::TriangleNormal(
						Vector3(vertexArray.GetVertex(((a)* width + (b))).position.x, vertexArray.GetVertex(((a)* width + (b))).position.y, vertexArray.GetVertex(((a)* width + (b))).position.z),
						Vector3(vertexArray.GetVertex(((a)* width + (b + 1))).position.x, vertexArray.GetVertex(((a)* width + (b + 1))).position.y, vertexArray.GetVertex(((a)* width + (b + 1))).position.z),
						Vector3(vertexArray.GetVertex(((a + 1) * width + (b))).position.x, vertexArray.GetVertex(((a + 1) * width + (b))).position.y, vertexArray.GetVertex(((a + 1) * width + (b))).position.z)
						);

					quadNormals[4] = Vector3::TriangleNormal(
						Vector3(vertexArray.GetVertex(((a)* width + (b))).position.x, vertexArray.GetVertex(((a)* width + (b))).position.y, vertexArray.GetVertex(((a)* width + (b))).position.z),
						Vector3(vertexArray.GetVertex(((a - 1) * width + (b + 1))).position.x, vertexArray.GetVertex(((a - 1) * width + (b + 1))).position.y, vertexArray.GetVertex(((a - 1) * width + (b + 1))).position.z),
						Vector3(vertexArray.GetVertex(((a)* width + (b + 1))).position.x, vertexArray.GetVertex(((a)* width + (b + 1))).position.y, vertexArray.GetVertex(((a)* width + (b + 1))).position.z)
						);

					quadNormals[5] = Vector3::TriangleNormal(
						Vector3(vertexArray.GetVertex(((a)* width + (b))).position.x, vertexArray.GetVertex(((a)* width + (b))).position.y, vertexArray.GetVertex(((a)* width + (b))).position.z),
						Vector3(vertexArray.GetVertex(((a - 1) * width + (b))).position.x, vertexArray.GetVertex(((a - 1) * width + (b))).position.y, vertexArray.GetVertex(((a - 1) * width + (b))).position.z),
						Vector3(vertexArray.GetVertex(((a - 1) * width + (b + 1))).position.x, vertexArray.GetVertex(((a - 1) * width + (b + 1))).position.y, vertexArray.GetVertex(((a - 1) * width + (b + 1))).position.z)
						);

					sum = quadNormals[0] + quadNormals[1] + quadNormals[2] + quadNormals[3] + quadNormals[4] + quadNormals[5];
					normal = sum / Vector3(6.0, 6.0, 6.0);
					normal = normal * Vector3(-1.0, -1.0, -1.0);

					Vertex v = vertexArray.GetVertex((a * width + b));
					v.normal = normal;
					vertexArray.SetVertex(a * width + b, v);
				}
			}
		}
	};

	void Terrain::SetupVBO()
	{
		vertexArray.GenerateVBO();
	};

	void Terrain::Render()
	{
		shader->Bind();

		controller->Bind(0);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		textures[0]->Bind(1);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		textures[1]->Bind(2);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		textures[2]->Bind(3);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		textures[3]->Bind(4);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

		vertexArray.Render();

		textures[3]->Bind(4);
		textures[2]->Bind(3);
		textures[1]->Bind(2);
		textures[0]->Bind(1);
		controller->Bind(0);

		shader->Unbind();
	};

	void Terrain::Render(const Matrix &worldMatrix)
	{
		glPushMatrix();
		glLoadMatrixf(((Matrix)worldMatrix).m);
		Render();
		glPopMatrix();
	};

	void Terrain::RenderWaypoints(const Matrix &worldMatrix)
	{
		glPushMatrix();
		glLoadMatrixf(((Matrix)worldMatrix).m);
		
		Vector3 v;
		glPointSize(5.0f);
		glBegin(GL_POINTS);
		for (int z = 0; z < length; z++)
		{
			for (int x = 0; x < width; x++)
			{
				v = waypoints[z][x]->Position();
				glVertex3f(v.x, v.y, v.z);
			}
		}
		glEnd();
		glPointSize(1.0f);
		glPopMatrix();
	};

	float Terrain::GetHeight(float x, float z)
	{
		if ((x >= 0 && z >= 0) && (x < width - 1 && z < length - 1))
		{
			float distanceFromLeft, distanceFromTop;
			distanceFromLeft = fmod(x, 1.0f);
			distanceFromTop = fmod(z, 1.0f);

			Vertex v1 = vertexArray.GetVertex((int)z * width + (int)x);
			Vertex v2 = vertexArray.GetVertex((int)z * width + (int)x + 1);
			Vertex v3 = vertexArray.GetVertex(((int)z + 1) * width + (int)x);
			Vertex v4 = vertexArray.GetVertex(((int)z + 1) * width + ((int)x + 1));

			float topHeight = lerp(v1.position.y, v2.position.y, distanceFromLeft);
			float bottomheight = lerp(v3.position.y, v4.position.y, distanceFromLeft);

			float baseHeight = lerp(topHeight, bottomheight, distanceFromTop);
			//end formula for following terrain

			return baseHeight;
		}

		return FLT_MIN;
	};

	float Terrain::GetHeight(const Vector3 &pos)
	{
		return GetHeight(pos.x, pos.z);
	};

	BoundingBox Terrain::Bounds()
	{
		return BoundingBox();	//temp
	};

	Waypoint *Terrain::WaypointAt(float x, float z)
	{
		if (x < 0 || x > width - 1 || z < 0 || z > length - 1)
			return NULL;
		return waypoints[(int)z][(int)x];
	}
};
