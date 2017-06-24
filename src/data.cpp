#include "data.h"

Data* Data::instance()
{
	if(!_instance)
		_instance = new Data();

	return _instance;
}

void Data::load()
{
	/* Sheets */

	_sheets[SH_PLAYER].load(SH_PLAYER_FILE);
	_sheets[SH_GOAT].load(SH_GOAT_FILE);
	_sheets[SH_OBSTACLES].load(SH_OBSTACLES_FILE);
	_sheets[SH_SIGNS].load(SH_SIGNS_FILE);
	_sheets[SH_ANIM_SIGN].load(SH_ANIM_SIGN_FILE);
	_sheets[SH_FONT].load(SH_FONT_FILE);

	/* Player Sprites */

	_sprites[SP_PLAYER_DOWN].frames = PLAYER_FRAMES;
	_sprites[SP_PLAYER_DOWN].duration = PLAYER_DURATION;
	_sprites[SP_PLAYER_DOWN].loop = PLAYER_LOOP;
	_sprites[SP_PLAYER_DOWN].sheet = &_sheets[SH_PLAYER];
	_sprites[SP_PLAYER_DOWN].generateFrames(SPRITE_SIZE, SPRITE_SIZE,
		SP_PLAYER_DOWN);

	_sprites[SP_PLAYER_LEFT1].frames = PLAYER_FRAMES;
	_sprites[SP_PLAYER_LEFT1].duration = PLAYER_DURATION;
	_sprites[SP_PLAYER_LEFT1].loop = PLAYER_LOOP;
	_sprites[SP_PLAYER_LEFT1].sheet = &_sheets[SH_PLAYER];
	_sprites[SP_PLAYER_LEFT1].generateFrames(SPRITE_SIZE, SPRITE_SIZE,
		SP_PLAYER_LEFT1);

	_sprites[SP_PLAYER_LEFT2].frames = PLAYER_FRAMES;
	_sprites[SP_PLAYER_LEFT2].duration = PLAYER_DURATION;
	_sprites[SP_PLAYER_LEFT2].loop = PLAYER_LOOP;
	_sprites[SP_PLAYER_LEFT2].sheet = &_sheets[SH_PLAYER];
	_sprites[SP_PLAYER_LEFT2].generateFrames(SPRITE_SIZE, SPRITE_SIZE,
		SP_PLAYER_LEFT2);

	_sprites[SP_PLAYER_LEFT3].frames = PLAYER_FRAMES;
	_sprites[SP_PLAYER_LEFT3].duration = PLAYER_DURATION;
	_sprites[SP_PLAYER_LEFT3].loop = PLAYER_LOOP;
	_sprites[SP_PLAYER_LEFT3].sheet = &_sheets[SH_PLAYER];
	_sprites[SP_PLAYER_LEFT3].generateFrames(SPRITE_SIZE, SPRITE_SIZE,
		SP_PLAYER_LEFT3);

	_sprites[SP_PLAYER_RIGHT1].frames = PLAYER_FRAMES;
	_sprites[SP_PLAYER_RIGHT1].duration = PLAYER_DURATION;
	_sprites[SP_PLAYER_RIGHT1].loop = PLAYER_LOOP;
	_sprites[SP_PLAYER_RIGHT1].sheet = &_sheets[SH_PLAYER];
	_sprites[SP_PLAYER_RIGHT1].generateFrames(SPRITE_SIZE, SPRITE_SIZE,
		SP_PLAYER_RIGHT1);

	_sprites[SP_PLAYER_RIGHT2].frames = PLAYER_FRAMES;
	_sprites[SP_PLAYER_RIGHT2].duration = PLAYER_DURATION;
	_sprites[SP_PLAYER_RIGHT2].loop = PLAYER_LOOP;
	_sprites[SP_PLAYER_RIGHT2].sheet = &_sheets[SH_PLAYER];
	_sprites[SP_PLAYER_RIGHT2].generateFrames(SPRITE_SIZE, SPRITE_SIZE,
		SP_PLAYER_RIGHT2);

	_sprites[SP_PLAYER_RIGHT3].frames = PLAYER_FRAMES;
	_sprites[SP_PLAYER_RIGHT3].duration = PLAYER_DURATION;
	_sprites[SP_PLAYER_RIGHT3].loop = PLAYER_LOOP;
	_sprites[SP_PLAYER_RIGHT3].sheet = &_sheets[SH_PLAYER];
	_sprites[SP_PLAYER_RIGHT3].generateFrames(SPRITE_SIZE, SPRITE_SIZE,
		SP_PLAYER_RIGHT3);

	_sprites[SP_PLAYER_HIT].frames = SP_PLAYER_HIT_FRAMES;
	_sprites[SP_PLAYER_HIT].sheet = &_sheets[SH_PLAYER];
	_sprites[SP_PLAYER_HIT].generateFrames(SPRITE_SIZE, SPRITE_SIZE,
		SP_PLAYER_HIT);

	_sprites[SP_PLAYER_GROUND].frames = SP_PLAYER_GROUND_FRAMES;
	_sprites[SP_PLAYER_GROUND].sheet = &_sheets[SH_PLAYER];
	_sprites[SP_PLAYER_GROUND].generateFrames(SPRITE_SIZE, SPRITE_SIZE,
		SP_PLAYER_GROUND);

	/* Obstacle Sprites */

	_sprites[SP_OBSTACLE1].frames = OBSTACLE_FRAMES;
	_sprites[SP_OBSTACLE1].sheet = &_sheets[SH_OBSTACLES];
	_sprites[SP_OBSTACLE1].generateFrames(SPRITE_SIZE, SPRITE_SIZE,
		SP_OBSTACLE1_ROW);

	_sprites[SP_OBSTACLE2].frames = OBSTACLE_FRAMES;
	_sprites[SP_OBSTACLE2].sheet = &_sheets[SH_OBSTACLES];
	_sprites[SP_OBSTACLE2].generateFrames(SPRITE_SIZE, SPRITE_SIZE,
		SP_OBSTACLE2_ROW);

	_sprites[SP_OBSTACLE3].frames = OBSTACLE_FRAMES;
	_sprites[SP_OBSTACLE3].sheet = &_sheets[SH_OBSTACLES];
	_sprites[SP_OBSTACLE3].generateFrames(SPRITE_SIZE, SPRITE_SIZE,
		SP_OBSTACLE3_ROW);

	_sprites[SP_OBSTACLE4].frames = OBSTACLE_FRAMES;
	_sprites[SP_OBSTACLE4].sheet = &_sheets[SH_OBSTACLES];
	_sprites[SP_OBSTACLE4].generateFrames(SPRITE_SIZE, SPRITE_SIZE,
		SP_OBSTACLE4_ROW);

	/* Goat Sprites */

	_sprites[SP_GOAT_LEFT].frames = SP_GOAT_LEFT_FRAMES;
	_sprites[SP_GOAT_LEFT].duration = SP_GOAT_LEFT_DURATION;
	_sprites[SP_GOAT_LEFT].loop = SP_GOAT_LEFT_LOOP;
	_sprites[SP_GOAT_LEFT].sheet = &_sheets[SH_GOAT];
	_sprites[SP_GOAT_LEFT].generateFrames(SPRITE_SIZE, SPRITE_SIZE,
		SP_GOAT_LEFT_ROW);

	_sprites[SP_GOAT_RIGHT].frames = SP_GOAT_RIGHT_FRAMES;
	_sprites[SP_GOAT_RIGHT].duration = SP_GOAT_RIGHT_DURATION;
	_sprites[SP_GOAT_RIGHT].loop = SP_GOAT_RIGHT_LOOP;
	_sprites[SP_GOAT_RIGHT].sheet = &_sheets[SH_GOAT];
	_sprites[SP_GOAT_RIGHT].generateFrames(SPRITE_SIZE, SPRITE_SIZE,
		SP_GOAT_RIGHT_ROW);

	/* Sign Sprites */

	_sprites[SP_SIGN1].frames = SIGN_FRAMES;
	_sprites[SP_SIGN1].sheet = &_sheets[SH_SIGNS];
	_sprites[SP_SIGN1].generateFrames(SIGN_WIDTH, SIGN_HEIGHT, SP_SIGN1_ROW);

	_sprites[SP_SIGN2].frames = SIGN_FRAMES;
	_sprites[SP_SIGN2].sheet = &_sheets[SH_SIGNS];
	_sprites[SP_SIGN2].generateFrames(SIGN_WIDTH, SIGN_HEIGHT, SP_SIGN2_ROW);

	_sprites[SP_SIGN3].frames = SIGN_FRAMES;
	_sprites[SP_SIGN3].sheet = &_sheets[SH_SIGNS];
	_sprites[SP_SIGN3].generateFrames(SIGN_WIDTH, SIGN_HEIGHT, SP_SIGN3_ROW);

	_sprites[SP_SIGN4].frames = SP_SIGN4_FRAMES;
	_sprites[SP_SIGN4].duration = SP_SIGN4_DURATION;
	_sprites[SP_SIGN4].loop = SP_SIGN4_LOOP;
	_sprites[SP_SIGN4].sheet = &_sheets[SH_ANIM_SIGN];
	_sprites[SP_SIGN4].generateFrames(SIGN_WIDTH, SIGN_HEIGHT, SP_SIGN4_ROW);
}

Data* Data::_instance = nullptr;
