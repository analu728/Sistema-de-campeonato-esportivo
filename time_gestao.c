#include <stdio.h>
#include <stdlib.h>
#include "time_gestao.h"

void inicializarVetTimes(VetTimes *v){
    v->itens = malloc(CAPACIDADE_INICIAL * sizeof(Time));
    if (v->itens == NULL){
        printf("Erro: falha ao alocar memoria para os times.\n");
        exit(1);
    }

    v->cap = CAPACIDADE_INICIAL;
    v->qtd = 0;
}
void liberarVetTimes(VetTimes *v){
    free(v->itens);
    v->itens = NULL;
    v->qtd = 0;
    v->cap = 0;
}