#ifndef DATA_H_
#define DATA_H_

#include "sprite.h"

class Data
{
public:
	// Returns a pointer to the singleton instance.
	static Data* instance();

	// Loads all of the needed resources.
	void load();

	// Returns a pointer to the sprite specified.
	inline Sprite* sprite(int index) { return &_sprites[index]; }

private:
	Data() { }

	// Singleton instance.
	static Data* _instance;

	// Array of sprite sheets.
	SpriteSheet _sheets[1];

	// Array of sprites.
	Sprite _sprites[1];
};

/* Sheets */

#define SH_PLAYER 0
#define SH_PLAYER_FILE "data/player.bmp"

/* Sprites */

#define SPRITE_SIZE 32

#define SP_PLAYER_DOWN 0
#define SP_PLAYER_DOWN_ROW 0
#define SP_PLAYER_DOWN_FRAMES 6
#define SP_PLAYER_DOWN_DURATION 0.9f
#define SP_PLAYER_DOWN_LOOP true

#endif
