#ifndef LIGHT_H
#define LIGHT_H

#include "Color4.h"
#include "Vector4.h"
#include "Matrix.h"
#include "tinyxml.h"

namespace Wrench
{
	class Light
	{
	protected:
		int lightNum;
		Vector4 position;
		Color4 ambient;
		Color4 specular;
		Color4 diffuse;

	public:
		Light();
		Light(int nLightNum);
		Light(int nLightNum, Vector3 nPosition, Color4 nAmbient, Color4 nSpecular, Color4 nDiffuse);
		Light(TiXmlElement *entry);

		void Enable();
		void Disable();
		void Render(const Matrix &matrix);
	};
}

#endif
