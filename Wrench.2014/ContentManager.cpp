#include "ContentManager.h"
#include "tinyxml.h"
#include "MissingModel.h"
#include "ModelObj.h"
#include "Utils.h"

#include <iterator>

using namespace std;

namespace Wrench
{
	ContentManager::ContentManager()
	{
		blank = new Texture(Color4(1, 1, 1, 1), 4, 4);
	};

	ContentManager::~ContentManager()
	{
		for (auto it : models)
			delete it.second;

		for (auto it : textures)
			delete it.second;

		models.clear();
		textures.clear();
	};

	bool ContentManager::LoadFile(const char *filename)
	{
		TiXmlDocument doc;

		if (doc.LoadFile(filename))
		{
			if (TiXmlElement *root = doc.RootElement())
			{
				XmlLoop(root, entry)
				{
					string valueStr = entry->ValueStr();
					string name = "";

					entry->QueryStringAttribute("Name", &name);

					if (!valueStr.compare("Texture"))
						AddTexture(name, new Texture(entry));
					else if (!valueStr.compare("Shader"))
						AddShader(name, new Shader(entry));
					else if (!valueStr.compare("Model"))
					{
						string mFile = "";
						string tName = "";

						entry->QueryStringAttribute("Filename", &mFile);
						entry->QueryStringAttribute("Texture", &tName);

						AddModel(name, new ModelObj(mFile.c_str(), GetTexture(tName)));
					}
					else{}
				}

				return true;
			}
		}

		return false;
	}

	Model *ContentManager::AddModel(string name, Model *m)
	{
		models[name] = m;
		return GetModel(name);
	};

	Model *ContentManager::GetModel(string name)
	{
		if (models[name])
			return models[name];
		return MissingModel::Get();
	};

	Texture *ContentManager::AddTexture(string name, Texture *t)
	{
		textures[name] = t;
		return GetTexture(name);
	};

	Texture *ContentManager::GetTexture(string name)
	{
		if (textures[name])
			return textures[name];
		return blank;
	};

	Shader *ContentManager::AddShader(string name, Shader *s)
	{
		shaders[name] = s;
		return GetShader(name);
	};

	Shader *ContentManager::GetShader(string name)
	{
		if (shaders[name])
			return shaders[name];
		return NULL;
	};

}