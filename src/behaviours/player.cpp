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

	if(Input::input(Down))
		printf("down\n");

	if(Input::input(Left))
		printf("left\n");

	if(Input::input(Right))
		printf("right\n");

	if(Input::input(Pause))
		printf("pause\n");

	if(Input::input(Reset))
		printf("reset\n");
}
