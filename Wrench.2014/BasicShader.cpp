#include "BasicShader.h"
#include "BasicMaterial.h"

namespace Wrench
{
	BasicShader *BasicShader::instance = NULL;

	BasicShader::BasicShader()
	{
		if (this->Load("./Content/Shaders/Basic/v.glsl", "./Content/Shaders/Basic/f.glsl"))
		{
			this->Bind();
			diffuseTex = this->GetUniform("DiffuseTex");
			normalTex = this->GetUniform("NormalTex");
			specularTex = this->GetUniform("SpecularTex");

			glUniform1i(diffuseTex, BASICMATERIAL_DIFFUSE);
			glUniform1i(normalTex, BASICMATERIAL_NORMAL);
			glUniform1i(specularTex, BASICMATERIAL_SPECULAR);
			this->Unbind();
		}
	};

	BasicShader *BasicShader::Get()
	{
		if (!instance)
			instance = new BasicShader();
		return instance;
	};

}
