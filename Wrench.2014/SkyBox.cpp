#include "SkyBox.h"
#include "Texture.h"
#include "GLee.h"
#include <gl/GL.h>
#include <gl/GLU.h>

namespace Wrench
{
	SkyBox::SkyBox(Scene *nScene, Node *nFollowing)
		: Node(nScene)
	{
		transform.SetScale(1.0f);
		following = nFollowing;
	};

	void SkyBox::Render()
	{
		Vector3 min = Vector3(-100, -100, -100);
		Vector3 max = Vector3(100, 100, 100);

		Texture::Missing()->Bind();

		glBegin(GL_QUADS);
		glTexCoord2f(0, 0);
		glVertex3f(max.x, min.y, min.z);
		glTexCoord2f(1, 0);
		glVertex3f(min.x, min.y, min.z);
		glTexCoord2f(1, 1);
		glVertex3f(min.x, min.y, max.z);
		glTexCoord2f(0, 1);
		glVertex3f(max.x, min.y, max.z);

		glTexCoord2f(0, 0);
		glVertex3f(max.x, max.y, max.z);
		glTexCoord2f(1, 0);
		glVertex3f(min.x, max.y, max.z);
		glTexCoord2f(1, 1);
		glVertex3f(min.x, max.y, min.z);
		glTexCoord2f(0, 1);
		glVertex3f(max.x, max.y, min.z);

		glTexCoord2f(0, 0);
		glVertex3f(max.x, max.y, min.z);
		glTexCoord2f(1, 0);
		glVertex3f(min.x, max.y, min.z);
		glTexCoord2f(1, 1);
		glVertex3f(min.x, min.y, min.z);
		glTexCoord2f(0, 1);
		glVertex3f(max.x, min.y, min.z);

		glTexCoord2f(0, 0);
		glVertex3f(max.x, min.y, max.z);
		glTexCoord2f(1, 0);
		glVertex3f(min.x, min.y, max.z);
		glTexCoord2f(1, 1);
		glVertex3f(min.x, max.y, max.z);
		glTexCoord2f(0, 1);
		glVertex3f(max.x, max.y, max.z);

		glTexCoord2f(0, 0);
		glVertex3f(max.x, max.y, max.z);
		glTexCoord2f(1, 0);
		glVertex3f(max.x, max.y, min.z);
		glTexCoord2f(1, 1);
		glVertex3f(max.x, min.y, min.z);
		glTexCoord2f(0, 1);
		glVertex3f(max.x, min.y, max.z);

		glTexCoord2f(0, 0);
		glVertex3f(min.x, max.y, min.z);
		glTexCoord2f(1, 0);
		glVertex3f(min.x, max.y, max.z);
		glTexCoord2f(1, 1);
		glVertex3f(min.x, min.y, max.z);
		glTexCoord2f(0, 1);
		glVertex3f(min.x, min.y, min.z);

		glEnd();

		Texture::Missing()->Unbind();
	};

	void SkyBox::Render(const Matrix &matrix)
	{
		if (following)
			transform.SetPosition(following->GetTransform()->Position());

		glPushMatrix();
		glLoadMatrixf((transform.GetMatrix() * (Matrix)matrix).m);
		Render();
		glPopMatrix();
	};
}
