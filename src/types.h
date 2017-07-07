#ifndef TYPES_H_
#define TYPES_H_

#include <SDL_rect.h>
#include <SDL_stdinc.h>
typedef SDL_Rect Rect, Hitbox;

struct Vector2
{
	int x;
	int y;
};

struct Vector2f
{
	void operator+=(const Vector2f& v)
	{
		x += v.x; y += v.y;
	}

	void operator-=(const Vector2f& v)
	{
		x -= v.x; y -= v.y;
	}

	void operator*=(float a)
	{
		x *= a; y *= a;
	}

	Vector2f operator*(float a) const
	{
		Vector2f v;
		v.x = x * a;
		v.y = y * a;
		return v;
	}

	bool operator==(const Vector2f& v) const
	{
		if(x == v.x && y == v.y)
			return true;
		return false;
	}

	Vector2 vector2() const
	{
		return Vector2{(int)x, (int)y};
	}

	static constexpr Vector2f zero()
	{
		return Vector2f{0.0f, 0.0f};
	}

	float x;
	float y;
};

struct Colour
{
	Uint8 r;
	Uint8 g;
	Uint8 b;
	Uint8 a;
};

#endif
