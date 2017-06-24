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
		add.y -= VELOCITY_MOD.y;
	if(Input::input(Key::Down))
		add.y += VELOCITY_MOD.y;
	if(Input::input(Key::Left))
		add.x -= VELOCITY_MOD.x;
	if(Input::input(Key::Right))
		add.x += VELOCITY_MOD.x;

	_physics->addVelocity(add);
}

void PlayerBehaviour::updateSprite()
{
	// TODO
}
