#include "TerrainMaterial.h"

namespace Wrench
{
	TerrainMaterial::TerrainMaterial()
	{
		SetDiffuseMap(TERRAINMATERIAL_DIFFUSE0, NULL);
		SetDiffuseMap(TERRAINMATERIAL_DIFFUSE1, NULL);
		SetDiffuseMap(TERRAINMATERIAL_DIFFUSE2, NULL);
		SetDiffuseMap(TERRAINMATERIAL_DIFFUSE3, NULL);

		SetControllerMap(NULL);
	};

	TerrainMaterial::TerrainMaterial(Texture *nDiffuse0, Texture *nDiffuse1, Texture *nDiffuse2, Texture *nDiffuse3, Texture *nController)
	{
		SetDiffuseMap(TERRAINMATERIAL_DIFFUSE0, nDiffuse0);
		SetDiffuseMap(TERRAINMATERIAL_DIFFUSE1, nDiffuse1);
		SetDiffuseMap(TERRAINMATERIAL_DIFFUSE2, nDiffuse2);
		SetDiffuseMap(TERRAINMATERIAL_DIFFUSE3, nDiffuse3);

		SetControllerMap(nController);
	};

	void TerrainMaterial::SetDiffuseMap(int ID, Texture *nDiffuseN)
	{
		textures[ID] = nDiffuseN ? nDiffuseN : Texture::Missing();
	};

	Texture *TerrainMaterial::GetDiffuse(int ID)
	{
		return textures[ID];
	};

	void TerrainMaterial::SetControllerMap(Texture *nController)
	{
		textures[TERRAINMATERIAL_CONTROLLER] = nController ? nController : Texture::DefaultSpecularMap();
	};

	Texture *TerrainMaterial::GetController()
	{
		return textures[TERRAINMATERIAL_CONTROLLER];
	};

}
