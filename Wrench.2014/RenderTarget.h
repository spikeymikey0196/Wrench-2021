#ifndef RENDERTARGET_H
#define RENDERTARGET_H

#include "GLee.h"
#include <GL/gl.h>
#include <GL/glu.h>
#include "Texture.h"

namespace Wrench
{
	class RenderTarget
	{
	private:
		Texture *t;

	protected:
		unsigned int fbID;
		unsigned int colorID;
		unsigned int depthID;

		int width;
		int height;

	public:
		RenderTarget(int w, int h);
		void Bind();
		void Unbind();
		Texture *GetTexture();
	};
}

#endif
