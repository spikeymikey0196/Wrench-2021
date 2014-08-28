#ifndef SKYBOX_H
#define SKYBOX_H

#include "Node.h"

namespace Wrench
{
	class SkyBox : public Node
	{
	protected:
		Node *following;

	public:
		SkyBox(Scene *nScene, Node *nFollowing);
		virtual void Render();
		virtual void Render(const Matrix &matrix);
	};
}



#endif