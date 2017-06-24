#ifndef BEHAVIOURS_BEHAVIOUR_H_
#define BEHAVIOURS_BEHAVIOUR_H_

#include "../physics.h"
#include "../renderer.h"

class Behaviour
{
	friend class GameObject;

public:
	Behaviour() { }

	virtual ~Behaviour() { }

	// Updates the behavior state.
	virtual void update() = 0;

protected:
	// Pointer to the corresponding physics component.
	Physics* _physics = nullptr;

	// Pointer to the corresponding renderer component.
	Renderer* _renderer = nullptr;
};

#endif
