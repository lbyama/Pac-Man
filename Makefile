IDIR =.
CC=g++
LDLIBS =  -lsfml-graphics -lsfml-window -lsfml-system -lm  -lpng
CFLAGS=-I$(IDIR) -g -Wextra

LDFLAGS= $(CFLAGS)

ODIR=.
LIBS= $(LDLIBS) $(LDFLAGS)

_DEPS = window.h main_class.h character.h pacman.h ghost.h game.h tilemap.h enum.h keypressed.h keyhandler.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

SDIR = SO

_SO = thread.h system.h semaphore.h cpu.h debug.h timer.h traits.h
SO = $(patsubst %,$(SDIR)/%,$(_SO))

_OBJ = main.o window.o main_class.o thread.o system.o semaphore.o cpu.o debug.o timer.o character.o pacman.o ghost.o game.o tilemap.o keypressed.o keyhandler.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

$(ODIR)/%.o: %.c $(DEPS)
	$(CC) -std=c++14 -c -o $@ $< $(CFLAGS) -Wextra

$(ODIR)/%.o: %.c $(SO)
	$(CC) -std=c++14 -c -o $@ $< -Wextra

main: $(OBJ)
	$(CC) -std=c++14 -o $@ $^ $(CFLAGS) $(LIBS)

cpu.o: SO/cpu.cc
	g++ -c $< -o $@ -Wall -std=c++17 -g
system.o: SO/system.cc
	g++ -c $< -o $@ -Wall -std=c++17 -g
timer.o: SO/timer.cc
	g++ -c $< -o $@ -Wall -std=c++17 -g
thread.o: SO/thread.cc
	g++ -c $< -o $@ -Wall -std=c++17 -g
semaphore.o: SO/semaphore.cc
	g++ -c $< -o $@ -Wall -std=c++17 -g
debug.o: SO/debug.cc
	g++ -c $< -o $@ -Wall -std=c++17 -g
main_class.o: main_class.cc
	g++ -c $< -o $@ -Wall -std=c++17 -g

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~ 
	
valgrind:
	valgrind --tool=memcheck --leak-check=yes ./main
