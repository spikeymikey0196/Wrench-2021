#ifndef MODELOBJ_H
#define MODELOBJ_H

#include "Model.h"
#include "BoundingBox.h"
#include "Texture.h"
#include "Vertex.h"
#include "tinyxml.h"

namespace Wrench
{
	class ModelObj : public Model
	{
	protected:
		Texture *texture;
		unsigned int vboID;
		unsigned int indexVBOID;
		int numFaces;

	public:
		ModelObj();
		ModelObj(const char *filename);
		ModelObj(const char *filename, Texture *t);

		bool Load(const char *filename);
		virtual void Render();
		virtual BoundingBox Bounds();
	};
}

#endif