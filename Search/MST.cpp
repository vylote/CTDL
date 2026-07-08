#include <bits/stdc++.h>
using namespace std;

struct Edge {
    int u, v, w;
    bool operator>(const Edge &other) const {
        return w > other.w;
    }
};

void prim(vector<vector<pair<int,int>>> &graph, int start) {
    int n = graph.size();
    vector<bool> inMST(n, false);
    priority_queue<Edge, vector<Edge>, greater<Edge>> pq;

    inMST[start] = true;
    for (auto [v, w] : graph[start]) {
        pq.push({start, v, w});
    }

    int totalCost = 0;
    cout << "Cac canh trong MST:\n";

    while (!pq.empty()) {
        Edge e = pq.top(); pq.pop();
        if (inMST[e.v]) continue;

        inMST[e.v] = true;
        totalCost += e.w;
        cout << e.u << " - " << e.v << " (w=" << e.w << ")\n";

        for (auto [nv, w] : graph[e.v]) {
            if (!inMST[nv]) {
                pq.push({e.v, nv, w});
            }
        }
    }

    cout << "Tong chi phi MST = " << totalCost << "\n";
}

int main() {
    int n = 5;
    vector<vector<pair<int,int>>> graph(n);

    auto addEdge = [&](int u, int v, int w) {
        graph[u].push_back({v,w});
        graph[v].push_back({u,w});
    };

    addEdge(0,1,2);
    addEdge(0,2,3);
    addEdge(1,2,1);
    addEdge(1,3,4);
    addEdge(2,3,5);
    addEdge(2,4,6);
    addEdge(3,4,7);

    prim(graph, 0);
}
