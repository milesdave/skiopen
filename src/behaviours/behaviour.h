#ifndef BEHAVIOURS_BEHAVIOUR_H_
#define BEHAVIOURS_BEHAVIOUR_H_

#include "../gameobject.h"

class Behaviour
{
	friend class GameObject;

public:
	Behaviour() { }

	virtual ~Behaviour() { }

	// Updates the behavior state.
	virtual void update() = 0;

	// Handles player input.
	virtual void handleInput() { }

	// Handles a collision event.
	virtual void collide() { }

protected:
	// Pointer to the GameObject this behaviour belongs to.
	GameObject* _gameObject = nullptr;
};

#endif
