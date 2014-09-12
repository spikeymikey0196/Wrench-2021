#include "Material.h"

namespace Wrench
{
	Material::Material()
	{
		for (int a = 0; a < 8; a++)
			textures[a] = NULL;
	};

	Material::Material(Texture *t0, Texture *t1, Texture *t2, Texture *t3, Texture *t4, Texture *t5, Texture *t6, Texture *t7)
	{
		textures[0] = t0;
		textures[1] = t1;
		textures[2] = t2;
		textures[3] = t3;
		textures[4] = t4;
		textures[5] = t5;
		textures[6] = t6;
		textures[7] = t7;
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
