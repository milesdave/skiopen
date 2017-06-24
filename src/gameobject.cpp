#include "behaviours/behaviour.h"
#include "gameobject.h"
#include "sprite.h"

GameObject::GameObject() { }

GameObject::~GameObject()
{
	if(_behaviour)
		delete _behaviour;
}

void GameObject::update()
{
	if(_behaviour)
		_behaviour->update();

	_physics.update();
}

void GameObject::render()
{
	_renderer.render(_physics.getPosition());
}

void GameObject::setBehaviour(Behaviour *behaviour)
{
	if(_behaviour)
		delete _behaviour;

	_behaviour = behaviour;
	_behaviour->_physics = &_physics;
	_behaviour->_renderer = &_renderer;
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
