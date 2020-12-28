#include "keyhandler.h"

KeyHandler::KeyHandler(Game *game){
	_game = game;
}
 
bool KeyHandler::Handler(){
	if(!_key.GetHandled()){
		Key key = _key.GetKey();
		if(key == U_KEY){
			_game->SetDirection((int)PACMAN,UP);
			std::cout << "^^" << std::endl;
		}else if(key == L_KEY){
			_game->SetDirection((int)PACMAN,LEFT);
			std::cout << "<<" << std::endl;
		}else if(key == D_KEY){
			_game->SetDirection((int)PACMAN,DOWN);
			std::cout << "vv" << std::endl;
		}else if(key == R_KEY){
			_game->SetDirection((int)PACMAN,RIGHT);
			std::cout << ">>" << std::endl;
		}else if(key == P_KEY){
			//_game->Pause();
			_paused = !_paused && true;
			std::cout << "Jogo pausado" << std::endl; // mudar pra algo em thread
		}
		_key.SetHandled(true);
	}
	return _paused;
}
