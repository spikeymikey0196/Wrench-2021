#ifndef MODELPMD_H
#define MODELPMD_H

#include "Model.h"
#include "Vertex.h"
#include "VertexArray.h"

namespace Wrench
{
	class ModelPMD : public Model
	{
	protected:
		unsigned int vboID;
		unsigned int indexVBOID;
		int numFaces;

		VertexArray vertexArray;

	public:
		ModelPMD(const char *filename);

		bool Load(const char *filename);
		virtual void Render();
		virtual BoundingBox Bounds();
	};
}


#endif
