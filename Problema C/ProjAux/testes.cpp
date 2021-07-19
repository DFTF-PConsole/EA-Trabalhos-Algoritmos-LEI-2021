/*  AUTORES: Cláudia Campos N.2018285941 | Dário Félix N.2018275530  */

// FICHEIRO: trab.cpp (funcoes pra auxiliar os testes das funcoes em trab.cpp)



/* HEADERS */
#include "header_trab.h"
#include "header_testes.h"




/* FUNCOES */
void mainTesteMooshak() {
    // ler input
    int t, n, m, q, a, b, d;

    std::cin >> t;

    for (int i = 0; i < t; ++i) {
        std::cin >> n >> m >> q;
        std::deque<Node> adj;

        for (int k = 0; k < n; ++k) {
            adj.emplace_back(k);
        }

        std::deque<Circuit> circuits;
        std::deque<int> questions(q, 0);

        for (int j = 0; j < m; ++j) {
            std::cin >> a >> b >> d;
            adj[a - 1].neighbors.emplace_back(adj[b - 1].id, d);
        }

        tarjan(adj, circuits);

        if(q > 2) {
            for (auto &circuit : circuits) {
                kruskal(adj, circuit, n);
            }
        }

        switch (q) {
            case 4:
                questions[3] = question04(circuits);
                [[fallthrough]];
            case 3:
                questions[2] = question03(circuits);
                [[fallthrough]];
            default:
                [[fallthrough]];
            case 2:
                questions[1] = question02(circuits);
                [[fallthrough]];
            case 1:
                questions[0] = question01(circuits);
                break;
        }

        printDeque(questions, 0, q);
    }
}



void printMatrix(const int *matrix, int lines, int columns) {
    for (int i = 0, j; i < lines; ++i) {
        for (j = 0; j < columns - 1; ++j) {
            std::cout << matrix[INDEX(i, j, columns)] << "\t";
        }
        std::cout << matrix[INDEX(i, j, columns)] << std::endl;
    }
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
