#ifndef MODEL_H
#define MODEL_H

#include "BoundingBox.h"
#include "Matrix.h"

namespace Wrench
{
	class Model
	{
	protected:
		BoundingBox bounds;

	public:
		Model();
		
		virtual void Render() = 0;
		virtual void Render(const Matrix &matrix);
		virtual BoundingBox Bounds() = 0;
		virtual void SetBounds(const BoundingBox &nBounds);
	};
}

#endif
