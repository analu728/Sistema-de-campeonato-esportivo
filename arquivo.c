#include "arquivo.h"
#include <stdio.h>
#include <stdlib.h>

void salvarTimes(const VetTimes *vt) {
    FILE *f = fopen("data/times.txt", "w");
    if (f == NULL) {
        printf("Erro ao abrir arquivo para salvar times.\n");
        return;
    }

    for (int i = 0; i < vt->qtd; i++) {
        fprintf(f, "%d %s %d %d %d %d %d %d\n",
                vt->itens[i].id,
                vt->itens[i].nome,
                vt->itens[i].pontos,
                vt->itens[i].vitorias,
                vt->itens[i].empates,
                vt->itens[i].derrotas,
                vt->itens[i].golsPro,
                vt->itens[i].golsContra);
    }

    fclose(f);
}
void carregarTimes(VetTimes *vt) {
    FILE *f = fopen("data/times.txt", "r");
    if (f == NULL) {
        return; // arquivo ainda não existe (primeira vez rodando) — não é erro, só não tem nada pra carregar ainda
    }

    Time t;
    while (fscanf(f, "%d %s %d %d %d %d %d %d",
                   &t.id, t.nome, &t.pontos, &t.vitorias,
                   &t.empates, &t.derrotas, &t.golsPro, &t.golsContra) == 8) {

        if (vt->qtd == vt->cap) {
            int novaCapacidade = vt->cap + INCREMENTO_CAPACIDADE;
            Time *temp = realloc(vt->itens, novaCapacidade * sizeof(Time));
            if (temp == NULL) {
                printf("Erro ao expandir memoria ao carregar times.\n");
                fclose(f);
                return;
            }
            vt->itens = temp;
            vt->cap = novaCapacidade;
        }

        vt->itens[vt->qtd] = t;
        vt->qtd++;
    }

    fclose(f);
}