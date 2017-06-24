#ifndef BEHAVIOURS_OBSTACLE_H_
#define BEHAVIOURS_OBSTACLE_H_

#include "behaviour.h"

class ObstacleBehaviour : public Behaviour
{
public:
	ObstacleBehaviour();

	~ObstacleBehaviour();

	// Updates the obstacle GameObject.
	void update() override;
};

#endif
