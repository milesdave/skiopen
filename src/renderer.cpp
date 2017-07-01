#include <SDL.h>
#include "camera.h"
#include "game.h"
#include "renderer.h"
#include "sprite.h"

Renderer::Renderer() { }

Renderer::~Renderer() { }

void Renderer::setSprite(Sprite *sprite)
{
	// The new sprite is the same as the old one.
	if(_sprite == sprite)
		return;

	_sprite = sprite;
	_frame = 0;
	_timer = 0.0f;
	_startTime = SDL_GetTicks();
	_fps = _sprite->duration / _sprite->frames;
	_complete = _sprite->frames == 1 ? true : false;
}

void Renderer::render(Vector2f position)
{
	if(!_sprite)
		return;

	animate();

	Vector2 relative = Game::instance()->camera()->relative(Vector2 { (int)position.x, (int)position.y });
	Rect source = _sprite->clips[_frame];
	Rect destination = Game::centre(Rect { relative.x, relative.y, source.w, source.h }, relative);

	SDL_RenderCopy(Game::instance()->renderer(), _sprite->sheet->texture, &source, &destination);
}

void Renderer::animate()
{
	// Sprite does not loop/is complete.
	if(_complete && !_sprite->loop)
		return;

	_timer += SDL_GetTicks() - _startTime;

	// Time to change sprite frame.
	if(_timer / 1000.0f > _fps)
	{
		if(_frame < _sprite->frames - 1)
		{
			_frame++;
		}
		else
		{
			_complete = true;

			// Does not loop.
			if(!_sprite->loop)
				return;

			_frame = 0;
		}

		// Restart the timer.
		_startTime = SDL_GetTicks();
		_timer = 0.0f;
	}
}
