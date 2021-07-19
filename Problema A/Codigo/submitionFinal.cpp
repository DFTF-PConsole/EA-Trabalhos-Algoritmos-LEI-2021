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
 *  Problem A - 2048 clean up!                                                  *
 *  FCTUC - DEI/LEI - Estrategias Algoritmicas                                  *
 *  Coimbra, 11 de abril de 2021, 23:59h                                        *
 ********************************************************************************/


#include <iostream>
#include <iomanip>
#include <cmath>
#include <cstring>
#include <algorithm>

#define INDICE(I, J, N)  (((I)*N) + (J))
#define LIM 30          //sizeof(int) * 8 - 2
#define PLAYS 4
#define IMPOSSIVEL "no solution"

struct board {
    int *board;
    int countNum;
    int countPlaysNeeded;
    bool isEqual;
};

int bestPlayNum;
int maxPlaysNum;

int esquerda(int *, int, int, bool *);

int direita(int *, int, int, bool *);

int cima(int *, int, int, bool *);

int baixo(int *, int, int, bool *);

bool isInteger(double);

int sumArray(const int *, int);

bool isSolvable(int *, int);

bool isSolvable2(const int *, int);

int countNonZeroElements(const int *, int);

void calcJogo(const int *, int, int, int, int (*[])(int *, int, int, bool *));

int preCalcJogo(const int *, int, int);

/* FUNÇÕES */
int esquerda(int *matriz, int n, int countNum, bool *isEqual) {
    int ultimoIndiceSomado, ultimoIndiceZero, tempIndice, i, j;
    *isEqual = true;
    for (i = 0; i < n; ++i) {
        for (j = 0, ultimoIndiceSomado = ultimoIndiceZero = -1; j < n - 1; j++) {
            if (ultimoIndiceZero == -1 && matriz[INDICE(i, j, n)] == 0)
                ultimoIndiceZero = j;
            if (matriz[INDICE(i, j, n)] == matriz[INDICE(i, j + 1, n)] && matriz[INDICE(i, j, n)] != 0) {
                matriz[INDICE(i, j, n)] += matriz[INDICE(i, j + 1, n)];
                matriz[INDICE(i, j + 1, n)] = 0;
                ultimoIndiceSomado = j;
                ultimoIndiceZero = j + 1;
                countNum--;
                *isEqual = false;
            } else {
                if (matriz[INDICE(i, j, n)] == 0 && (matriz[INDICE(i, j + 1, n)] != 0)) {
                    matriz[INDICE(i, ultimoIndiceZero, n)] = matriz[INDICE(i, j + 1, n)];
                    matriz[INDICE(i, j + 1, n)] = 0;
                    tempIndice = ultimoIndiceZero;
                    ultimoIndiceZero += 1;
                    *isEqual = false;
                    if (tempIndice > 0 && matriz[INDICE(i, tempIndice - 1, n)] == matriz[INDICE(i, tempIndice, n)] &&
                        (tempIndice - 1) != ultimoIndiceSomado) {
                        matriz[INDICE(i, tempIndice - 1, n)] += matriz[INDICE(i, tempIndice, n)];
                        matriz[INDICE(i, tempIndice, n)] = 0;
                        ultimoIndiceSomado = tempIndice - 1;
                        ultimoIndiceZero -= 1;
                        countNum--;
                    }
                }
            }
        }
    }

    return countNum;
}

int direita(int *matriz, int n, int countNum, bool *isEqual) {
    int ultimoIndiceSomado, ultimoIndiceZero, tempIndice, i, j;
    *isEqual = true;
    for (i = 0; i < n; i++) {
        for (j = n - 1, ultimoIndiceSomado = ultimoIndiceZero = -1; j > 0; j--) {
            if (ultimoIndiceZero == -1 && matriz[INDICE(i, j, n)] == 0)
                ultimoIndiceZero = j;
            if (matriz[INDICE(i, j, n)] == matriz[INDICE(i, j - 1, n)] && matriz[INDICE(i, j, n)] != 0) {
                matriz[INDICE(i, j, n)] += matriz[INDICE(i, j - 1, n)];
                matriz[INDICE(i, j - 1, n)] = 0;
                ultimoIndiceSomado = j;
                ultimoIndiceZero = j - 1;
                countNum--;
                *isEqual = false;
            } else {
                if (matriz[INDICE(i, j, n)] == 0 && (matriz[INDICE(i, j - 1, n)] != 0)) {
                    matriz[INDICE(i, ultimoIndiceZero, n)] = matriz[INDICE(i, j - 1, n)];
                    matriz[INDICE(i, j - 1, n)] = 0;
                    tempIndice = ultimoIndiceZero;
                    ultimoIndiceZero -= 1;
                    *isEqual = false;
                    if (tempIndice < n - 1 && matriz[INDICE(i, tempIndice, n)] == matriz[INDICE(i, tempIndice + 1, n)] &&
                        tempIndice + 1 != ultimoIndiceSomado) {
                        matriz[INDICE(i, tempIndice + 1, n)] += matriz[INDICE(i, tempIndice, n)];
                        matriz[INDICE(i, tempIndice, n)] = 0;
                        ultimoIndiceSomado = tempIndice + 1;
                        ultimoIndiceZero += 1;
                        countNum--;
                    }
                }
            }
        }
    }

    return countNum;
}

int cima(int *matriz, int n, int countNum, bool *isEqual) {
    int ultimoIndiceSomado, ultimoIndiceZero, tempIndice, i, j;
    *isEqual = true;
    for (j = 0; j < n; j++) {
        for (i = 0, ultimoIndiceSomado = ultimoIndiceZero = -1; i < n - 1; i++) {
            if (ultimoIndiceZero == -1 && matriz[INDICE(i, j, n)] == 0)
                ultimoIndiceZero = i;
            if (matriz[INDICE(i, j, n)] == matriz[INDICE(i + 1, j, n)] && matriz[INDICE(i, j, n)] != 0) {
                matriz[INDICE(i, j, n)] += matriz[INDICE(i + 1, j, n)];
                matriz[INDICE(i + 1, j, n)] = 0;
                ultimoIndiceSomado = i;
                ultimoIndiceZero = i + 1;
                countNum--;
                *isEqual = false;
            } else {
                if (matriz[INDICE(i, j, n)] == 0 && (matriz[INDICE(i + 1, j, n)] != 0)) {
                    matriz[INDICE(ultimoIndiceZero, j, n)] = matriz[INDICE(i + 1, j, n)];
                    matriz[INDICE(i + 1, j, n)] = 0;
                    tempIndice = ultimoIndiceZero;
                    ultimoIndiceZero += 1;
                    *isEqual = false;
                    if (tempIndice > 0 && matriz[INDICE(tempIndice - 1, j, n)] == matriz[INDICE(tempIndice, j, n)] &&
                        tempIndice - 1 != ultimoIndiceSomado) {
                        matriz[INDICE(tempIndice - 1, j, n)] += matriz[INDICE(tempIndice, j, n)];
                        matriz[INDICE(tempIndice, j, n)] = 0;
                        ultimoIndiceSomado = tempIndice - 1;
                        ultimoIndiceZero -= 1;
                        countNum--;
                    }
                }
            }
        }
    }

    return countNum;
}

int baixo(int *matriz, int n, int countNum, bool *isEqual) {
    int ultimoIndiceSomado, ultimoIndiceZero, tempIndice, i, j;
    *isEqual = true;
    for (j = 0; j < n; j++) {
        for (i = n - 1, ultimoIndiceSomado = ultimoIndiceZero = -1; i > 0; i--) {
            if (ultimoIndiceZero == -1 && matriz[INDICE(i, j, n)] == 0)
                ultimoIndiceZero = i;
            if (matriz[INDICE(i, j, n)] == matriz[INDICE(i - 1, j, n)] && matriz[INDICE(i, j, n)] != 0) {
                matriz[INDICE(i, j, n)] += matriz[INDICE(i - 1, j, n)];
                matriz[INDICE(i - 1, j, n)] = 0;
                ultimoIndiceSomado = i;
                ultimoIndiceZero = i - 1;
                countNum--;
                *isEqual = false;
            } else {
                if (matriz[INDICE(i, j, n)] == 0 && (matriz[INDICE(i - 1, j, n)] != 0)) {
                    matriz[INDICE(ultimoIndiceZero, j, n)] = matriz[INDICE(i - 1, j, n)];
                    matriz[INDICE(i - 1, j, n)] = 0;
                    tempIndice = ultimoIndiceZero;
                    ultimoIndiceZero -= 1;
                    *isEqual = false;
                    if (tempIndice < n - 1 &&
                        matriz[INDICE(tempIndice + 1, j, n)] == matriz[INDICE(tempIndice, j, n)] &&
                        tempIndice + 1 != ultimoIndiceSomado) {
                        matriz[INDICE(tempIndice + 1, j, n)] += matriz[INDICE(tempIndice, j, n)];
                        matriz[INDICE(tempIndice, j, n)] = 0;
                        ultimoIndiceSomado = tempIndice + 1;
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

bool isInteger(double n) {
    double nAbs = std::abs(n);
    return std::floor(nAbs) == nAbs;
}

int sumArray(const int *vector, int n) {
    int sum = 0;
    for(int i = 0; i < n; ++i) {
        sum += vector[i];
    }
    return sum;
}

bool isSolvable2(const int *vector, int n) {
    return isInteger(log2(sumArray(vector, n)));
}

bool isSolvable(int *vector, int n) {
    int ocurrences[LIM] = {}, sum = 0;
    for (int i = 0; i < n; ++i) {
        if (vector[i] != 0) {
            ocurrences[(int) log2(vector[i]) - 1]++;
        }
    }
    for (int i = 0; i < LIM - 1; ++i) {
        if (ocurrences[i] > 1) {
            ocurrences[i + 1] += ocurrences[i] / 2;
            ocurrences[i] = ocurrences[i] % 2;
        }
        sum += ocurrences[i];
    }
    return (sum == 1);
}

int preCalcJogo(const int *tabuleiro, int tamanho, int maxPlays) {
    int (*moves[PLAYS])(int *, int, int, bool *) = {esquerda, direita, cima, baixo};
    bestPlayNum = maxPlays + 1;
    maxPlaysNum = maxPlays;
    int countNum = countNonZeroElements(tabuleiro, tamanho * tamanho);
    if (isSolvable2(tabuleiro, tamanho * tamanho)) {
        calcJogo(tabuleiro, tamanho, 0, countNum, moves);
    }
    (bestPlayNum == maxPlaysNum + 1) ? (std::cout << IMPOSSIVEL << std::endl) : (std::cout << bestPlayNum << std::endl);
    return bestPlayNum;
}

bool compareCountNumAscending(struct board a, struct board b) {
    return a.countNum < b.countNum;
}

void inicializaBoards(struct board *boards, int numBoards, const int *mainBoard, int mainBoardsize, int countNum, int (*moves[])(int *, int, int, bool *)) {
    for (int i = 0; i < numBoards; ++i) {
        (boards + i)->board = (int *) malloc(sizeof(int) * mainBoardsize * mainBoardsize);
        memcpy((boards + i)->board, mainBoard, sizeof(int) * mainBoardsize * mainBoardsize);
        (boards + i)->countNum = moves[i]((boards + i)->board, mainBoardsize, countNum, &((boards + i)->isEqual));
        (boards + i)->countPlaysNeeded = ceil(log2((boards + i)->countNum));
    }
}

void eliminaBoards(struct board *boards, int numBoards) {
    for (int i = 0; i < numBoards; ++i) {
        free((boards + i)->board);
    }
}

void calcJogo(const int *tabuleiro, int tamanho, int countPlays, int countNum, int (*moves[])(int *, int, int, bool *)) {
    if (countPlays > maxPlaysNum || countPlays >= bestPlayNum) {
        return;
    } else if (countNum == 1) {
        bestPlayNum = countPlays;
        return;
    }

    struct board tabs[PLAYS];

    inicializaBoards(tabs, PLAYS, tabuleiro, tamanho, countNum, moves);

    std::sort(tabs, tabs + PLAYS - 1, compareCountNumAscending);

    for (struct board t : tabs) {
        if (!t.isEqual && countPlays < bestPlayNum - 1 && t.countPlaysNeeded <= (maxPlaysNum - countPlays)) {
            calcJogo(t.board, tamanho, countPlays + 1, t.countNum, moves);
        }
    }

    eliminaBoards(tabs, PLAYS);
}

int main() {
    int step = 0, n = 0, m = 0, *game;

    std::cin >> step;

    for (int k = 0; k < step; ++k) {

        std::cin >> n >> m;

        game = (int *) malloc(sizeof(int) * n * n);

        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                std::cin >> game[INDICE(i, j, n)];
            }
        }
        preCalcJogo(game, n, m);

        free(game);
    }
    return 0;
}
