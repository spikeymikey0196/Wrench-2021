#include "RenderTarget.h"

namespace Wrench
{
	RenderTarget::RenderTarget(int w, int h)
	{
		t = NULL;
		width = w;
		height = h;

		glGenFramebuffersEXT(1, &fbID);
		glGenTextures(1, &colorID);
		glGenRenderbuffersEXT(1, &depthID);

		glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, fbID);

		glBindTexture(GL_TEXTURE_2D, colorID);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0,GL_RGBA, GL_INT, NULL);
		glFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT,GL_COLOR_ATTACHMENT0_EXT,GL_TEXTURE_2D, colorID, 0);

		glBindRenderbufferEXT(GL_RENDERBUFFER_EXT, depthID);
		glRenderbufferStorageEXT(GL_RENDERBUFFER_EXT,GL_DEPTH_COMPONENT24, width, height);
		glFramebufferRenderbufferEXT(GL_FRAMEBUFFER_EXT,GL_DEPTH_ATTACHMENT_EXT,GL_RENDERBUFFER_EXT, depthID);

		Unbind();

		t = new Texture(colorID, w, h);
	};

	void RenderTarget::Bind()
	{
		glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, fbID);
	};

	void RenderTarget::Unbind()
	{
		glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, 0);
	};

	Texture *RenderTarget::GetTexture()
	{
		return t;
	}
};
