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

void cadastrarTime(VetTimes *vt) {

    if (vt->qtd == vt->cap) {
        vt->cap += INCREMENTO_CAPACIDADE;
        vt->itens = realloc(vt->itens, vt->cap * sizeof(Time));
    }

    Time novo;
    novo.id = vt->qtd + 1; // id do time

    printf("\n--- CADASTRAR TIME ---\n");
    printf("Nome do time: ");
    scanf(" %[^\n]", novo.nome); // Lê a string com espaços

    // Inicializa zerado
    novo.pontos = 0;
    novo.vitorias = 0;
    novo.empates = 0;
    novo.derrotas = 0;
    novo.golsPro = 0;
    novo.golsContra = 0;

    vt->itens[vt->qtd] = novo;
    vt->qtd++;

    printf("Time '%s' cadastrado com sucesso! (ID: %d)\n", novo.nome, novo.id);
}
