#include "ghost.h"

Mode Ghost::_main_mode = SCATTER;

Ghost::Ghost(CharacterName name) : Character(name){
	_mode = SCATTER;
	_CR[0] = -1;
	_CR[1] = -1;
	_ghost_house = false;
}
 

void Ghost::Reset(){
	_direction = LEFT;
	SetSpeed(0.75);
	_x = _tilemap.GetPosition((int)_name,0);
	_y = _tilemap.GetPosition((int)_name,1);
	_b_x = 0.0;
	_b_y = 0.0;
	_x_px = _tilemap.GetPosition_px((int)_name,0);
	_y_px = _tilemap.GetPosition_px((int)_name,1);
	_eaten = false;
	_mode = SCATTER;
	_CR[0] = -1;
	_CR[1] = -1;
	_ghost_house = false;

}

void Ghost::TTScatter(){
	if(_name == BLINKY){
		_TT[0] = -2;
		_TT[1] = 24 ;
	}else if(_name == PINKY){
		_TT[0] = -2 ;
		_TT[1] = 3;
	}else if(_name == INKY){
		_TT[0] = 31;
		_TT[1] = 27;
	}else if(_name == CLYDE){
		_TT[0] = 31;
		_TT[1] = 0;
	}
}

void Ghost::Leave_GH(){
	if(_y_px > 13*8 + 4){
		_y_px--;
	}else if(_y_px < 13*8 + 4){
		_y_px++;
	}else{
		//std::cout << _name << " - _x_px: " << _x_px-1 << std::endl;
		_x_px--;
	}

	if(_x_px <= 11*8 + 4){
		//std::cout << _name << ". ENTORU\n";
		_x = 11;
		_y = 13;
		_CR[0]= _x;
		_CR[1]=_y;
		_tilemap.SetPosition(_x,(int)_name,0);
		_tilemap.SetPosition(_y,(int)_name,1);
		_ghost_house = false;
		SetDirection(LEFT);
		SetMode(_main_mode);
	}
	_tilemap.SetPosition_px(_x_px,(int)_name,0);
	_tilemap.SetPosition_px(_y_px,(int)_name,1);
}

bool Ghost::isInGH(){
	return _ghost_house;
}

void Ghost::SetGH(bool gh){
	_ghost_house = gh;
}

void  Ghost::TTChase(){
	Direction dir = _tilemap.GetDirection((int)PACMAN);
	int x = _tilemap.GetPosition((int)PACMAN,0);
	int y = _tilemap.GetPosition((int)PACMAN,1);
	if(_name == BLINKY){
		_TT[0] = x ;
		_TT[1] = y;
	}else if(_name == PINKY){
		if(dir == UP){
			x -= 4;
		}else if(dir == LEFT){
			y -= 4;
		}else if(dir == DOWN){
			x +=4;
		}else if(dir == RIGHT){
			y += 4;
		}
		_TT[0] = x;
		_TT[1] = y;
	}else if(_name == INKY){
		if(dir == UP){
			x -= 2;
		}else if(dir == LEFT){
			y -= 2;
		}else if(dir == DOWN){
			x += 2;
		}else if(dir == RIGHT){
			y += 2;
		}
		_TT[0] = _tilemap.GetPosition((int)BLINKY,0) + (x - _tilemap.GetPosition((int)BLINKY,0))*2;
		_TT[1] = _tilemap.GetPosition((int)BLINKY,1) + (y - _tilemap.GetPosition((int)BLINKY,1))*2;
	}else if(_name == CLYDE){
		if(distanceTT(_x,_y,x,y)>8){
			_TT[0] = x;
			_TT[1] = y;
		}else{
			_TT[0] = 30;
			_TT[1] = 0;
		}
	}
}

bool  Ghost::Crossroad(){
	if(_x != _CR[0] || _y != _CR[1]){
		if(_direction == UP || _direction == DOWN){
			if((isDirectionAvailable(LEFT)|| isDirectionAvailable(RIGHT)) && _x_px >= _x*8 + 2 && _x_px <= _x*8 + 6){
				_CR[0] = _x;
				_CR[1] = _y;
				return true;
			}
		}else if(_direction == LEFT || _direction == RIGHT){
			if((isDirectionAvailable(UP)|| isDirectionAvailable(DOWN)) && _y_px >= _y*8 + 2 && _y_px <= _y*8 + 6){
				_CR[0] = _x;
				_CR[1] = _y;
				return true;
			}
		}
	}
	return false;
}

bool Ghost::isDirectionAvailable(Direction direction){
	bool special_CR = false;
	bool reverse_direction = (int)direction != (int)_direction + 2 && (int)direction != (int)_direction - 2;
	
	int i;
	int CR_position[4][2] = {
		{23,12},
		{23,15},
		{11,12},
		{11,15}
	};

	if(_mode != FRIGHTENED && direction == UP){
		for(i=0;i<4;i++){
			if(_x == CR_position[i][0] && _y == CR_position[i][1]){
				special_CR = true;
			}
		}
	}

	return isNextTileAvailable(direction) && reverse_direction && !special_CR;
}


float Ghost::distanceTT(Direction direction){
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
	return sqrt(pow(x-_TT[0],2) + pow(y-_TT[1],2));
}

float Ghost::distanceTT(int x1, int y1, int x2, int y2){
	return sqrt(pow(x1-x2,2) + pow(y1-y2,2));
}


void  Ghost::CR_Decision(){
	int i, directions_available = 0,dir;
	float distance[4], dist;
	bool dir_b[4];
	
	for(i=0;i<4;i++){
		dir_b[i] = isDirectionAvailable((Direction)i);
	}
	
	for(i=0;i<4;i++){
		if(dir_b[i]){
			directions_available++;
			dir = i;
		}
	}
	if(directions_available > 1){
		if(_mode == FRIGHTENED && !_eaten){
			do{
				dir = rand()%4;
			}while(!dir_b[dir]);
		} else{
			if(_eaten){
				_TT[0] = 14;
				_TT[1] = 13;
			}else if(_mode == SCATTER){
				TTScatter();
			}else if(_mode == CHASE){
				TTChase();
			}
			dist = 5000;//uma distancia impossivelmente GRANDE
			
			for(i=0;i<4;i++){
				distance[i] = distanceTT((Direction)i);
				if(dir_b[i] && distance[i]<dist){
					dist = distance[i];
					dir = i;
				}
			}
		}
	}
	char a;
	//std::cout << dir;
	//std::cin >> a;

	SetDirection((Direction)dir); 
}


void Ghost::SetMode(Mode mode){
	if(!_eaten ){//&& !_tunnel
		if(mode == FRIGHTENED){
			SetSpeed(0.5);
		} else{
			SetSpeed(0.75);
		}
		if(_mode != FRIGHTENED && mode != _mode){ //se ele estava em SCATTER ou CHASE e mudou de modo
			ReverseDirection();
			_CR[0] = -1;
			_CR[1] = -1;
		}
	}
	_mode = mode;
	_tilemap.SetMode((int)_name,_mode);
}

void Ghost::SetMainMode(Mode mode){
	_main_mode = mode;
}

void Ghost::ReverseDirection(){
    int dir = (int)_direction;
		dir < 2 ? dir +=2 : dir -=2;
    _direction = (Direction)dir;
}

Mode Ghost::GetMode(){
    return _mode;
}

void Ghost::SetEaten(bool eaten){
    _eaten = eaten;
    if(_eaten == true){
        SetSpeed(1.4);
    }
		_tilemap.SetEaten(_eaten,(int)_name);
}
