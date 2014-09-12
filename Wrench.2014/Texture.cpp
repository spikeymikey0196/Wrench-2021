#include "Texture.h"
#include <string>

using namespace std;

namespace Wrench
{
	Texture *Texture::missing = NULL;
	Texture *Texture::diffuseMap = NULL;
	Texture *Texture::normalMap = NULL;
	Texture *Texture::specularMap = NULL;

	Texture::Texture()
	{
		texID = 0;
		texWidth = 0.0;
		texHeight = 0.0;
		pixelWidth = 0.0;
		pixelHeight = 0.0;
	};
	
	Texture::Texture(const char *filename)
		: Texture()
	{
		Load(filename);
	};
	
	Texture::Texture(Color4 color, int width, int height)
		: Texture()
	{
		CreateBlank(color, width, height);
	};

	Texture::Texture(unsigned int TexID, int width, int height)
		: Texture()
	{
		texID = TexID;
		texWidth = (float)width;
		texHeight = (float)height;
		pixelWidth = 1.0 / texWidth;
		pixelHeight = 1.0 / texHeight;
	};

	Texture::Texture(int width, int height, unsigned char *bytes)
	{
		texWidth = (float)width;
		texHeight = (float)height;

		pixelWidth = 1.0 / texWidth;
		pixelHeight = 1.0 / texHeight;

		glPixelStorei(GL_UNPACK_ALIGNMENT, 4);

		glGenTextures(1, &texID);
		glBindTexture(GL_TEXTURE_2D, texID);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, bytes);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

		glBindTexture(GL_TEXTURE_2D, 0);
	};

	Texture::Texture(TiXmlElement *entry)
	{
		string tFile = "";
		entry->QueryStringAttribute("Filename", &tFile);

		Load(tFile.c_str());
	}

	Texture::~Texture()
	{
		if(texID > 0)
		{
			glDeleteTextures(1, &texID);
		}
	};
	
	bool Texture::Load(const char *filename)
	{
		int w = 0;
		int h = 0;
		texID = SOIL_load_OGL_texture(filename, SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT);
		
		glBindTexture(GL_TEXTURE_2D, texID);

		glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_WIDTH, &w);
		glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_HEIGHT, &h);
		
		texWidth = (float)w;
		texHeight = (float)h;

		pixelWidth = 1.0 / texWidth;
		pixelHeight = 1.0 / texHeight;

		return false;
	};
	
	void Texture::CreateBlank(Color4 color, int width, int height)
	{
		texWidth = (float)width;
		texHeight = (float)height;

		pixelWidth = 1.0 / texWidth;
		pixelHeight = 1.0 / texHeight;

		unsigned char *buffer = new unsigned char[4 * width * height];
		
		for(int y = 0; y < height; y++)
		{
			for(int x = 0; x < width; x++)
			{
				buffer[y * width * 4 + x * 4] = color.r * 255;
				buffer[y * width * 4 + x * 4+1] = color.g * 255;
				buffer[y * width * 4 + x * 4+2] = color.b * 255;
				buffer[y * width * 4 + x * 4+3] = color.a * 255;
			}
		}
		
		glPixelStorei(GL_UNPACK_ALIGNMENT,4);

		glGenTextures(1, &texID);
		glBindTexture(GL_TEXTURE_2D, texID);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, buffer);

		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_CLAMP_TO_EDGE);

		glBindTexture(GL_TEXTURE_2D, 0);

		delete[] buffer;
	};
	
	void Texture::Bind()
	{
		glBindTexture(GL_TEXTURE_2D, texID);
	};
	
	void Texture::Bind(int channel)
	{
		glActiveTexture(GL_TEXTURE0 + channel);
		Bind();
	};
	
	void Texture::Unbind()
	{
		glBindTexture(GL_TEXTURE_2D, 0);
	};
	
	void Texture::Unbind(int channel)
	{
		glActiveTexture(GL_TEXTURE0 + channel);
		Unbind();
	};
	
	float Texture::Width()
	{
		return texWidth;
	};
	
	float Texture::Height()
	{
		return texHeight;
	};
	
	float Texture::PixelWidth()
	{
		return pixelWidth;
	};
	
	float Texture::PixelHeight()
	{
		return pixelHeight;
	};
	
	Texture *Texture::Missing()
	{
		if (missing == NULL)
		{
			unsigned char *bytes = new unsigned char[80];

			for (int y = 0; y < 4; y++)
			{
				for (int x = 0; x < 4; x++)
				{
					Color4 c = Color4(1, 1, 1, 1);

					if (y % 2 == 0)
					{
						if (x % 2 == 1)
							c = Color4(0, 0, 1, 1);
					}
					else
					{
						if (x % 2 == 0)
							c = Color4(0, 0, 1, 1);
					}

					int p = c.RGBA();
					memcpy(&bytes[y * 16 + x * 4], &p, 4);
				}
			}
			missing = new Texture(4, 4, bytes);

			missing->Bind();
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
			missing->Unbind();
		}

		return missing;
	};

	Texture *Texture::DefaultDiffuseMap()
	{
		if (!diffuseMap)
			diffuseMap = new Texture(Color4(1, 1, 1, 1), 1, 1);
		return diffuseMap;
	};

	Texture *Texture::DefaultNormalMap()
	{
		if (!normalMap)
			normalMap = new Texture(Color4(0.5, 0.5, 0.5, 1.0),1,1);
		return normalMap;
	};

	Texture *Texture::DefaultSpecularMap()
	{
		if (!specularMap)
			specularMap = new Texture(Color4(0, 0, 0, 1), 1, 1);
		return specularMap;
	};

}
