#ifndef BASICMATERIAL_H
#define BASICMATERIAL_H

#include "Material.h"

#define BASICMATERIAL_DIFFUSE 0
#define BASICMATERIAL_NORMAL 1
#define BASICMATERIAL_SPECULAR 2


namespace Wrench
{
	class BasicMaterial : public Material
	{
	public:
		BasicMaterial();
		BasicMaterial(Texture *nDiffuseMap, Texture *nNormalMap, Texture *nSpecularMap);

		virtual void SetDiffuseMap(Texture *nDiffuseMap);
		virtual Texture *GetDiffuseMap();

		virtual void SetNormalMap(Texture *nNormalMap);
		virtual Texture *GetNormalMap();

		virtual void SetSpecularMap(Texture *nSpecularMap);
		virtual Texture *GetSpecularMap();
	};
}

#endif
