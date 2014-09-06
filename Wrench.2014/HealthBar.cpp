#include "HealthBar.h"
#include "GLee.h"
#include <GL/gl.h>
#include <GL/glu.h>

HealthBar::HealthBar(UIElement *nParent, const Rect &nBounds, Range<int> *nTarget)
	: UIElement(nParent, nBounds, NULL, Rect(), [](UIElement*e, int x, int y){})
{
	target = nTarget;
};

void HealthBar::Render()
{
	float scaleFactor = bounds.width / (float)target->Max();

	glColor3f(0.5f, 0.5f, 0.5f);
	glBegin(GL_TRIANGLES);
		glVertex2f(bounds.Left(), bounds.Top());
		glVertex2f(bounds.Right(), bounds.Bottom());
		glVertex2f(bounds.Right(), bounds.Top());
	
		glVertex2f(bounds.Left(), bounds.Top());
		glVertex2f(bounds.Left(), bounds.Bottom());
		glVertex2f(bounds.Right(), bounds.Bottom());
	glEnd();

	glColor3f(0.0f,1.0f,0.0f);
	glBegin(GL_TRIANGLES);
		glVertex2f(bounds.Left(), bounds.Top());
		glVertex2f(bounds.Left() + target->Value() * scaleFactor, bounds.Bottom());
		glVertex2f(bounds.Left() + target->Value() * scaleFactor, bounds.Top());

		glVertex2f(bounds.Left(), bounds.Top());
		glVertex2f(bounds.Left(), bounds.Bottom());
		glVertex2f(bounds.Left() + target->Value() * scaleFactor, bounds.Bottom());
	glEnd();

	glColor3f(1, 1, 1);
};
