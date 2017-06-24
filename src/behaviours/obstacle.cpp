#include "../camera.h"
#include "../game.h"
#include "obstacle.h"

ObstacleBehaviour::ObstacleBehaviour() { }

ObstacleBehaviour::~ObstacleBehaviour() { }

void ObstacleBehaviour::update()
{
	Rect geometry = _gameObject->spritePosition();

	// Delete if we're above the camera.
	if(geometry.y + geometry.h < Game::instance()->camera()->getGeometry().y)
		_gameObject->setDeleteFlag(true);
}
