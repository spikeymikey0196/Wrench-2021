#include "Viewport.h"
#include "GLee.h"
#include "Utils.h"
#include <string>
#include <GL/gl.h>
#include <GL/glu.h>

using namespace std;

namespace Wrench
{
	Viewport::Viewport()
	{
		x = 0.0f;
		y = 0.0f;
		width = 1.0f;
		height = 1.0f;
		aspectRatio = 1.0f;
		minDepth = 0.1f;
		maxDepth = 1.0f;
	};

	Viewport::Viewport(float nX, float nY, float nWidth, float nHeight)
	{
		x = nX;
		y = nY;
		width = nWidth;
		height = nHeight;
		aspectRatio = width / height;
		minDepth = 0.1f;
		maxDepth = 1.0f;
	};

	Viewport::Viewport(float nX, float nY, float nWidth, float nHeight, float nMinDepth, float nMaxDepth)
	{
		x = nX;
		y = nY;
		width = nWidth;
		height = nHeight;
		aspectRatio = width / height;
		minDepth = nMinDepth;
		maxDepth = nMaxDepth;
	};

	Viewport::Viewport(TiXmlElement *entry)
		: Viewport()
	{
		XmlLoop(entry, it)
		{
			string valueStr = it->ValueStr();

			if (!valueStr.compare("X")) x = stof(it->GetText());
			if (!valueStr.compare("Y")) y = stof(it->GetText());
			if (!valueStr.compare("Width")) width = stof(it->GetText());
			if (!valueStr.compare("Height")) height = stof(it->GetText());
			if (!valueStr.compare("MaxDepth")) minDepth = stof(it->GetText());
			if (!valueStr.compare("MinDepth")) maxDepth = stof(it->GetText());
		}

		aspectRatio = width / height;
	}

	void Viewport::UseViewport()
	{
		glViewport(x, y, width, height);

		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		gluPerspective(45.0, aspectRatio, minDepth, maxDepth);

		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
	};

	Rect Viewport::Bounds()
	{
		return Rect(x, y, width, height);
	};

	float Viewport::Near()
	{
		return minDepth;
	}

	float Viewport::Far()
	{
		return maxDepth;
	}
}