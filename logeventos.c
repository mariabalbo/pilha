#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct{
    int *dados;
    int t;
    int s;
    int K;
    int tam;
} eventos;

void init(eventos *evento, int cap) {
    evento->K = cap; 
    evento->dados = (int *)malloc(evento->K * sizeof(int));
    evento->s = evento->t=evento->tam=0;
    for(int i = 0; i < evento->K; i++){
        evento->dados[i] = -1;
    }
}

int size(eventos *evento){
    if(evento->t >= evento->s){
        return evento->t - evento->s;
    } else {
        return evento->K - evento->s + evento->t;
    }
}

void add(eventos *evento, int n){
    if((evento->t+1)%(evento->K)==evento->s){
        evento->s=(evento->s+1)%evento->K;
        evento->dados[evento->t]=n;
        evento->t=(evento->t+1)% evento->K;
    } else {
        evento->dados[evento->t]=n;
        evento->t=(evento->t+1)%evento->K;
        evento->tam++;
    }
}

void remover(eventos *evento){
    if(evento->t==evento->s){
        printf("CLEAR");
    } else {
        int x= evento->dados[evento->s];
        evento->dados[evento->s]=-1;
        evento->s=(evento->s+1)%evento->K;
        if(x!=-1){
            printf("%d", x);
        }
    }
}

void increase(eventos *evento, int inc){
    int novo_cap = evento->K + inc;
    int *novo_dados=(int*)malloc(novo_cap*sizeof(int));
    
    int tam = size(evento);
    for(int i=0; i < tam; i++){
        novo_dados[i] = evento->dados[(evento->s + i) % evento->K];
    }
    
    for(int i = tam; i < novo_cap; i++){
        novo_dados[i] = -1;
    }
    
    free(evento->dados);
    evento->dados = novo_dados;
    evento->K = novo_cap;
    evento->s = 0; 
    evento->t = evento->tam; 
}

void list(eventos *evento){
    if(evento->t==evento->s){
        printf("EMPTY");
    } else {
        int i=evento->s;
        do {
            printf("%d ", evento->dados[i]);
            i=(i+1)%evento->K;
        } while(i!=evento->t);
    }
}

void print(eventos *evento){
    for(int i=0 ; i<evento->K ; i++){
        int ocupado=0;
        if(evento->tam>0){
            int dist = (i-(evento->s)+evento->K)%evento->K;
            if(dist<evento->tam){
                ocupado=1;
            }
        }
        if(ocupado){
            printf("%d", evento->dados[i]);
        } else {
            printf("-");
        }
        if(i<evento->K-1){
            printf(" ");
        }
    }
}

void end(eventos *evento){
    free(evento->dados);
    free(evento);
}

int main(){
    int K,n, inc;
    eventos *evento;
    scanf("%d", &K);
    evento = (eventos*)malloc(sizeof(eventos)); 
    init(evento, K);
    char com[50];
    while(scanf("%s", com)!=EOF){
        if(strcmp(com, "ADD")==0){
            scanf("%d", &n);
            add(evento,n);
        } else if(strcmp(com, "REMOVE")==0){
            remover(evento);
        } else if(strcmp(com, "LIST")==0){
            list(evento);
        } else if(strcmp(com, "PRINT")==0){
            print(evento);
        } else if(strcmp(com, "INCREASE")==0){
            scanf("%d", &inc);
            increase(evento, inc);
        } else if(strcmp(com, "END")==0){
            end(evento);
            break;
        }
    }
    return 0;
}

