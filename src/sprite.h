#ifndef SPRITE_H_
#define SPRITE_H_

#include "types.h"

struct SDL_Texture;

struct SpriteSheet
{
	~SpriteSheet();

	// Loads a sprite sheet file.
	void load(const char *file);

	// The sprite sheet texture.
	SDL_Texture* texture = nullptr;
};

struct Sprite
{
	~Sprite();

	// Generates the sprite's animation frames.
	void generateFrames(int width, int height, int row);

	// The number of frames for the animation.
	int frames = 1;

	// The duration of the animation (seconds).
	float duration = 0.0f;

	// Whether or not the animation loops.
	bool loop = true;

	// Animation frame clips.
	Rect* clips = nullptr;

	// The sprite sheet.
	SpriteSheet* sheet = nullptr;
};

#endif
