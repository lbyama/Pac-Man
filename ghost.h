#ifndef ghost_h
#define ghost_h

#include <iostream>
#include <cstdlib>
#include "enum.h"
#include "character.h"
#include <cmath>
 
class Ghost : public Character{
    public:
			Ghost(CharacterName name);
        void TTScatter();
        void TTChase();
        bool Crossroad();
        void CR_Decision();
        void ReverseDirection();
				void Leave_GH();
				bool isDirectionAvailable(Direction direction);
				float distanceTT(Direction direction);
				float distanceTT(int x1, int y1, int x2, int y2);
        void SetMode(Mode mode);
				static void SetMainMode(Mode mode);
        Mode GetMode();
        void SetEaten(bool eaten);
				void SetGH(bool);
				bool isInGH();
				void Reset();
    private:
      	Mode _mode;
				static Mode _main_mode;
				int _TT[2]; //Target Tile
        bool _ghost_house; 
				int _CR[2];
};

#endif
