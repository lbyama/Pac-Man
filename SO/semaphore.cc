#include "semaphore.h"
 
__BEGIN_API

Semaphore::Semaphore(int v){
	_v = v;	
}

Semaphore::~Semaphore(){
	wakeup_all();
}

void Semaphore::p(){//down, sleep
	db<Semaphore>(TRC)<<"Semaphore::p() foi chamada\n";

	if(fdec(_v) < 1){
		sleep();
	}

}

void Semaphore::v(){ //up, wakeup
db<Semaphore>(TRC)<<"Semaphore::v() foi chamada\n";
	if(finc(_v) < 0){
		wakeup();
	}	
}

// Atomic operations
//retornar valor anterior
int Semaphore::finc(volatile int & number){
	db<Semaphore>(INF)<<"Semaphore::finc() foi chamada\n";
	
	return CPU::xadd(number,1);
}

int Semaphore::fdec(volatile int & number){
	db<Semaphore>(INF)<<"Semaphore::fdec() foi chamada\n";
	
	return CPU::xadd(number,-1);
}

// Thread operations
void Semaphore::sleep(){
	db<Semaphore>(TRC)<<"Semaphore::sleep() foi chamada\n";
	Thread::sleep(_sleeping);
}

void Semaphore::wakeup(){
	db<Semaphore>(TRC)<<"Semaphore::wakeup() foi chamada\n";
	Thread::wakeup(_sleeping);
}

void Semaphore::wakeup_all(){
	db<Semaphore>(TRC)<<"Semaphore::wakeup_all() foi chamada\n";
	Thread::wakeup_all(_sleeping);
}

__END_API
