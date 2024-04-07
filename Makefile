run: build
	./tema1

build: main.c train_list.c train_list.h command_queue.c command_queue.h
	gcc main.c train_list.c command_queue.c -o tema1 -std=c99

clean:
	rm -rf tema1