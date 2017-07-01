#include <SDL.h>
#include "game.h"
#include "text.h"

#define CHARS 96
#define ASCII_OFFSET 32
#define ROWS 6
#define COLS 16
#define SIZE 10

Text::Text() { }

Text::~Text()
{
	if(_chars)
		delete[] _chars;
}

void Text::setFont(SpriteSheet* font)
{
	if(_chars)
		delete[] _chars;

	_font = font;
	_chars = new Rect[CHARS];

	// Generate the character positions.
	for(int r = 0; r < ROWS; r++)
		for(int c = 0; c < COLS; c++)
			_chars[(r * COLS) + c] = Rect { c * SIZE, r * SIZE, SIZE, SIZE };
}

void Text::render() const
{
	if(!_font)
		return;

	int offset = _position.x;

	for(unsigned int i = 0; i < _text.length(); i++)
	{
		char c = _text[i] - ASCII_OFFSET;

		Rect source = _chars[(int)c];
		Rect destination = { offset, _position.y, SIZE, SIZE };
		SDL_RenderCopy(Game::instance()->renderer(), _font->texture,
			&source, &destination);

		offset += SIZE;
	}
}
