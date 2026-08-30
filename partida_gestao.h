#ifndef PARTIDA_GESTAO_H
#define PARTIDA_GESTAO_H

#include "tipos.h"

void inicializarVetPartidas(VetPartidas *vp);
void cadastrarPartida(VetPartidas *vp, const VetTimes *vt);
void atualizarPartida(VetPartidas *vp, int id);
void removerPartida(VetPartidas *vp, int id);
void registrarResultado(VetPartidas *vp, VetTimes *vt);
void exibirChaveamentoMataMata(const VetPartidas *vp, const VetTimes *vt);
void liberarVetPartidas(VetPartidas *vp);

#endif
