#include <SDL.h>
#include "game.h"
#include "sprite.h"

SpriteSheet::~SpriteSheet()
{
	if(texture)
		SDL_DestroyTexture(texture);
}

void SpriteSheet::load(const char *file)
{
	SDL_Surface* surface = SDL_LoadBMP(file);
	if(!surface)
		Game::instance()->panic("SDL_LoadBMP()", SDL_GetError());

	SDL_SetColorKey(surface, SDL_TRUE, SDL_MapRGB(surface->format, 0xFF, 0x00, 0xB0));

	if(texture)
		SDL_DestroyTexture(texture);

	texture = SDL_CreateTextureFromSurface(Game::instance()->renderer(), surface);
	if(!texture)
		Game::instance()->panic("SDL_CreateTextureFromSurface()", SDL_GetError());

	SDL_FreeSurface(surface);
}

Sprite::~Sprite()
{
	if(clips)
		delete[] clips;
}

void Sprite::generateFrames(int width, int height, int row)
{
	clips = new Rect[frames];

	for(int i = 0; i < frames; i++)
	{
		clips[i].x = i * width;
		clips[i].y = row * height;
		clips[i].w = width;
		clips[i].h = height;
	}
}
