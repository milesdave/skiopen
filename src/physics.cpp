#include <cmath>
#include "game.h"
#include "physics.h"

#define RAD2DEG(x) ((x / M_PI) * 180)

Physics::Physics() { }

Physics::~Physics() { }

void Physics::update()
{
	_position += (_velocity * Game::instance()->deltaTime());
	applyFriction();
	calculateAngle();
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

	calculateAngle();
}

void Physics::applyFriction()
{
	// Move X towards 0.
	if(_velocity.x > 0.0f)
		_velocity.x -= _friction.x;
	else if(_velocity.x < 0.0f)
		_velocity.x += _friction.x;

	// Move Y towards 0.
	if(_velocity.y > 0.0f)
		_velocity.y -= _friction.y;
	else if(_velocity.y < 0.0f)
		_velocity.y += _friction.y;
}

void Physics::calculateAngle()
{
	_angle = (float)RAD2DEG(atan2(_velocity.y, _velocity.x));
}

Hitbox Physics::getHitbox()
{
	return Game::centre(_hitbox, _position);
}
