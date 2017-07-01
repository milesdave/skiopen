#include "../input.h"
#include "player.h"

PlayerBehaviour::PlayerBehaviour() { }

PlayerBehaviour::~PlayerBehaviour() { }

void PlayerBehaviour::update()
{
	if(_state == Collision || _state == Stopped)
	{
		handleCollision();
	}
	else
	{
		handleInput();
		updateSprite();
	}
}

void PlayerBehaviour::collide()
{
	// We're already in the collision state.
	if(_state == Collision)
	{
		return;
	}
	// We're stuck in the same/another object.
	else if(_state == Stopped)
	{
		_gameObject->physics()->addVelocity(Vector2f { 0.0f, 200.0f });
		_collisionTimer.stop();
	}

	_state = Collision;
	_gameObject->physics()->setFriction(Vector2f { 5.0f, 5.0f });
	_gameObject->renderer()->setSprite(
		Data::instance()->sprite((int)_state));
}

void PlayerBehaviour::handleInput()
{
	Vector2f add = { 0.0f, 0.0f };

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

void PlayerBehaviour::handleCollision()
{
	Vector2f velocity = _gameObject->physics()->velocity();

	// Player has stopped moving.
	if(velocity == Vector2f::zero())
	{
		// Start the timer and set the state.
		if(!_collisionTimer.started())
		{
			_collisionTimer.start();

			_state = Stopped;
			_gameObject->renderer()->setSprite(
				Data::instance()->sprite((int)_state));
		}
		// Reset the player.
		else if(_collisionTimer.started()
			&& _collisionTimer.milliseconds() > 500)
		{
			_collisionTimer.stop();

			_state = Down;
			_gameObject->physics()->setFriction(Vector2f { 1.0f, 0.5f });
		}
	}
}

void PlayerBehaviour::updateSprite()
{
	float angle = _gameObject->physics()->angle();
	Vector2f velocity = _gameObject->physics()->velocity();

	switch(_state)
	{
	case Down:
		if(velocity == Vector2f::zero())
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
	case Collision:
		break;
	}

	_gameObject->renderer()->setSprite(Data::instance()->sprite((int)_state));
}
