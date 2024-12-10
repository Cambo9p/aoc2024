CC = gcc


CFLAGS = -Wall -Werror -lpthread 

SRC = src/main.c src/lib.c
#SRC = src/*.c
OBJ = $(SRC:.c=.o)

TARGET = aoc

all: $(TARGET)


$(TARGET): $(OBJ)
	$(CC) -o $@ $^ 

clean:
	rm -f $(OBJ) $(TARGET)

test:
	gcc -std=c99 -g -o test src/main.o src/lib.o
