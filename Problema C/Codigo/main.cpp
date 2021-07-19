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
 *      > Cantinas do SASUC                                                     *
 *      > Cafe                                                                  *
 *      > Professores                                                           *
 *      > Mooshak, quando quer                                                  *
 *                                                                              *
 *  Problem C - Bike Lanes                                                      *
 *  FCTUC - DEI/LEI - Estrategias Algoritmicas                                  *
 *  Coimbra, 25 de maio de 2021, 23:59h                                         *
 ********************************************************************************/
 
 // VERSAO 4

#include <iostream>
#include <algorithm>
#include <list>
#include <deque>
#include <stack>

#define UNVISITED -1

using namespace std;

/*

INPUT:

6
12 18 4
2 1 3
3 2 4
4 1 2
4 2 8
2 5 3
5 2 5
3 6 4
6 3 2
6 5 6
7 5 4
8 6 9
7 8 1
7 9 2
9 10 8
10 7 4
8 11 2
11 12 12
12 10 3
4 4 3
2 1 3
3 2 4
4 1 2
4 2 8
4 4 4
2 1 3
3 2 4
1 4 2
4 2 8
4 4 3
2 1 3
3 2 4
1 4 2
4 2 8
4 4 2
2 1 3
3 2 4
1 4 2
4 2 8
4 4 1
2 1 3
3 2 4
1 4 2
4 2 8

 */

class Neighbor;

class Node {

    public:

        int id{};
        list<Neighbor> neighbors;

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

        list<int> poi;
        int laneLength = 0;

        Circuit() = default;

        bool isPoiOfCircuit(int id) {
            return find(this->poi.begin(), this->poi.end(), id) != this->poi.end();
        }

};

bool compareTo(const Edge edge1, const Edge edge2) {
    return edge1.cost < edge2.cost;
}

int isPresent(deque<Edge> &edges, Edge edge) {
    for (int i = 0; i < (int) edges.size(); ++i) {
        if (edges[i].isSameEdge(edge)) {
            return i;
        }
    }
    return -1;
}

void printDeque(const deque<int> &v, int start, int end) {
    int i;
    for (i = start; i < end - 1; ++i) {
        cout << v[i] << " ";
    }
    cout << v[i] << endl;
}

void tarjanStep(int v, int *t, const deque<Node> &adj, deque<int> &dfs, deque<int> &low, deque<bool> &inStack, stack<int>& stack, deque<Circuit>& circuits) {
    dfs[v] = low[v] = (*t)++;
    stack.push(adj[v].id);
    inStack[v] = true;

    for(auto &edge : adj[v].neighbors) {
        int w = edge.dest;
        if (dfs[w] == UNVISITED) {
            tarjanStep(w, t, adj, dfs, low, inStack, stack, circuits);
            low[v] = min(low[v], low[w]);
        } else if (inStack[w]) {
            low[v] = min(low[v], dfs[w]);
        }
    }

    if (low[v] == dfs[v]) {
        Circuit circuit = Circuit();
        int w;

        for (w = stack.top(), circuit.poi.push_back(w), stack.pop(), inStack[w] = false; w != v;
        w = stack.top(), circuit.poi.push_back(w), stack.pop(), inStack[w] = false);

        if ((int) circuit.poi.size() >= 2) {
            circuits.push_back(circuit);
        }
    }

}

void tarjan(const deque<Node> &adj, deque<Circuit>& circuits) {
    int t = 0;
    deque<int> dfs(adj.size(), UNVISITED);
    deque<int> low(adj.size(), UNVISITED);
    deque<bool> inStack(adj.size(), false);
    stack<int> stack;

    for (int v = 0; v < (int) adj.size(); ++v) {
        if(dfs[v] == UNVISITED) {
            tarjanStep(v, &t, adj, dfs, low, inStack, stack, circuits);
        }
    }

    inStack.clear();
    low.clear();
    dfs.clear();
}

int question01(const deque<Circuit> &circuits) {
    return circuits.size();
}

int question02(const deque<Circuit> &circuits) {
    int n = 0;
    for (const auto &circuit : circuits) {
        n = max(n, (int) circuit.poi.size());
    }
    return n;
}

int question03(deque<Circuit> &circuits) {
    int n = 0;
    for (auto &circuit : circuits) {
        n = max(n, circuit.laneLength);
    }
    return n;
}

int question04(deque<Circuit> &circuits) {
    int totalLength = 0;
    for (auto &circuit : circuits) {
        totalLength += circuit.laneLength;
    }
    return totalLength;
}

void make_set(deque<int> &set, deque<int> &rank) {
    for (int i = 0; i < min((int) set.size(), (int) rank.size()); ++i) {
        set[i] = i;
        rank[i] = 0;
    }
}

int find_set(deque<int> &set, int a) {
    if(set[a] != a) {
        set[a] = find_set(set, set[a]);
    }
    return set[a];
}

void link_set(deque<int> &set, deque<int> &rank, int a, int b) {
    if (rank[a] > rank[b]) {
        set[b] = a;
    } else {
        set[a] = b;
    } if (rank[a] == rank[b]) {
        ++rank[b];
    }
}

void union_set(deque<int> &set, deque<int> &rank, int a, int b) {
    link_set(set, rank, find_set(set, a), find_set(set, b));
}

void kruskal(deque<Node> &adj, Circuit &circuit, int n) {
    deque<int> set(n);
    deque<int> rank(n);

    make_set(set, rank);

    deque<Edge> edges;

    for (auto &poi : circuit.poi) {
        for (auto &neighbor : adj[poi].neighbors) {
            if (circuit.isPoiOfCircuit(neighbor.dest)) {
                edges.emplace_back(poi, neighbor.dest, neighbor.cost);
            }
        }
    }

    sort(edges.begin(), edges.end(), compareTo);

    for (auto &edge : edges) {
        if(find_set(set, edge.node1) != find_set(set, edge.node2)) {
            circuit.laneLength += edge.cost;
            union_set(set, rank, edge.node1, edge.node2);
        }
    }

    edges.clear();

}

int main() {
    int t, n, m, q, a, b, d;

    cin >> t;

    for (int i = 0; i < t; ++i) {

        cin >> n >> m >> q;

        deque<Node> adj;

        for (int k = 0; k < n; ++k) {
            adj.emplace_back(k);
        }

        deque<Circuit> circuits;
        deque<int> questions(q, 0);

        for (int j = 0; j < m; ++j) {
            cin >> a >> b >> d;
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

    return 0;
}
