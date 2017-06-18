#include "../input.h"
#include "player.h"

// TODO TMP
#include <cstdio>

PlayerBehaviour::PlayerBehaviour() { }

PlayerBehaviour::~PlayerBehaviour() { }

void PlayerBehaviour::update()
{
	if(Input::input(Up))
		printf("up\n");
}
