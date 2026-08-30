#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "time_gestao.h"

void inicializarVetTimes(VetTimes *vt){
    vt->itens = malloc(CAPACIDADE_INICIAL * sizeof(Time));
    if (vt->itens == NULL){
        printf("Erro: falha ao alocar memoria para os times.\n");
        exit(1);
    }

    vt->cap = CAPACIDADE_INICIAL;
    vt->qtd = 0;
}
void liberarVetTimes(VetTimes *vt){
    free(vt->itens);
    vt->itens = NULL;
    vt->qtd = 0;
    vt->cap = 0;
}

void cadastrarTime(VetTimes *vt) {


    if (vt->qtd == vt->cap) {
        int nova_capacidade=vt->cap+INCREMENTO_CAPACIDADE;
        Time *temp =realloc(vt->itens, nova_capacidade * sizeof(Time));

        if (temp==NULL){
            printf("Nao foi possivel realocar memoria\n");
            exit(1);
        }
        vt->itens=temp;
        vt->cap=nova_capacidade;
    }

    Time novo;
    novo.id = vt->qtd + 1; // id do time

    printf("\nCadastrar Time\n");
    printf("Nome do time: \n");
    scanf(" %[^\n]", novo.nome); // le o nome do time c os espaços

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
void listarTimes(const VetTimes *vt){
    if (vt->qtd == 0) {
        printf("\nNenhum time cadastrado ainda.\n");
        return;
    }
    printf("\nLista de times:\n");
    for (int i = 0; i < vt->qtd; i++) {
        printf("ID: %d | Nome: %-20s | Pontos: %d | V: %d | E: %d | D: %d\n",
               vt->itens[i].id,
               vt->itens[i].nome,
               vt->itens[i].pontos,
               vt->itens[i].vitorias,
               vt->itens[i].empates,
               vt->itens[i].derrotas);
    }
}
void atualizarTime(VetTimes *vt, int id, const char *novoNome){
    int i, encontrado=0;
    for(i=0;i<vt->qtd;i++){
        if(vt->itens[i].id==id){
            strcpy(vt->itens[i].nome, novoNome);
            encontrado=1;
        }
        if(encontrado==1){
            break;
        }
    }
    if (encontrado==0){
        printf("ID do Time não encontrado.");
    }
    
}
void removerTime(VetTimes *vt, int id){
    int i, encontrado=0, j;
    for(i=0;i<vt->qtd;i++){
        if(vt->itens[i].id==id){
            for (j = i; j < vt->qtd - 1; j++) {
                vt->itens[j] = vt->itens[j + 1];
            }
            vt->qtd--;
            encontrado=1;
        }
        if(encontrado==1){
            break;
        }
    }
    if (encontrado==0){
        printf("ID do Time não encontrado.");
    }
}