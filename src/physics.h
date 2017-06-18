#ifndef PHYSICS_H_
#define PHYSICS_H_

#include "types.h"

class Physics
{
public:
	Physics();

	~Physics();

	// Updates the position of the GameObject.
	void update();

	// Returns the position of the GameObject.
	inline Vector2F getPosition() const { return m_position; }

	// Sets the GameObject position.
	inline void setPosition(Vector2F position) { m_position = position; }

	// Returns the velocity of the GameObject.
	inline Vector2F getVelocity() const { return m_velocity; }

	// Sets the GameObject velocity.
	inline void setVelocity(Vector2F velocity) { m_velocity = velocity; }

private:
	// Position of the GameObject.
	Vector2F m_position = { 0.0f, 0.0f };

	// Velocity of the GameObject.
	Vector2F m_velocity = { 0.0f, 0.0f };
};

#endif
