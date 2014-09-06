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
						Model *mdl = NULL;

						entry->QueryStringAttribute("Filename", &mFile);
						entry->QueryStringAttribute("Texture", &tName);

						mdl = new ModelObj(mFile.c_str(), GetTexture(tName));

						XmlLoop(entry, modelEntry)
						{
							valueStr = modelEntry->ValueStr();

							if (!valueStr.compare("Bounds"))
								mdl->SetBounds(BoundingBox(modelEntry));
						}


						AddModel(name, mdl);
					}
					else if (!valueStr.compare("Terrain"))
					{
						entry->QueryStringAttribute("Name", &name);
						string t0 = "";
						string t1 = "";
						string t2 = "";
						string t3 = "";
						string controller = "";
						string heightmap = "";

						XmlLoop(entry, tEntry)
						{
							valueStr = tEntry->ValueStr();

							if (!valueStr.compare("Terrain"))
								controller = tEntry->GetText();
							else if (!valueStr.compare("Texture"))
							{
								int id = 0;
								tEntry->QueryIntAttribute("ID", &id);

								switch (id)
								{
								case 0: t0 = tEntry->GetText(); break;
								case 1: t1 = tEntry->GetText(); break;
								case 2: t2 = tEntry->GetText(); break;
								case 3: t3 = tEntry->GetText(); break;
								default: break;
								}
							}
							else if (!valueStr.compare("Heightmap"))
							{
								heightmap = tEntry->GetText();
							}
							else {}
						}

						AddTerrain(name, new Terrain(heightmap, GetTexture(controller), GetTexture(t0), GetTexture(t1), GetTexture(t2), GetTexture(t3)));
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

	Terrain *ContentManager::AddTerrain(string name, Terrain *t)
	{
		terrain[name] = t;
		return GetTerrain(name);
	};

	Terrain *ContentManager::GetTerrain(string name)
	{
		if (terrain[name])
			return terrain[name];
		return NULL;
	};

}