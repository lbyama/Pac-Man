#include "cpu.h"
#include <iostream>

__BEGIN_API
 
void CPU::Context::save()
{
		db<CPU>(TRC)<<"CPU::Context::Save() foi chamada\n";
    setcontext(&_context);
}

void CPU::Context::load()
{ 
		db<CPU>(TRC)<<"CPU::Context::Load() foi chamada\n";
    getcontext(&_context);
}

CPU::Context::~Context()
{
		db<CPU>(TRC)<<"CPU::Context::~Context() foi chamada\n";
		if(_stack != 0 ){
			delete[] _stack;
    	_stack = 0;
		}
}

void CPU::switch_context(Context *from, Context *to)
{
		db<CPU>(TRC)<<"CPU::Context::switch_context() foi chamada\n";
		swapcontext(&from->_context, &to->_context);	
}

int CPU::xadd(volatile int & number, int add){
	int val = add;
	__asm__ __volatile__("lock xadd %0, %2":"=a"(val):"a"(val),"m"(number) : "memory");
	return val;
}

__END_API
