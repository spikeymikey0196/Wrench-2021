#ifndef TERRAINMATERIAL_H
#define TERRAINMATERIAL_H

#include "Material.h"

#define TERRAINMATERIAL_DIFFUSE0 1
#define TERRAINMATERIAL_DIFFUSE1 2
#define TERRAINMATERIAL_DIFFUSE2 3
#define TERRAINMATERIAL_DIFFUSE3 4
#define TERRAINMATERIAL_CONTROLLER 0

namespace Wrench
{

	class TerrainMaterial : public Material
	{
	public:
		TerrainMaterial();
		TerrainMaterial(Texture *nDiffuse0, Texture *nDiffuse1, Texture *nDiffuse2, Texture *nDiffuse3, Texture *nController);

		virtual void SetDiffuseMap(int ID, Texture *nDiffuseN);
		virtual Texture *GetDiffuse(int ID);

		virtual void SetControllerMap(Texture *nController);
		virtual Texture *GetController();
	};
}

#endif