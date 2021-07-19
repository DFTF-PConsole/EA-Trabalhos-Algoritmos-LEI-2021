/*  AUTORES: Cláudia Campos N.2018285941 | Dário Félix N.2018275530  */

// FICHEIRO: trab.cpp (funcoes pra auxiliar os testes das funcoes em trab.cpp)



/* HEADERS */
#include "header_trab.h"
#include "header_testes.h"



/* FUNCOES */
void mainTesteJogo() {
    //

    int matriz1[3 * 3] = {
            0, 2, 2,
            4, 8, 0,
            0, 0, 0
    };

    int matriz2[1 * 1] = {
            2
    };

    int matriz3[4 * 4] = {
            0, 2, 2, 0,
            4, 8, 0, 2,
            0, 0, 0, 2,
            4, 0, 0, 8
    };

    int matriz4[5 * 5] = {
            0, 2, 2, 0, 0,
            4, 8, 0, 2, 0,
            0, 0, 0, 2, 0,
            4, 0, 0, 8, 0,
            0, 8, 8, 8, 8
    };

    char str[2];
    bool lixoBool;
    int lixoCountNum;

    printf("\n\n### REGRAS JOGO ### Q: Sair | A: Esquerda | D: Direita | W: Cima | S: Baixo \n\n");

    // --- LINKAR APENAS AQUI ---
    int* link_matriz = matriz4;     // matriz
    int link_n = 5;                 // n correspondente M(n,n)
    // --- --- ---

    lixoCountNum = countNonZeroElements(link_matriz, link_n * link_n);
    printf("\nINFO INICIAL: countNum:%d\n\n", lixoCountNum);

    do {
        printJogo(link_matriz, link_n);
        lixoBool = true;
        printf("\n> ");
        getStringStdin(str, 2);

        switch (str[0]) {
            case 'a':
            case 'A':
                lixoCountNum = esquerda(link_matriz, link_n, lixoCountNum, &lixoBool);
                printf("\nINFO: countNum:%d | isEqual: %d\n\n", lixoCountNum, lixoBool);
                break;

            case 'd':
            case 'D':
                lixoCountNum = direita(link_matriz, link_n, lixoCountNum, &lixoBool);
                printf("\nINFO: countNum:%d | isEqual: %d\n\n", lixoCountNum, lixoBool);
                break;

            case 'w':
            case 'W':
                lixoCountNum = cima(link_matriz, link_n, lixoCountNum, &lixoBool);
                printf("\nINFO: countNum:%d | isEqual: %d\n\n", lixoCountNum, lixoBool);
                break;

            case 's':
            case 'S':
                lixoCountNum = baixo(link_matriz, link_n, lixoCountNum, &lixoBool);
                printf("\nINFO: countNum:%d | isEqual: %d\n\n", lixoCountNum, lixoBool);
                break;
        }

    } while (str[0] != 'q' && str[0] != 'Q');
}



int mainTesteSolvable() {

    int step = 0, n = 0, m = 0;

    std::cin >> step;

    for (int k = 0; k < step; ++k) {

        std::cin >> n >> m;
        int game[n][n];

        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                std::cin >> game[i][j];
            }
        }
        std::cout << "K = " << k << std::endl << "N = " << n << std::endl << "M = " << m << std::endl;
        printMatrix((int*)game, n, n);
        std::cout << "|" << isSolvable((int*)game, n * n) << "|" << std::endl;
    }

    return 0;
}



void mainTesteMooshak() {
    int step = 0, n = 0, m = 0;

    std::cin >> step;

    for (int k = 0; k < step; ++k) {

        std::cin >> n >> m;
        int game[n][n];

        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                std::cin >> game[i][j];
            }
        }

        preCalcJogo((int *) game, n, m);
    }
}



void mainTestePseudoMooshak() {

    int matriz1[3 * 3] = {
            0, 2, 2,
            4, 8, 0,
            0, 0, 0
    };

    int matriz2[1 * 1] = {
            2
    };

    int matriz3[4 * 4] = {
            0, 2, 2, 0,
            4, 8, 0, 2,
            0, 0, 0, 2,
            4, 0, 0, 8
    };

    int matriz4[5 * 5] = {
            0, 2, 2, 0, 0,
            4, 8, 0, 2, 0,
            0, 0, 0, 2, 0,
            4, 0, 0, 8, 0,
            0, 8, 8, 8, 8
    };

    // --- LINKAR APENAS AQUI ---
    int* link_matriz = matriz3;     // matriz
    int link_n = 4;                 // n correspondente M(n,n)
    // --- --- ---

    int n = link_n, m = 10;

    preCalcJogo((int *) link_matriz, n, m);
}



void printMatrix(int* matrix, int line, int col) {
    for (int i = 0; i < line * col; ++i) {
        if (i % col == col - 1) {
            std::cout << matrix[i] << std::endl;
        }
        else {
            std::cout << matrix[i] << " ";
        }
    }
}


/*
void printVector(int* vector, int n) {
    int i = 0;
    for (; i < n - 1; ++i) {
        std::cout << vector[i] << " ";
    }
    std::cout << vector[i] << std::endl;
}
*/


void printJogo(int matriz[], int n) {
    int nn = n * n;
    for (int i = 0; i < nn; i++) {
        if (i % n == 0)
            putchar('\n');
        printf(" %2d ", matriz[i]);
    }
    putchar('\n');
}



void getStringStdin(char string[], int n) {
    /* DESCRICAO: Funcao personalizada para ler, guardar e tratar dados no STDIN, limpando o restante.
     * INPUT: string: local onde é guardada os chars recolhidos | n: tamanho máximo suportado por string
     * OUTPUT: --- */

    int i = 0, c;

    // ler stdin ate atingir o final do stdin ou da memoria disponivel
    while (i < (n - 1) && ((string[i] = (char)getchar()) != '\n' && string[i] != EOF))
        i++;

    // (If) Sobrou dados no stdin > Limpar stdin
    if (string[i] != '\n' && string[i] != EOF)
        while ((c = getchar()) != '\n' && c != EOF);

    // Colocar terminador '\0' no fim
    string[i] = '\0';
}




std::vector<int> left(std::vector<int> linha, int tam_board, int& num_pecas_ativas, int& flag_esquerda) {
    int aux = -1;

    //Calcula a jun��o dos numeros iguais
    for (int i = 0; i < tam_board; i++) {
        if (linha[i] == 0) { //caso a linha seja vazia ignora se
            continue;
        }
        if (aux == -1) { //lembrar a coluna de i
            aux = i;
            continue;
        }
        if (linha[aux] != linha[i]) { //se a linha seguinte n�o tiver valor igual avan�a as duas colunas
            aux = i;
            continue;
        }
        if (linha[aux] == linha[i]) { //se a linha seguinte tiver o valor igual somam se e reseta se o aux
            linha[aux] = linha[aux] + linha[i];
            linha[i] = 0;
            aux = -1;
            num_pecas_ativas--;
            flag_esquerda = 1;
        }
    }

    //Move os numeros para as novas posi��es
    for (int i = 0; i < tam_board * tam_board; i++) {
        aux = i % tam_board; //usamos isto para percorrer o array 2 vezes

        if (aux == tam_board - 1) { //caso seja o ultimo elemento da tabela
            continue;
        }
        if (linha[aux] == 0 && linha[aux + 1] != 0)
        {
            linha[aux] = linha[aux + 1];
            linha[aux + 1] = 0;
            flag_esquerda = 1;
        }

    }

    return linha;
}

std::vector<int> rigth(std::vector<int> linha, int tam_board, int& num_pecas_ativas, int& flag_direita) {
    int aux = -1;

    //Calcula a jun��o dos numeros iguais
    for (int i = tam_board - 1; i >= 0; i--) {
        if (linha[i] == 0) { //caso a linha seja vazia ignora se
            continue;
        }
        if (aux == -1) { //lembrar a coluna de i
            aux = i;
            continue;
        }
        if (linha[aux] != linha[i]) { //se a linha seguinte n�o tiver valor igual avan�a as duas colunas
            aux = i;
            continue;
        }
        if (linha[aux] == linha[i]) { //se a linha seguinte tiver o valor igual somam se e reseta se o aux
            linha[aux] = linha[aux] + linha[i];
            linha[i] = 0;
            aux = -1;
            num_pecas_ativas--;
            flag_direita = 1;

        }
    }

    //Move os numeros para as novas posi��es
    for (int i = tam_board * tam_board - 1; i >= 0; i--) {
        aux = i % tam_board; //usamos isto para percorrer o array 2 vezes

        if (aux == 0) { //caso seja o ultimo elemento da tabela
            continue;
        }
        if (linha[aux] == 0 && linha[aux - 1] != 0)
        {
            linha[aux] = linha[aux - 1];
            linha[aux - 1] = 0;
            flag_direita = 1;
        }

    }

    return linha;
}



//Vai buscar a coluna selecionada e transforma num so array
std::vector<int> getColum(std::vector<std::vector<int>> board, int tam_board, int colum) {
    std::vector<int> end;
    for (int i = 0; i < tam_board; i++) {
        end.push_back(board[i][colum]);
    }
    return end;
}

//Insere na board a nova coluna
std::vector<std::vector<int>> remakeColum(std::vector<std::vector<int>> board, int tam_board, int colum, std::vector<int> new_colum) {
    for (int i = 0; i < tam_board; i++) {
        board[i][colum] = new_colum[i];
    }
    return board;
}

//Usa o metodo left para operar em cima da coluna obtida pelo getColum
std::vector<std::vector<int>> UP(std::vector<std::vector<int>> board, int tam_board, int& num_pecas_ativas, int& flag_up) {
    std::vector<int> aux;

    for (int i = 0; i < tam_board; i++) {
        aux = getColum(board, tam_board, i);
        aux = left(aux, tam_board, num_pecas_ativas, flag_up);
        board = remakeColum(board, tam_board, i, aux);
    }

    return board;
}

//Usa o metodo rigth para operar em cima da coluna obtida pelo getColum
std::vector<std::vector<int>> DOWN(std::vector<std::vector<int>> board, int tam_board, int& num_pecas_ativas, int& flag_down) {
    std::vector<int> aux;

    for (int i = 0; i < tam_board; i++) {
        aux = getColum(board, tam_board, i);
        aux = rigth(aux, tam_board, num_pecas_ativas, flag_down);
        board = remakeColum(board, tam_board, i, aux);
    }

    return board;
}


std::vector<std::vector<int>> rigth_all_lines(std::vector<std::vector<int>> board, int tam_board, int& num_pecas_ativas, int& flag_direita) {
    for (int i = 0; i < tam_board; i++) {
        board[i] = rigth(board[i], tam_board, num_pecas_ativas, flag_direita);
    }
    return board;
}


std::vector<std::vector<int>> left_all_lines(std::vector<std::vector<int>> board, int tam_board, int& num_pecas_ativas, int& flag_esquerda) {
    for (int i = 0; i < tam_board; i++) {
        board[i] = left(board[i], tam_board, num_pecas_ativas, flag_esquerda);
    }
    return board;
}



void mainTesteHelpBeatriz() {
    //



    int matriz1[3 * 3] = {
            0, 2, 2,
            4, 8, 0,
            0, 0, 0
    };

    int matriz2[1 * 1] = {
            2
    };

    int matriz3[4 * 4] = {
            0, 2, 2, 0,
            4, 8, 0, 2,
            0, 0, 0, 2,
            4, 0, 0, 8
    };

    int matriz4[5 * 5] = {
            0, 2, 2, 0, 0,
            4, 8, 0, 2, 0,
            0, 0, 0, 2, 0,
            4, 0, 0, 8, 0,
            0, 8, 8, 8, 8
    };

    std::vector<std::vector<int>> ma1 = { {0, 2, 2, 0},
                                          {4, 8, 0, 2},
                                          {0, 0, 0, 2},
                                          {4, 0, 0, 8} };


    std::vector<std::vector<int>> ma2 = { {4, 2, 2},
                                          {0, 16, 0},
                                          {0, 0, 0} };

    std::vector<std::vector<int>> ma3 = { {2, 0, 0, 0},
                                          {0, 0, 0, 0},
                                          {0, 0, 0, 0},
                                          {0, 0, 0, 0} };



    char str[2];
    //bool lixoBool;
    //int lixoCountNum;
    int result;

    printf("\n\n### REGRAS JOGO ### Q: Sair | A: Esquerda | D: Direita | W: Cima | S: Baixo \n\n");

    // --- LINKAR APENAS AQUI ---
    int* link_matriz = matriz4;     // matriz
    int link_n = 4;                 // n correspondente M(n,n)
    // --- --- ---

    //lixoCountNum = countNonZeroElements(link_matriz, link_n * link_n);
    //printf("\nINFO INICIAL: countNum:%d\n\n", lixoCountNum);
    int num_pecas_ativas = 10;
    int flag_esquerda = 1;

    result = verific_possible(ma3, link_n);
    printf("\nINFO INICIAL: Verifica:%d\n\n", result);

    do {
        printJogoBeatriz(ma3);
        //printJogo(link_matriz, link_n);
        //lixoBool = true;
        printf("\n> ");
        getStringStdin(str, 2);

        switch (str[0]) {
            case 'a':
            case 'A':
                //lixoCountNum = esquerda(link_matriz, link_n, lixoCountNum, &lixoBool);
                //printf("\nINFO: countNum:%d | isEqual: %d\n\n", lixoCountNum, lixoBool);
                ma3 = left_all_lines(ma3, link_n, num_pecas_ativas, flag_esquerda);
                break;

            case 'd':
            case 'D':
                //lixoCountNum = direita(link_matriz, link_n, lixoCountNum, &lixoBool);
                //printf("\nINFO: countNum:%d | isEqual: %d\n\n", lixoCountNum, lixoBool);
                ma3 = rigth_all_lines(ma3, link_n, num_pecas_ativas, flag_esquerda);
                break;

            case 'w':
            case 'W':
                //lixoCountNum = cima(link_matriz, link_n, lixoCountNum, &lixoBool);
                //printf("\nINFO: countNum:%d | isEqual: %d\n\n", lixoCountNum, lixoBool);
                ma3 = UP(ma3, link_n, num_pecas_ativas, flag_esquerda);
                break;

            case 's':
            case 'S':
                //lixoCountNum = baixo(link_matriz, link_n, lixoCountNum, &lixoBool);
                //printf("\nINFO: countNum:%d | isEqual: %d\n\n", lixoCountNum, lixoBool);
                ma3 = DOWN(ma3, link_n, num_pecas_ativas, flag_esquerda);
                break;
        }

    } while (str[0] != 'q' && str[0] != 'Q');
}


void printJogoBeatriz(const std::vector<std::vector<int>>& ma) {

    putchar('\n');
    for (const std::vector<int>& linha : ma) {
        for (int num : linha) {
            printf(" %2d ", num);
        }
        putchar('\n');
    }
    putchar('\n');

}

int verific_possible(std::vector<std::vector<int>> board, int tam_board) {  // TODO WTF
    int menor = 0;
    bool duplo = false;

    for (int i = 0; i < tam_board; i++) {
        for (int j = 0; j < tam_board; j++) {
            if (menor == 0 && board[i][j] > 0) {
                menor = board[i][j];
                continue;
            }
            if (board[i][j] != 0 && board[i][j] < menor) {
                menor = board[i][j];
                duplo = false;
                continue;
            }
            if (board[i][j] == menor) {
                duplo = true;
            }
        }
    }
    if (duplo) {
        return 0;
    }
    else {
        return -1;
    }
}

