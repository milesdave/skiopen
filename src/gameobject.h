#ifndef GAMEOBJECT_H_
#define GAMEOBJECT_H_

#include "physics.h"
#include "renderer.h"
#include "types.h"

class Behaviour;

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

	// Returns a pointer to the behaviour component.
	inline Behaviour* behaviour() const { return _behaviour; }

	// Sets the behaviour component.
	void setBehaviour(Behaviour* behaviour);

	// Gets the delete flag status.
	inline bool deleteFlag() const { return _delete; }

	// Sets the delete flag status.
	inline void setDeleteFlag(bool flag) { _delete = flag; }

	// Returns the GameObject sprite geometry.
	Rect spritePosition() const;

private:
	// State of whether or not the GameObject should be deleted.
	bool _delete = false;

	// The renderer component object.
	Renderer _renderer;

	// The physics component object.
	Physics _physics;

	// The behaviour component object.
	Behaviour* _behaviour = nullptr;
};

#endif
