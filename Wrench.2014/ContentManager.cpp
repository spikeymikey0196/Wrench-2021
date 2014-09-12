#include "ContentManager.h"
#include "tinyxml.h"
#include "MissingModel.h"
#include "ModelObj.h"
#include "Utils.h"
#include "BasicMaterial.h"
#include "TerrainMaterial.h"

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
					else if (!valueStr.compare("Font"))
					{
						string fontFile = "";
						Rect letterSize = Rect();
						int asciiOffset = 0;

						entry->QueryStringAttribute("Filename", &fontFile);
						entry->QueryIntAttribute("AsciiOffset", &asciiOffset);
						entry->QueryFloatAttribute("LetterWidth", &letterSize.width);
						entry->QueryFloatAttribute("LetterHeight", &letterSize.height);

						AddFont(name, new Font(fontFile, letterSize, asciiOffset));
					}
					else if (!valueStr.compare("Terrain"))
					{
						string heightmap = "";
						Material *m = NULL;

						XmlLoop(entry, tEntry)
						{
							valueStr = tEntry->ValueStr();

							if (!valueStr.compare("Material"))
							{
								m = GetMaterial(string(tEntry->GetText()));
							}
							else if (!valueStr.compare("Heightmap"))
							{
								heightmap = tEntry->GetText();
							}
							else {}
						}

						AddTerrain(name, new Terrain(heightmap, m));
					}
					else if (!valueStr.compare("Material"))
					{
						Texture *textures[8] = { NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL };

						XmlLoop(entry, tEntry)
						{
							valueStr = tEntry->ValueStr();

							if (!valueStr.compare("Texture"))
							{
								int ID = 0;
								string n = "";

								tEntry->QueryIntAttribute("ID", &ID);
								n = tEntry->GetText();

								textures[ID] = GetTexture(n);
							}
						}

						AddMaterial(name, new Material(textures[0], textures[1], textures[2], textures[3], textures[4], textures[5], textures[6], textures[7]));
					}
					else if (!valueStr.compare("BasicMaterial"))
					{
						Texture *dTex = NULL;
						Texture *nTex = NULL;
						Texture *sTex = NULL;

						XmlLoop(entry, tEntry)
						{
							valueStr = tEntry->ValueStr();

							if (!valueStr.compare(string("Diffuse")))
								dTex = GetTexture(tEntry->GetText());
							else if (!valueStr.compare(string("Norml")))
								nTex = GetTexture(tEntry->GetText());
							else if(!valueStr.compare(string("Specular")))
								sTex = GetTexture(tEntry->GetText());
							else{}
						}

						AddMaterial(name, new BasicMaterial(dTex, nTex, sTex));
					}
					else if (!valueStr.compare("TerrainMaterial"))
					{
						Texture *controller = NULL;
						Texture *diffuse[4] = { NULL, NULL, NULL, NULL };

						XmlLoop(entry, tEntry)
						{
							valueStr = tEntry->ValueStr();

							if (!valueStr.compare("Diffuse"))
							{
								int ID = 0;
								tEntry->QueryIntAttribute("ID", &ID);

								diffuse[ID] = GetTexture(string(tEntry->GetText()));

								if (diffuse[ID])
								{
									diffuse[ID]->Bind(0);
									glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
									glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
									diffuse[ID]->Unbind(0);
								}
							}
							else if (!valueStr.compare("Controller"))
							{
								controller = GetTexture(string(tEntry->GetText()));
							}
							else{}
						}

						AddMaterial(name, new TerrainMaterial(diffuse[0], diffuse[1], diffuse[2], diffuse[3], controller));
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

	Font *ContentManager::AddFont(string name, Font *f)
	{
		fonts[name] = f;
		return GetFont(name);
	};

	Font *ContentManager::GetFont(string name)
	{
		return fonts[name];
	};

	Material *ContentManager::AddMaterial(string name, Material *m)
	{
		materials[name] = m;
		return GetMaterial(name);
	};

	Material *ContentManager::GetMaterial(string name)
	{
		return materials[name];
	};

}