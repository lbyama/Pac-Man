#ifndef timer_h
#define timer_h
 
#include "traits.h"
#include "debug.h"
#include <signal.h>
#include <sys/time.h>

__BEGIN_API

class Timer
{
public:
    typedef void (Function)(int);

    /*
		*Construtor que recebe o período (em us) para realizar *as interrupções do Timer e um ponteiro de
		*função que irá ser chamada para tratar a interrupção. *Function é definida na própria classe Timer. 
		*/
    Timer(const unsigned int period, const Function * handler);
    /*
		Este método deve resetar a contagem do Timer.
		*/
	void stop_int();
	void return_int();
  void set_time(const unsigned int period);
  void reset();

private:
    // estrutura que define um tratador de sinal
    struct sigaction action;
    // estrutura de inicialização to timer
    struct itimerval timer;
    unsigned int _period;
    Function *_handler;
};

__END_API

#endif
