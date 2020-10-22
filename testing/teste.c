// gcc -Wall -Werror -std=c99 teste.c ATDs/list.c ATDs/stack.c monotone-chain.c util.c -o teste -lm
#include <stdio.h>
#include <stdlib.h>
#include "../util.h"
#include "../ATDs/stack.h"
#include "../ATDs/list.h"
#include "../monotone-chain.h"
#include <math.h>

float arctg_p(point p){
    return atan(p.y/p.x);
}

int indice_esquerda(point* p,int tamanho){
    
    int mais_esquerda = 0;

    for(int i = 0; i < tamanho; i++){
        if(p[i].x < p[mais_esquerda].x){
            mais_esquerda = i;
        }
        else if(p[i].x == p[mais_esquerda].x){
            if(p[i].y < p[mais_esquerda].y){
                mais_esquerda = i;
            }
        }
    }
    return mais_esquerda;
}

int indice_direita(point* p, int tamanho){

    int mais_direita = 0;

    for(int i = 0; i < tamanho; i++){
        if(p[i].x > p[mais_direita].x){
            mais_direita = i;
        }
        else if(p[i].x == p[mais_direita].x){
            if(p[i].y < p[mais_direita].y){
                mais_direita = i;
            }
        }
    }
    return mais_direita;
    
}

int indice_cima(point* p,int tamanho){
    int mais_acima = 0;

    for(int i = 0; i < tamanho; i++){
        if(p[i].y > p[mais_acima].y){
            mais_acima = i;
        }
        else if(p[i].y == p[mais_acima].y){
            if(p[i].x < p[mais_acima].x){
                mais_acima = i;
            }
        }
    }
    return mais_acima;
}

int indice_baixo(point* p,int tamanho){
    int mais_abaixo = 0;

    for(int i = 0; i < tamanho; i++){
        if(p[i].y < p[mais_abaixo].y){
            mais_abaixo = i;
        }
        else if(p[i].y == p[mais_abaixo].y){
            if(p[i].x < p[mais_abaixo].x){
                mais_abaixo = i;
            }
        }
    }
    return mais_abaixo;
    
}


// Ordena em sentido horário
void quick(point* v, int c, int f){
    
    if(c >= f){
        return;
    }

    int m = (c + f)/2;
    point pivo = v[m];
    int i = c;
    int j = f;

    while(1){

        while(arctg_p(v[i]) < arctg_p(pivo)){
            i++;
        }
        while(arctg_p(v[j]) > arctg_p(pivo)){
            j--;
    
        }

        if(j <= i) break;

        point tmp = v[i];
        v[i] = v[j];
        v[j] = tmp;
        
        i++;
        j--;
    }
    quick(v,c,m);
    quick(v,m+1,f);
}

int tamanho = 4;

point pontos[4] = {{3,5},{6,2},{2,-2},{1,0}};

int main(){

    char c;
    int sentido;
    scanf("%c %d",&c,&sentido);

    quick(pontos,0,3);

    
    for(int i = 0; i < 4; i++){
        printf("x:%.2f y:%.2f\n",pontos[i].x,pontos[i].y);
    }
    

    
    printf("Esquerda: %d\n",indice_esquerda(pontos,4));
    printf("Direita: %d\n",indice_direita(pontos,4));
    printf("Baixo: %d\n",indice_baixo(pontos,4));
    printf("Cima: %d\n",indice_cima(pontos,4));


    
    switch(c){

        case 'L':
        
        if(sentido == 0){
            
            for(int i = indice_esquerda(pontos,tamanho); i < tamanho ; i++){
                printf("%.2f %.2f\n",pontos[i].x,pontos[i].y);
            }

            for(int i = 0; i <= indice_esquerda(pontos,tamanho) - 1 ; i++){
                printf("%.2f %.2f\n",pontos[i].x,pontos[i].y);
            }
        }

        else if(sentido == 1){

            for(int i = indice_esquerda(pontos,tamanho); i >= 0 ; i--){
                printf("%.2f %.2f\n",pontos[i].x,pontos[i].y);
            }

            for(int i = 3; i > indice_esquerda(pontos,tamanho); i--){
                printf("%.2f %.2f\n",pontos[i].x,pontos[i].y);
            }            

        }

        break;
        
        case 'R':

        if(sentido == 0){
            
            for(int i = indice_direita(pontos,tamanho); i < tamanho ; i++){
                printf("%.2f %.2f\n",pontos[i].x,pontos[i].y);
            }

            for(int i = 0; i <= indice_direita(pontos,tamanho) - 1 ; i++){
                printf("%.2f %.2f\n",pontos[i].x,pontos[i].y);
            }
        }

        
        break;
        
        case 'D':
    
        break;
        
        case 'U':
        break;
        
        default:
        break;
    }

    

    return 0;
}