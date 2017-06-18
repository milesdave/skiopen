#ifndef BEHAVIOURS_PLAYER_H_
#define BEHAVIOURS_PLAYER_H_

#include "behaviour.h"

class PlayerBehaviour : public Behaviour
{
public:
	PlayerBehaviour();

	~PlayerBehaviour();

	// Updates the player GameObject.
	void update() override;
};

#endif
