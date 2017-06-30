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
		v.x = x * a;
		v.y = y * a;
		return v;
	}

	bool operator==(const Vector2F& v)
	{
		if(x == v.x && y == v.y)
			return true;
		return false;
	}

	static constexpr Vector2F zero()
	{
		return Vector2F { 0.0f, 0.0f };
	}

	float x;
	float y;
};

#endif
