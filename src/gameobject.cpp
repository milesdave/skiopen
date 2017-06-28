#include "behaviours/behaviour.h"
#include "game.h"
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

void GameObject::setBehaviour(Behaviour* behaviour)
{
	if(_behaviour)
		delete _behaviour;

	_behaviour = behaviour;

	if(_behaviour)
		_behaviour->_gameObject = this;
}

Rect GameObject::spritePosition() const
{
	Rect sprite = { 0, 0, 0, 0 };

	if(_renderer.getSprite())
	{
		Rect dimentions = _renderer.getSprite()->clips[0];
		sprite.w = dimentions.w;
		sprite.h = dimentions.h;
	}

	sprite = Game::centre(sprite, _physics.getPosition());

	return sprite;
}
