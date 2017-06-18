#ifndef GAMEOBJECT_H_
#define GAMEOBJECT_H_

#include "physics.h"
#include "renderer.h"

class Behavior;

class GameObject
{
public:
	GameObject();

	~GameObject();

	// Updates the GameObject state.
	void update();

	// Renders the GameObject.
	void render();

	// Returns a pointer to the renderer component.
	inline Renderer* renderer() { return &_renderer; }

	// Returns a pointer to the physics component.
	inline Physics* physics() { return &_physics; }

	// Returns a pointer to the behavior component.
	inline Behavior* getBehavior() const { return _behavior; }

	// Sets the behavior component.
	void setBehavior(Behavior *behavior);

	// Gets the delete flag status.
	inline bool getDeleteFlag() const { return _delete; }

	// Sets the delete flag status.
	inline bool setDeleteFlag(bool flag) { _delete = flag; }

private:
	// should the GameObject be deleted?
	bool _delete = false;

	// renderer component
	Renderer _renderer;

	// physics component
	Physics _physics;

	// behavior component
	Behavior *_behavior = nullptr;
};

#endif
