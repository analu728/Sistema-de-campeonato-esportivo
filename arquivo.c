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
void salvarPartidas(const VetPartidas *vp) {
    FILE *f = fopen("data/partidas.txt", "w");
    if (f == NULL) {
        printf("Erro ao abrir arquivo para salvar partidas.\n");
        return;
    }
    for (int i = 0; i < vp->qtd; i++) {
        fprintf(f, "%d %d %d %d %d %d %d %d %d %s\n",
                vp->itens[i].id,
                vp->itens[i].idCasa,
                vp->itens[i].idFora,
                vp->itens[i].golsCasa,
                vp->itens[i].golsFora,
                vp->itens[i].data.dia,
                vp->itens[i].data.mes,
                vp->itens[i].data.ano,
                vp->itens[i].disputada,
                vp->itens[i].fase);
    }
    fclose(f);
}

void carregarPartidas(VetPartidas *vp) {
    FILE *f = fopen("data/partidas.txt", "r");
    if (f == NULL) {
        return;
    }
    Partida p;
    while (fscanf(f, "%d %d %d %d %d %d %d %d %d %s",
                  &p.id, &p.idCasa, &p.idFora, &p.golsCasa, &p.golsFora,
                  &p.data.dia, &p.data.mes, &p.data.ano, &p.disputada, p.fase) == 10) {
        if (vp->qtd == vp->cap) {
            int novaCapacidade = vp->cap + INCREMENTO_CAPACIDADE;
            Partida *temp = realloc(vp->itens, novaCapacidade * sizeof(Partida));
            if (temp == NULL) {
                printf("Erro ao expandir memoria ao carregar partidas.\n");
                fclose(f);
                return;
            }
            vp->itens = temp;
            vp->cap = novaCapacidade;
        }
        vp->itens[vp->qtd] = p;
        vp->qtd++;
    }
    fclose(f);
}