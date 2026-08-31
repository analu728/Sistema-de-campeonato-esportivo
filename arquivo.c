#include "arquivo.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void salvarTimes(const VetTimes *vt) {
    FILE *f = fopen("data/times.txt", "w");
    if (f == NULL) {
        printf("Erro ao abrir arquivo para salvar times.\n");
        return;
    }

    for (int i = 0; i < vt->qtd; i++) {
        fprintf(f, "%d %d %d %d %d %d %d %s\n",
                vt->itens[i].id,
                vt->itens[i].pontos,
                vt->itens[i].vitorias,
                vt->itens[i].empates,
                vt->itens[i].derrotas,
                vt->itens[i].golsPro,
                vt->itens[i].golsContra,
                vt->itens[i].nome);
    }

    fclose(f);
}
void carregarTimes(VetTimes *vt) {
    FILE *f = fopen("data/times.txt", "r");
    if (f == NULL) {
        return; 
    }

    Time t;
    while (fscanf(f, "%d %d %d %d %d %d %d",
                   &t.id, &t.pontos, &t.vitorias,
                   &t.empates, &t.derrotas, &t.golsPro, &t.golsContra) == 7) {

        if (fscanf(f, " %63[^\n]", t.nome) != 1) {
            break; 
        }
        
        int len = strlen(t.nome);
        while (len > 0 && (t.nome[len-1] == '\r' || t.nome[len-1] == '\n')) {
            t.nome[len-1] = '\0';
            len--;
        }

        if (vt->qtd == vt->cap) {
            int novaCapacidade = vt->cap + INCREMENTO_CAPACIDADE;
            Time *temp = realloc(vt->itens, novaCapacidade * sizeof(Time));
            if (temp == NULL) {
                printf("Erro ao expandir memória ao carregar times.\n");
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
