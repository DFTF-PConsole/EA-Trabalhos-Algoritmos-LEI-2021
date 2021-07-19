/*  AUTORES: Cláudia Campos N.2018285941 | Dário Félix N.2018275530  */

// FICHEIRO: header_testes.h (relativo ao testes.cpp)


#ifndef TRAB1_NOVO_HEADER_TESTES_H
#define TRAB1_NOVO_HEADER_TESTES_H


/* BIBLIOTECAS */
#include <cstdio>
#include <iostream>
#include <vector>


/* CONSTANTES */



/* MACROS */




/* DEFINICOES e ESTRUTURAS */




/* PROTOTIPOS */
void mainTesteJogo();
int mainTesteSolvable();
void printJogo(int [], int n);
void getStringStdin(char [], int n);
void printMatrix(int* , int , int);
//void printVector(int* , int );
void mainTesteMooshak();
void mainTestePseudoMooshak();


// HELP BEATRIZ - Copyrights
void mainTesteHelpBeatriz();
std::vector<std::vector<int>> DOWN(std::vector<std::vector<int>> board, int tam_board, int& num_pecas_ativas, int& flag_down);
std::vector<std::vector<int>> UP(std::vector<std::vector<int>> board, int tam_board, int& num_pecas_ativas, int& flag_up);
std::vector<std::vector<int>> remakeColum(std::vector<std::vector<int>> board, int tam_board, int colum, std::vector<int> new_colum);
std::vector<int> getColum(std::vector<std::vector<int>> board, int tam_board, int colum);
std::vector<int> rigth(std::vector<int> linha, int tam_board, int& num_pecas_ativas, int& flag_direita);
std::vector<int> left(std::vector<int> linha, int tam_board, int& num_pecas_ativas, int& flag_esquerda);
std::vector<std::vector<int>> rigth_all_lines(std::vector<std::vector<int>> board, int tam_board, int& num_pecas_ativas, int& flag_direita);
std::vector<std::vector<int>> left_all_lines(std::vector<std::vector<int>> board, int tam_board, int& num_pecas_ativas, int& flag_esquerda);
void printJogoBeatriz(const std::vector<std::vector<int>>& ma);
int verific_possible(std::vector<std::vector<int>> board, int tam_board);



#endif
