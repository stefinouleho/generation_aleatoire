CFLAGS=-g -Wall

run: molecules
	./molecules 10000 3

val: molecules
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./molecules

molecules: molecules.o
	gcc ${CFLAGS} molecules.o -o molecules
	
molecules.o: molecules.c molecules.h
	gcc ${CFLAGS} -c molecules.c

clean:
	rm -f *.o


