#ifndef BASICSHADER_H
#define BASICSHADER_H

#include "Shader.h"

namespace Wrench
{
	class BasicShader : public Shader
	{
	protected:
		unsigned int diffuseTex;
		unsigned int normalTex;
		unsigned int specularTex;

		static BasicShader *instance;

		BasicShader();

	public:
		static BasicShader* Get();
	};
}

#endif
