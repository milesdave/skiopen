#ifndef BEHAVIOURS_GOAT_H_
#define BEHAVIOURS_GOAT_H_

#include "obstacle.h"

class GoatBehaviour : public ObstacleBehaviour
{
public:
	GoatBehaviour();

	~GoatBehaviour() override;

	// Updates the goat GameObject.
	void update() override;

	// Possible directions for the goat to move.
	enum Direction
	{
		Left = 0,
		Right = 1
	};

	// Sets the direction of the goat to move.
	inline void setDirection(Direction direction) { _direction = direction; }

private:
	// Direction of the goat to move.
	Direction _direction;
};

#endif
