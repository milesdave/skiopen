#include "../input.h"
#include "player.h"

#include <cstdio> // TODO

PlayerBehaviour::PlayerBehaviour() { }

PlayerBehaviour::~PlayerBehaviour() { }

void PlayerBehaviour::update()
{
	handleInput();
	updateSprite();
}

void PlayerBehaviour::collide()
{
	printf("Ouch!\n");
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

	_gameObject->physics()->addVelocity(add);
}

void PlayerBehaviour::updateSprite()
{
	float angle = _gameObject->physics()->getAngle();
	Vector2F velocity = _gameObject->physics()->getVelocity();

	switch(_state)
	{
	case Down:
		if(velocity.x == 0.0f && velocity.y == 0.0f)
			return;
		if(angle < 85.0f)
			_state = Right1;
		else if(angle > 95.0f)
			_state = Left1;
		break;
	case Left1:
		if(angle < 95.0f)
			_state = Down;
		else if(angle > 130.0f)
			_state = Left2;
		break;
	case Left2:
		if(angle < 130.0f)
			_state = Left1;
		else if(angle > 150.0f)
			_state = Left3;
		break;
	case Left3:
		if(angle < 150.0f)
			_state = Left2;
		break;
	case Right1:
		if(angle > 85.0f)
			_state = Down;
		else if(angle < 50.0f)
			_state = Right2;
		break;
	case Right2:
		if(angle > 50.0f)
			_state = Right1;
		else if(angle < 30.0f)
			_state = Right3;
		break;
	case Right3:
		if(angle > 30.0f)
			_state = Right2;
		else if(velocity.x == 0.0f)
			_state = Down;
		break;
	case Stopped:
		if(velocity.x != 0.0f || velocity.y != 0.0f)
			_state = Down;
		break;
	}

	_gameObject->renderer()->setSprite(Data::instance()->sprite((int)_state));
}
