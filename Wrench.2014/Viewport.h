#ifndef VIEWPORT_H
#define VIEWPORT_H

#include "Rect.h"
#include "Matrix.h"
#include "tinyxml.h"

namespace Wrench
{
	class Viewport
	{
	protected:
		float x;
		float y;
		float width;
		float height;
		float aspectRatio;
		float minDepth;
		float maxDepth;

	public:
		Viewport();
		Viewport(float nX, float nY, float nWidth, float nHeight);
		Viewport(float nX, float nY, float nWidth, float nHeight, float nMinDepth, float nMaxDepth);
		Viewport(TiXmlElement *entry);
		void UseViewport();
		Rect Bounds();

		float Near();
		float Far();
	};
}

#endif