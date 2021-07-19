/*  AUTORES: Cláudia Campos N.2018285941 | Dário Félix N.2018275530  */

// FICHEIRO: trab.cpp (funcoes a submeter no mooshak)



/* HEADERS */
#include "header_trab.h"
#include "header_testes.h"



/* VARS GLOBAIS */



/* FUNCOES */
int modAbs(int a, int mod) {
    return ((a % mod) + mod) % mod;
}



int modAdd(int a, int b, int mod) {
    return (modAbs(a, mod) + modAbs(b, mod)) % mod;
}



int modSub(int a, int b, int mod) {
    return modAdd(a, -b, mod);
}




int calc(Cache cache[], int eu) {
    int i;

    for (i = 0 ; i < eu ; i++) {
        if (cache[i].h == cache[eu].h && cache[i].H == cache[eu].H) {
            cache[eu].dados = cache[i].dados;
            break;
        }
    }

    if (cache[eu].dados.empty()) {  // vector novo
        cache[eu].dados.push_back(rotinaCalcArcos(MIN_n, cache[eu].h, cache[eu].H));    // i = 0

        for (i = 1 ; i < cache[eu].n ; i++) { // i >= 1
            cache[eu].dados.push_back(modAdd(cache[eu].dados[i-1], rotinaCalcArcos(MIN_n + i, cache[eu].h, cache[eu].H), MODULO));
        }

    } else if (cache[i].dados.size() + MIN_n < (unsigned int) cache[eu].n) {  // completar vector ate o novo n
        for ( ; i < cache[eu].n ; i++) { // i >= 1
            cache[eu].dados.push_back(modAdd(cache[eu].dados[i-1], rotinaCalcArcos(MIN_n + i, cache[eu].h, cache[eu].H), MODULO));
        }
    }   // else: o valor de n ja se encontra calculado


    return cache[eu].dados[cache[eu].n - MIN_n];
}



int rotinaCalcArcos(int n, int h, int H) {
    std::vector<std::vector<int>> matriz(n, std::vector<int>(H));
    //int matriz [n][H];
    int i, j, z;
    int acumula;

    for (i = 0 ; i < H ; i++) {
        matriz [0][i] = 0;
    }

    matriz [0][H-h] = 1;  // caso base

    for (i = 1 ; i < n ; i++) {
        for (j = H-1 ; j >= 0 ; j--) {
            matriz[i][j] = 0;
            for (z = j+1 ; z <= j+h-1 ; z++) {
                matriz[i][j] = modAdd(matriz[i][j], (z >= H) ? 0 : matriz[i-1][z] , MODULO);
            }
        }
    }

    for (i = 2 ; i < n ; i++) {
        for (j = 0; j <= H-h ; j++) {
            for (z = j-1 ; z >= j-h+1 ; z--) {
                matriz[i][j] = modAdd(matriz[i][j], (z < 0) ? 0 : matriz[i-1][z] , MODULO);
            }
        }
    }

    for (acumula=0, i = 2 ; i < n ; i++) {
        acumula = modAdd(acumula, matriz [i][H-h] , MODULO);
    }

    return acumula;
}


int rotinaCalcArcosVersaoFuckOff(int n, int h, int H) {
    int HMax = std::min(h + ((h-1) * (n-1)), H) - (h-1);
    std::vector<std::vector<int>> matriz(n, std::vector<int>(HMax));
    int i, j, z;

    // CASO BASE
    for (j = 0 ; j < HMax-1 ; j++)
        matriz [0][j] = 0;
    matriz [0][HMax-1] = 1;

    // SUBIDA
    for (i = 1 ; i < n ; i++) {
        matriz[i][HMax-1] = 0;
        for (j = HMax-2 ; j >= 0 ; j--) {
            matriz[i][j] = matriz[i-1][j+1];
            for (z = j+2 ; (z <= j+h-1) && (z < HMax) ; z++) {
                matriz[i][j] = modAdd(matriz[i][j], matriz[i-1][z], MODULO);
            }
        }
    }

    // DESCIDA
    for (i = 2 ; i < n ; i++) {
        for (j = 0; j < HMax ; j++) {
            for (z = j-1 ; (z >= j-h+1) && (z >= 0) ; z--) {
                    matriz[i][j] = modAdd(matriz[i][j], matriz[i-1][z], MODULO);
            }
        }
        matriz[i][HMax-1] = modAdd(matriz[i-1][HMax-1], matriz[i][HMax-1], MODULO);
    }

    return matriz[n-1][HMax-1];
}



int rotinaCalcArcosVersaoMotherFucker(int n, int h, int H) {
    int HMax = std::min(h + ((h-1) * (n-1)), H) - (h-1);
    std::vector<std::vector<int>> matriz(n, std::vector<int>(HMax));
    int i, j, cache;

    // CASO BASE
    for (j = 0 ; j < HMax-1 ; j++)
        matriz [0][j] = 0;
    matriz [0][HMax-1] = 1;

    // SUBIDA
    for (i = 1 ; i < n ; i++) {
        matriz[i][HMax-1] = 0;
        for (j = HMax-2 ; j >= 0 ; j--) {
            matriz[i][j] = modAdd(matriz[i-1][j+1], matriz[i][j+1], MODULO);
            if (j+h < HMax)
                matriz[i][j] = modSub(matriz[i][j], matriz[i-1][j+h], MODULO);
        }
    }

    // DESCIDA
    for (i = 2 ; i < n ; i++) {
        for (j = 1, cache = 0; j < HMax ; j++) {
            cache = modAdd(cache, matriz[i-1][j-1], MODULO);
            if (j-h >= 0)
                cache = modSub(cache, matriz[i-1][j-h], MODULO);
            matriz[i][j] = modAdd(matriz[i][j], cache, MODULO);
        }
        matriz[i][HMax-1] = modAdd(matriz[i-1][HMax-1], matriz[i][HMax-1], MODULO);
    }

    return matriz[n-1][HMax-1];
}



// VERSAO FINAL
int rotinaCalcArcosVersaoMotherFuckerFinal(int n, int h, int H) {
    int HMax = std::min(h + ((h-1) * (n-1)), H) - (h-1);
    int nMax = std::min(1 + (2 * (HMax-1)), n);
    int i, j, cache;

    int * matriz = (int *) malloc(nMax * HMax * sizeof(int));
    if (matriz == nullptr)
        return -1;

    // Interpretar:  Matriz[i][j]  <=>  Matriz[INDICE(i, j, nMax)]  <=>  Matriz[(((i)*nMax) + (j))]
    // 0 <= i < HMax (linhas)
    // 0 <= j < nMax (colunas)

    // CASO BASE
    for (i = 0 ; i < HMax-1 ; i++)
        matriz[INDICE(i, 0, nMax)] = 0;
    matriz[INDICE(HMax-1, 0, nMax)] = 1;


    // SUBIDA
    for (j = 1 ; j < nMax ; j++) {
        matriz[INDICE(HMax-1, j, nMax)] = 0;
        for (i = HMax-2 ; i >= 0 ; i--) {
            matriz[INDICE(i, j, nMax)] = modAdd(matriz[INDICE(i+1, j-1, nMax)], matriz[INDICE(i+1, j, nMax)], MODULO);
            if (i+h < HMax)
                matriz[INDICE(i, j, nMax)] = modSub(matriz[INDICE(i, j, nMax)], matriz[INDICE(i+h, j-1, nMax)], MODULO);
        }
    }

    // DESCIDA
    for (j = 2 ; j < nMax ; j++) {
        for (i = 1, cache = 0; i < HMax ; i++) {
            cache = modAdd(cache, matriz[INDICE(i-1, j-1, nMax)], MODULO);
            if (i-h >= 0)
                cache = modSub(cache, matriz[INDICE(i-h, j-1, nMax)], MODULO);
            matriz[INDICE(i, j, nMax)] = modAdd(matriz[INDICE(i, j, nMax)], cache, MODULO);
        }
        matriz[INDICE(HMax -1, j, nMax)] = modAdd(matriz[INDICE(HMax -1, j -1, nMax)], matriz[INDICE(HMax -1, j, nMax)], MODULO);
    }


    cache = matriz[INDICE(HMax -1, nMax -1, nMax)];

    free((void *) matriz);

    return cache;
}


