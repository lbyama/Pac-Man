#ifndef cpu_h
#define cpu_h 

#include <ucontext.h>
#include <iostream>
#include "traits.h"
#include "debug.h"

__BEGIN_API

class CPU
{
    public:

        class Context
        {
        private:
            static const unsigned int STACK_SIZE = Traits<CPU>::STACK_SIZE;
        public:
            Context() {
								db<CPU>(TRC)<<"CPU::Context::Context() foi chamada\n";
                _stack = 0;
                load();                
            }

            template<typename ... Tn>
            Context(void (* func)(Tn ...), Tn ... an){
								db<CPU>(TRC)<<"CPU::Context::Context(void (* func)(Tn ...), Tn ... an) foi chamada\n";
                getcontext(&_context);
                _stack = new char[STACK_SIZE];
                _context.uc_stack.ss_sp = &_stack;
                _context.uc_stack.ss_size = STACK_SIZE;
                _context.uc_link = 0;
                makecontext(&_context, (void(*)())func, sizeof ...(an), an...);
            };

            ~Context();

            void save();
            void load();

        private:            
            char *_stack;
        public:
            ucontext_t _context;
        };

    public:
			static int xadd(volatile int & number, int add);

      static void switch_context(Context *from, Context *to);

};

__END_API

#endif

