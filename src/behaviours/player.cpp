#include "../input.h"
#include "player.h"

PlayerBehaviour::PlayerBehaviour() { }

PlayerBehaviour::~PlayerBehaviour() { }

void PlayerBehaviour::update()
{
	handleInput();
}

void PlayerBehaviour::handleInput()
{
	if(Input::input(Key::Up))
	{
		// TODO
	}
}

void PlayerBehaviour::updateSprite()
{
	// TODO
}
