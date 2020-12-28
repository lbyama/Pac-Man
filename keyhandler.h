#ifndef keyhandler_h
#define keyhandler_h

#include <iostream>
#include "enum.h"
#include "keypressed.h"
#include "game.h"
 
class KeyHandler{
	public:
		KeyHandler(Game *game);
		bool Handler();
	private:
		KeyPressed _key;
		Game *_game;
		bool _paused;
};

#endif
