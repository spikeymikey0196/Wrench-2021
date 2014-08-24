#ifndef TEXTURE_H
#define TEXTURE_H

#include "GLee.h"
#include <GL/gl.h>
#include <GL/glu.h>

#include "SOIL.h"
#include "Color4.h"
#include "tinyxml.h"

namespace Wrench
{
	class Texture
	{
	protected:
		GLuint texID;
		float texWidth;
		float texHeight;
		float pixelWidth;
		float pixelHeight;

		static Texture *missing;
	
	public:
		Texture();
		Texture(const char *filename);
		Texture(Color4 color, int width, int height);
		Texture(unsigned int TexID, int width, int height);
		Texture(int width, int height, unsigned char *bytes);
		Texture(TiXmlElement *entry);
		~Texture();

		bool Load(const char *filename);
		void CreateBlank(Color4 color, int width, int height);

		void Bind();
		void Bind(int channel);
		void Unbind();
		void Unbind(int channel);

		float Width();
		float Height();
		float PixelWidth();
		float PixelHeight();

		static Texture *Missing();
	};
}

#endif