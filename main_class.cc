#include "main_class.h"

__BEGIN_API

Thread *Main::window_thread = 0;
Thread *Main::keyboard_thread = 0;
Thread *Main::pacman_thread = 0;
Thread *Main::blinky_thread;
Thread *Main::pinky_thread;
Thread *Main::inky_thread;
Thread *Main::clyde_thread;
Thread *Main::game_thread;

Semaphore *Main::tm_sem = 0;
Semaphore *Main::GH_sem = 0;
 
int Main::timer_mode = 0;
int Main::mode_periods[7] = {7,20,7,20,5,20,5};
int Main::current_mode = 0;
int Main::timer_GH[4] = {-1,-1,-1,-1};
int Main::timer_FRIGHTENED = 0;
int Main::timer_start = 3;
				
Window *Main::window = 0;
KeyHandler *Main::handler;
Pacman *Main::pacman;
Ghost *Main::blinky;  
Ghost *Main::pinky;
Ghost *Main::inky;
Ghost *Main::clyde;
Game *Main::game;

bool Main::_open = false;
bool Main::_paused = false;
bool Main::_leaving = false;
bool Main::_victory = false;
bool Main::_death = false;
bool Main::_game_over = false;

__END_API 

