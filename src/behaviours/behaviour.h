#ifndef BEHAVIOURS_BEHAVIOUR_H_
#define BEHAVIOURS_BEHAVIOUR_H_

#include "../physics.h"

class Behaviour
{
	friend class GameObject;

public:
	Behaviour() { }

	virtual ~Behaviour() { }

	// Updates the behavior state.
	virtual void update() = 0;

protected:
	// Pointer to corresponding physics component.
	Physics *_physics = nullptr;
};

#endif