#ifndef RENDERER_H_
#define RENDERER_H_

#include "types.h"

struct Sprite;

class Renderer
{
public:
	Renderer();

	~Renderer();

	// Renders the sprite.
	void render(Vector2F position);

	// Returns a pointer to the sprite.
	inline Sprite* getSprite() const { return _sprite; }

	// Sets the current sprite.
	void setSprite(Sprite* sprite);

	// Returns true if the animation has ended.
	inline bool complete() const { return _complete; }

private:
	// updates the animation
	void animate();

	// sprite to render
	Sprite* _sprite = nullptr;

	// current sprite frame
	int _frame = 0;

	// time when the animation started
	int _startTime = 0;

	// current animation time
	float _timer = 0.0f;

	// animation fps
	float _fps = 0.0f;

	// is the animation complete?
	bool _complete = false;
};

#endif
