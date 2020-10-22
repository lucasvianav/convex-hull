all:
	gcc -Wall -Werror -std=c99 main.c ATDs/list.c ATDs/stack.c monotone-chain.c util.c -o main -lm
run:
	./main