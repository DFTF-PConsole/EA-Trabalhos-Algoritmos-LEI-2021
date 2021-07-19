/********************************************************************************
 * "YOU MAY THINK THAT THIS FUNCTION IS OBSOLETE AND DOESNT SEEM TO DO ANYTHING *
 * AND YOU WOULD BE CORRECT BUT WHEN WE REMOVE THIS FUNTION FOR SOME REASON     *
 * THE WHOLE PROGRAM CRASHES AND WE CANT FIGURE OUT WHY SO HERE IT WILL STAY"   *
 *                                       - Fernando Pessoa (segundo a internet) *
 *  Autores:                                                                    *
 *      > Claudia Campos (N.2018285941)                                         *
 *      > Dario Felix (N.2018275530)                                            *
 *                                                                              *
 *  Agradecimentos:                                                             *
 *      > Google                                                                *
 *      > Stackoverflow                                                         *
 *      > IDEs                                                                  *
 *      > Take Away do Pingo Doce                                               *
 *      > Take Away do SASUC                                                    *
 *      > Cafe                                                                  *
 *      > Professores                                                           *
 *      > Mooshak, quando quer                                                  *
 *                                                                              *
 *  Problem B - ARChitecture                                                    *
 *  FCTUC - DEI/LEI - Estrategias Algoritmicas                                  *
 *  Coimbra, 30 de abril de 2021, 23:59h                                        *
 ********************************************************************************/


#include <iostream>
#include <cstdlib>

#define INDICE(I, J, N)  (((I)*(N)) + (J))

#define MODULO 1000000007



int modAbs(int a, int mod) {
    return ((a % mod) + mod) % mod;
}



int modAdd(int a, int b, int mod) {
    return (modAbs(a, mod) + modAbs(b, mod)) % mod;
}


int modSub(int a, int b, int mod) {
    return modAdd(a, -b, mod);
}


int rotinaCalcArcos(int n, int h, int H) {
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



int main() {
    // LER INPUT
    int t = 0, n = 0, h = 0, H = 0;
    std::cin >> t;

    for (int i = 0; i < t; ++i) {
        std::cin >> n >> h >> H;
		
        if (n < 3 || H <= h)
            std::cout << 0 << std::endl;
        else
            std::cout << rotinaCalcArcos(n, h, H) << std::endl;
    }
	
	return 0;
}

