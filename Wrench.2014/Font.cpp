#include "Font.h"

namespace Wrench
{
	Font::Font()
	{
		texture = NULL;
		asciiOffset = 0;
	};

	Font::Font(string filename, const Rect &LetterSize, int AsciiOffset)
	{
		Load(filename, LetterSize, AsciiOffset);
	};

	void Font::Load(string filename, const Rect &LetterSize, int AsciiOffset)
	{
		letterSize = LetterSize;
		asciiOffset = AsciiOffset;

		texture = new Texture(filename.c_str());
	};

	void Font::Render(string text, const Color4 &color, const Vector2 &location, float scale)
	{
		Rect renderLoc = letterSize;
		unsigned int currentLetter = 0;

		if (texture)
			texture->Bind();

		glPushMatrix();
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glEnable(GL_BLEND);

		glTranslatef(location.x, location.y, 0);
		glScalef(scale, scale, 1);
		glColor4f(color.r, color.g, color.b, color.a);

		glBegin(GL_QUADS);
		while (currentLetter < text.length())
		{
			if (text[currentLetter] == '\t')
			{
				int charOffset = renderLoc.x / letterSize.width;
				int addOffset = charOffset % 4;

				renderLoc.x += (4.0 - (float)addOffset) * letterSize.width;
			}
			else if (text[currentLetter] == '\n')
			{
				renderLoc.y += letterSize.height;
				renderLoc.x = 0.0;
			}
			else
			{
				Rect texCoords;

				texCoords.x = (float)((int)(text[currentLetter] - asciiOffset) % (int)(texture->Width() / letterSize.width)) * (texture->PixelWidth() * letterSize.width);
				texCoords.y = 1.0f - (float)((int)(text[currentLetter] - asciiOffset) / (int)(texture->Width() / letterSize.width) + 1.0f) * (texture->PixelHeight() * letterSize.height);
				texCoords.width = texture->PixelWidth() * letterSize.width;
				texCoords.height = texture->PixelHeight() * letterSize.height;






				glTexCoord2f(texCoords.x, texCoords.y);
				
				glVertex2f(renderLoc.x, renderLoc.y + renderLoc.height);

				glTexCoord2f(texCoords.x + texCoords.width, texCoords.y);
				glVertex2f(renderLoc.x + renderLoc.width, renderLoc.y + renderLoc.height);

				glTexCoord2f(texCoords.x + texCoords.width, texCoords.y + texCoords.height); 
				glVertex2f(renderLoc.x + renderLoc.width, renderLoc.y);

				glTexCoord2f(texCoords.x, texCoords.y + texCoords.height);
				glVertex2f(renderLoc.x, renderLoc.y);


				renderLoc.x += letterSize.width;
			}

			currentLetter++;
		}
		glEnd();
		glColor4f(1,1,1,1);

		glPopMatrix();
	};
}
