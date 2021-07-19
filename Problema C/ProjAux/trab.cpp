/*  AUTORES: Cláudia Campos N.2018285941 | Dário Félix N.2018275530  */

// FICHEIRO: trab.cpp (funcoes a submeter no mooshak)



/* HEADERS */
#include "header_trab.h"
#include "header_testes.h"



/* VARS GLOBAIS */



/* FUNCOES */
bool compareTo(const Edge edge1, const Edge edge2) {
    return edge1.cost < edge2.cost;
}



int isPresent(std::deque<Edge> &edges, Edge edge) {
    for (int i = 0; i < (int) edges.size(); ++i) {
        if (edges[i].isSameEdge(edge)) {
            return i;
        }
    }
    return -1;
}



void printDeque(const std::deque<int> &v, int start, int end) {
    int i;
    for (i = start; i < end - 1; ++i) {
        std::cout << v[i] << " ";
    }
    std::cout << v[i] << std::endl;
}



void tarjanStep(int v, int *t, const std::deque<Node> &adj, std::deque<int> &dfs, std::deque<int> &low, std::deque<bool> &inStack, std::stack<int>& stack, std::deque<Circuit>& circuits) {
    dfs[v] = low[v] = (*t)++;
    stack.push(adj[v].id);
    inStack[v] = true;

    for(auto &edge : adj[v].neighbors) {
        int w = edge.dest;
        if (dfs[w] == UNVISITED) {
            tarjanStep(w, t, adj, dfs, low, inStack, stack, circuits);
            low[v] = std::min(low[v], low[w]);
        } else if (inStack[w]) {
            low[v] = std::min(low[v], dfs[w]);
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



void tarjan(const std::deque<Node> &adj, std::deque<Circuit>& circuits) {
    int t = 0;
    std::deque<int> dfs(adj.size(), UNVISITED);
    std::deque<int> low(adj.size(), UNVISITED);
    std::deque<bool> inStack(adj.size(), false);
    std::stack<int> stack;

    for (int v = 0; v < (int) adj.size(); ++v) {
        if(dfs[v] == UNVISITED) {
            tarjanStep(v, &t, adj, dfs, low, inStack, stack, circuits);
        }
    }

    inStack.clear();
    low.clear();
    dfs.clear();
}



int question01(const std::deque<Circuit> &circuits) {
    return circuits.size();
}



int question02(const std::deque<Circuit> &circuits) {
    int n = 0;
    for (const auto &circuit : circuits) {
        n = std::max(n, (int) circuit.poi.size());
    }
    return n;
}



int question03(std::deque<Circuit> &circuits) {
    int n = 0;
    for (auto &circuit : circuits) {
        n = std::max(n, circuit.laneLength);
    }
    return n;
}



int question04(std::deque<Circuit> &circuits) {
    int totalLength = 0;
    for (auto &circuit : circuits) {
        totalLength += circuit.laneLength;
    }
    return totalLength;
}



void make_set(std::deque<int> &set, std::deque<int> &rank) {
    for (int i = 0; i < std::min((int) set.size(), (int) rank.size()); ++i) {
        set[i] = i;
        rank[i] = 0;
    }
}



int find_set(std::deque<int> &set, int a) {
    if(set[a] != a) {
        set[a] = find_set(set, set[a]);
    }
    return set[a];
}



void link_set(std::deque<int> &set, std::deque<int> &rank, int a, int b) {
    if (rank[a] > rank[b]) {
        set[b] = a;
    } else {
        set[a] = b;
    } if (rank[a] == rank[b]) {
        ++rank[b];
    }
}



void union_set(std::deque<int> &set, std::deque<int> &rank, int a, int b) {
    link_set(set, rank, find_set(set, a), find_set(set, b));
}



void kruskal(std::deque<Node> &adj, Circuit &circuit, int n) {
    std::deque<int> set(n);
    std::deque<int> rank(n);

    make_set(set, rank);

    std::deque<Edge> edges;

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


