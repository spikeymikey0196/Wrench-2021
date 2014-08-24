#include "Rect.h"
#include "Utils.h"
#include <cmath>
#include <algorithm>

using namespace std;

namespace Wrench
{
	Rect::Rect()
	{
		x = 0.0f;
		y = 0.0f;
		width = 0.0f;
		height = 0.0f;
	};

	Rect::Rect(const Vector2 &v, float Width, float Height)
	{
		x = v.x;
		y = v.y;
		width = Width;
		height = Height;
	};

	Rect::Rect(float X, float Y, float Width, float Height)
	{
		x = X;
		y = Y;
		width = Width;
		height = Height;
	};

	Rect::Rect(TiXmlElement *entry)
	{
		XmlLoop(entry, it)
		{
			string valueStr = it->ValueStr();

			if (!valueStr.compare("X"))
				x = stof(it->GetText());
			else if (!valueStr.compare("Y"))
				y = stof(it->GetText());
			else if (!valueStr.compare("Width"))
				width = stof(it->GetText());
			else if (!valueStr.compare("Height"))
				height = stof(it->GetText());
			else{}
		}
	};

	float Rect::Left()
	{
		return x;
	};

	float Rect::Right()
	{
		return x + width;
	};

	float Rect::Top()
	{
		return y;
	};

	float Rect::Bottom()
	{
		return y + height;
	};

	Vector2 Rect::Center()
	{
		return Vector2(x + width/2.0f, y + height/2.0f);
	};

	bool Rect::IsEmpty()
	{
		if(x == 0.0f && y == 0.0f && width == 0.0f && height == 0.0f)
			return true;
		return false;
	};

	bool Rect::Intersects(const Rect &other)
	{
		if(this->Left() > other.x + other.width) return false;
		if(this->Right() < other.x) return false;
		if(this->Top() > other.y + other.height) return false;
		if(this->Bottom() < other.y) return false;

		return true;
	};

	bool Rect::Intersects(const Rect &other, Rect &resultArea)
	{
		if(Intersects(other))
		{
			float right_side = min(this->x + this->width, other.x + other.width);
			float left_side = max(this->x, other.x);
			float top_side = max(this->y, other.y);
			float bottom_side = min(this->y + this->height, other.y + other.height);

			resultArea = Rect(left_side, top_side, right_side - left_side, bottom_side - top_side);

			return true;
		}

		return false;
	};

	bool Rect::Intersects(const Vector2 &other)
	{
		if(this->Left() > other.x) return false;
		if(this->Right() < other.x) return false;
		if(this->Top() > other.y) return false;
		if(this->Bottom() < other.y) return false;

		return true;
	};
}
