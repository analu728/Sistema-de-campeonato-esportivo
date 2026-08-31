#include <stdio.h>
#include "tipos.h"
#include "time_gestao.h"
#include "partida_gestao.h"
#include "arquivo.h"
#include "utils.h"

void menuTimes(VetTimes *vt) {
    int opcao, id;
    char novoNome[64];
    do {
        printf("\n================ MENU TIMES ================\n");
        printf("| 1 - Cadastrar time                        |\n");
        printf("| 2 - Listar times                          |\n");
        printf("| 3 - Alterar dados de um time              |\n");
        printf("| 4 - Remover time                          |\n");
        printf("| 5 - Ver classificacao                     |\n");
        printf("| 0 - Voltar                                |\n");
        printf("==============================================\n");
        printf("Opcao: ");
        int lido = scanf(" %d", &opcao);
        if (lido != 1) {
            printf("Entrada invalida! Digite apenas o numero da opcao.\n");
            int c;
            while ((c = getchar()) != '\n' && c != EOF);
            opcao = -1;
        }
        switch (opcao) {
            case 1:
                cadastrarTime(vt);
                break;
            case 2:
                listarTimes(vt);
                break;
            case 3:
                printf("Digite o ID do time que deseja alterar (0 para cancelar): ");
                scanf("%d", &id);
                if (id == 0) {
                    printf("Operacao cancelada.\n");
                    break;
                }
                printf("Digite o novo nome: ");
                scanf(" %[^\n]", novoNome);
                atualizarTime(vt, id, novoNome);
                break;
            case 4:
                printf("Digite o ID do time que deseja remover (0 para cancelar): ");
                scanf("%d", &id);
                if (id == 0) {
                    printf("Operacao cancelada.\n");
                    break;
                }
                removerTime(vt, id);
                break;
            case 5:
                exibirClassificacao(vt);
                break;
            case 0:
                printf("Voltando ao menu principal...\n");
                break;
            default:
                printf("Opçao invalida.\n");
                break;
        }
    } while (opcao != 0);
}

void menuPartidas(VetPartidas *vp, VetTimes *vt) {
    int opcao, id;
    do {
        printf("\n=============== MENU PARTIDAS ===============\n");
        printf("| 1 - Cadastrar partida                     |\n");
        printf("| 2 - Atualizar partida                     |\n");
        printf("| 3 - Remover partida                       |\n");
        printf("| 4 - Registrar resultado                   |\n");
        printf("| 5 - Ver chaveamento                       |\n");
        printf("| 0 - Voltar                                |\n");
        printf("==============================================\n");
        printf("Opcao: ");
        int lido = scanf(" %d", &opcao);
        if (lido != 1) {
            printf("Entrada invalida! Digite apenas o numero da opçao.\n");
            int c;
            while ((c = getchar()) != '\n' && c != EOF);
            opcao = -1;
        }
        switch (opcao) {
            case 1:
                cadastrarPartida(vp, vt);
                break;
            case 2:
                printf("Digite o ID da partida que deseja atualizar (0 para cancelar): ");
                scanf("%d", &id);
                if (id == 0) {
                    printf("Operacao cancelada.\n");
                    break;
                }
                atualizarPartida(vp, id);
                break;
            case 3:
                printf("Digite o ID da partida que deseja remover (0 para cancelar): ");
                scanf("%d", &id);
                if (id == 0) {
                    printf("Operacao cancelada.\n");
                    break;
                }
                removerPartida(vp, id);
                break;
            case 4:
                registrarResultado(vp, vt);
                break;
            case 5:
                exibirChaveamentoMataMata(vp, vt);
                break;
            case 0:
                printf("Voltando ao menu principal...\n");
                break;
            default:
                printf("Opçao invalida.\n");
                break;
        }
    } while (opcao != 0);
}

int main() {
    int opcao;
    VetTimes vt;
    VetPartidas vp;
    inicializarVetTimes(&vt);
    carregarTimes(&vt);
    inicializarVetPartidas(&vp);
    carregarPartidas(&vp);

    do {
        printf("\n============ SISTEMA DE CAMPEONATO ESPORTIVO ============\n");
        printf("| 1 - Gerenciar Times                                    |\n");
        printf("| 2 - Gerenciar Partidas                                 |\n");
        printf("| 0 - Sair                                               |\n");
        printf("===========================================================\n");
        printf("Opcao: ");
        int lido = scanf(" %d", &opcao);
        if (lido != 1) {
            printf("Entrada invalida! Digite apenas o numero da opçao.\n");
            int c;
            while ((c = getchar()) != '\n' && c != EOF);
            opcao = -1;
        }
        switch (opcao) {
            case 1:
                menuTimes(&vt);
                break;
            case 2:
                menuPartidas(&vp, &vt);
                break;
            case 0:
                printf("Encerrando\n");
                break;
            default:
                printf("Opçao invalida.\n");
                break;
        }
    } while (opcao != 0);

    salvarTimes(&vt);
    salvarPartidas(&vp);
    liberarVetTimes(&vt);
    liberarVetPartidas(&vp);
    
return 0;
}