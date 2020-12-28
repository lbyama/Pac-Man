#include "tilemap.h"
 
Tile Tilemap::_maze[31][28] ={
{W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W},
{W,o,o,o,o,o,o,o,o,o,o,o,o,W,W,o,o,o,o,o,o,o,o,o,o,o,o,W},
{W,o,W,W,W,W,o,W,W,W,W,W,o,W,W,o,W,W,W,W,W,o,W,W,W,W,o,W},
{W,o,W,W,W,W,o,W,W,W,W,W,o,W,W,o,W,W,W,W,W,o,W,W,W,W,o,W},
{W,O,W,W,W,W,o,W,W,W,W,W,o,W,W,o,W,W,W,W,W,o,W,W,W,W,O,W},
{W,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,W},
{W,o,W,W,W,W,o,W,W,o,W,W,W,W,W,W,W,W,o,W,W,o,W,W,W,W,o,W},
{W,o,W,W,W,W,o,W,W,o,W,W,W,W,W,W,W,W,o,W,W,o,W,W,W,W,o,W},
{W,o,o,o,o,o,o,W,W,o,o,o,o,W,W,o,o,o,o,W,W,o,o,o,o,o,o,W},
{W,W,W,W,W,W,o,W,W,W,W,W,u,W,W,u,W,W,W,W,W,o,W,W,W,W,W,W},
{u,u,u,u,u,W,o,W,W,W,W,W,u,W,W,u,W,W,W,W,W,o,W,u,u,u,u,u},
{u,u,u,u,u,W,o,W,W,u,u,u,u,u,u,u,u,u,u,W,W,o,W,u,u,u,u,u},
{u,u,u,u,u,W,o,W,W,u,W,W,W,G,G,W,W,W,u,W,W,o,W,u,u,u,u,u},
{W,W,W,W,W,W,o,W,W,u,W,u,u,u,u,u,u,W,u,W,W,o,W,W,W,W,W,W},
{P,u,u,u,u,u,o,u,u,u,W,u,u,u,u,u,u,W,u,u,u,o,u,u,u,u,u,P},
{W,W,W,W,W,W,o,W,W,u,W,u,u,u,u,u,u,W,u,W,W,o,W,W,W,W,W,W},
{u,u,u,u,u,W,o,W,W,u,W,W,W,W,W,W,W,W,u,W,W,o,W,u,u,u,u,u},
{u,u,u,u,u,W,o,W,W,u,u,u,u,u,u,u,u,u,u,W,W,o,W,u,u,u,u,u},
{u,u,u,u,u,W,o,W,W,u,W,W,W,W,W,W,W,W,u,W,W,o,W,u,u,u,u,u},
{W,W,W,W,W,W,o,W,W,u,W,W,W,W,W,W,W,W,u,W,W,o,W,W,W,W,W,W},
{W,o,o,o,o,o,o,o,o,o,o,o,o,W,W,o,o,o,o,o,o,o,o,o,o,o,o,W},
{W,o,W,W,W,W,o,W,W,W,W,W,o,W,W,o,W,W,W,W,W,o,W,W,W,W,o,W},
{W,o,W,W,W,W,o,W,W,W,W,W,o,W,W,o,W,W,W,W,W,o,W,W,W,W,o,W},
{W,O,o,o,W,W,o,o,o,o,o,o,o,u,u,o,o,o,o,o,o,o,W,W,o,o,O,W},
{W,W,W,o,W,W,o,W,W,o,W,W,W,W,W,W,W,W,o,W,W,o,W,W,o,W,W,W},
{W,W,W,o,W,W,o,W,W,o,W,W,W,W,W,W,W,W,o,W,W,o,W,W,o,W,W,W},
{W,o,o,o,o,o,o,W,W,o,o,o,o,W,W,o,o,o,o,W,W,o,o,o,o,o,o,W},
{W,o,W,W,W,W,W,W,W,W,W,W,o,W,W,o,W,W,W,W,W,W,W,W,W,W,o,W},
{W,o,W,W,W,W,W,W,W,W,W,W,o,W,W,o,W,W,W,W,W,W,W,W,W,W,o,W},
{W,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,W},
{W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W}
};

int Tilemap::_positions[5][2] = 
{{23,13}, //pacman [vertical][horizontal]
{11,13}, //blinky
{14,11}, //pinky 
{14,13}, //inky
{14,15}}; // clyde

int Tilemap::_positions_px[5][2] = 
{{23*8 + 4, 13*8 + 4},
{11*8 + 4, 13*8 + 4},
{14*8 + 4, 11*8 + 4},
{14*8 + 4, 13*8 + 4},
{14*8 + 4, 15*8 + 4}};

unsigned int Tilemap::_points = 0;
unsigned int Tilemap::_high_score = 0;

Mode Tilemap::_mode[5] = {CHASE,CHASE,CHASE,CHASE,CHASE};

Direction Tilemap::_directions[5] =
{LEFT,LEFT,LEFT,LEFT,LEFT};

int Tilemap::_lives = 3;

bool Tilemap::_eaten[5] = {false, false, false, false, false};

void Tilemap::SetMode(int name,Mode mode){
	_mode[name] = mode;
}

Mode Tilemap::GetMode(int name){
	return _mode[name];
}

int Tilemap::GetLives(){
	return _lives;
}
void Tilemap::SetDirection(Direction direction,int i){
	_directions[i] = direction;
}

void Tilemap::SetPosition(int i,int x, int y){
	_positions[x][y] = i;
}

void Tilemap::SetPosition_px(int i, int x, int y){
	_positions_px[x][y] = i;
}

Direction Tilemap::GetDirection(int i){
	return _directions[i];
}

int Tilemap::GetPosition(int x, int y){
	return _positions[x][y];
}

int Tilemap::GetPosition_px(int x, int y){
	return _positions_px[x][y];
}

Tile Tilemap::GetMaze(int x, int y){
    return _maze[x][y];
}

void Tilemap::SetMaze(Tile tile, int x, int y){
    _maze[x][y] = tile;
}
void Tilemap::AddPoints(int points){
	_points += points;
	if(_high_score < _points){
		_high_score = _points;
	}
}

int Tilemap::GetScore(){
	return _points;
}

int Tilemap::GetHighScore(){
	return _high_score;
}

void Tilemap::SetEaten(bool eaten,int name){
	_eaten[name] = eaten;
}
bool Tilemap::GetEaten(int name){
	return _eaten[name];
}


void Tilemap::ResetMaze(){
	int positions[5][2] = 
	{{23,13},
	{11,13},
	{14,11},
	{14,13}, 
	{14,15}};

	int i,j;

	for(i=0;i<5;i++){
		for(j=0;j<2;j++){
			_mode[i] = SCATTER;
			_positions[i][j] = positions[i][j];
			_positions_px[i][j] = _positions[i][j]*8 + 4;
			_directions[i] = LEFT;
		}
	}
}

void Tilemap::LoseLife(){
	_lives--;
}
