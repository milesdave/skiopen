#ifndef BEHAVIOURS_PLAYER_H_
#define BEHAVIOURS_PLAYER_H_

#include "../data.h"
#include "../input.h"
#include "../timer.h"
#include "../types.h"
#include "behaviour.h"

class PlayerBehaviour : public Behaviour
{
public:
	PlayerBehaviour();

	~PlayerBehaviour() override;

	// Updates the player GameObject.
	void update() override;

	// Handle user interaction.
	void handleInput() override;

	// Handles a collision event.
	void collide() override;

private:
	// Handles the collions state.
	void handleCollision();

	// Changes the sprite if neccissary.
	void updateSprite();

	// Possible states for the sprite.
	enum State
	{
		Down = SP_PLAYER_DOWN,
		Left1 = SP_PLAYER_LEFT1,
		Left2 = SP_PLAYER_LEFT2,
		Left3 = SP_PLAYER_LEFT3,
		Right1 = SP_PLAYER_RIGHT1,
		Right2 = SP_PLAYER_RIGHT2,
		Right3 = SP_PLAYER_RIGHT3,
		Collision = SP_PLAYER_HIT,
		Stopped = SP_PLAYER_GROUND
	};

	// Current sprite state.
	State _state = Down;

	// After collision wait timer.
	Timer _collisionTimer;

	// The Input class instance.
	Input* _input = nullptr;

	// Vector to modify the velocity with.
	static constexpr Vector2f VELOCITY_MOD = { 4.0f, 2.5f };
	static constexpr Vector2f VELOCITY_MOD_HALF = { 1.0f, 0.75f };

	// Controller analogue stick deadzones.
	static constexpr Sint16 DEADZONE = 22000;
	static constexpr Sint16 DEADZONE_HALF = 15000;
};

#endif
