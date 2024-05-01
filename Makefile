run:
	./tema2
build:
	gcc -Wall -o tema2 main.c tree.c tasks_helpers.c
clean:
	rm tema2
