#if _WIN32 && _DEBUG
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#ifndef DBG_NEW
#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
#define new DBG_NEW
#endif
#endif

#include "game.h"
#include "levels/mainlevel.h"

int main(int argc, char* argv[])
{
	{
		Game game;
		game.init();
		game.addLevel(new MainLevel());
		game.setLevel(L_MAIN);
		game.loop();
	}

#if _WIN32 &&_DEBUG
	_CrtDumpMemoryLeaks();
#endif

	return 0;
}
