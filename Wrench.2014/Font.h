#ifndef FONT_H
#define FONT_H

#include "Texture.h"
#include "Rect.h"
#include "Color4.h"

#include <string>

using namespace std;

namespace Wrench
{
	class Font
	{
	protected:
		Texture *texture;
		Rect letterSize;
		int asciiOffset;

	public:
		Font();
		Font(string filename, const Rect &LetterSize, int AsciiOffset);
		~Font();
		void Load(string filename, const Rect &LetterSize, int AsciiOffset);
		void Render(string text, const Color4 &color, const Vector2 &location, float scale);
	};
}

#endif
