build: main.o train.o
	gcc main.o train.o -o tema1

main.o: main.c
	gcc -c main.c

train.o: train.c train.h
	gcc -c train.c
clean:
	rm app