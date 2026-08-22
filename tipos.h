#ifndef TIPOS_H
#define TIPOS_H

typedef struct {
    int dia, mes, ano;
} Data;
typedef struct {
 int id;
 char nome[64];
 int pontos;
 int vitorias;
 int empates;
 int derrotas;
 int golsPro;
 int golsContra;
} Time;
typedef struct {
 int id;
 int idCasa;
 int idFora;
 int golsCasa;
 int golsFora;
 Data data;
 int disputada; // 0=agendada, 1=concluída
} Partida;
typedef struct {
 Time *itens;
 int qtd, cap;
} VetTimes;
typedef struct {
 Partida *itens;
 int qtd, cap;
} VetPartidas;
// Opcional: regras de desempate parametrizáveis
typedef struct {
 int pesoPontos; // ex.: 1000
 int pesoVitorias; // ex.: 10
 int pesoSaldoGols; // ex.: 1
 int pesoGolsPro; // ex.: 1
} RegrasDesempate;

#define CAPACIDADE_INICIAL 10
#define INCREMENTO_CAPACIDADE 10

#endif