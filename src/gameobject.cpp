#include "behaviours/behaviour.h"
#include "gameobject.h"
#include "sprite.h"

GameObject::~GameObject()
{
	if(_behavior)
		delete _behavior;
}

void GameObject::update()
{
	if(_behavior)
		_behavior->update();

	_physics.update();
}

void GameObject::render()
{
	_renderer.render(_physics.getPosition());
}

void GameObject::setBehavior(Behavior *behavior)
{
	if(_behavior)
		delete _behavior;

	_behavior = behavior;
	_behavior->_physics = &_physics;
}
