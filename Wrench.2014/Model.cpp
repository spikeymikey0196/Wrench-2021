#include "Model.h"
#include "GLee.h"
#include <gl/GL.h>
#include <gl/GLU.h>

namespace Wrench
{
	Model::Model(){}

	void Model::Render(const Matrix &matrix)
	{
		glPushMatrix();
		glLoadMatrixf(((Matrix)matrix).m);
		Render();
		glPopMatrix();
	};

	void Model::SetBounds(const BoundingBox &nBounds)
	{
		bounds = nBounds;
	};

}