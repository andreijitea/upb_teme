CC = gcc
CFLAGS = -Wall -Werror -Wextra -std=c99
EXEC = tema3
SRC = main.c task1.c task2.c

build:
	touch $(EXEC).in
	$(CC) $(CFLAGS) $(SRC) -o $(EXEC)

clean:
	rm $(EXEC)