#ifndef BEHAVIOURS_OBSTACLE_H_
#define BEHAVIOURS_OBSTACLE_H_

#include "behaviour.h"

class ObstacleBehaviour : public Behaviour
{
public:
	ObstacleBehaviour();

	~ObstacleBehaviour() override;

	// Updates the obstacle GameObject.
	void update() override;

protected:
	// Checks if the GameObject should be deleted.
	void checkDelete();
};

#endif
