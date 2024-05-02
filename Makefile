CC = gcc
CFLAGS = -Wall -Werror -Wextra
EXEC = tema2
SRC = main.c tree.c tasks_helpers.c

build:
	$(CC) $(CFLAGS) $(SRC) -o $(EXEC)
clean:
	rm $(EXEC)
