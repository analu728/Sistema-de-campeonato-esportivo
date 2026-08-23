#include <stdio.h>
#include "tipos.h"
#include "time_gestao.h"
#include "partida_gestao.h"
#include "arquivo.h"
#include "utils.h"

int main(void) {

    VetTimes vt;

    inicializarVetTimes(&vt);
    printf("Capacidade: %d, Quantidade: %d\n", vt.cap, vt.qtd);
    liberarVetTimes(&vt);
    
return 0;
}
