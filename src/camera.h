#ifndef CAMERA_H_
#define CAMERA_H_

#include "types.h"

class GameObject;

class Camera
{
public:
	Camera();

	~Camera();

	// Updates the camera position.
	void update();

	// Sets the GameObject to follow.
	void setFocus(GameObject *focus);

	// Returns the camera geometry.
	inline Rect getGeometry() const { return _geometry; }

	// Sets the camera geometry.
	void setGeometry(Rect geometry);

	// Returns true if the rectangle is on screen.
	bool onScreen(Rect rect) const;

	// Returns a new position relative to the camera.
	Vector2 relative(Vector2 position) const;

private:
	// GameObject to follow.
	GameObject *_focus = nullptr;

	// Camera position and dimentions.
	Rect _geometry = { 0, 0, 0, 0 };

	// Deadzone position and dimentions.
	Rect _deadzone = { 0, 0, 0, 0 };
};

#endif
