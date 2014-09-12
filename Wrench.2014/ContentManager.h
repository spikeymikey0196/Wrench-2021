#ifndef CONTENTMANAGER_H
#define CONTENTMANAGER_H

#include "Model.h"
#include "Texture.h"
#include "Shader.h"
#include "Terrain.h"
#include "Font.h"
#include "Material.h"

#include <map>
#include <string>

using namespace std;

namespace Wrench
{
	class ContentManager
	{
	protected:
		map<string, Model *> models;
		map<string, Texture *> textures;
		map<string, Shader*> shaders;
		map<string, Terrain *> terrain;
		map<string, Font *> fonts;
		map<string, Material *> materials;

		Texture *blank;

	public:
		ContentManager();
		~ContentManager();
		virtual bool LoadFile(const char *filename);

		Model *AddModel(string name, Model *m);
		Model *GetModel(string name);

		Texture *AddTexture(string name, Texture *t);
		Texture *GetTexture(string name);

		Shader *AddShader(string name, Shader *s);
		Shader *GetShader(string name);

		Terrain *AddTerrain(string name, Terrain *t);
		Terrain *GetTerrain(string name);

		Font *AddFont(string name, Font *f);
		Font *GetFont(string name);

		Material *AddMaterial(string name, Material *m);
		Material *GetMaterial(string name);
	};
}

#endif
