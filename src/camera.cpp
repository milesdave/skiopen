#include "camera.h"
#include "gameobject.h"
#include "physics.h"
#include "renderer.h"

Camera::Camera() { }

Camera::~Camera() { }

void Camera::update()
{
	if(!_focus)
		return;

	Rect sprite = _focus->spritePosition();
	Vector2 pos = { sprite.x, sprite.y };
	Vector2 rel = relative(pos);

	// Outside deadzone left.
	if(rel.x < _deadzone.x)
		_geometry.x = pos.x - _deadzone.x;

	// Outside deadzone right.
	if(rel.x > _deadzone.x + _deadzone.w)
		_geometry.x = pos.x - (_deadzone.x + _deadzone.w);

	// Outside deadzone top.
	if(rel.y < _deadzone.y)
		_geometry.y = pos.y - _deadzone.y;

	// Outside deadzone bottom.
	if(rel.y > _deadzone.y + _deadzone.h)
		_geometry.y = pos.y - (_deadzone.y + _deadzone.h);
}

void Camera::setFocus(GameObject *focus)
{
	_focus = focus;

	Vector2 position = _focus->physics()->position().vector2();

	// Centre on focus' position.
	_geometry.x = position.x - (_geometry.w / 2);
	_geometry.y = position.y - (_geometry.h / 3);
}

void Camera::setGeometry(Rect geometry)
{
	_geometry = geometry;

	_deadzone.w = _geometry.w / 3;
	_deadzone.h = _geometry.h / 3;
	_deadzone.x = (_geometry.w / 2) - (_deadzone.w / 2);
	_deadzone.y = (_geometry.h / 3) - (_deadzone.h / 2);
}

bool Camera::onScreen(Rect rect) const
{
	if(rect.x + rect.w > _geometry.x && rect.x < _geometry.x + _geometry.w)
		if(rect.y + rect.h > _geometry.y && rect.y < _geometry.y + _geometry.h)
			return true;

	return false;
}

Vector2 Camera::relative(Vector2 position) const
{
	return Vector2{position.x - _geometry.x, position.y - _geometry.y};
}
