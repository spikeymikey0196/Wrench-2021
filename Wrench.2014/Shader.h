#ifndef SHADER_H
#define SHADER_H

#include "GLee.h"
#include <GL/GL.h>
#include <GL/glu.h>
#include <string>
#include "tinyxml.h"

using namespace std;

namespace Wrench
{
	class Shader
	{
	protected:
		GLuint vShader;
		GLuint fShader;
		GLuint program;

		string ReadFile(const char *filename);
	public:
		Shader();
		Shader(const char *vFile, const char *fFile);
		Shader(TiXmlElement *entry);
		bool Load(const char *vFile, const char *fFile);
		void Bind();
		void Unbind();
		GLuint GetUniform(const char *name);
	};
};

#endif
