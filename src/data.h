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

	// Returns a pointer to the SpriteSheet specified.
	inline SpriteSheet* sheet(int index) { return &_sheets[index]; }

private:
	Data() { }

	// Singleton instance.
	static Data* _instance;

	// Array of sprite sheets.
	SpriteSheet _sheets[6];

	// Array of sprites.
	Sprite _sprites[19];
};

/* Sheets */

#define SH_PLAYER 0
#define SH_PLAYER_FILE "data/player.bmp"

#define SH_GOAT 1
#define SH_GOAT_FILE "data/goat.bmp"

#define SH_OBSTACLES 2
#define SH_OBSTACLES_FILE "data/obstacles.bmp"

#define SH_SIGNS 3
#define SH_SIGNS_FILE "data/signs.bmp"

#define SH_ANIM_SIGN 4
#define SH_ANIM_SIGN_FILE "data/sign-animated.bmp"

#define SH_FONT 5
#define SH_FONT_FILE "data/font.bmp"

/* Player Sprites */

#define SPRITE_SIZE 32
#define PLAYER_FRAMES 6
#define PLAYER_DURATION 0.9f
#define PLAYER_LOOP true

#define SP_PLAYER_DOWN 0
#define SP_PLAYER_LEFT1 1
#define SP_PLAYER_LEFT2 2
#define SP_PLAYER_LEFT3 3
#define SP_PLAYER_RIGHT1 4
#define SP_PLAYER_RIGHT2 5
#define SP_PLAYER_RIGHT3 6

#define SP_PLAYER_HIT 7
#define SP_PLAYER_HIT_FRAMES 1

#define SP_PLAYER_GROUND 8
#define SP_PLAYER_GROUND_FRAMES 1

/* Obstacle Sprites */

#define OBSTACLE_FRAMES 1

#define SP_OBSTACLE1 9
#define SP_OBSTACLE1_ROW 0

#define SP_OBSTACLE2 10
#define SP_OBSTACLE2_ROW 1

#define SP_OBSTACLE3 11
#define SP_OBSTACLE3_ROW 2

#define SP_OBSTACLE4 12
#define SP_OBSTACLE4_ROW 3

/* Goat Sprites */

#define SP_GOAT_LEFT 13
#define SP_GOAT_LEFT_ROW 0
#define SP_GOAT_LEFT_FRAMES 7
#define SP_GOAT_LEFT_DURATION 1.5f
#define SP_GOAT_LEFT_LOOP true

#define SP_GOAT_RIGHT 14
#define SP_GOAT_RIGHT_ROW 1
#define SP_GOAT_RIGHT_FRAMES 7
#define SP_GOAT_RIGHT_DURATION 1.5f
#define SP_GOAT_RIGHT_LOOP true

/* Sign Sprites */

#define SIGN_WIDTH 100
#define SIGN_HEIGHT 64
#define SIGN_FRAMES 1

#define SP_SIGN1 15
#define SP_SIGN1_ROW 0

#define SP_SIGN2 16
#define SP_SIGN2_ROW 1

#define SP_SIGN3 17
#define SP_SIGN3_ROW 2

#define SP_SIGN4 18
#define SP_SIGN4_ROW 0
#define SP_SIGN4_FRAMES 30
#define SP_SIGN4_DURATION 9.0f
#define SP_SIGN4_LOOP true

#endif
