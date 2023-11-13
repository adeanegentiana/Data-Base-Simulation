CC=gcc
CFLAGS=-Wall -Wextra -g
SRC=tema1.c
OBJS=little_functions.o data_manipulation.o data_definition.o data_query.o


build: tema1


tema1: $(SRC) $(OBJS) structures.h functions.h little_functions.h
	$(CC) $(CFLAGS) $(SRC) $(OBJS) -o $@

data_manipulation.o: data_manipulation.c
	$(CC) $(CFLAGS) $^ -c

data_definition.o: data_definition.c
	$(CC) $(CFLAGS) $^ -c

data_query.o: data_query.c
	$(CC) $(CFLAGS) $^ -c

little_functions.o: little_functions.c little_functions.h
	$(CC) $(CFLAGS) $< -c

run:
	python checker.py

.PHONY: clean

clean:
	rm -f *.o tema1
