#ifndef character_h
#define character_h

#include "enum.h"
#include "tilemap.h"
#include <cmath> 
#include <iostream>

//typedef enum {W, G, P, u, o, e, O, E, b, p, i, c, m, f} Tile;
//typedef enum {SCATTER, CHASE, FRIGHTENED, DYING} Mode;
//typedef enum {UP, LEFT, RIGHT, DOWN} Direction;

 
class Character{
    public:
        Character(CharacterName name);
        void Run();
        int Move();
        void UpdatePosition(); 
        void SetSpeed(float percentage);
				void SetDirection(Direction direction);
				bool isNextTileAvailable(Direction direction);
				
        int GetX();
        int GetY();
        float GetX_px();
        float GetY_px();
				void SetX(int x); //não sei se precisa
        void SetY(int y);
        void SetX_px(float x_px);
        void SetY_px(float y_px);
        void SetEaten(bool eaten);
        bool GetEaten();
    protected:
        CharacterName _name;
        Tilemap _tilemap;
        int _x; //posicao na matriz
        int _y;
				float _b_x;
				float _b_y;
        int _x_px; // posicao em px, para ser impressa
        int _y_px;
        Direction _direction;
        float _speed; // px/Frame
        bool _eaten;
};

#endif
