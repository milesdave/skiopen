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

	/* Sprites */

	_sprites[SP_PLAYER_DOWN].frames = SP_PLAYER_DOWN_FRAMES;
	_sprites[SP_PLAYER_DOWN].duration = SP_PLAYER_DOWN_DURATION;
	_sprites[SP_PLAYER_DOWN].loop = SP_PLAYER_DOWN_LOOP;
	_sprites[SP_PLAYER_DOWN].sheet = &_sheets[SH_PLAYER];
	_sprites[SP_PLAYER_DOWN].generateFrames(SPRITE_SIZE, SPRITE_SIZE, SP_PLAYER_DOWN_ROW);
}

Data* Data::_instance = nullptr;
