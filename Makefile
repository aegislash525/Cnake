CC=cc
DEBUG=-g -fsanitize=address
CFLAGS=-Wall -Werror -Wextra -O2 -pedantic -std=c99
LFLAGS=-lncurses
OUT_DIR=./bin

MAIN=./src/main.c
FOOD=./src/food/food.c
SNAKE=./src/snake/snake.c

all: main

main:
	$(CC) $(CFLAGS) $(MAIN) $(FOOD) $(SNAKE) -o $(OUT_DIR)/snake_game.out $(LFLAGS)

test:
	$(CC) $(CFLAGS) $(DEBUG) $(MAIN) $(FOOD) $(SNAKE) -o $(OUT_DIR)/test.out $(LFLAGS)
	@./bin/test.out

clean:
	@echo "Cleaning"
	@rm -rf ./$(OUT_DIR)/*
	@echo "All is clean now!"

.PHONY: all clean
