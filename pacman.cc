#include "pacman.h"

Pacman::Pacman(CharacterName name): Character(name){
	SetSpeed(0.8);
}
void Pacman::Reset(){
	SetSpeed(0.8);
	_direction = _tilemap.GetDirection((int)PACMAN);
	_x =_tilemap.GetPosition((int)_name, 0);
	_y =_tilemap.GetPosition((int)_name, 1);
	_x_px =_tilemap.GetPosition_px((int)_name, 0);
	_y_px =_tilemap.GetPosition_px((int)_name, 1);
	_eaten = false;
} 
