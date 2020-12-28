#ifndef traits_h
#define traits_h
 
#define __BEGIN_API             namespace SOLUTION {
#define __END_API               }
#define __USING_API            using namespace SOLUTION;

__BEGIN_API

class CPU; 
class Thread; 
class Debug;
class System;
class Lists;
class Semaphore;

template<typename T>
struct Traits {
	static const bool debugged = false;
};

template<> struct Traits<CPU> : public Traits<void>
{
    static const unsigned int STACK_SIZE = 64512;
		//static const unsigned int STACK_SIZE = 8388608;
		static const bool debugged = false;
};

template<> struct Traits<System> 
{
 static const bool debugged = false;
};

template<> struct Traits<Thread> : public Traits<void>
{
 static const bool debugged = false;
 static const bool timer_p = false;
 static const int QUANTUM = 15000;
};

template<> struct Traits<Lists> 
{
 static const bool debugged = false;
};

template<> struct Traits<Semaphore> 
{
 static const bool debugged = false;
};

template<> struct Traits<Debug>: public Traits<void>
{
  static const bool error = false;
  static const bool warning = false;
  static const bool info = true;
  static const bool trace = true;
};

/*
FAZER OPÇÃO DE HABILITAR PREEMPÇÃO POR TEMPO
Definir Quantum
*/

__END_API

#endif
