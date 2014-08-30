#ifndef HTTPTEXTURE_H
#define HTTPTEXTURE_H

#include "Texture.h"
#include <future>

using namespace std;

namespace Wrench
{
	class HTTPTexture : public Texture
	{
	protected:
		Texture *downloadedTexture;
		future<Texture *> download;

	public:
		HTTPTexture(const char *domain, const char *filename, const char *saveLocation);

		void Bind();
		void Bind(int channel);
		void Unbind();
		void Unbind(int channel);

		float Width();
		float Height();
		float PixelWidth();
		float PixelHeight();
	};
}

#endif