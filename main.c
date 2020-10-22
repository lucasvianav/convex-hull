#include <stdio.h>
#include <stdlib.h>
#include "util.h"
#include "./ATDs/stack.h"
#include "./ATDs/list.h"
#include "monotone-chain.h"
#include <math.h>


int main(){

    // Registra a quantidade total de pontos
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

    // Registra a partir de que lugar será iniciada a impressão e qual o sentido
    char inicio_impressao[1];
    int sentido_impressao;

    scanf("%s",inicio_impressao);
    scanf("%d",&sentido_impressao);


    // Chama a função que determina os pontos do fecho convexo e calcula a porcentagem de pontos nele
    list* fecho = convexHull(lista_pontos); 
    float porcentagem_fecho = (float)(((float)100 *list_getLength(fecho))/(list_getLength(lista_pontos)));


    
    // Switch case referente ao ponto que a impressão será iniciada
    switch(inicio_impressao[0]){

        case 'L':
        if(sentido_impressao == 0){
            lista_impressao_horaria(fecho,indice_esquerda_lista(fecho));
        }

        else if(sentido_impressao == 1){
            lista_impressao_anti_horaria(fecho,indice_esquerda_lista(fecho));
        }
            
        break;
        
        case 'R':

        if(sentido_impressao == 0){
            lista_impressao_horaria(fecho,indice_direita_lista(fecho));
        }

        else if(sentido_impressao == 1){
            lista_impressao_anti_horaria(fecho,indice_direita_lista(fecho));
        }
        break;
        
        case 'D':

        if(sentido_impressao == 0){
           lista_impressao_horaria(fecho,indice_baixo_lista(fecho));
        }

        else if(sentido_impressao == 1){
            lista_impressao_anti_horaria(fecho,indice_baixo_lista(fecho));
        }
        
        break;
        
        case 'U':

        if(sentido_impressao == 0){
            lista_impressao_horaria(fecho,indice_cima_lista(fecho));
        }

        else if(sentido_impressao == 1){
           lista_impressao_anti_horaria(fecho,indice_cima_lista(fecho));
        }
        
        break;
        
        default:
        break;
    }


    printf("%.2f\n",porcentagem_fecho);

    return 0;
}
