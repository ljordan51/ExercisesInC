util.o: util.c util.h
	gcc -c util.c

trout.o: trout.c trout.h util.h
	gcc -c trout.c

main.o: main.c trout.h util.h
	gcc -c main.c

trout: main.o trout.o util.o
	gcc main.o trout.o util.o -Wall -o trout