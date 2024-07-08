all: tp2

run: tp2
		@./tp2

tp2: main.o estrategias.o
		gcc -g main.o estrategias.o -o tp2

main.o: main.c
		gcc -c main.c -g

estrategias.o: estrategias.c estrategias.h
		gcc -c estrategias.c -g

clean:
		rm *.o tp2*
