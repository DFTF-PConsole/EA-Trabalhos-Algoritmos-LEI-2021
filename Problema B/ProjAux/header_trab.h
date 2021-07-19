/*  AUTORES: Cláudia Campos N.2018285941 | Dário Félix N.2018275530  */

// FICHEIRO: header_trab.h (relativo ao trab.cpp)


#ifndef TRAB1_NOVO_HEADER_TRAB_H
#define TRAB1_NOVO_HEADER_TRAB_H


/* BIBLIOTECAS */
#include <cstdio>
#include <iostream>
#include <cmath>
#include <vector>
#include <cstdlib>



/* CONSTANTES */
#define MODULO 1000000007
#define MAX_t 20        // Numero casos de teste
#define MAX_n 500       // Numero de blocos (largura)
#define MIN_n 3
#define MAX_h 500       // Altura do bloco / Numero de pecas do bloco
#define MIN_h 2
#define MAX_H 60000     // Altura maxima a atingir (incluindo o h)




/* MACROS */
#define INDICE(I, J, N)  (((I)*(N)) + (J))



/* DEFINIÇÕES e ESTRUTURAS */
typedef struct {
    int n;
    int h;
    int H;
    std::vector<int> dados;
} Cache;




/* PROTOTIPOS */
int modAbs(int a, int mod);
int modAdd(int a, int b, int mod);
int modSub(int a, int b, int mod);
int calc(Cache cache[], int eu);
int rotinaCalcArcos(int n, int h, int H);
int rotinaCalcArcosVersaoFuckOff(int n, int h, int H);
int rotinaCalcArcosVersaoMotherFucker(int n, int h, int H);
int rotinaCalcArcosVersaoMotherFuckerFinal(int n, int h, int H);



#endif
