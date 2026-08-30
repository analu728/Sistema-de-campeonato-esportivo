#ifndef UTILS_H
#define UTILS_H

#include "tipos.h"

int BuscarTime(const VetTimes *vt, int id);
int BuscarPartida(const VetPartidas *vp, int id);

int validardata(Data d);
int validarplacar(int gols);
int validarnome(const char *nome);

#endif
