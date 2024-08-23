CC=gcc
CCFLAGS=-g -lraylib -lGL -lm -lpthread -ldl -lrt -lX11
SRC=./src/main.c

all:    build

.PHONY: all main

build: ./**/*.c ./**/*.h
	$(shell mkdir -p ./build)
	@$(CC) $(SRC) $(CCFLAGS) -o ./build/game

run: build
	@./build/game

clean:
	@rm -rf ./build