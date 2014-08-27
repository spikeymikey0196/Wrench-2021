#include "Light.h"
#include "GLee.h"
#include "Utils.h"
#include <gl/GL.h>
#include <gl/GLU.h>
#include <string>

using namespace std;

namespace Wrench
{
	Light::Light()
	{
		lightNum = 0;
		position = Vector4(0, 0, 0, 1);
		ambient = Color4(0.5, 0.5, 0.5, 1);
		specular = Color4(1, 1, 1, 1);
		diffuse = Color4(1, 1, 1, 1);
	};

	Light::Light(int nLightNum)
		: Light()
	{
		lightNum = nLightNum;
	};

	Light::Light(int nLightNum, Vector3 nPosition, Color4 nAmbient, Color4 nSpecular, Color4 nDiffuse)
	{
		lightNum = nLightNum;
		position = Vector4(nPosition, 0);
		ambient = nAmbient;
		specular = nSpecular;
		diffuse = nDiffuse;
	};

	Light::Light(TiXmlElement *entry)
	{
		XmlLoop(entry, it)
		{
			string valueStr = it->ValueStr();

			if (!valueStr.compare("Position"))
				position = Vector4(Vector3(it), 1.0f);
			else if (!valueStr.compare("Ambient"))
				ambient = Color4(it);
			else if (!valueStr.compare("Specular"))
				specular = Color4(it);
			else if (!valueStr.compare("Diffuse"))
				diffuse = Color4(it);
			else if (!valueStr.compare("LightID"))
				lightNum = stoi(it->GetText());
			else {}
		}
	};

	void Light::Enable()
	{
		glEnable(GL_LIGHTING);
		glEnable(GL_LIGHT0 + lightNum);
		glEnable(GL_COLOR_MATERIAL);

		glLightfv(GL_LIGHT0 + lightNum, GL_AMBIENT, ambient.color);
		glLightfv(GL_LIGHT0 + lightNum, GL_DIFFUSE, diffuse.color);
		glLightfv(GL_LIGHT0 + lightNum, GL_SPECULAR, specular.color);
		glLightfv(GL_LIGHT0 + lightNum, GL_POSITION, position.pos);
	};

	void Light::Disable()
	{
		glDisable(GL_LIGHT0 + lightNum);
	};

	void Light::Render(const Matrix &matrix)
	{
		glBindTexture(GL_TEXTURE_2D, 0);
		glColor3f(diffuse.r, diffuse.g, diffuse.b);
		glPointSize(8.0f);

		glPushMatrix();
			glLoadMatrixf(((Matrix)matrix).m);
			glBegin(GL_POINTS);
				glVertex3f(position.x, position.y, position.z);
			glEnd();
		glPopMatrix();

		glPointSize(1.0f);
		glColor4f(1, 1, 1, 1);
	};
}
