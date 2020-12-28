#include "game.h"

Game::Game(Pacman *_pac, Ghost *_b, Ghost *_p, Ghost *_i, Ghost *_c){
	_pacman = _pac;
	_ghosts[0] = _b;
	_ghosts[1] = _p;
	_ghosts[2] = _i;
	_ghosts[3] = _c;
}
 

void Game::UpdateTilemap(){
	//std::cout <<"Game::UpdateTilemap(): rodando\n";
	UpdateDots();
	UpdateGhosts();
	UpdateFruits();
}

bool Game::UpdateDots(){
    /*
    Checks if Pac-Man ate a dot
    */
    int pacx = _pacman->GetX();
    int pacy = _pacman->GetY();
		int i;
		bool rtn = false;

    if(_tilemap.GetMaze(pacx,pacy) == o){
        _tilemap.SetMaze(u,pacx,pacy);
        _dot_counter++;
        _tilemap.AddPoints(10);
    }else if(_tilemap.GetMaze(pacx,pacy) == O){
        _tilemap.SetMaze(u,pacx,pacy);
				for(i=0;i<4;i++){
					_ghosts[i]->SetMode(FRIGHTENED);
					rtn = true;
				}
        _dot_counter++;
        _tilemap.AddPoints(50);
    }
		return rtn;
}

int Game::UpdateGhosts(){
	int pacx, pacy, gx[4],gy[4],i,rtn = -1;
	pacx = _pacman->GetX();
	pacy = _pacman->GetY();
	for(i=0;i<4;i++){
		gx[i] = _ghosts[i]->GetX();
		gy[i] = _ghosts[i]->GetY();
	}
	for(i=0;i<4;i++){
		if((gx[i] >= 13 && gx[i]<=15)&& (gy[i] >=11 && gy[i]<=16) && !_ghosts[i]->isInGH()){
			_ghosts[i]->SetGH(true);
			_ghosts[i]->SetEaten(false);
			rtn = i;
			break;
		}
	}
	for(i=0;i<4;i++){
		if(pacx == gx[i] && pacy == gy[i]){
			if(_ghosts[i]->GetMode() == FRIGHTENED){
				if(!_ghosts[i]->GetEaten()){
					_ghosts[i]->SetEaten(true);
					_tilemap.AddPoints(200);
				}
			}else if(!_ghosts[i]->GetEaten()){
				_pacman->SetEaten(true);
			}
		}
	}
	return rtn;
}

void Game::UpdateFruits(){
	int pacx = _pacman->GetX();
	int pacy = _pacman->GetY();

	if(_dot_counter == 70 || _dot_counter == 170){
		_tilemap.SetMaze(f,17,13);
	}
	if(_tilemap.GetMaze(pacx,pacy) == f){
		_tilemap.SetMaze(u,17,13);
		_tilemap.AddPoints(100);
	}
}

void Game::SetDirection(int name,Direction direction){
	//std::cout <<"Game::SetDirection(): rodando\n";
	if(name == 0){
		_pacman->SetDirection(direction);
	}else{
		_ghosts[name-1]->SetDirection(direction);
	}
}

bool Game::isVictory(){
	if(_dot_counter == 244){
		return true;
	}else{
		return false;
	}
}

bool Game::isDeath(){
	if(_pacman->GetEaten()){
		return true;
	}else{
		return false;
	}
}

bool Game::isGameOver(){
	if(_tilemap.GetLives() == 0){
		return true;
	}else{
		return false;
	}
}

void Game::Death(){
	_tilemap.LoseLife();
	_tilemap.ResetMaze();
	_pacman->Reset();
	_ghosts[0]->Reset();
	_ghosts[1]->Reset();
	_ghosts[2]->Reset();
	_ghosts[3]->Reset();
}
