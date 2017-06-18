#include "game.h"
#include "physics.h"

Physics::Physics() { }

Physics::~Physics() { }

void Physics::update()
{
	m_velocity *= Game::instance()->deltaTime();
	m_position += m_velocity;

	// TODO Friction.
	m_velocity.x = 0.0f;
	m_velocity.y = 0.0f;
}
