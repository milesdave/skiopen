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
	inline Vector2F getPosition() const { return _position; }

	// Sets the GameObject position.
	inline void setPosition(Vector2F position) { _position = position; }

	// Returns the velocity of the GameObject.
	inline Vector2F getVelocity() const { return _velocity; }

	// Sets the GameObject velocity.
	inline void setVelocity(Vector2F velocity) { _velocity = velocity; calculateAngle(); }

	// Adds the specified velocity to the GameObject.
	void addVelocity(Vector2F velocity);

	// Sets the maximum velocity of the GameObject.
	inline void setMaxVelocity(Vector2F maxVelocity) { _maxVelocity = maxVelocity; }

	// Sets the minimum velocity of the GameObject.
	inline void setMinVelocity(Vector2F minVelocity) { _minVelocity = minVelocity; }

	// Sets the friction for the GameObject.
	inline void setFriction(Vector2F friction) { _friction = friction; }

	// Returns the angle of the GameObject.
	inline float getAngle() const { return _angle; }

	// Sets the angle of the GameObject.
	inline void setAngle(float angle) { _angle = angle; }

private:
	// Applies friction to the GameObject.
	void applyFriction();

	// Calculates the angle based on the velocity,
	void calculateAngle();

	// Position of the GameObject.
	Vector2F _position = { 0.0f, 0.0f };

	// Velocity of the GameObject.
	Vector2F _velocity = { 0.0f, 0.0f };

	// Maximum velocity of the GameObject.
	Vector2F _maxVelocity = { 0.0f, 0.0f };

	// Maximum negative velocity of the GameObject.
	Vector2F _minVelocity = { 0.0f, 0.0f };

	// Friction for the GameObject.
	Vector2F _friction = { 1.0f, 1.0f };

	// Angle of the GameObject.
	float _angle = 0.0f;
};

#endif
