#ifndef game_h
#define game_h

#include <iostream>
#include "enum.h"
#include "tilemap.h"
#include "character.h"
#include "pacman.h"
#include "ghost.h"
//#include "SO/timer.h"
 
class Game{
		public:
				Game(Pacman *_pac, Ghost *_b, Ghost *_p, Ghost *_i, Ghost *_c);
        void UpdateTilemap();
        bool UpdateDots();
        int UpdateGhosts();
        void UpdateFruits();
				bool isVictory();
				bool isDeath();
				bool isGameOver();
				void SetDirection(int name, Direction direction);
				void Death();

    private:
        Tilemap _tilemap;
        //Timer *_timer_mode;
        //Timer *_timer_ghost_house;
        //Timer *_timer_frightened;
        unsigned int _dot_counter;
        Pacman *_pacman;
        Ghost *_ghosts[4];
};


#endif
