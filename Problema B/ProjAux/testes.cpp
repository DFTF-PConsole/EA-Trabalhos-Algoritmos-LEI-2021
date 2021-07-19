/*  AUTORES: Cláudia Campos N.2018285941 | Dário Félix N.2018275530  */

// FICHEIRO: trab.cpp (funcoes pra auxiliar os testes das funcoes em trab.cpp)



/* HEADERS */
#include "header_trab.h"
#include "header_testes.h"



/* FUNCOES */
void mainTesteMooshak() {
    // ler input

    int t = 0, n = 0, h = 0, H = 0;
    std::cin >> t;

    Cache cache[t];

    for (int i = 0; i < t; ++i) {
        std::cin >> n >> h >> H;
        cache[i].H = H;
        cache[i].h = h;
        cache[i].n = n;
        //metadados[i].resultado = 0;
        std::cout << calc(cache, i) << std::endl;
    }

}



void mainTesteMooshakV2() {
    // LER INPUT
    int t = 0, n = 0, h = 0, H = 0;
    std::cin >> t;

    for (int i = 0; i < t; ++i) {
        std::cin >> n >> h >> H;

        if (n < 3 || H <= h)
            std::cout << 0 << std::endl;
        else
            std::cout << rotinaCalcArcosVersaoMotherFuckerFinal(n, h, H) << std::endl;
    }
}



void mainTestePseudoMooshak() {


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
