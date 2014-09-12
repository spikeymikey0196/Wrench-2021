#ifndef TERRAINMATERIAL_H
#define TERRAINMATERIAL_H

#include "Material.h"

#define TERRAINMATERIAL_DIFFUSE0 0
#define TERRAINMATERIAL_DIFFUSE1 1
#define TERRAINMATERIAL_DIFFUSE2 2
#define TERRAINMATERIAL_DIFFUSE3 3
#define TERRAINMATERIAL_CONTROLLER 4

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