all:
	gcc -g3 -fsanitize=address -fsanitize=undefined -fno-omit-frame-pointer -Wall -Werror -std=c99 main.c ./ATDs/list.c ./ATDs/list.h ./ATDs/stack.c ./ATDs/stack.h monotone-chain.c monotone-chain.h util.c util.h -o main
run:
	./main
