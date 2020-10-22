listsMain:
	gcc -g3 -fsanitize=address -fsanitize=undefined -fno-omit-frame-pointer -Wall -Werror -std=c99 lists-main.c ../ATDs/list.c ../ATDs/list.h ../ATDs/stack.c ../ATDs/stack.h ../util.c ../util.h -o lists-main
run-listsMain:
	./lists-main
hullAlgMain:
	gcc -g3 -fsanitize=address -fsanitize=undefined -fno-omit-frame-pointer -Wall -Werror -std=c99 hullAlg-main.c ../ATDs/list.c ../ATDs/list.h ../ATDs/stack.c ../ATDs/stack.h ../util.c ../util.h ../monotone-chain.c ../monotone-chain.h -o hullAlg-main
run-hullAlgMain:
	./hullAlg-main
