#ifndef INPUT_H_
#define INPUT_H_

#include <SDL.h>
#include "structures/queue.h"
#include "types.h"

class Input
{
public:
	~Input();

	// Possible controller inputs.
	enum In
	{
		// Digital inputs.
		A = SDL_CONTROLLER_BUTTON_A,
		B = SDL_CONTROLLER_BUTTON_B,
		X = SDL_CONTROLLER_BUTTON_X,
		Y = SDL_CONTROLLER_BUTTON_Y,
		Select = SDL_CONTROLLER_BUTTON_BACK,
		Home = SDL_CONTROLLER_BUTTON_GUIDE,
		Start = SDL_CONTROLLER_BUTTON_START,
		L3 = SDL_CONTROLLER_BUTTON_LEFTSTICK,
		R3 = SDL_CONTROLLER_BUTTON_RIGHTSTICK,
		L1 = SDL_CONTROLLER_BUTTON_LEFTSHOULDER,
		R1 = SDL_CONTROLLER_BUTTON_RIGHTSHOULDER,
		Up = SDL_CONTROLLER_BUTTON_DPAD_UP,
		Down = SDL_CONTROLLER_BUTTON_DPAD_DOWN,
		Left = SDL_CONTROLLER_BUTTON_DPAD_LEFT,
		Right = SDL_CONTROLLER_BUTTON_DPAD_RIGHT,

		// Analogue inputs.
		LeftStickX = (Right + 1) + SDL_CONTROLLER_AXIS_LEFTX,
		LeftStickY = (Right + 1) + SDL_CONTROLLER_AXIS_LEFTY,
		RightStickX = (Right + 1) + SDL_CONTROLLER_AXIS_RIGHTX,
		RightStickY = (Right + 1) + SDL_CONTROLLER_AXIS_RIGHTY,
		L2 = (Right + 1) + SDL_CONTROLLER_AXIS_TRIGGERLEFT,
		R2 = (Right + 1) + SDL_CONTROLLER_AXIS_TRIGGERRIGHT
	};

	// Eveything about a single input event.
	struct InputEvent
	{
		In input;
		Sint16 state;
	};

	// Returns a pointer to this singleton instance.
	static Input* instance();

	// Opens a controller if one is dectected.
	void initController();

	// Closes a controller if one is open.
	void closeController();

	// Returns the state of the specified input right now.
	Sint16 getInput(In input) const;

	// Returns a constant reference to the input event queue, allowing it
	// to be copied.
	inline const Queue<InputEvent>& events() const { return _events; }

	// Converst an SDL_Event and adds it to the Queue. Should only be used
	// by the Game class.
	void offerEvent(const SDL_Event& e);

	// Clears the event queue. Should only be used by the Game class.
	inline void clearEvents() { _events.clear(); }

private:
	Input();

	// The connected controller.
	SDL_GameController* _controller = nullptr;

	// The event queue.
	Queue<InputEvent> _events;

	// This singleton instance.
	static Input* _instance;
};

#endif
