#ifndef BEHAVIOURS_PLAYER_H_
#define BEHAVIOURS_PLAYER_H_

#include "behaviour.h"

class PlayerBehaviour : public Behaviour
{
public:
	PlayerBehaviour();

	~PlayerBehaviour() override;

	// Updates the player GameObject.
	void update() override;

private:
	// Handle user interaction.
	void handleInput();

	// Changes the sprite if neccissary.
	void updateSprite();

	// Possible states for the sprite.
	enum State
	{
		Down,
		Left1,
		Left2,
		Left3,
		Right1,
		Right2,
		Right3,
		Collision,
		Stopped
	};

	// Current sprite state.
	State _state = Down;
};

#endif
