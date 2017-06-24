#include "game.h"
#include "physics.h"

#define RAD2DEG(x) ((x / M_PI) * 180)

Physics::Physics() { }

Physics::~Physics() { }

void Physics::update()
{
	_velocity *= Game::instance()->deltaTime();
	_position += _velocity;

	// TODO Decay velocity.
}

void Physics::addVelocity(Vector2F velocity)
{
	// TODO
}
