#include "Water.h"
#include "WMath.h"

namespace Wrench
{
	extern unsigned int GetTicks();

	Water::Water()
	{
		width = 0;
		length = 0;

		vertexArray = VertexArray(VA_INDICES);

		shader = Shader::DefaultWater();
		tex0 = shader->GetUniform("tex0");
		ticks = shader->GetUniform("time");
	};

	Water::Water(int nWidth, int nHeight, float waterHeight, Texture *nTexture)
		: Water()
	{
		CreateBlank(nWidth, nHeight, waterHeight);

		texture = nTexture;
	};

	void Water::CreateBlank(int nWidth, int nLength, float waterHeight)
	{
		width = nWidth;
		length = nLength;

		for (int z = 0; z < nLength; z++)
		{
			for (int x = 0; x < nWidth; x++)
			{
				vertexArray.PushVertex({ { (float)x, waterHeight, (float)z }, { (float)x, (float)z }, { 1, 1, 1 }, { 1, 1, 1, 1 } });
			}
		}

		for (int z = 0; z < nLength - 1; z++)
		{
			for (int x = 0; x < nWidth - 1; x++)
			{
				vertexArray.PushTriangleIndices(z * nWidth + x, (z + 1) * nWidth + x, z * nWidth + x + 1);
				vertexArray.PushTriangleIndices((z + 1) * nWidth + x, (z + 1) * nWidth + x + 1, z * nWidth + x + 1);
			}
		}
	};

	void Water::SetHeight(int x, int z, float vertexHeight)
	{
		Vertex v = vertexArray.GetVertex(x + (z * width));
		v.position.y = vertexHeight;

		vertexArray.SetVertex(x + (z * width), v);
	};

	void Water::SetupVBO()
	{
		vertexArray.GenerateVBO();
	};

	void Water::Render()
	{
		shader->Bind();

		glUniform1i(tex0, 0);
		glUniform1f(ticks, GetTicks());

		texture->Bind(0);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

		vertexArray.Render();

		texture->Bind(0);

		shader->Unbind();
	};

	void Water::Render(const Matrix &worldMatrix)
	{
		glPushMatrix();
		glLoadMatrixf(((Matrix)worldMatrix).m);
		Render();
		glPopMatrix();
	};

	float Water::GetHeight(float x, float z)
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

	float Water::GetHeight(const Vector3 &pos)
	{
		return GetHeight(pos.x, pos.z);
	};

	BoundingBox Water::Bounds()
	{
		return BoundingBox();	//temp
	};
}
