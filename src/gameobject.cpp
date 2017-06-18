#include "behaviours/behaviour.h"
#include "gameobject.h"
#include "sprite.h"

GameObject::GameObject() { }

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

Rect GameObject::spritePosition() const
{
	Rect sprite = { 0, 0, 0, 0 };

	Vector2F position = _physics.getPosition();
	sprite.x = (int)position.x;
	sprite.y = (int)position.y;

	if(_renderer.getSprite())
	{
		Rect dimentions = _renderer.getSprite()->clips[0];
		sprite.w = dimentions.w;
		sprite.h = dimentions.h;
	}

	return sprite;
}
