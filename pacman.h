#ifndef pacman_h
#define pacman_h

#include <iostream>
#include "enum.h"
#include "character.h"

class Pacman : public Character{
    public:
			Pacman(CharacterName name);
			void Reset();
    private:
 
};

#endif
