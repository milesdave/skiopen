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
};

#endif
