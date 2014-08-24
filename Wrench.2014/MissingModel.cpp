#include "MissingModel.h"
#include "GLee.h"
#include <gl/GL.h>
#include <gl/GLU.h>
#include <cstring>

using namespace std;

namespace Wrench
{
	Texture *MissingModel::texture = NULL;
	MissingModel *MissingModel::instance = NULL;

	MissingModel::MissingModel()
	{
		texture = Texture::Missing();
	};

	MissingModel *MissingModel::Get()
	{
		if (instance == NULL)
			instance = new MissingModel();
		return instance;
	};

	void MissingModel::Render()
	{
		Vector3 min = Vector3(-1, -1, -1);
		Vector3 max = Vector3(1, 1, 1);

		texture->Bind();

		//temp - replace once vertex array and vbo classes in place


		glBegin(GL_QUADS);
		glTexCoord2f(0, 0);
		glVertex3f(max.x, max.y, min.z);
		glTexCoord2f(1, 0);
		glVertex3f(min.x, max.y, min.z);
		glTexCoord2f(1, 1);
		glVertex3f(min.x, max.y, max.z);
		glTexCoord2f(0, 1);
		glVertex3f(max.x, max.y, max.z);
		
		glTexCoord2f(0, 0);
		glVertex3f(max.x, min.y, max.z);
		glTexCoord2f(1, 0);
		glVertex3f(min.x, min.y, max.z);
		glTexCoord2f(1, 1);
		glVertex3f(min.x, min.y, min.z);
		glTexCoord2f(0, 1);
		glVertex3f(max.x, min.y, min.z);
		
		glTexCoord2f(0, 0);
		glVertex3f(max.x, max.y, max.z);
		glTexCoord2f(1, 0);
		glVertex3f(min.x, max.y, max.z);
		glTexCoord2f(1, 1);
		glVertex3f(min.x, min.y, max.z);
		glTexCoord2f(0, 1);
		glVertex3f(max.x, min.y, max.z);
		
		glTexCoord2f(0, 0);
		glVertex3f(max.x, min.y, min.z);
		glTexCoord2f(1, 0);
		glVertex3f(min.x, min.y, min.z);
		glTexCoord2f(1, 1);
		glVertex3f(min.x, max.y, min.z);
		glTexCoord2f(0, 1);
		glVertex3f(max.x, max.y, min.z);
		
		glTexCoord2f(0, 0);
		glVertex3f(min.x, max.y, max.z);
		glTexCoord2f(1, 0);
		glVertex3f(min.x, max.y, min.z);
		glTexCoord2f(1, 1);
		glVertex3f(min.x, min.y, min.z);
		glTexCoord2f(0, 1);
		glVertex3f(min.x, min.y, max.z);
		
		glTexCoord2f(0, 0);
		glVertex3f(max.x, max.y, min.z);
		glTexCoord2f(1, 0);
		glVertex3f(max.x, max.y, max.z);
		glTexCoord2f(1, 1);
		glVertex3f(max.x, min.y, max.z);
		glTexCoord2f(0, 1);
		glVertex3f(max.x, min.y, min.z);
		
		glEnd();
		
		texture->Unbind();
	};

	BoundingBox MissingModel::Bounds()
	{
		return BoundingBox(Vector3(-1,-1,-1), Vector3(1,1,1));
	};

	void MissingModel::ShrinkXZ(){};
}