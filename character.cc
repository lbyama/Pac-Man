#include "character.h"

Character::Character(CharacterName name){
	_name = name;
	_direction = LEFT;
	SetSpeed(0.75);
	_x = _tilemap.GetPosition((int)name,0);
	_y = _tilemap.GetPosition((int)name,1);
	_b_x = 0.0;
	_b_y = 0.0;
	_x_px = _tilemap.GetPosition_px((int)name,0);
	_y_px = _tilemap.GetPosition_px((int)name,1);
	_eaten = false;
}

 
int Character::Move(){
	//std::cout << _name <<". Character::Move(): rodando\n";
	if(_direction == UP){
		if(isNextTileAvailable(UP)){
			_b_x -= _speed;
		}else if(!isNextTileAvailable(UP) && _x_px + _b_x - _speed> _x*8 +4){
			_b_x -= _speed;
		}
	}else if(_direction == LEFT ){
		if( isNextTileAvailable(LEFT)){
			_b_y -= _speed;
		}else if(!isNextTileAvailable(LEFT) && _y_px + _b_y - _speed> _y*8 +4){
			_b_y -= _speed;
		}
	}else if(_direction == DOWN){
		if ( isNextTileAvailable(DOWN)){
			_b_x += _speed;
		}else if(!isNextTileAvailable(DOWN) && _x_px + _b_x + _speed < _x*8 +4){
			_b_x += _speed;
		}
	}else if(_direction == RIGHT){
		if(isNextTileAvailable(RIGHT)){
			_b_y += _speed;
		}else if(!isNextTileAvailable(RIGHT) && _y_px + _b_y + _speed < _y*8 +4){
			_b_y += _speed;
		}
	}
	//std::cout << "_x: " << _x;
	//std::cout << "\n_y: " << _y << "\n";
	//std::cout << "_x_px: " << _x_px;
	//std::cout << "\n_y_px: " << _y_px << "\n";
	//std::cout << "b_x: " << std::to_string(_b_x);
	//std::cout << "\n_b_y: " << std::to_string(_b_y)<< "\n";
	//std::cout << "\n_speed: " << std::to_string(_speed)<< "\n";
	char a;
	//std::cin >> a;

	UpdatePosition();
	return 1;
}

void Character::UpdatePosition(){
	//std::cout << _name <<". Character::UpdatePosition(): rodando\n";
	if(_x == 14 && _y_px < 6){
		_y = 27;
		_y_px = _y*8 + 2;
	}else if(_x == 14 && _y_px > 27*8 + 2){
		_y = 0;
		_y_px = _y*8 + 6;
	}
	_x_px += (int)_b_x;
	_y_px += (int)_b_y;
	_b_x -= (int)_b_x;
	_b_y -= (int)_b_y;
	
	_tilemap.SetPosition_px(_x_px,(int)_name,0);
	_tilemap.SetPosition_px(_y_px,(int)_name,1);

	int x = 0,  y = 0;
		x = (int)_x_px; //x do meio do tile 
		x = x - x%8;
		x = x/8;
		if(x > 30){
			_x_px = 29*8;
			x = 29;
		}else if(x < 0){
			_x_px = 8;
			x = 1;
		}
		_x = x;
		y = (int)_y_px; //y do meio do tile
		y = y - y%8;
		y = y/8 ;
		if(y > 27){
			//_y_px = 26*8;
			y = 27;
		}else if(y < 0){
			//_y_px = 8;
			y = 0;
		}
		_y = y;
		_tilemap.SetPosition(_x,(int)_name,0);
		_tilemap.SetPosition(_y,(int)_name,1);
}

void Character::SetSpeed(float percentage){
	_speed = percentage*75.0/FPS;
}

bool Character::isNextTileAvailable(Direction direction){
	//std::cout << "Character::isNextTileAvailable(): rodando\n";
	int x,y;
	x = _x;
	y = _y;
	if(direction == UP){
		x--;
	}else if(direction == LEFT){
		y--;
	}else if(direction == DOWN){
		x++;
	}else if(direction == RIGHT){
		y++;
	}
	return _tilemap.GetMaze(x,y) != W && (_tilemap.GetMaze(x,y) != G || _eaten);
}

void Character::SetDirection(Direction direction){
	//std::cout << _name <<". Character::SetDirection(): rodando\n";
	if((direction == UP && isNextTileAvailable(UP)) || (direction == DOWN && isNextTileAvailable(DOWN))){
		if(_y_px >= _y*8 + 2 &&  _y_px <= _y*8 + 6){
			_b_y = 0.0;
			_y_px = _y*8 + 4;
			_direction = direction;
			_tilemap.SetDirection(direction,(int)_name);
		}
	}
	if((direction == LEFT && isNextTileAvailable(LEFT)) || (direction == RIGHT && isNextTileAvailable(RIGHT))){
		if(_x_px >= _x*8 + 2 && _x_px <= _x*8 + 6){
			_b_x = 0.0;
			_x_px = _x*8 + 4;
			_direction = direction;
			_tilemap.SetDirection(direction,(int)_name);
		}
	}
}

int Character::GetX(){
    return _x;
}

int Character::GetY(){
    return _y;
}

float Character::GetX_px(){
    return _x_px;
}

float Character::GetY_px(){
    return _y_px;
}

void Character::SetX(int x){
    _x = x;
}

void Character::SetY(int y){
    _y = y;
}

void Character::SetX_px(float x_px){
    _x_px = x_px;
}

void Character::SetY_px(float y_px){
    _y_px = y_px;
}


void Character::SetEaten(bool eaten){
    _eaten = eaten;
		_tilemap.SetEaten(_eaten,(int)_name);
}

bool Character::GetEaten(){
    return _eaten;
}
