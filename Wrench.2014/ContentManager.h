#ifndef CONTENTMANAGER_H
#define CONTENTMANAGER_H

#include "Model.h"
#include "Texture.h"
#include "Shader.h"

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
	};
}

#endif
