#include <bits/stdc++.h>
using namespace std;

const int INF = 1e9;

int main() {
    int N, M;
    cin >> N >> M;

    vector<vector<array<int, 4>>> graph(N);
    

    vector<tuple<int, int, int>> edges;
    
    for (int i = 0; i < M; i++) {
        int u, v, c;
        cin >> u >> v >> c;
        edges.push_back({u, v, c});
        

        int forward_idx = graph[u].size();
        int backward_idx = graph[v].size();
        
        graph[u].push_back({v, c, 0, backward_idx});
     
        graph[v].push_back({u, 0, 0, forward_idx});
    }
    
    int s, t;
    cin >> s >> t;
    
    int max_flow = 0;

    while (true) {
        vector<int> parent(N, -1);
        vector<int> parent_edge(N, -1);
        queue<int> q;
        
        q.push(s);
        parent[s] = s;
        

        while (!q.empty() && parent[t] == -1) {
            int u = q.front();
            q.pop();
            
            for (int i = 0; i < graph[u].size(); i++) {
                auto& edge = graph[u][i];
                int v = edge[0];
                int capacity = edge[1];
                int flow = edge[2];

                if (parent[v] == -1 && capacity > flow) {
                    parent[v] = u;
                    parent_edge[v] = i;
                    q.push(v);
                }
            }
        }

        if (parent[t] == -1) {
            break;
        }
        
        int path_flow = INF;
        int curr = t;
        while (curr != s) {
            int prev = parent[curr];
            int edge_idx = parent_edge[curr];
            auto& edge = graph[prev][edge_idx];
            path_flow = min(path_flow, edge[1] - edge[2]);
            curr = prev;
        }
        

        curr = t;
        while (curr != s) {
            int prev = parent[curr];
            int edge_idx = parent_edge[curr];

            graph[prev][edge_idx][2] += path_flow;
            
     
            int rev_idx = graph[prev][edge_idx][3];
            graph[curr][rev_idx][2] -= path_flow;
            
            curr = prev;
        }
        
        max_flow += path_flow;
    }
    
    cout << max_flow << endl;
    

    for (int i = 0; i < M; i++) {
        int u = get<0>(edges[i]);
        int v = get<1>(edges[i]);
        int c = get<2>(edges[i]);

        int flow = 0;
        for (auto& edge : graph[u]) {
            if (edge[0] == v && edge[1] == c) {
                flow = edge[2];
                break;
            }
        }
        
        cout << u << " " << v << " " << flow << "/" << c << endl;
    }
    
    return 0;
}
