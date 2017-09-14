CC=gcc
O_FILES=SPTicTacToe.o SPTicTacToeGameWin.o SPTicTacToeGUIManager.o SPTicTacToeMainWin.o main.o
C_FLAGS=-std=c99 -Wall -Wextra -g

all: ttt

ttt: $(O_FILES)
	$(CC) -o $@ $(C_FLAGS) $^ -L/usr/local/lib/sdl_2.0.5/lib -Wl,-rpath,/usr/local/lib/sdl_2.0.5/lib -Wl,--enable-new-dtags -lSDL2 -lSDL2main

%.o: %.c %.h
	$(CC) -c $< $(C_FLAGS) -I/usr/include/SDL2 -D_REENTRANT
#	$(CC) -c $< $(C_FLAGS) -I/usr/local/lib/sdl_2.0.5/include/SDL2 -D_REENTRANT


main.o: main.c
	$(CC) -c $< $(C_FLAGS) -I/usr/include/SDL2 -D_REENTRANT
#	$(CC) -c $< $(C_FLAGS) -I/usr/local/lib/sdl_2.0.5/include/SDL2 -D_REENTRANT
.PHONY: clean

clean:
	rm -rf *.o chessprog
