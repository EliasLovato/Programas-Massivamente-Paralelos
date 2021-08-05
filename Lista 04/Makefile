all:	prog prog2

prog: prog.o mysecond.o
	gcc -fopenmp -o prog prog.o mysecond.o -lm

prog2: prog2.o mysecond.o
	gcc -fopenmp -o prog2 prog2.o mysecond.o -lm

prog.o: prog.c
	gcc -fopenmp -c prog.c

prog2.o: prog2.c
	gcc -fopenmp -c prog2.c

mysecond.o: mysecond.c
	gcc -c mysecond.c

clean:
	rm -f *.o prog prog2
