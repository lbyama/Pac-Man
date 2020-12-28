#include "system.h"

__BEGIN_API 

void System::init(void (*main)(void *)){
	db<System>(TRC)<<"System::init foi chamada\n";
  setvbuf (stdout, 0, _IONBF, 0); 
	db<System>(INF) << "System::init: buffer de saida foi desativado\n";
	Thread::init(main);
}

__END_API
