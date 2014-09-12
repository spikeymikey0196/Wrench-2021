#include "Material.h"

namespace Wrench
{
	Material::Material()
	{
		for (int a = 0; a < 8; a++)
			textures[a] = NULL;
	};

	void Material::Bind()
	{
		for (int a = 0; a < 8; a++)
			if (textures[a])
				textures[a]->Bind(a);
	};

	void Material::Unbind()
	{
		for (int a = 7; a >= 0; a--)
			if (textures[a])
				textures[a]->Unbind(a);
	};

	void Material::SetTexture(int texNum, Texture *t)
	{
		textures[texNum] = t;
	};

}
