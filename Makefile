CC=gcc
CFLAGS=-Wall -g

OBJ=main.o 2048_functions.o

all: build

%.o: %.c
	$(CC) -c $< -o $@ $(CFLAGS)

2048: $(OBJ)
	$(CC) $^ -o $@ -lcurses

build: $(OBJ)
	$(CC) $^ -o 2048 -lcurses

run:
	./2048

clean:
	rm -f $(OBJ) 2048
