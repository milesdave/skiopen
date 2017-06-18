#ifndef LEVELS_LEVEL_H_
#define LEVELS_LEVEL_H_

class Level
{
public:
	virtual ~Level() { }

	// Called when the level is loaded.
	virtual void onLoad() = 0;

	// Called to update the level.
	virtual void update() = 0;

	// Called to render anything needed by the level.
	virtual void render() = 0;

	// Called when the game is paused.
	virtual void pause() = 0;

	// Called when the level has finished.
	virtual void onExit() = 0;
};

#define LEVELS 1

#define L_MAIN 0

#endif
