/*  AUTORES: Cláudia Campos N.2018285941 | Dário Félix N.2018275530  */

// FICHEIRO: header_trab.h (relativo ao trab.cpp)


#ifndef TRAB1_NOVO_HEADER_TRAB_H
#define TRAB1_NOVO_HEADER_TRAB_H


/* BIBLIOTECAS */
#include <iostream>
#include <algorithm>
#include <list>
#include <deque>
#include <stack>



/* CONSTANTES */
#define UNVISITED -1



/* MACROS */




/* DEFINIÇÕES e ESTRUTURAS */




/* PROTOTIPOS CLASSES */
class Neighbor;
class Node;
class Edge;
class Circuit;




/* CLASSES */
class Node {
    public:
        int id{};
        std::list<Neighbor> neighbors;

        Node() = default;

        explicit Node(int id) {
            this->id = id;
        }
};



class Edge {
    public:
        int node1;
        int node2;
        int cost;

        Edge() = default;

        Edge(int node1, int node2, int cost) {
            this->node1 = node1;
            this->node2 = node2;
            this->cost = cost;
        }

        bool isSameEdge(Edge edge) {
            return ((this->node1 == edge.node1 || this->node1 == edge.node2) &&
                    (this->node2 == edge.node1 || this->node2 == edge.node2));
        }
};



class Neighbor {
    public:
        int dest;
        int cost;

        Neighbor(int dest, int cost) {
            this->dest = dest;
            this->cost = cost;
        }
};



class Circuit {
    public:
        std::list<int> poi;
        int laneLength = 0;

        Circuit() = default;

        bool isPoiOfCircuit(int id) {
            return find(this->poi.begin(), this->poi.end(), id) != this->poi.end();
        }
};



/* PROTOTIPOS FUNCOES */
bool compareTo(const Edge edge1, const Edge edge2);
int isPresent(std::deque<Edge> &edges, Edge edge);
void printDeque(const std::deque<int> &v, int start, int end);
void tarjanStep(int v, int *t, const std::deque<Node> &adj, std::deque<int> &dfs, std::deque<int> &low, std::deque<bool> &inStack, std::stack<int>& stack, std::deque<Circuit>& circuits);
void tarjan(const std::deque<Node> &adj, std::deque<Circuit>& circuits);
int question01(const std::deque<Circuit> &circuits);
int question02(const std::deque<Circuit> &circuits);
int question03(std::deque<Circuit> &circuits);
int question04(std::deque<Circuit> &circuits);
void make_set(std::deque<int> &set, std::deque<int> &rank);
int find_set(std::deque<int> &set, int a);
void link_set(std::deque<int> &set, std::deque<int> &rank, int a, int b);
void union_set(std::deque<int> &set, std::deque<int> &rank, int a, int b);
void kruskal(std::deque<Node> &adj, Circuit &circuit, int n);



#endif
