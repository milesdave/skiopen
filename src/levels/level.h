#ifndef LEVELS_LEVEL_H_
#define LEVELS_LEVEL_H_

class Level
{
public:
	virtual ~Level() { }

	// Called when the level is loaded.
	virtual void onLoad() = 0;

	// Called to update the level.
	virtual void update() { }

	// Called to render anything needed by the level.
	virtual void render() { }

	// Called when the game is paused.
	virtual void pause(bool paused) { }

	// Called when the level has finished.
	virtual void onExit() { }
};

#endif
