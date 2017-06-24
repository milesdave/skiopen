#include "game.h"
#include "physics.h"

#define RAD2DEG(x) ((x / M_PI) * 180)

Physics::Physics() { }

Physics::~Physics() { }

void Physics::update()
{
	_velocity *= Game::instance()->deltaTime();
	_position += _velocity;
	_velocity -= _friction;
}

void Physics::addVelocity(Vector2F velocity)
{
	_velocity += velocity;

	// Clamp to max value if we go above.
	if(_velocity.x > _maxVelocity.x)
		_velocity.x = _maxVelocity.x;
	if(_velocity.y > _maxVelocity.y)
		_velocity.y = _maxVelocity.y;

	// Clamp to min value if we go below.
	if(_velocity.x < _minVelocity.x)
		_velocity.x = _minVelocity.x;
	if(_velocity.y < _minVelocity.y)
		_velocity.y = _minVelocity.y;
}
