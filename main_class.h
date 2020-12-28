#ifndef main_class_h
#define main_class_h

#include <iostream>
#include "window.h"
#include "pacman.h"
#include "ghost.h"
#include "game.h"
#include "keyhandler.h"
#include "SO/cpu.h"
#include "SO/traits.h"
#include "SO/thread.h"
#include "SO/semaphore.h"
#include "SO/timer.h"
#include <unistd.h>
 
__BEGIN_API

class Main
{
public:
	Main() {
	}

	static void run(void * name){
		pacman = new Pacman(PACMAN);
		blinky = new Ghost(BLINKY);
		pinky = new Ghost(PINKY);
		inky = new Ghost(INKY);
		clyde = new Ghost(CLYDE);
		game = new Game(pacman,blinky,pinky,inky,clyde);
		handler = new KeyHandler(game);

		tm_sem = new Semaphore();
		GH_sem = new Semaphore();
		
		////std::cout << "Inicializando...\n";

		window_thread = new Thread(printScreen);
		keyboard_thread = new Thread(keyInput);
		game_thread = new Thread(runGame);
		pacman_thread = new Thread(pacMan);
		blinky_thread = new Thread(Gblinky);
		pinky_thread = new Thread(Gpinky);
		inky_thread = new Thread(Ginky);
		clyde_thread = new Thread(Gclyde);

		int ec;
		ec = window_thread->join();
		
		////std::cout << "O jogo foi encerrado\n";
		
		delete window_thread;
		delete keyboard_thread;
		delete pacman_thread;
		delete blinky_thread;
		delete pinky_thread;
		delete inky_thread;
		delete clyde_thread;
		delete game_thread;

		delete window;
		delete handler;
		delete pacman;
		delete blinky;
		delete pinky;
		delete inky;
		delete clyde;
		delete game;
	}

	~Main() {}

private:

	static void printScreen(){
			int i = 0;
			_open = true;
			window = new Window();
			timer_start = 2*FPS;
			while(timer_start > 0){
				window->start();
				timer_start--;
			}
			while(_open){
				window->KeyboardInput();
				if(!_paused){
					if(_death){
						for(i=0;i<11;i++){
							timer_start = 0.1*FPS; //mudar 
							while(timer_start > 0){
								window->death(i);
								timer_start--;
							}
						}
					}else if(_victory){
						timer_start = FPS; //mudar 
						while(timer_start > 0){
							timer_start--;
						}
						window->victory();
						_open = false;
					}else if(_game_over){
						timer_start = FPS; //mudar 
						while(timer_start > 0){
							timer_start--;
						}
						window->game_over();
						_open = false;
					}else{
						_open = window->run();
					}
					tick();
				}
				Thread::yield();
			}
			window_thread->thread_exit(0); // decidir exit code
	}

	static void keyInput(){
			while(_open){
				if(!_paused){
					tm_sem->p();
				}
				_paused = handler->Handler();
				if(!_paused){
					tm_sem->v();
				}
				Thread::yield();
			}
			keyboard_thread->thread_exit(0); // decidir exit code
	}

	static void pacMan(){
		while(_open){
			tm_sem->p(); //down
			pacman->Move();
			tm_sem->v(); //up

			Thread::yield();
		}
		pacman_thread->thread_exit(0);
	}

	static void Gblinky(){
		bool _leave = false;
		while(_open){
			////std::cout << "Gblinky(): rodando\n";
			if(blinky->isInGH() && timer_GH[(int)BLINKY-1]==0){
				if(!_leave){				
					//std::cout << "B Tentou dar down\n";
					blinky->SetMode((Mode)(current_mode%2));
					GH_sem->p();
				}
				//std::cout << " B Conseguiu\n";
				tm_sem->p();
				blinky->Leave_GH();
				tm_sem->v();
				_leave = blinky->isInGH();
				if(!_leave){
					timer_GH[(int)BLINKY-1] = -1;
					GH_sem->v();
				}
			}else{
				tm_sem->p(); //down
				if(timer_mode == 0 || timer_FRIGHTENED == 0){
					blinky->SetMode((Mode)(current_mode%2));
				}
				blinky->Move();
				if(blinky->Crossroad()){
					blinky->CR_Decision();
				}
				tm_sem->v(); //up
			}
			Thread::yield();
		}
		blinky_thread->thread_exit(0);
	}

	static void Gpinky(){
		bool _leave = false;
		while(_open){
			if(pinky->isInGH() && timer_GH[(int)PINKY-1]==0){
				if(!_leave){
					//std::cout << "P Tentou dar down\n";
					pinky->SetMode((Mode)(current_mode%2));
					GH_sem->p();
				}
				//std::cout << "P Conseguiu\n";
				tm_sem->p();
				pinky->Leave_GH();
				tm_sem->v();
				_leave = pinky->isInGH();
				if(!_leave){
					timer_GH[(int)PINKY-1] = -1;
					GH_sem->v();
				}
			}else{
				tm_sem->p(); //down
				if(timer_mode == 0 || timer_FRIGHTENED == 0){
					pinky->SetMode((Mode)(current_mode%2));
				}
				pinky->Move();
				if(pinky->Crossroad()){
					pinky->CR_Decision();
				}
				tm_sem->v(); //up
			}
			Thread::yield();
		}
		pinky_thread->thread_exit(0);
	}

	static void Ginky(){
		bool _leave = false;
		while(_open){
			if(inky->isInGH() && timer_GH[(int)INKY-1]==0){
				if(!_leave){
					//std::cout << "I Tentou dar down\n";
					inky->SetMode((Mode)(current_mode%2));
					GH_sem->p();
				}
				//std::cout << "I Conseguiu\n";
				tm_sem->p();
				inky->Leave_GH();
				tm_sem->v();
				_leave = inky->isInGH();
				if(!_leave){
					timer_GH[(int)INKY-1] = -1;
					GH_sem->v();
				}
			}else{
				tm_sem->p(); //down
				if(timer_mode == 0 || timer_FRIGHTENED == 0){
					inky->SetMode((Mode)(current_mode%2));
				}
				inky->Move();
				if(inky->Crossroad()){
					inky->CR_Decision();
				}
				tm_sem->v(); //up
			}
			Thread::yield();
		}
		inky_thread->thread_exit(0);
	}

	static void Gclyde(){
		bool _leave = false;
		while(_open){
			if(clyde->isInGH() && timer_GH[(int)CLYDE-1]==0){
				//std::cout << "C Tentou dar down\n";
				if(!_leave){
					clyde->SetMode((Mode)(current_mode%2));
					GH_sem->p();
				}
				//std::cout << " C Conseguiu\n";
				tm_sem->p();
				clyde->Leave_GH();
				tm_sem->v();
				_leave = clyde->isInGH();
				if(!_leave){
					timer_GH[(int)CLYDE-1] = -1;
					GH_sem->v();
				}
			}else{
				tm_sem->p(); //down
				if(timer_mode == 0 || timer_FRIGHTENED == 0){
					clyde->SetMode((Mode)(current_mode%2));
				}
				clyde->Move();
				if(clyde->Crossroad()){
					clyde->CR_Decision();
				}
				tm_sem->v(); //up
			}
			Thread::yield();
		}
		clyde_thread->thread_exit(0);
	}

	static void runGame(){
		int i;
		while(_open){
			tm_sem->p(); //down
			if(_death){
				game->Death();
				current_mode = 0;
				_death = false;
			}
			if(game->UpdateDots()){
				timer_FRIGHTENED = 0.5*6*FPS;
			}
			i = game->UpdateGhosts();
			if(i>=0 && timer_GH[i] == -1){
				timer_GH[i] = 0.5*(rand()%7+1)*FPS;
			}
			game->UpdateFruits();
			_victory = game->isVictory();
			_game_over = game->isGameOver();
			if(!_game_over){
				_death = game->isDeath();
			}

			tm_sem->v(); //up
			Thread::yield();
		}
		game_thread->thread_exit(0);
	}

	static void tick(){
		int i;
		if(timer_FRIGHTENED >= 0){
			timer_FRIGHTENED--;
		}else if(timer_mode >= 0){
			timer_mode--;
		}
		if(timer_mode == -1){
			if(current_mode < 7){
				timer_mode = 0.5*mode_periods[current_mode]*FPS;
				current_mode++; 
			}
		}
		for(i=0;i<4;i++){
			if(timer_GH[i] > 0){
				timer_GH[i]--;
			}
		}

		if(timer_start > 0){
			timer_start--;
		}
		Thread::yield();
	}

	private:
		static Thread *window_thread;
		static Thread *keyboard_thread;
		static Thread *pacman_thread;
		static Thread *blinky_thread;
		static Thread *pinky_thread;
		static Thread *inky_thread;
		static Thread *clyde_thread;
		static Thread *game_thread;
		
		static Semaphore *tm_sem;
		static Semaphore *GH_sem;

		static int timer_mode;
		static int mode_periods[7];
		static int current_mode;
		static int timer_GH[4];
		static int timer_FRIGHTENED;
		static int timer_start;

		static Window *window;
		static KeyHandler *handler;
		static Pacman *pacman;
		static Ghost *blinky;  
		static Ghost *pinky;
		static Ghost *inky;
		static Ghost *clyde;
		static Game *game;

		static bool _open;
		static bool _paused;
		static bool _leaving;
		static bool _victory;
		static bool _death;
		static bool _game_over;
};

__END_API

#endif


