#ifndef MISSINGMODEL_H
#define MISSINGMODEL_H

#include "Model.h"
#include "Texture.h"

namespace Wrench
{
	class MissingModel : public Model
	{
	protected:
		//static vars
		static Texture *texture;
		static MissingModel *instance;

		MissingModel();

	public:
		static MissingModel *Get();
		virtual void Render();
		virtual BoundingBox Bounds();
		virtual void ShrinkXZ();
	};
}

#endif