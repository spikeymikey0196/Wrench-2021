#ifndef SKYBOX_H
#define SKYBOX_H

#include "Node.h"

namespace Wrench
{
	class SkyBox : public Node
	{
	public:
		SkyBox(Scene *nScene);
		virtual void Render();
		virtual void Render(const Matrix &matrix);
	};
}



#endif