all: vector.o test.o
	gcc test.o vector.o -o test.out
functions.o: vector.c
	gcc -c vector.c -o vector.o
main_r.o: test.c
	gcc -c test.c -o test.o
clean:
	$(RM) test.out
	$(RM) vector.o
	$(RM) test.o
