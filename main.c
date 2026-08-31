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
        printf("\n--- Menu Times ---\n");
        printf("Cadastrar time: 1\nListar times: 2\nAlterar dados de um time: 3\nRemover time: 4\nVoltar: 0\n");
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
                printf("Digite o ID do time que deseja alterar: ");
                scanf("%d", &id);
                printf("Digite o novo nome: ");
                scanf(" %[^\n]", novoNome);
                atualizarTime(vt, id, novoNome);
                break;
            case 4:
                printf("Digite o ID do time que deseja remover: ");
                scanf("%d", &id);
                removerTime(vt, id);
                break;
            case 0:
                printf("Voltando ao menu principal...\n");
                break;
            default:
                printf("Opcao invalida.\n");
                break;
        }
    } while (opcao != 0);
}

void menuPartidas(VetPartidas *vp, VetTimes *vt) {
    int opcao, id;
    do {
        printf("\n--- Menu Partidas ---\n");
        printf("Cadastrar partida: 1\nAtualizar partida: 2\nRemover partida: 3\nRegistrar resultado: 4\nVer chaveamento: 5\nVoltar: 0\n");
        int lido = scanf(" %d", &opcao);
        if (lido != 1) {
            printf("Entrada invalida! Digite apenas o numero da opcao.\n");
            int c;
            while ((c = getchar()) != '\n' && c != EOF);
            opcao = -1;
        }
        switch (opcao) {
            case 1:
                cadastrarPartida(vp, vt);
                break;
            case 2:
                printf("Digite o ID da partida que deseja atualizar: ");
                scanf("%d", &id);
                atualizarPartida(vp, id);
                break;
            case 3:
                printf("Digite o ID da partida que deseja remover: ");
                scanf("%d", &id);
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
                printf("Opcao invalida.\n");
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

    do {
        printf("\nSistema de Campeonato Esportivo\n");
        printf("Gerenciar Times: 1\nGerenciar Partidas: 2\nSair: 0\n");
        int lido = scanf(" %d", &opcao);
        if (lido != 1) {
            printf("Entrada invalida! Digite apenas o numero da opcao.\n");
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
                printf("Opcao invalida.\n");
                break;
        }
    } while (opcao != 0);

    salvarTimes(&vt);
    liberarVetTimes(&vt);
    liberarVetPartidas(&vp);
    
return 0;
}