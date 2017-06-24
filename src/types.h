#ifndef TYPES_H_
#define TYPES_H_

#include <SDL_rect.h>
typedef SDL_Rect Rect, Hitbox;

struct Vector2
{
	int x;
	int y;
};

struct Vector2F
{
	void operator+=(const Vector2F& v)
	{
		x += v.x; y += v.y;
	}

	void operator-=(const Vector2F& v)
	{
		x -= v.x; y -= v.y;
	}

	void operator*=(float a)
	{
		x *= a; y *= a;
	}

	Vector2F operator*(float a)
	{
		Vector2F v;
		v.x = this->x * a;
		v.y = this->y * a;
		return v;
	}

	float x;
	float y;
};

#endif
