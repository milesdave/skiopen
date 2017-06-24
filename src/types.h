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

	float x;
	float y;
};

#endif
