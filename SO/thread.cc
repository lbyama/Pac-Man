#include "thread.h"
 
__BEGIN_API
    int Thread::_count = 0;
		Thread * Thread::_running = 0;
		Timer * Thread::_timer = 0;

    Thread Thread::_main; 
    CPU::Context Thread::_main_context; 
    Thread Thread::_dispatcher;
    Thread::Ready_Queue Thread::_ready;
		Thread::Ready_Queue Thread::_suspended;

    int Thread::switch_context(Thread * prev, Thread * next){
			db<Thread>(TRC)<<"Thread::switch_context() foi chamada\n";

      if(next == 0){
				db<Thread>(ERR)<< "Thread::switch_context: mudança de Thread falhou\n";
        return -1;
      }
			next->set_state(RUNNING);
			_running = next;

			db<Thread>(INF)<<"Thread::switch_context(): _running = * Thread " << _running->id() << "\n";

			db<Thread>(TRC)<<"Thread::switch_context(): Thread " << prev->id() << " => Thread " << next->id() << "\n";
			if(_timer != 0 ){
				_timer->reset();
				_timer->return_int();
			}
			CPU::switch_context(prev->context(),next->context());
      return 0;
    }

    void Thread::thread_exit (int exit_code){
			db<Thread>(TRC)<<"Thread::exit() foi chamada\n";
			if(_timer != 0){
				_timer->stop_int();
			}
			set_state(FINISHING);

			_exit_code = exit_code;
			db<Thread>(TRC)<<"Thread::exit: Thread " << _id << " saiu\n";

			if(_joined != 0){
				_joined->resume();
			}else{
				Thread::yield();
			}
    }

    Thread::Context* Thread::context(){
      return _context;
    }

    int Thread::id(){
      return _id;
    }

    Thread::State Thread::state(){
	    return _state;
    }

    void Thread::set_state(Thread::State state){
	    db<Thread>(TRC)<<"Thread::set_state(): Thread " << this->id() << " => ";

	    switch(state){
		    case 0:
			    db<Thread>(TRC)<<"RUNNING\n";
			    break;
		    case 1:
			    db<Thread>(TRC)<<"READY\n";
			    break;
		    case 2:
			    db<Thread>(TRC)<<"SUSPENDED\n";
			    break;
		    case 3:
			    db<Thread>(TRC)<<"WAITING\n";
			    break;
		    case 4:
			    db<Thread>(TRC)<<"FINISHING\n";
			    break;
	    }
	    _state = state;
    }

    Thread::Ready_Queue::Element* Thread::link(){
	    return &_link;
    }

    void Thread::update_link(){
	    db<Thread>(TRC)<<"Thread::update_link() foi chamada\n";

	    link()->rank(std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now().time_since_epoch()).count());
	    db<Thread>(TRC)<<"Thread::update_link: Thread " << id() << " teve seu link atualizado \n";
    }

    void Thread::insert_queue(Thread * thread,Thread::Ready_Queue & fila){
	    db<Thread>(TRC)<<"Thread::insert_queue() foi chamada\n";
	    
	    if(thread == 0){
			    db<Thread>(ERR)<<"Thread::insert_queue() foi chamada com ponteiro nulo\n";
			    return;
	    }
	    if(thread == &_dispatcher){
		    fila.insert_head(thread->link());
	    }else{
		    thread->update_link();
		    fila.insert(thread->link());
	    }

	    db<Thread>(TRC)<<"Thread::insert_queue: Thread " << thread->id() << " foi inserida na ";
	    if(&fila == &_ready){
		    db<Thread>(TRC)<<" _ready\n";
		    thread->set_state(READY);
	    }else if (&fila == &_suspended){
		    db<Thread>(TRC)<<" _suspended\n";
		    thread->set_state(SUSPENDED);
	    }else{
		    db<Thread>(TRC)<<" _sleeping\n";
		    thread->set_state(WAITING);
	    }
    }

	void Thread::remove_queue(Thread * thread, Thread::Ready_Queue & fila){
		db<Thread>(TRC)<<"Thread::remove_queue() foi chamada\n";

		fila.remove(thread->link());
		db<Thread>(TRC)<<"Thread::remove_queue: Thread " << thread->id() << " foi removida da ";
		if(&fila == &_ready){
			db<Thread>(TRC)<<" _ready\n";
		}else if (&fila == &_suspended){
			db<Thread>(TRC)<<" _suspended\n";
		}else{
			db<Thread>(TRC)<<" _sleeping\n";
		}
	}


	int Thread::join(){
		db<Thread>(TRC)<<"Thread::join() foi chamada\n";
		if(_timer != 0){
			_timer->stop_int();
		}

		if(this == _running){
			db<Thread>(ERR)<<"Thread::join(): Thread " << this->id() << " tentou dar join() em si mesma\n";
			return -1;
		}
		if(this->_joined != 0){
			db<Thread>(ERR)<<"Thread::join(): Thread " << this->id() << " ja recebeu join de outra thread\n";
			return -1;
		}
		db<Thread>(TRC)<<"Thread::join(): Thread " << _running->id() << " deu join na Thread " << this->id() << "\n";
		suspend();//suspender a thread que está rodando

		return _exit_code; 
	}

	void Thread::suspend(){
		db<Thread>(TRC)<<"Thread::suspend() foi chamada\n";

		//_running->set_state(SUSPENDED);
		this->_joined = _running;

		insert_queue(_running,_suspended);// colocar na lista de suspensas
		
		db<Thread>(TRC)<<"Thread::suspend(): Thread " << _running->id() << " foi suspendida\n";

		yield();
	}

	void Thread::resume(){
		db<Thread>(TRC)<<"Thread::resume() foi chamada\n";
		
		remove_queue(this,_suspended);

		db<Thread>(TRC)<<"Thread::resume(): Thread " << this->id() << " foi acordada\n";
		switch_context(_running,this);
	}

		/*
     * NOVO MÉTODO DESTE TRABALHO.
     * Daspachante (disptacher) de threads. 
     * Executa enquanto houverem threads do usuário.
     * Chama o escalonador para definir a próxima tarefa a ser executada.
     */
	void Thread::dispatcher(){
		while(_ready.size()>0){
			//int a;
			//std::cin >> a;
			db<Thread>(TRC)<<"Thread::dispatcher() foi chamada\n";
			Thread *prox = proxima(); // acha proxima
			Thread *ant = _running;
			
			remove_queue(prox,_ready); //tira a prox da lista de ready
			insert_queue(&_dispatcher,_ready); //se insere na lista de ready
			switch_context(ant,prox);
		}
		switch_context(&_dispatcher,&_main);
	}

	Thread * Thread::proxima(){
		db<Thread>(INF) << "Thread::proxima() foi chamada\n";
		if(_ready.size() == 0){
			return 0;
		}
		return _ready.head()->object();
	}

		/*
     * NOVO MÉTODO DESTE TRABALHO.
     * Realiza a inicialização da class Thread.
     * Cria as Threads main e dispatcher.
     */ 
	void Thread::init(void (*main)(void *)){
		db<Thread>(TRC) << "Thread::init foi chamada\n";
		std::string name;
		name = "main";
		new (&_main_context) Context(); //placement new
		
		new (&_main) Thread(main,(void *)name.data());
		db<Thread>(TRC) << "Thread::init: Thread main foi criada\n";
		
		remove_queue(&_main,_ready);

		_running = &_main;

		if(Traits<Thread>::timer_p){
			_timer = new Timer(Traits<Thread>::QUANTUM,(void(*)(int))reschedule);
		}else{
			new (&_dispatcher) Thread(dispatcher); 
			db<Thread>(TRC) << "Thread::init: Thread dispatcher foi criada\n";	
		}

		CPU::switch_context(&_main_context,_main.context());
	}

		/*
     * Devolve o processador para a thread dispatcher que irá escolher outra thread pronta
     * para ser executada.
     */
	void Thread::yield(){
		db<Thread>(TRC)<<"Thread::yield() foi chamada pela Thread " << _running->id() << "\n";
		Thread *prox = proxima();
		if(prox != 0){
			if(_running->state() == RUNNING && _running != &_main){ //se ela n estiver finishing, suspended ou waiting e não for a main
				insert_queue(_running,_ready); // se insere no ready
			}
			remove_queue(prox,_ready);
			switch_context(_running,prox);
		}
		if(_ready.size() == 0 && _timer != 0){
			delete _timer;
		}
	}
		
	void Thread::sleep(Ready_Queue & _sleeping){
		db<Thread>(TRC)<<"Thread::sleep() foi chamada\n";
		if(_timer != 0){
			_timer->stop_int();
		}
		insert_queue(_running,_sleeping);//colocar pra dormir
		_running->_sleepList = &_sleeping;
		yield();
	}

	void Thread::wakeup(Ready_Queue & _sleeping){
		db<Thread>(TRC)<<"Thread::wakeup() foi chamada\n";
		if(_timer != 0){
			_timer->stop_int();
		}
		if(_sleeping.size() != 0){
			Thread * thread = _sleeping.head()->object();
			Thread * prev = _running;

			remove_queue(thread, _sleeping);
			insert_queue(prev,_ready);
			
			thread->_sleepList = 0;

			switch_context(prev,thread);
		}
	}
	/* condition variable: broadcast?
	*/
	void Thread::wakeup_all(Ready_Queue & _sleeping){
		db<Thread>(TRC) << "Thread::wakeup_all(): foi chamada\n";
		Thread * thread = 0;
		while(_sleeping.size()>0){
			thread = _sleeping.tail()->object();
			remove_queue(thread, _sleeping);
			thread->set_state(READY);
			thread->_sleepList = 0;
			_ready.insert_head(thread->link());
		}
		yield();
	}

    // realizar o reescalonamento do sistema
	void Thread::reschedule(){
		if(_timer == 0){
			db<Thread>(ERR) << "Thread::Reschedule() foi chamado sem objetos instanciados";
		}else{
			_timer->stop_int();
			yield();
		} 
	}
    
			/*
     * Destrutor de uma thread. Realiza todo os procedimentos para manter a consistência da classe.
     */ 
	Thread::~Thread(){
		db<Thread>(TRC) << "Thread~Thread() foi chamada\n";
		if(_timer != 0){
			_timer->stop_int();
		}

		if(_sleepList != 0){
			remove_queue(this, *this->_sleepList);
		}

		delete _context;
		_context = 0;	

		db<Thread>(TRC) << "Thread::~Thread: Thread " << id() << " foi destruida\n";
		if(_timer != 0){
			_timer->reset();
			_timer->return_int();
		}
	}

__END_API
