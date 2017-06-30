#ifndef TEXT_H_
#define TEXT_H_

#include <string>
#include "sprite.h"
#include "types.h"

class Text
{
public:
	Text();

	~Text();

	// Sets the text to render.
	inline void setText(std::string text) { _text = text; }

	// Sets the position of the text.
	inline void setPosition(Vector2 position) { _position = position; }

	// Sets the font SpriteSheet.
	void setFont(SpriteSheet* font);

	// Displays the text.
	void render() const;

private:
	// The text to be displayed.
	std::string _text;

	// The text's position on screen.
	Vector2 _position;

	// The font SpriteSheet.
	SpriteSheet* _font = nullptr;

	// The character positions on the SpriteSheet.
	Rect* _chars = nullptr;
};

#endif
