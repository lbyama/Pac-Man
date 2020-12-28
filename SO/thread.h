#ifndef thread_h
#define thread_h
 
#include "cpu.h"
#include "traits.h"
#include "debug.h"
#include "list.h"
#include "timer.h"
#include <ctime> 
#include <chrono>

__BEGIN_API

class Thread
{
protected:
    typedef CPU::Context Context;
public:

    typedef Ordered_List<Thread> Ready_Queue;

    // Thread State
    enum State {
        RUNNING, // 0
        READY,	// 1
				SUSPENDED, // 2
				WAITING, //3
        FINISHING // 4
    };

    Thread() {
			db<Thread>(TRC) << "Thread::Thread() foi chamada\n";
			_id = -1;
			db<Thread>(TRC) << "Thread::Thread: Thread" << _id << " foi criada\n";
		}

    template<typename ... Tn>
    Thread(void (* entry)(Tn ...), Tn ... an);

    static Thread * running() { return _running; }

    static int switch_context(Thread * prev, Thread * next);

    /*
     * Termina a thread.
     * exit_code é o código de término devolvido pela tarefa (ignorar agora, vai ser usado mais tarde).
     * Quando a thread encerra, o controle deve retornar à main. 
     */  
    void thread_exit (int exit_code);

    int id();

		Context* context();

		State state();

		Ready_Queue::Element * link();

		void update_link();

		void set_state(State state);

		static void insert_queue(Thread * thread, Ready_Queue & fila);

		static void remove_queue(Thread * thread, Ready_Queue & fila);

		/*
		Este método deve suspender a thread em execução até que a thread “alvo” finalize. O inteiro retornado por join() é o argumento recebido por thread_exit(), ou seja, exit_code (novo atributo _exit_code necessário na classe Thread – pergunta: quando o atributo _exit_code deve ser inicializado?). Como tratar a suspensão e o resumo de uma Thread?
		*/
		int join();

		/*
		Suspende a Thread até que resume() seja chamado. Como tratar as Threads suspensas dentro do SO? Deve -se fazer alguma alteração no estado (enum State) da Thread?
		*/
		void suspend();

		/*
		Acorda uma Thread que estava suspensa.
		*/
		void resume();
		

    /*
     * NOVO MÉTODO DESTE TRABALHO.
     * Despachante (dispatcher) de threads. 
     * Executa enquanto houverem threads do usuário.
     * Chama o escalonador para definir a próxima tarefa a ser executada.
     */
    static void dispatcher(); 
		
		/*
		* NOVO MÉTODO PRÓPRIO
		* Escalonador FIFO: Escolhe a thread mais antiga que não seja a main
		*/
		static Thread * proxima();

    /*
     * NOVO MÉTODO DESTE TRABALHO.
     * Realiza a inicialização da class Thread.
     * Cria as Threads main e dispatcher.
     */ 
    static void init(void (*main)(void *));

    /*
     * Devolve o processador para a thread dispatcher que irá escolher outra thread pronta
     * para ser executada.
     */
    static void yield(); 
	
		static void sleep(Ready_Queue & _sleeping);

		static void wakeup(Ready_Queue & _sleeping);

		static void wakeup_all(Ready_Queue & _sleeping);

		static void reschedule();
    /*
     * Destrutor de uma thread. Realiza todo os procedimentos para manter a consistência da classe.
     */ 
    ~Thread();

private:
    int _id;
		int _exit_code;
    Context * volatile _context;
    Ready_Queue::Element _link; 
    volatile State _state;
		Thread * _joined;

    static Thread _main; 
    static Thread _dispatcher;
		static Thread * _running;
		static Ready_Queue _ready;
		static Ready_Queue _suspended;
		
		static int _count; 
		static Context _main_context;
		Ready_Queue *_sleepList;

		static Timer * _timer;
};

template<typename ... Tn>
Thread::Thread(void (* entry)(Tn ...), Tn ... an){
	if(_timer != 0){
			_timer->stop_int();
		}

		db<Thread>(TRC)<<"Thread::Thread(void (* entry)(Tn ...), Tn ... an) foi chamada\n";
		_id = _count;
		_count++;
		_context = new Context(entry,an...);
		_joined = 0;

		new (&_link) Ready_Queue::Element(this,(std::chrono::duration_cast<std::chrono::microseconds>
 (std::chrono::high_resolution_clock::now().time_since_epoch()).count()));

		db<Thread>(INF)<<"Thread::Thread(void (* entry)(Tn ...), Tn ... an): _count = " << _count << "\n";
		db<Thread>(TRC)<<"Thread::Thread(void (* entry)(Tn ...), Tn ... an): Thread " << _id << " foi criada\n";

		insert_queue(this,_ready);
		if(_timer != 0){
			_timer->reset();
			_timer->return_int();
		}

}
__END_API

#endif
