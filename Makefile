all:
	gcc  -g3 -fsanitize=address -fsanitize=undefined -fno-omit-frame-pointer -Wall -Werror -std=c99 main.c ./ADTs/list.c ./ADTs/list.h ./ADTs/stack.c ./ADTs/stack.h monotone-chain.c monotone-chain.h util.c util.h -o main
timeMain:
	gcc  -g3 -fsanitize=address -fsanitize=undefined -fno-omit-frame-pointer -Wall -Werror -std=c99 main.c ./ADTs/list.c ./ADTs/list.h ./ADTs/stack.c ./ADTs/stack.h ./time/tempo.c ./time/tempo.h monotone-chain.c monotone-chain.h util.c util.h -o main
run:
	./main
