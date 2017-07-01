#include "goat.h"

GoatBehaviour::GoatBehaviour() { }

GoatBehaviour::~GoatBehaviour() { }

void GoatBehaviour::update()
{
	switch(_direction)
	{
		case Left:
			_gameObject->physics()->setVelocity(Vector2f { -50.0f, 0.0f });
			break;
		case Right:
			_gameObject->physics()->setVelocity(Vector2f { 50.0f, 0.0f });
			break;
	}

	checkDelete();
}
