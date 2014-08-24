#include "Shader.h"
#include <fstream>

using namespace std;

namespace Wrench
{
	Shader::Shader()
	{
		vShader = 0;
		fShader = 0;
		program = 0;
	};

	Shader::Shader(const char *vFile, const char *fFile)
		: Shader()
	{
		Load(vFile, fFile);
	};

	Shader::Shader(TiXmlElement *entry)
	{
		string fFile = "";
		string vFile = "";

		entry->QueryStringAttribute("Vert", &vFile);
		entry->QueryStringAttribute("Frag", &fFile);

		Load(vFile.c_str(), fFile.c_str());
	};

	bool Shader::Load(const char *vFile, const char *fFile)
	{
		string vContents = "";
		string fContents = "";

		vContents = ReadFile(vFile);
		fContents = ReadFile(fFile);

		if (vContents.size() == 0 || fContents.size() == 0)
			return false;

		vShader = glCreateShader(GL_VERTEX_SHADER);
		fShader = glCreateShader(GL_FRAGMENT_SHADER);

		const char *f = fContents.c_str();
		const char *v = vContents.c_str();

		glShaderSource(vShader, 1, &v, NULL);
		glShaderSource(fShader, 1, &f, NULL);

		glCompileShader(vShader);
		glCompileShader(fShader);

		program = glCreateProgram();

		glAttachShader(program, vShader);
		glAttachShader(program, fShader);

		glLinkProgram(program);

		return true;
	};

	void Shader::Bind()
	{
		glUseProgram(program);
	};

	void Shader::Unbind()
	{
		glUseProgram(0);
	};

	GLuint Shader::GetUniform(const char *name)
	{
		return glGetUniformLocation(program, name);
	};

	string Shader::ReadFile(const char *filename)
	{
		string contents = "";
		ifstream cFile(filename);

		if (cFile.is_open())
		{
			cFile.seekg(0, std::ios::end);
			contents.resize(cFile.tellg());
			cFile.seekg(0, std::ios::beg);
			cFile.read(&contents[0], contents.size());
			cFile.close();

			return contents;
		}

		return "";
	};
}