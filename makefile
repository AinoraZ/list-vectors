all: vector.o main.o
	gcc main.o vector.o -o test.out
functions.o: vector.c
	gcc -c vector.c -o vector.o
main_r.o: main.c
	gcc -c main.c -o main.o
clean:
	$(RM) test.out
	$(RM) vector.o
	$(RM) main.o
