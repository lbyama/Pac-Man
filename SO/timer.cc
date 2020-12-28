#include "timer.h"
 
__BEGIN_API

/*
*Construtor que recebe o período (em us) para realizar *as interrupções do Timer e um ponteiro de
*função que irá ser chamada para tratar a interrupção. *Function é definida na própria classe
*Timer. 
*/
Timer::Timer(const unsigned int period, const Function * handler){
	_period = period;
	_handler = handler;

	timer.it_interval.tv_sec = 0;
	timer.it_interval.tv_usec = _period; //seta como não periodico
	timer.it_value.tv_sec = 0;
	timer.it_value.tv_usec = _period; //seta timer inicial

	action.sa_handler = signal(SIGALRM, _handler); //seta interrupcao alarme

	setitimer (ITIMER_REAL, &timer, 0);//inicia o timer
}

void Timer::stop_int(){
	action.sa_handler = signal(SIGALRM, SIG_IGN); 
}
void Timer::return_int(){
	action.sa_handler = signal(SIGALRM, _handler);
}

void Timer::set_time(const unsigned int period){
	setitimer (ITIMER_REAL, &timer, 0);//reseta o timer
	_period = period;

	timer.it_interval.tv_usec = _period; //seta como periodico
	timer.it_value.tv_usec = _period; //seta timer inicial

	setitimer (ITIMER_REAL, &timer, 0);//inicia o timer
}

/*
Este método deve resetar a contagem do Timer.
*/
void Timer::reset(){
	setitimer (ITIMER_REAL, &timer, 0);//reseta o timer
}

__END_API
