/*  AUTORES: Cláudia Campos N.2018285941 | Dário Félix N.2018275530  */

// FICHEIRO: trab.cpp (funcoes a submeter no mooshak)



/* HEADERS */
#include "header_trab.h"
#include "header_testes.h"



/* VARS GLOBAIS */
int bestPlayNum;
int maxPlaysNum;


/* FUNCOES */
int esquerda(int matriz [], int n, int countNum, bool * isEqual) {
    int ultimoIndiceSomado, ultimoIndiceZero, tempIndice, i, j;

    for (i = 0; i < n; i++) {
        for (j = 0, ultimoIndiceSomado = ultimoIndiceZero = -1; j < n - 1; j++) {
            if (ultimoIndiceZero == -1 && matriz[INDICE(i, j, n)] == 0)
                ultimoIndiceZero = j;
            if (matriz[INDICE(i, j, n)] == matriz[INDICE(i, j+1, n)] && matriz[INDICE(i, j, n)] != 0) {
                matriz[INDICE(i, j, n)] += matriz[INDICE(i, j+1, n)];
                matriz[INDICE(i, j+1, n)] = 0;
                ultimoIndiceSomado = j;
                ultimoIndiceZero = j+1;
                countNum--;
                *isEqual = false;
            } else {
                if (matriz[INDICE(i, j, n)] == 0 && (matriz[INDICE(i, j+1, n)] != 0)) {
                    matriz[INDICE(i, ultimoIndiceZero, n)] = matriz[INDICE(i, j + 1, n)];
                    matriz[INDICE(i, j+1, n)] = 0;
                    tempIndice = ultimoIndiceZero;
                    ultimoIndiceZero += 1;
                    *isEqual = false;
                    if (tempIndice > 0 && matriz[INDICE(i, tempIndice -1, n)] == matriz[INDICE(i, tempIndice, n)] && (tempIndice-1) != ultimoIndiceSomado) {
                        matriz[INDICE(i, tempIndice-1, n)] += matriz[INDICE(i, tempIndice, n)];
                        matriz[INDICE(i, tempIndice, n)] = 0;
                        ultimoIndiceSomado = tempIndice -1;
                        ultimoIndiceZero -= 1;
                        countNum--;
                    }
                }
            }
        }
    }

    return countNum;
}



int direita(int matriz[], int n, int countNum, bool * isEqual) {
    int ultimoIndiceSomado, ultimoIndiceZero, tempIndice, i, j;

    for (i = 0; i < n; i++) {
        for (j = n-1, ultimoIndiceSomado = ultimoIndiceZero = -1; j > 0 ; j--) {
            if (ultimoIndiceZero == -1 && matriz[INDICE(i, j, n)] == 0)
                ultimoIndiceZero = j;
            if (matriz[INDICE(i, j, n)] == matriz[INDICE(i, j - 1, n)] && matriz[INDICE(i, j, n)] != 0) {
                matriz[INDICE(i, j, n)] += matriz[INDICE(i, j - 1, n)];
                matriz[INDICE(i, j - 1, n)] = 0;
                ultimoIndiceSomado = j;
                ultimoIndiceZero = j-1;
                countNum--;
                *isEqual = false;
            }
            else {
                if (matriz[INDICE(i, j, n)] == 0 && (matriz[INDICE(i, j - 1, n)] != 0)) {
                    matriz[INDICE(i, ultimoIndiceZero, n)] = matriz[INDICE(i, j - 1, n)];
                    matriz[INDICE(i, j - 1, n)] = 0;
                    tempIndice = ultimoIndiceZero;
                    ultimoIndiceZero -= 1;
                    *isEqual = false;
                    if (tempIndice < n-1 && matriz[INDICE(i, tempIndice, n)] == matriz[INDICE(i, tempIndice +1, n)] && tempIndice+1 != ultimoIndiceSomado) {
                        matriz[INDICE(i, tempIndice+1, n)] += matriz[INDICE(i, tempIndice, n)];
                        matriz[INDICE(i, tempIndice, n)] = 0;
                        ultimoIndiceSomado = tempIndice +1;
                        ultimoIndiceZero += 1;
                        countNum--;
                    }
                }
            }
        }
    }

    return countNum;
}



int cima(int matriz[], int n, int countNum, bool * isEqual) {
    int ultimoIndiceSomado, ultimoIndiceZero, tempIndice, i, j;

    for (j = 0; j < n; j++) {
        for (i = 0, ultimoIndiceSomado = ultimoIndiceZero = -1; i < n - 1; i++) {
            if (ultimoIndiceZero == -1 && matriz[INDICE(i, j, n)] == 0)
                ultimoIndiceZero = i;
            if (matriz[INDICE(i, j, n)] == matriz[INDICE(i + 1, j, n)] && matriz[INDICE(i, j, n)] != 0) {
                matriz[INDICE(i, j, n)] += matriz[INDICE(i + 1, j, n)];
                matriz[INDICE(i + 1, j, n)] = 0;
                ultimoIndiceSomado = i;
                ultimoIndiceZero = i+1;
                countNum--;
                *isEqual = false;
            }
            else {
                if (matriz[INDICE(i, j, n)] == 0 && (matriz[INDICE(i + 1, j, n)] != 0)) {
                    matriz[INDICE(ultimoIndiceZero, j, n)] = matriz[INDICE(i + 1, j, n)];
                    matriz[INDICE(i + 1, j, n)] = 0;
                    tempIndice = ultimoIndiceZero;
                    ultimoIndiceZero += 1;
                    *isEqual = false;
                    if (tempIndice > 0 && matriz[INDICE(tempIndice -1, j, n)] == matriz[INDICE(tempIndice, j, n)] && tempIndice-1 != ultimoIndiceSomado) {
                        matriz[INDICE(tempIndice-1, j, n)] += matriz[INDICE(tempIndice, j, n)];
                        matriz[INDICE(tempIndice, j, n)] = 0;
                        ultimoIndiceSomado = tempIndice -1;
                        ultimoIndiceZero -= 1;
                        countNum--;
                    }
                }
            }
        }
    }

    return countNum;
}



int baixo(int matriz[], int n, int countNum, bool * isEqual) {
    int ultimoIndiceSomado, ultimoIndiceZero, tempIndice, i, j;

    for (j = 0; j < n; j++) {
        for (i = n - 1, ultimoIndiceSomado = ultimoIndiceZero = -1; i > 0; i--) {
            if (ultimoIndiceZero == -1 && matriz[INDICE(i, j, n)] == 0)
                ultimoIndiceZero = i;
            if (matriz[INDICE(i, j, n)] == matriz[INDICE(i - 1, j, n)] && matriz[INDICE(i, j, n)] != 0) {
                matriz[INDICE(i, j, n)] += matriz[INDICE(i - 1, j, n)];
                matriz[INDICE(i - 1, j, n)] = 0;
                ultimoIndiceSomado = i;
                ultimoIndiceZero = i-1;
                countNum--;
                *isEqual = false;
            }
            else {
                if (matriz[INDICE(i, j, n)] == 0 && (matriz[INDICE(i - 1, j, n)] != 0)) {
                    matriz[INDICE(ultimoIndiceZero, j, n)] = matriz[INDICE(i - 1, j, n)];
                    matriz[INDICE(i - 1, j, n)] = 0;
                    tempIndice = ultimoIndiceZero;
                    ultimoIndiceZero -= 1;
                    *isEqual = false;
                    if (tempIndice < n-1 && matriz[INDICE(tempIndice+1, j, n)] == matriz[INDICE(tempIndice, j, n)] && tempIndice+1 != ultimoIndiceSomado) {
                        matriz[INDICE(tempIndice+1, j, n)] += matriz[INDICE(tempIndice, j, n)];
                        matriz[INDICE(tempIndice, j, n)] = 0;
                        ultimoIndiceSomado = tempIndice +1;
                        ultimoIndiceZero += 1;
                        countNum--;
                    }
                }
            }
        }
    }

    return countNum;
}



int countNonZeroElements(const int *vector, int n) {
    int sum = 0;
    for (int i = 0; i < n; ++i) {
        if (*(vector + i)) {
            sum++;
        }
    }
    return sum;
}

/*
int sumVectorElements(const int *vector, int n) {
    int sum = 0;
    for (int i = 0; i < n; ++i) {
        sum += vector[i];
    }
    return sum;
}
*/


bool isSolvable(int *vector, int n) {
    int ocurrences[LIM] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    for (int i = 0; i < n; ++i) {
        if (vector[i] != 0) {
            ocurrences[(int) log2(vector[i]) - 1]++;
        }
    }
    int sum = 0;
    for (int i = 0; i < LIM - 1; ++i) {
        if (ocurrences[i] > 1) {
            ocurrences[i + 1] += ocurrences[i] / 2;
            ocurrences[i] = ocurrences[i] % 2;
        }
        sum += ocurrences[i];
    }
    return (sum == 1);
}



void copyArray(int *a, const int *b, int n) {
    for (int i = 0; i < n; ++i) {
        a[i] = b[i];
    }
}


int preCalcJogo(const int * tabuleiro, int tamanho, int maxPlays) {
    bestPlayNum = maxPlays + 1;
    maxPlaysNum = maxPlays;
    int countNum = countNonZeroElements(tabuleiro, tamanho * tamanho);
    if (isSolvable((int *) tabuleiro, tamanho * tamanho))
        calcJogo(tabuleiro, tamanho, 0, countNum);
    (bestPlayNum == maxPlaysNum + 1) ? (std::cout << IMPOSSIVEL << std::endl) : (std::cout << bestPlayNum << std::endl);
    return bestPlayNum;
}



void calcJogo(const int *tabuleiro, int tamanho, int countPlays, int countNum) {
    if (countPlays > maxPlaysNum || countPlays >= bestPlayNum ) {
        return;
    } else if (countNum == 1) {
        bestPlayNum = countPlays;
        return;
    }

    int dobroTamanho = tamanho * tamanho;
    int tabEsq[dobroTamanho], tabDir[dobroTamanho], tabCim[dobroTamanho], tabBai[dobroTamanho];
    int i;

    Heuristicas tabs[4];

    tabs[0].tab = tabEsq;
    tabs[1].tab = tabDir;
    tabs[2].tab = tabCim;
    tabs[3].tab = tabBai;

    for (i = 0; i < 4; i++)
        tabs[i].isEqual = true;

    for (Heuristicas t : tabs)
        copyArray(t.tab, tabuleiro, dobroTamanho);

    tabs[0].countNum = esquerda(tabEsq, tamanho, countNum, &(tabs[0].isEqual));
    tabs[1].countNum = direita(tabDir, tamanho, countNum, &(tabs[1].isEqual));
    tabs[2].countNum = cima(tabCim, tamanho, countNum, &(tabs[2].isEqual));
    tabs[3].countNum = baixo(tabBai, tamanho, countNum, &(tabs[3].isEqual));


    for (i = 0; i < 4; i++)
        tabs[i].countPlaysNeed = ceil(log2(tabs[i].countNum));


    // Ordenar Tabuleiros
    Heuristicas temp;
    int low = 0, high = 3, j;
    for (i = low + 1; i <= high; ++i) {
        for (j = low; j < i; ++j) {
            if ((tabs[i].countNum - tabs[j].countNum) < 0) {
                temp = tabs[i];
                tabs[i] = tabs[j];
                tabs[j] = temp;
            }
        }
    }

    i = 0;
    for (Heuristicas t : tabs) {
        if (!tabs[i].isEqual && countPlays < bestPlayNum -1 && tabs[i].countPlaysNeed <= (maxPlaysNum - countPlays))
            calcJogo(t.tab, tamanho, countPlays + 1, tabs[i].countNum);
        i++;
    }

}


/*
void game(int *matrix, int num, int maxPlays, int numPlays, int *playNum) {
    if (countNonZeroElements(matrix, num * num) == 1 && ((*playNum == -1) || (numPlays < *playNum))) {
        *playNum = numPlays;
        return;
    } else if (numPlays == maxPlays) {
        return;
    }

    int aux[num * num];
    copyArray(aux, matrix, num * num);
    esquerda(aux, num);
    if (!isEqual(matrix, aux, num * num)) {
        game(aux, num, maxPlays, numPlays + 1, playNum);
    }

    copyArray(aux, matrix, num * num);
    direita(aux, num);
    if (!isEqual(matrix, aux, num * num)) {
        game(aux, num, maxPlays, numPlays + 1, playNum);
    }

    copyArray(aux, matrix, num * num);
    cima(aux, num);
    if (!isEqual(matrix, aux, num * num)) {
        game(aux, num, maxPlays, numPlays + 1, playNum);
    }

    copyArray(aux, matrix, num * num);
    baixo(aux, num);
    if (!isEqual(matrix, aux, num * num)) {
        game(aux, num, maxPlays, numPlays + 1, playNum);
    }
}
*/

/*
int jogo(int *matrix, int num, int maxPlays) {
    int playNum = -1;
    game(matrix, num, maxPlays, 0, &playNum);
    (playNum == -1) ? std::cout << IMPOSSIVEL << std::endl : std::cout << playNum << std::endl;
    return playNum;
}
*/


/*
bool checkSimetriaHorizontal(const int matrizEsq [], const int matrizDir [], int n) {
    int ptr [n];

    int i, j;

    for (i = 0; i<n ; i++) {
        for (j = 0; j<n && matrizDir[INDICE(i, j, n)] == 0 ; j++);
        ptr[i] = (j >= n ? -1 : j);
    }

    for (i = 0; i<n ; i++) {
        if (matrizEsq[INDICE(i, 0, n)] == 0 && ptr[i] == -1)
            continue;   // ainda sao simetricos
        else if (matrizEsq[INDICE(i, 0, n)] != 0 && ptr[i] == -1)
            return false;   // nao sao simetricos

        for (j = 0; j < n; j++, ptr[i]++) {
            if ((matrizEsq[INDICE(i, j, n)] == 0 && ptr[i] < n) || (matrizEsq[INDICE(i, j, n)] != 0 && ptr[i] >= n))
                return false;   // nao sao simetricos

            if (matrizEsq[INDICE(i, j, n)] != matrizDir[INDICE(i, ptr[i], n)])
                return false;   // nao sao simetricos
        }
    }

    return true;
}


bool checkSimetriaVertical(const int matrizCim [], const int matrizBai [], int n) {
    int ptr [n];

    int i, j;

    for (j = 0; j<n ; j++) {
        for (i = 0; i<n && matrizBai[INDICE(i, j, n)] == 0 ; i++);
        ptr[j] = (i >= n ? -1 : i);
    }

    for (j = 0; j<n ; j++) {
        if (matrizCim[INDICE(0, j, n)] == 0 && ptr[j] == -1)
            continue;   // ainda sao simetricos
        else if (matrizCim[INDICE(0, j, n)] != 0 && ptr[j] == -1)
            return false;   // nao sao simetricos

        for (i = 0; i < n; i++, ptr[j]++) {
            if ((matrizCim[INDICE(i, j, n)] == 0 && ptr[j] < n) || (matrizCim[INDICE(i, j, n)] != 0 && ptr[j] >= n))
                return false;   // nao sao simetricos

            if (matrizCim[INDICE(i, j, n)] != matrizBai[INDICE(i, ptr[j], n)])
                return false;   // nao sao simetricos
        }
    }

    return false;
}

*/


/*
bool isEqual(const int *a, const int *b, int n) {
    int i = 0;
    for (; i < n && a[i] == b[i]; ++i);
    return i == n;
}
*/
