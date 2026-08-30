#ifndef TIME_GESTAO_H
#define TIME_GESTAO_H

#include "tipos.h"

void inicializarVetTimes(VetTimes *vt);
void liberarVetTimes(VetTimes *vt);
void cadastrarTime(VetTimes *vt);
void listarTimes(const VetTimes *vt);
void atualizarTime(VetTimes *vt, int id, const char *novoNome);
void removerTime(VetTimes *vt, int id);

#endif
