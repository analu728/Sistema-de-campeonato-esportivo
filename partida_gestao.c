#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "partida_gestao.h"
#include "utils.h"

void inicializarVetPartidas(VetPartidas *vp) {
    vp->qtd = 0;
    vp->cap = 10;
    vp->itens = (Partida *) malloc(vp->cap * sizeof(Partida));

    if (vp->itens == NULL) {
        printf("Erro: Falha ao alocar memoria para partidas\n");
    }
}
void cadastrarPartida(VetPartidas *vp, const VetTimes *vt) {
    if (vp->qtd >= vp->cap) {
        vp->cap *= 2;
        vp->itens = (Partida *) realloc(vp->itens, vp->cap * sizeof(Partida));
        if (vp->itens == NULL) {
            printf("Erro: Falha ao expandir a memoria de partidas.\n");
            return;
        }
    }
    if (vp->qtd >= 100) {
        printf("Erro: Limite maximo de partidas atingido.\n");
        return;
    }

    Partida nova;

    printf("\n--- Cadastrar/Agendar Partida ---\n");
    printf("(Digite 0 no ID do time da casa a qualquer momento para cancelar e voltar)\n");

    int maiorId = 0;
    for (int i = 0; i < vp->qtd; i++) {
        if (vp->itens[i].id > maiorId) {
            maiorId = vp->itens[i].id;
        }
    }
    nova.id = maiorId + 1; // ID da partida gerado automaticamente

    printf("ID do Time da Casa: ");
    scanf("%d", &nova.idCasa);
    if (nova.idCasa == 0) {
        printf("Operacao cancelada.\n");
        return;
    }
    if (BuscarTime(vt, nova.idCasa) == -1) {
        printf("Erro: Time da casa (ID %d) nao foi encontrado.\n", nova.idCasa);
        return;
    }

    printf("ID do Time de Fora: ");
    scanf("%d", &nova.idFora);
    if (BuscarTime(vt, nova.idFora) == -1) {
        printf("Erro: Time de fora (ID %d) nao foi encontrado.\n", nova.idFora);
        return;
    }

    if (nova.idCasa == nova.idFora) {
        printf("Erro: Um time nao pode jogar contra ele mesmo.\n");
        return;
    }

    printf("Fase (ex: Grupos, Oitavas, Quartas, Semifinal, Final): ");
    scanf(" %[^\n]", nova.fase);

    printf("Data da Partida (Dia Mes Ano ex: 15 10 2026): ");
    scanf("%d %d %d", &nova.data.dia, &nova.data.mes, &nova.data.ano);

    if (!validardata(nova.data)) {
        printf("Erro: Data invalida! Operacao cancelada.\n");
        return;
    }

    nova.golsCasa = 0;
    nova.golsFora = 0;
    nova.disputada = 0;

    vp->itens[vp->qtd] = nova;
    vp->qtd++;

    printf("Partida agendada com sucesso!\n");
}
void atualizarPartida(VetPartidas *vp, int id) {
    int idx = BuscarPartida(vp, id);
    if (idx == -1) {
        printf("Erro: Partida nao encontrada.\n");
        return;
    }

    if (vp->itens[idx].disputada == 1) {
        printf("Erro: Partida ja foi disputada.\n");
        return;
    }

    printf("\nAlterar Dados da Partida ID %d \n", id);
    printf("Nova Fase (ex: Oitavas, Semifinal, Final): ");
    scanf(" %[^\n]", vp->itens[idx].fase);

    printf("Nova Data (Dia Mes Ano ex: 15 10 2026): ");
    scanf("%d %d %d", &vp->itens[idx].data.dia, &vp->itens[idx].data.mes, &vp->itens[idx].data.ano);

    if (!validardata(vp->itens[idx].data)) {
        printf("Data invalida! Operacao cancelada.\n");
        return;
    }

    printf("Partida atualizada com sucesso!\n");
}
void removerPartida(VetPartidas *vp, int id) {
    int idx = BuscarPartida(vp, id);
    if (idx == -1) {
        printf("Erro: Partida nao encontrada.\n");
        return;
    }

    for (int i = idx; i < vp->qtd - 1; i++) {
        vp->itens[i] = vp->itens[i + 1];
    }
    vp->qtd--;
    printf("Partida removida com sucesso!\n");
}
void registrarResultado(VetPartidas *vp, VetTimes *vt) {
    int idPartida, golsCasa, golsFora;

    printf("\nRegistrar resultado\n");
    printf("Digite o ID da partida (0 para cancelar): ");
    scanf("%d", &idPartida);

    if(idPartida==0){
        printf("Operaçao cancelada.\n");
        return;
    }

    int idxP = BuscarPartida(vp, idPartida);
    if (idxP == -1) {
        printf("Erro: Partida nao encontrada.\n");
        return;
    }

    Partida *p = &vp->itens[idxP];
    if (p->disputada == 1) {
        printf("Erro: Esta partida ja teve seu resultado registrado.\n");
        return;
    }

    int idxCasaConfirma = BuscarTime(vt, p->idCasa);
    int idxForaConfirma = BuscarTime(vt, p->idFora);
    char nomeCasaConfirma[64] = "Desconhecido";
    char nomeForaConfirma[64] = "Desconhecido";
    if (idxCasaConfirma != -1) strcpy(nomeCasaConfirma, vt->itens[idxCasaConfirma].nome);
    if (idxForaConfirma != -1) strcpy(nomeForaConfirma, vt->itens[idxForaConfirma].nome);

    printf("\n--- Confirme a partida ---\n");
    printf("Partida %d: %s (casa) x %s (fora)\n", p->id, nomeCasaConfirma, nomeForaConfirma);

    printf("Gols do Time da Casa (%s): ", nomeCasaConfirma);
    scanf("%d", &golsCasa);
    printf("Gols do Time de Fora (%s): ", nomeForaConfirma);
    scanf("%d", &golsFora);

   if (!validarplacar(golsCasa) || !validarplacar(golsFora)) {
        printf("Erro: Placar nao pode ser negativo.\n");
        return;
    }

    int idxCasa = BuscarTime(vt, p->idCasa);
    int idxFora = BuscarTime(vt, p->idFora);

    if (idxCasa == -1 || idxFora == -1) {
        printf("Erro: Times envolvidos nao foram encontrados na base.\n");
        return;
    }

    p->golsCasa = golsCasa;
    p->golsFora = golsFora;
    p->disputada = 1;

    Time *tCasa = &vt->itens[idxCasa];
    Time *tFora = &vt->itens[idxFora];

    tCasa->golsPro += golsCasa;
    tCasa->golsContra += golsFora;
    tFora->golsPro += golsFora;
    tFora->golsContra += golsCasa;

    if (golsCasa > golsFora) {
        tCasa->pontos += 3;
        tCasa->vitorias++;
        tFora->derrotas++;
    } else if (golsFora > golsCasa) {
        tFora->pontos += 3;
        tFora->vitorias++;
        tCasa->derrotas++;
    } else {
        tCasa->pontos += 1;
        tFora->pontos += 1;
        tCasa->empates++;
        tFora->empates++;
    }

    printf("Placar e estatisticas atualizados com sucesso!\n");
}
void exibirChaveamentoMataMata(const VetPartidas *vp, const VetTimes *vt) {
    if (vp->qtd == 0) {
        printf("\nNenhuma partida cadastrada.\n");
        return;
    }
    printf("\n========================== CHAVEAMENTO MATA-MATA ==========================\n");

    char fases[5][20] = {"Grupos", "Oitavas", "Quartas", "Semifinal", "Final"};

    for (int f = 0; f < 5; f++) {
        int encontrouNaFase = 0;

        for (int i = 0; i < vp->qtd; i++) {
                if (compararString(vp->itens[i].fase, fases[f])) {                if (!encontrouNaFase) {
                    printf("\n--- %s ---\n", fases[f]);
                    encontrouNaFase = 1;
                }

                int idxCasa = BuscarTime(vt, vp->itens[i].idCasa);
                int idxFora = BuscarTime(vt, vp->itens[i].idFora);

                char nomeCasa[64] = "Desconhecido";
                char nomeFora[64] = "Desconhecido";

                if (idxCasa != -1) strcpy(nomeCasa, vt->itens[idxCasa].nome);
                if (idxFora != -1) strcpy(nomeFora, vt->itens[idxFora].nome);

                printf("Partida ID %d: %s ", vp->itens[i].id, nomeCasa);

                if (vp->itens[i].disputada) {
                    printf("[%d x %d]", vp->itens[i].golsCasa, vp->itens[i].golsFora);
                    if (vp->itens[i].golsCasa > vp->itens[i].golsFora) {
                        printf(" -> Vencedor: %s", nomeCasa);
                    } else if (vp->itens[i].golsFora > vp->itens[i].golsCasa) {
                        printf(" -> Vencedor: %s", nomeFora);
                    } else {
                        printf(" -> Empate");
                    }
                } else {
                    printf(" [ vs ] ");
                    printf(" %s (Agendada)", nomeFora);
                }
                printf("\n");
            }
        }
    }
}
void liberarVetPartidas(VetPartidas *vp) {
    if (vp->itens != NULL) {
        free(vp->itens);
        vp->itens = NULL;
    }
    vp->qtd = 0;
}
