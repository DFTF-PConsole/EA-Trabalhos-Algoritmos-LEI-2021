/*  AUTORES: Cláudia Campos N.2018285941 | Dário Félix N.2018275530  */

// FICHEIRO: header_trab.h (relativo ao trab.cpp)


#ifndef TRAB1_NOVO_HEADER_TRAB_H
#define TRAB1_NOVO_HEADER_TRAB_H


/* BIBLIOTECAS */
#include <cstdio>
#include <iostream>
#include <cmath>



/* CONSTANTES */
#define IMPOSSIVEL "no solution"
#define LIM 30


/* MACROS */
#define INDICE(I, J, N)  (((I)*N) + (J))



/* DEFINIÇÕES e ESTRUTURAS */
typedef struct {
    int *tab;
    int countNum;               // heuristica: reduziu os numeros?
    int countPlaysNeed;         // heuristica: conta quantas jogadas precisamos ainda (na melhor das hipoteses)
    bool isEqual;                // heuristica: ficou igual?
} Heuristicas;



/* PROTOTIPOS */
int esquerda(int [], int, int, bool * );
int direita(int [], int, int, bool *);
int cima(int [], int, int, bool *);
int baixo(int [], int, int, bool *);
bool isSolvable(int *, int);
int countNonZeroElements(const int *, int);
void copyArray(int *, const int *, int);
void calcJogo(const int *, int, int, int);
int preCalcJogo(const int *, int, int);

//int sumVectorElements(const int *, int);
//void game(int *, int, int, int, int *);
//int jogo(const int *, int, int);
//bool checkSimetriaHorizontal(const int [], const int [], int);
//bool checkSimetriaVertical(const int [], const int [], int);
//bool isEqual(const int *, const int *, int);


#endif
