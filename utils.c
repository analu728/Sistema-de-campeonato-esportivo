#include "utils.h"
#include <string.h>
#include <stdio.h>

int BuscarTime(const VetTimes *vt, int id){
    for(int i=0;i<vt->qtd;i++){
        if(vt->itens[i].id==id){
            return i;//achou
        }
    }
    return -1;
}

int BuscarPartida(const VetPartidas *vp, int id){
    for(int i=0;i<vp->qtd;i++){
        if(vp->itens[i].id==id){
            return i;//achou
        }
    }
    return -1;
}

int validardata(Data d){
    if(d.mes<1 || d.mes>12) return 0;
    if(d.dia<1 || d.dia>31) return 0;
    if(d.ano<2000) return 0;

    if ((d.mes == 4||d.mes == 6 || d.mes == 9 || d.mes == 11) && d.dia > 30) {
        return 0;
    }
    if (d.mes == 2 && d.dia > 29) {
        return 0;
    }
    return 1;
}

int validarplacar(int gols){
    return gols>=0;
}
int validarnome(const char *nome) {
    if (nome==NULL||strlen(nome) == 0) {
        return 0;
    }
    return 1;
}
