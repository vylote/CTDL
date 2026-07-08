#include <bits/stdc++.h>
using namespace std;

struct Edge {
    int v, w;
};

void dijkstra(vector<vector<Edge>> &graph, int start) {
    int n = graph.size();
    vector<int> dist(n, INT_MAX);
    vector<int> parent(n, -1);

    priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> pq;

    dist[start] = 0;
    pq.push({0, start});

    while (!pq.empty()) {
        auto [d, u] = pq.top(); pq.pop();
        if (d > dist[u]) continue;

        for (auto e : graph[u]) {
            int v = e.v, w = e.w;
            if (dist[v] > dist[u] + w) {
                dist[v] = dist[u] + w;
                parent[v] = u;
                pq.push({dist[v], v});
            }
        }
    }

    cout << "Khoang cach ngan nhat tu dinh " << start << ":\n";
    for (int i = 0; i < n; i++) {
        cout << "den dinh " << i << " = " << dist[i] << "\n";
    }

    int target = n-1;
    cout << "\nDuong di toi " << target << ": ";
    vector<int> path;
    for (int v = target; v != -1; v = parent[v]) path.push_back(v);
    reverse(path.begin(), path.end());
    for (int v : path) cout << v << " ";
    cout << "\n";
}

int main() {
    int n = 5;
    vector<vector<Edge>> graph(n);

    auto addEdge = [&](int u, int v, int w) {
        graph[u].push_back({v,w});
        graph[v].push_back({u,w}); // nếu đồ thị vô hướng
    };

    addEdge(0,1,2);
    addEdge(0,2,4);
    addEdge(1,2,1);
    addEdge(1,3,7);
    addEdge(2,4,3);
    addEdge(3,4,1);

    dijkstra(graph, 0);
}
