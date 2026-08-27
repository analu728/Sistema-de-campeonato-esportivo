#include <stdio.h>
#include "tipos.h"
#include "time_gestao.h"
#include "partida_gestao.h"
#include "arquivo.h"
#include "utils.h"

int main(void) {
    int opcao, b;
    VetTimes vt;
    inicializarVetTimes(&vt);
    do{
        printf("Sistema de Campeonato Esportivo\n");
    printf("Escolha uma opcao:\nCadastrar time: 1\nListar times: 2\nAlterar dados de um time: 3\n");
    scanf(" %d", &opcao);
    switch(opcao){
        case 1:
            cadastrarTime(&vt);
            break;
        case 2:
            listarTimes(&vt);
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
