#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct{
    int *itens;
    int topo; //topo é um sinalizador da pilha, ele serve como uma flag, mostra a posicao que da pilha que estamos
    int capacidade;
} pilha;

void init(pilha *p, int capacidade){
    p->itens=(int*)malloc(capacidade*sizeof(int));
    p->topo=-1; //-1 pq depois quando for adicionar elementos sera t++ e ai o primeiro vai para a posicao 0
    p->capacidade=capacidade;
}

int empty(pilha *p){
    return p->topo==-1;
}

int full(pilha *p){
    return p->topo==9;
}

void add(pilha *p){
    p->capacidade*=2; //duplicar o tamanho
    p->itens=(int*)realloc(p->itens, p->capacidade * sizeof(int));
}

void lib(pilha *p){
    free(p->itens);
    p->topo=p->capacidade=-1;
}

void push(pilha *p, int valor){ //adiciona valores a pilha
    if(p->topo==p->capacidade -1){
        add(p);
    }
    p->itens[++p->topo] = valor; //o ++ vem antes pq o topo precisa sair do -1 pro 0 antes de adicionar algo, pq -1 não é indice
    //poderia ter feito p->topo++; p->itens[p->topo]=valor;
}

int pop(pilha *p){ //tira valores da pilha
    if(empty(p)){
       printf("Vazia");
    }
    return p->itens[p->topo--];
}

int peek(pilha *p){ //verifica o valor do topo
    if(empty(p)){
        printf("Pilha vazia");
        return -1;
    }
    return p->itens[p->topo];
}


int main(){
    pilha pilha;
    init(&pilha, 2);
    push(&pilha, 10);
    push(&pilha, 20);
    push(&pilha, 30);
    push(&pilha, 40);
    printf("Topo: %d\n", peek(&pilha));
    printf("Remove: %d\n", pop(&pilha));
    printf("Topo: %d\n", peek(&pilha));
    lib(&pilha);
    return 0;
}
