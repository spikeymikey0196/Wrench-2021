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
		virtual void Bind();
		virtual void Unbind();
		virtual void SetTexture(int texNum, Texture *t);
	};
}

#endif