#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "list.h"
#include "stack.h"

struct node_ {
    point p;
    struct node_ *next;
    struct node_ *previous;
}; typedef struct node_ node;

struct list_ {
    node *start;
    node *end;
    int length;
};

list* list_create(){
    list *newList = (list *)malloc(sizeof(list));

    if(newList){ 
        newList->start = NULL;
        newList->end = NULL;
        newList->length = 0;
    }

    return newList;
}

boolean list_isEmpty(list *l){
    if(l == NULL || l->length > 0){ return False; }

    else{ return True; }
}

int list_getLength(list *l){
    if(l == NULL){ return -1; }
    
    else{ return l->length; }
}

void list_insert(list *l, point p, int index){
    if(l != NULL && index >= 0 && index <= list_getLength(l)){
        node *newNode = (node *)malloc(sizeof(node));
        newNode->p = p;

        // If the element is added to the first index, insert the new node at the start
        if(index == 0){ 
            newNode->next = l->start;
            newNode->previous = NULL;
            l->start = newNode;

            if(list_isEmpty(l)){ l->end = newNode; }

            else{ l->start->next->previous = l->start; }
        }

        else if(index == list_getLength(l)){
            newNode->previous = l->end;
            newNode->next = NULL;
            l->end->next = newNode;
            l->end = newNode;
        }

        else{
            node *tmp;

            // If the position is in the list's first half
            if(index <= (int) list_getLength(l)/2){
                tmp = l->start; // Temporary variable that initially points the the list's beginning

                // Goes as far as the index node
                for(int i = 1; i < index; i++){ tmp = tmp->next; }

                // Inserts the node at the desired index
                newNode->next = tmp->next;
                newNode->previous = tmp;
                tmp->next->previous = newNode;
                tmp->next = newNode;
            }

            // If the position is in the list's second half
            else{
                tmp = l->end; // Temporary variable that initially points the the list's ending

                // Goes as far as the index node
                for(int i = list_getLength(l) - 1; i > index; i--){ tmp = tmp->previous; }

                // Inserts node at the desired index
                newNode->previous = tmp->previous;
                newNode->next = tmp;
                tmp->previous->next = newNode;
                tmp->previous = newNode;
            }
        }

        l->length++;

    }

    return;
}

void list_append(list *l, point p){
    list_insert(l, p, list_getLength(l));

    return;
}

point *list_get(list *l, int index){
    if(l != NULL && index < list_getLength(l)){
        node *tmp;
        
        // If the target-node is in the list's first half
        if(index <= (int) list_getLength(l)/2){
            tmp = l->start;

            // Goes as far as the index node
            for(int i = 0; i < index; i++){ tmp = tmp->next; }
        }

        // If the target-node is in the list's second half
        else{
            tmp = l->end;

            // Goes as far as the index node
            for(int i = list_getLength(l) - 1; i > index; i--){ tmp = tmp->previous; }
        }

        return &(tmp->p);
    }

    else{ return NULL; }
    
}

int list_search(list *l, point p){

    if(l != NULL && !list_isEmpty(l)){
        node *left = l->start, *right = l->end; 
        int leftIndex = 0, rightIndex = list_getLength(l) - 1;

        while((left->p.x != p.x || left->p.y != p.y) && (right->p.x != p.x || right->p.y != p.y) && left != right){
            left = left->next;
            leftIndex++;

            right = right->previous;
            rightIndex--;
        }
        
        if(left->p.x == p.x && left->p.y == p.y){ 
            return leftIndex;
        }
        
        else if(right->p.x == p.x && right->p.y == p.y){ 
            return rightIndex;
        }
        
        else{ return -1; }
    }

    else{ return -1; }
}

void list_remove(list *l, int index){
    if(l != NULL && index < list_getLength(l)){
        node *target = NULL; // Will point to the node at the desired index

        if(index == 0){
            target = l->start;

            l->start = target->next;
            l->start->previous = NULL;
        }

        else if(index == list_getLength(l) - 1){
            target = l->end;

            l->end = target->previous;
            l->end->next = NULL;
        }
        
        else{
            // If the target-node is in the list's first half
            if(index <= (int)list_getLength(l)/2){
                target = l->start;

                for(int i = 0; i < index; i++){ target = target->next; }
            }

            // If the target-node is in the list's second half
            else{
                target = l->end;

                for(int i = list_getLength(l) - 1; i > index; i--){ target = target->previous; }
            }

            target->next->previous = target->previous;
            target->previous->next = target->next;
        }

        // Deallocates the target-node
        free(target);
        target = NULL;

        // Decrements the length counter
        (l->length)--;

    }

    return;
}

// Auxiliar local function to deallocate all the list's nodes as recursion 
void deallocate(node **n){
    // If n ain't the list's last node, calls itself on the next node
    if(*n != NULL && (*n)->next != NULL){ deallocate(&((*n)->next)); }

    free(*n);
    *n = NULL;

    return;
}

void list_delete(list **l){
    if(*l != NULL){
        deallocate(&((*l)->start)); // Deallocates all the list's nodes

        free(*l);
        *l = NULL;

    }
        
    return;
}

void list_print(list *l){
    if(l != NULL){
        node *tmp = l->start;

        while(tmp != NULL){
            printf("%.2lf %.2lf\n", tmp->p.x, tmp->p.y);
            tmp = tmp->next;
        }
    }

    return;
}

void list_reverse(list *l){
    if(l != NULL){
        node *tmp;

        if(list_getLength(l) > 1){
            node *currentNode = l->end;

            for(int i = list_getLength(l) - 1; i >= 0; i--){
                tmp = currentNode->next;
                currentNode->next = currentNode->previous;
                currentNode->previous = tmp;

                currentNode = currentNode->next;
            }

        }

        tmp = l->start;
        l->start = l->end;
        l->end = tmp;

    }

    return;
}

// Local method that swaps the points in the nodes n1 and n2
void pointSwap(node *n1, node *n2){
    point tmp = n1->p;
    n1->p = n2->p;
    n2->p = tmp;

    return;
}

void list_swap(list *l, int i, int j){
    if(l != NULL && i < list_getLength(l) && j < list_getLength(l) && i != j){
        node *node_i; // Node at index i
        node *node_j; // Node at index j

        int middleIndex = (int)list_getLength(l)/2, k;

        // Assures that i < j
        if(i > j){
            k = i;
            i = j;
            j = k;
        }

        // Gets the above node variables pointing to it's corresponding nodes
        if(i > middleIndex && j > middleIndex){
            int k = list_getLength(l) - 1;
            node_j = l->end;
            while(k > j){
                node_j = node_j->previous;
                k--;
            }

            node_i = node_j;
            while(k > i){
                node_i = node_i->previous;
                k--;
            }
        }

        else if((i <= middleIndex/2 && j > middleIndex) || (i >= middleIndex/2 && j >= 3/2*middleIndex)){
            k = 0;
            node_i = l->start;
            while(k < i){
                node_i = node_i->next;
                k++;
            }

            k = list_getLength(l) - 1;
            node_j = l->end;
            while(k > j){
                node_j = node_j->previous;
                k--;
            }
        }

        else{
            int k = 0;
            node_i = l->start;
            while(k < i){
                node_i = node_i->next;
                k++;
            }

            node_j = node_i;
            while(k < j){
                node_j = node_j->next;
                k++;
            }
        }

        // Swaps the points in each node
        pointSwap(node_i, node_j);

    }

    return;
}

void list_shuffle(list *l){
    if(l != NULL){
        srand(time(NULL));

        // Current node to be swapped
        node *currentNode = l->end;
        int currentIndex = list_getLength(l)-1;
        
        // Auxiliar node variable in order to get the target node
        node *aux = l->start;
        int auxIndex = 0;

        // Target node's index (node to be swapped with the current one)
        int targetIndex;

        int distanceCurrent, distanceEnd, minDist;

        while(currentIndex > 0){
            // Randomly selects a target to the left of the current one
            targetIndex = rand() % (currentIndex+1);

            // Calculates which indexed node is the closest to targetIndex-node
            distanceCurrent = abs(targetIndex - currentIndex);
            distanceEnd = abs(targetIndex - (list_getLength(l) - 1));
            minDist = min4(distanceCurrent, abs(targetIndex - auxIndex), targetIndex, distanceEnd);

            // targetIndex-node is closest from the current-node
            if(minDist == distanceCurrent){
                aux = currentNode;
                auxIndex = currentIndex;
            }

            // targetIndex-node is closest from the first node
            else if(minDist == targetIndex){
                aux = l->start;
                auxIndex = 0;
            }

            // targetIndex-node is closest from the last node
            else if(minDist == distanceEnd){
                aux = l->end;
                auxIndex = list_getLength(l) - 1;
            }

            // Now, aux is the indexed node closest to targetIndex-node

            // Gets targetIndex-node to aux
            while(auxIndex < targetIndex){ // If it's on the right
                aux = aux->next; 
                auxIndex++;
            } 
            while(auxIndex > targetIndex){ // If it's on the left
                aux = aux->previous; 
                auxIndex--;
            } 

            pointSwap(aux, currentNode);

            currentNode = currentNode->previous;
            currentIndex--;
        }

    }

    return;
}

// Local function that quick sorts a given list
void quickSort(list *l, char key, int leftIndex, int rightIndex){
    if(0 <= leftIndex && leftIndex < rightIndex && rightIndex < list_getLength(l)){
        int left = leftIndex; // Current index on the left
        int right = rightIndex; // Current index on the right

        node *leftNode; // Current node on the left
        node *rightNode; // Current node on the right

        // Lists's middle index
        int middleIndex = (int)list_getLength(l)/2;
        // Auxiliar index variable
        int k;

        // Makes leftNode point to the leftmost node in the partition
        // And rightNode point to the rightmost node in the partition
        if(leftIndex > middleIndex && rightIndex > middleIndex){ // If both nodes are in the list's second half
            int k = list_getLength(l) - 1;
            rightNode = l->end;
            while(k > rightIndex){
                rightNode = rightNode->previous;
                k--;
            }

            leftNode = rightNode;
            while(k > leftIndex){
                leftNode = leftNode->previous;
                k--;
            }
        }

        // If the left node is in the list's first quarter and the right node in the second half
        // Or they're in the second and last quarters respectively
        else if((leftIndex <= middleIndex/2 && rightIndex > middleIndex) || (leftIndex >= middleIndex/2 && rightIndex >= 3/2*middleIndex)){
            k = 0;
            leftNode = l->start;
            while(k < leftIndex){
                leftNode = leftNode->next;
                k++;
            }

            k = list_getLength(l) - 1;
            rightNode = l->end;
            while(k > rightIndex){
                rightNode = rightNode->previous;
                k--;
            }
        }
        
        // If both nodes are in the list's first half
        // Or if they're in neighboring quarters (2nd and 3rd)
        else{
            int k = 0;
            leftNode = l->start;
            while(k < leftIndex){
                leftNode = leftNode->next;
                k++;
            }

            rightNode = leftNode;
            while(k < rightIndex){
                rightNode = rightNode->next;
                k++;
            }
        }

        // Now leftNode points to the partition's leftmost node
        // And rightNode points to the partition's rightmost node

        // Partition's middle index
        middleIndex = (int)((rightIndex+leftIndex)/2);
        point pivot = *list_get(l, middleIndex);

        // Separes the vector/subvector into two partitions
        while(True){

            // Selects elements from the left
            while( left <= rightIndex && cmpPoints(leftNode->p, pivot, key) ){
                leftNode = leftNode->next;
                left++;
            }

            // Selects elements from the right
            while( right >= leftIndex && cmpPoints(rightNode->p, pivot, toggleChar(key)) ){
                rightNode = rightNode->previous;
                right--;
            }

            // If swapping the above selected elements is worth it, do it
            if(left < right){ 
                pointSwap(leftNode, rightNode); // Swap

                // And pass to the next points
                leftNode = leftNode->next;
                left++;

                rightNode = rightNode->previous;
                right--;
            }

            // If the swap is not worth it, the vector was successfully partitionted
            else{ break; }

        }

        // Sorts the partitions
        quickSort(l, key, leftIndex, right);
        quickSort(l, key, right+1, rightIndex);

    }

    return;

}

void list_sort(list *l, char key){
    if(l != NULL && list_getLength(l) > 1){
        if(key != 'x' && key != 'X' && key != 'y' && key != 'Y'){ key = 'x'; }

        list_shuffle(l);
        quickSort(l, key, 0, list_getLength(l)-1);
    }

    return;
}

list *list_copy(list *l){
    if(l != NULL){
        list *copy = list_create();
        int length = list_getLength(l);

        node *tmp = l->start;

        for(int i = 0; i < length; i++){
            list_append(copy, tmp->p);

            tmp = tmp->next;
        }

        return copy;
    }

    else{ return NULL; }

}
 
void list_extend(list *l, list *target){
    if(l != NULL && target != NULL){
        int length = list_getLength(target);
        node *tmp = target->start;

        for(int i = 0; i < length; i++){
            list_append(l, tmp->p);

            tmp = tmp->next;
        }
    }

    return;
}


void list_extendStack(list *l, stack *target){
    if(l != NULL && target != NULL){
        stack *s = stack_copy(target);
        int length = stack_getLength(s);

        for(int i = 0; i < length; i++){
            list_append(l, *stack_pop(s));
        }

        stack_delete(&s);

    }

    return;
}

void list_attachStack(list *l, stack *target){
    if(l != NULL && target != NULL){
        int length = stack_getLength(target);

        for(int i = 0; i < length; i++){
            list_append(l, *stack_pop(target));
        }
        
        stack_delete(&target);

    }

    return;
}



int indice_esquerda_lista(list* l){

    int tamanho = list_getLength(l);

    int mais_esquerda = 0;
    point ponto_mais_esquerda = l->start->p;
    
    node* aux = l->start;

    for(int i = 0; i < tamanho; i++){
        if(aux->p.x < ponto_mais_esquerda.x){
            mais_esquerda = i;
            ponto_mais_esquerda = aux->p;
        }
        else if(aux->p.x == ponto_mais_esquerda.x){
            if(aux->p.y < ponto_mais_esquerda.y){
                mais_esquerda = i;
            }
        }
        aux = aux->next;
    }
    return mais_esquerda;
}

int indice_cima_lista(list* l){

    int tamanho = list_getLength(l);

    int mais_acima = 0;
    point ponto_mais_acima = l->start->p;
    
    node* aux = l->start;

    for(int i = 0; i < tamanho; i++){
        if(aux->p.y > ponto_mais_acima.y){
            mais_acima = i;
            ponto_mais_acima = aux->p;
        }
        else if(aux->p.y == ponto_mais_acima.y){
            if(aux->p.x < ponto_mais_acima.x){
                mais_acima = i;
            }
        }
        aux = aux->next;
    }
    return mais_acima;
}

int indice_baixo_lista(list* l){

    int tamanho = list_getLength(l);

    int mais_abaixo = 0;
    point ponto_mais_abaixo = l->start->p;
    
    node* aux = l->start;

    for(int i = 0; i < tamanho; i++){
        if(aux->p.y < ponto_mais_abaixo.y){
            mais_abaixo = i;
            ponto_mais_abaixo = aux->p;
        }
        else if(aux->p.y == ponto_mais_abaixo.y){
            if(aux->p.x < ponto_mais_abaixo.x){
                mais_abaixo = i;
            }
        }
        aux = aux->next;
    }
    return mais_abaixo;
    
}

int indice_direita_lista(list* l){

    int tamanho = list_getLength(l);

    int mais_direita = 0;
    point ponto_mais_direita = l->start->p;
    
    node* aux = l->start;

    for(int i = 0; i < tamanho; i++){
        if(aux->p.x > ponto_mais_direita.x){
            mais_direita = i;
            ponto_mais_direita = aux->p;
        }
        else if(aux->p.x == ponto_mais_direita.x){
            if(aux->p.y < ponto_mais_direita.y){
                mais_direita = i;
            }
        }
        aux = aux->next;
    }
    return mais_direita;
}

void lista_impressao_anti_horaria(list* l, int indice){

    int tamanho = list_getLength(l);

    int i = 0;
    node* aux = l->start;

    while(i != indice){
        aux = aux->next;
        i++;
    } 

    for (int i = indice; i < tamanho ; i++){
                printf("%.2f %.2f\n",aux->p.x,aux->p.y);
                aux = aux->next;
            }

            aux = l->start;

            for (int i = 0; i < indice; i++){
                printf("%.2f %.2f\n",aux->p.x,aux->p.y);
                aux = aux->next;
            }
    
    return;
}

void lista_impressao_horaria(list* l, int indice){

    int tamanho = list_getLength(l);

    int i = 0;
    node* aux = l->start;

    while(i != indice){
        aux = aux->next;
        i++;
    } 

    for (int i = indice; i >= 0 ; i--){
                printf("%.2f %.2f\n",aux->p.x,aux->p.y);
                aux = aux->previous;
            }

            aux = l->end;

            for (int i = tamanho - 1; i > indice; i--){
                printf("%.2f %.2f\n",aux->p.x,aux->p.y);
                aux = aux->previous;
            }
    
    return;
}
