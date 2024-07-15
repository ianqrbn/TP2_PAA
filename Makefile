all: tp2

run: tp2
		@./tp2

tp2: main.o estrategias.o tempo.o
		gcc -g main.o estrategias.o tempo.o -o tp2

main.o: main.c
		gcc -c main.c -g

estrategias.o: estrategias.c estrategias.h
		gcc -c estrategias.c -g

tempo.o: tempo.c tempo.h
		gcc -c tempo.c -g

clean:
		rm *.o tp2*
