build: main.o train_list.o command_queue.o
	gcc main.o train_list.o command_queue.o -o tema1

main.o: main.c
	gcc -c main.c

train_list.o: train_list.c train_list.h
	gcc -c train_list.c

command_queue.o: command_queue.c command_queue.h
	gcc -c command_queue.c
clean:
	rm app