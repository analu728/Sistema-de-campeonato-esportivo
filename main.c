#include <stdio.h>
#include "tipos.h"
#include "time_gestao.h"
#include "partida_gestao.h"
#include "arquivo.h"
#include "utils.h"

int main(void) {
    int opcao, b, id;
    char novoNome[64];
    VetTimes vt;
    inicializarVetTimes(&vt);
    do{
        printf("\nSistema de Campeonato Esportivo\n");
    printf("\nEscolha uma opcao:\nCadastrar time: 1\nListar times: 2\nAlterar dados de um time: 3\nRemover time: 4\n");
    int lido = scanf(" %d", &opcao);
    if (lido != 1) {
        printf("Entrada inválida! Digite apenas o número da opcao.\n");
        int c;
        while ((c = getchar()) != '\n' && c != EOF);
        opcao = -1; // um valor que não bate com nenhum case, pra cair no "default"
    }
    switch(opcao){
        case 1:
            cadastrarTime(&vt);
            break;
        case 2:
            listarTimes(&vt);
            break;
        case 3:
            printf("Digite o ID do time que deseja alterar: ");
            scanf("%d", &id);
            printf("Digite o novo nome: ");
            scanf(" %[^\n]", novoNome);
            atualizarTime(&vt, id, novoNome);
            break;
        case 4:
            printf("Digite o ID do time que deseja remover: ");
            scanf("%d", &id);
            removerTime(&vt, id);
            break;
        case 0:
            printf("Encerrando");
            break;
        default:
            printf("Opcao invalida.");
            break;
     }
    }while(opcao !=0);
    liberarVetTimes(&vt);
    return 0;
}
