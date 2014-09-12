#include "BasicMaterial.h"

namespace Wrench
{
	BasicMaterial::BasicMaterial()
		: Material()
	{
		SetDiffuseMap(NULL);
		SetNormalMap(NULL);
		SetSpecularMap(NULL);
	};

	BasicMaterial::BasicMaterial(Texture *nDiffuseMap, Texture *nNormalMap, Texture *nSpecularMap)
		: Material()
	{
		SetDiffuseMap(nDiffuseMap);
		SetNormalMap(nNormalMap);
		SetSpecularMap(nSpecularMap);
	};

	void BasicMaterial::SetDiffuseMap(Texture *nDiffuseMap)
	{
		textures[BASICMATERIAL_DIFFUSE] = nDiffuseMap ? nDiffuseMap : Texture::DefaultDiffuseMap();
	};

	Texture *BasicMaterial::GetDiffuseMap()
	{
		return textures[BASICMATERIAL_DIFFUSE];
	};

	void BasicMaterial::SetNormalMap(Texture *nNormalMap)
	{
		textures[BASICMATERIAL_NORMAL] = nNormalMap ? nNormalMap : Texture::DefaultNormalMap();
	};

	Texture *BasicMaterial::GetNormalMap()
	{
		return textures[BASICMATERIAL_NORMAL];
	};

	void BasicMaterial::SetSpecularMap(Texture *nSpecularMap)
	{
		textures[BASICMATERIAL_SPECULAR] = nSpecularMap ? nSpecularMap : Texture::DefaultSpecularMap();
	};

	Texture *BasicMaterial::GetSpecularMap()
	{
		return textures[BASICMATERIAL_SPECULAR];
	};

}
