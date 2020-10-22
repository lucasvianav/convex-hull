// gcc -Wall -Werror -std=c99 teste.c ATDs/list.c ATDs/stack.c monotone-chain.c util.c -o teste -lm
#include <stdio.h>
#include <stdlib.h>
#include "util.h"
#include "./ATDs/stack.h"
#include "./ATDs/list.h"
#include "monotone-chain.h"
#include <math.h>

int main(){


    int num_pontos;
    scanf("%d",&num_pontos);

    list* lista_pontos = list_create();
    int i;
    
    // Registra a lista de pontos e insere os nós
    for(i = 0; i < num_pontos; i++){

        float x,y;
        scanf("%f %f",&x,&y);

        point ponto_atual = {x,y};
        list_append(lista_pontos,ponto_atual);
    }

    printf("Mais de baixo: %d\n",indice_baixo_lista(lista_pontos));
    printf("Mais de cima: %d\n",indice_cima_lista(lista_pontos));
    printf("Mais da esquerda: %d\n",indice_esquerda_lista(lista_pontos));
    printf("Mais da direita: %d\n",indice_direita_lista(lista_pontos));

    return 0;
}