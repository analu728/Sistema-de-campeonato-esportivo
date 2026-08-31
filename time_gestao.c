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
            printf("Não foi possivel realocar memória.\n");
            exit(1);
        }
        vt->itens=temp;
        vt->cap=nova_capacidade;
    }

    Time novo;
    int maiorId=0;
    for(int i=0;i<vt->qtd;i++){
        if(vt->itens[i].id>maiorId){
            maiorId=vt->itens[i].id;
        }
    }
    novo.id= maiorId+1;

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
    printf("\n=========================== LISTA DE TIMES ===========================\n");
    printf("%-4s %-20s %-6s %-3s %-3s %-3s %-4s %-4s\n",
           "ID", "Nome", "Pts", "V", "E", "D", "GP", "GC");
    for (int i = 0; i < vt->qtd; i++) {
        printf("%-4d %-20s %-6d %-3d %-3d %-3d %-4d %-4d\n",
               vt->itens[i].id,
               vt->itens[i].nome,
               vt->itens[i].pontos,
               vt->itens[i].vitorias,
               vt->itens[i].empates,
               vt->itens[i].derrotas,
               vt->itens[i].golsPro,
               vt->itens[i].golsContra);
    }
    printf("========================================================================\n");
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
void exibirClassificacao(const VetTimes *vt){
    if (vt->qtd == 0){
        printf("\nNenhum time cadastrado ainda.\n");
        return;
    }

    Time *copia = malloc(vt->qtd * sizeof(Time));
    if (copia == NULL) {
        printf("Erro ao alocar memoria para classificacao.\n");
        return;
    }
    for (int i = 0; i < vt->qtd; i++) {
        copia[i] = vt->itens[i];
    }

    for (int i = 0; i < vt->qtd - 1; i++) {
        for (int j = 0; j < vt->qtd - 1 - i; j++) {
            int saldoJ = copia[j].golsPro - copia[j].golsContra;
            int saldoJ1 = copia[j+1].golsPro - copia[j+1].golsContra;
            int trocar = 0;
            if (copia[j].pontos < copia[j+1].pontos) trocar = 1;
            else if (copia[j].pontos == copia[j+1].pontos) {
                if (saldoJ < saldoJ1) trocar = 1;
                else if (saldoJ == saldoJ1 && copia[j].golsPro < copia[j+1].golsPro) trocar = 1;
            }
            if (trocar) {
                Time aux = copia[j];
                copia[j] = copia[j+1];
                copia[j+1] = aux;
            }
        }
    }

    printf("\n=================== TABELA DE CLASSIFICAÇÃO ===================\n");
    printf("%-4s %-20s %-6s %-3s %-3s %-3s %-4s %-4s %-4s\n",
           "Pos", "Time", "Pts", "V", "E", "D", "GP", "GC", "SG");
    for (int i = 0; i < vt->qtd; i++) {
        int saldo = copia[i].golsPro - copia[i].golsContra;
        printf("%-4d %-20s %-6d %-3d %-3d %-3d %-4d %-4d %-4d\n",
               i + 1, copia[i].nome, copia[i].pontos, copia[i].vitorias,
               copia[i].empates, copia[i].derrotas, copia[i].golsPro,
               copia[i].golsContra, saldo);
    }
    printf("=================================================================\n");

    free(copia);
}