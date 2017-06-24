#include "../input.h"
#include "player.h"

PlayerBehaviour::PlayerBehaviour() { }

PlayerBehaviour::~PlayerBehaviour() { }

void PlayerBehaviour::update()
{
	handleInput();
	updateSprite();
}

void PlayerBehaviour::handleInput()
{
	Vector2F add = { 0.0f, 0.0f };

	if(Input::input(Key::Up))
		add.y -= _velocityMod.y;
	if(Input::input(Key::Down))
		add.y += _velocityMod.y;
	if(Input::input(Key::Left))
		add.x -= _velocityMod.x;
	if(Input::input(Key::Right))
		add.x += _velocityMod.x;

	_physics->addVelocity(add);
}

void PlayerBehaviour::updateSprite()
{
	// TODO
}
