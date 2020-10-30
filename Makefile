all:
	gcc  -g3 -fsanitize=address -fsanitize=undefined -fno-omit-frame-pointer -Wall -Werror -std=c99 main.c ./ADTs/list.c ./ADTs/list.h ./ADTs/stack.c ./ADTs/stack.h monotone-chain.c ./time/tempo.c monotone-chain.h util.c util.h -o main
run:
	./main
