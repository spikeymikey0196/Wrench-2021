#ifndef MATERIAL_H
#define MATERIAL_H

#include "Texture.h"

namespace Wrench
{
	class Material
	{
	protected:
		Texture *textures[8];

	public:
		Material();
		Material(Texture *t0, Texture *t1, Texture *t2, Texture *t3, Texture *t4, Texture *t5, Texture *t6, Texture *t7);
		virtual void Bind();
		virtual void Unbind();
		virtual void SetTexture(int texNum, Texture *t);
	};
}

#endif