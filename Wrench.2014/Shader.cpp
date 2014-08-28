#include "Shader.h"
#include <fstream>

using namespace std;

namespace Wrench
{
	Shader *Shader::defaultTerrain = NULL;
	Shader *Shader::defaultWater = NULL;

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

		return LoadFromStrings(vContents, fContents);
	};

	bool Shader::LoadFromStrings(const string &vContents, const string &fContents)
	{
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

	Shader *Shader::DefaultTerrain()
	{
		if (defaultTerrain == NULL)
		{
			defaultTerrain = new Shader();
			defaultTerrain->LoadFromStrings("varying vec3 coord;\
				varying float intensity;\
				void main() {\
				\
				vec3 normal, lightDir;\
				vec4 diffuse;\
				float NdotL;\
				\
				normal = normalize(gl_NormalMatrix * gl_Normal);\
				lightDir = normalize(vec3(gl_LightSource[0].position));\
				NdotL = max(dot(normal, lightDir), 0.0);\
				diffuse = gl_FrontMaterial.diffuse * gl_LightSource[0].diffuse;\
				intensity = NdotL * diffuse;\
				\
				gl_TexCoord[0] = gl_MultiTexCoord0;\
				gl_FrontColor = gl_Color;\
				gl_Position = gl_ProjectionMatrix * gl_ModelViewMatrix * gl_Vertex;\
				coord = gl_Vertex;\
			}\
			", "uniform sampler2D tex0;\
			uniform sampler2D tex1;\
			uniform sampler2D tex2;\
			uniform sampler2D tex3;\
			uniform sampler2D tex4;\
			varying vec3 coord;\
			varying float intensity;\
			void main()\
			{\
				vec4 controller = texture2D(tex0, gl_TexCoord[0].st);\
				vec4 color = texture2D(tex4, vec2(coord.x, coord.z));\
				vec4 t1 = texture2D(tex1, vec2(coord.x, coord.z));\
				vec4 t2 = texture2D(tex2, vec2(coord.x, coord.z));\
				vec4 t3 = texture2D(tex3, vec2(coord.x, coord.z));\
				color = mix(color, t1, controller.r);\
				color = mix(color, t2, controller.g);\
				color = mix(color, t3, controller.b);\
				color.a = 1.0;\
				\
				intensity = max(0.2, intensity);\
				gl_FragColor = color * vec4(intensity, intensity, intensity, 1.0);\
			}\
			");
		}

		return defaultTerrain;
	};

	Shader *Shader::DefaultWater()
	{
		if (defaultWater == NULL)
		{
			defaultWater = new Shader();
			defaultWater->LoadFromStrings("uniform float time;\
				void main() {\
				vec4 pos = gl_Vertex;\
				pos.y = pos.y + sin(time / 500 + pos.x + pos.z) * 0.25;\
				gl_TexCoord[0] = gl_MultiTexCoord0;\
				gl_FrontColor = gl_Color;\
				gl_Position = gl_ProjectionMatrix * gl_ModelViewMatrix * pos;\
			}\
			", "uniform sampler2D tex0;\
			uniform float time;\
			void main()\
			{\
				vec4 color = texture2D(tex0, gl_TexCoord[0].st + vec2(time/1000.0, time/1000.0));\
				gl_FragColor = color * vec4(0.0, 0.0, 1.0, 0.6);\
			}\
			");
		}

		return defaultWater;
	};
}