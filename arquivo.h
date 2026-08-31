#ifndef ARQUIVO_H
#define ARQUIVO_H

#include "tipos.h"

void salvarTimes(const VetTimes *vt);
void carregarTimes(VetTimes *vt);
void salvarPartidas(const VetPartidas *vp);
void carregarPartidas(VetPartidas *vp);

#endif