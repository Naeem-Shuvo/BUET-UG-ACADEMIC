#include <bits/stdc++.h>
using namespace std;

const int INF = 1e9;

int maxFlow(vector<vector<array<int, 4>>>& graph, int s, int t, int N) {
    int max_flow = 0;
    
    while (true) {
        vector<int> parent(N, -1);
        vector<int> parent_edge(N, -1);
        queue<int> q;
        
        q.push(s);
        parent[s] = s;
        
        // BFS to find augmenting path
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
        
        // No augmenting path found
        if (parent[t] == -1) {
            break;
        }
        
        // Find minimum residual capacity
        int path_flow = INF;
        int curr = t;
        while (curr != s) {
            int prev = parent[curr];
            int edge_idx = parent_edge[curr];
            auto& edge = graph[prev][edge_idx];
            path_flow = min(path_flow, edge[1] - edge[2]);
            curr = prev;
        }
        
        // Update flow
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
    
    return max_flow;
}

void addEdge(vector<vector<array<int, 4>>>& graph, int u, int v, int capacity) {
    int forward_idx = graph[u].size();
    int backward_idx = graph[v].size();
    
    graph[u].push_back({v, capacity, 0, backward_idx});
    graph[v].push_back({u, 0, 0, forward_idx});
}

int main() {
    int N, K, M;
    cin >> N >> K >> M;
    
    // Create graph with source and sink
    // Node indexing:
    // 0 to K-1: Presiding Officers (Group A)
    // K to N-1: Polling Agents (Group B)
    // N: source
    // N+1: sink
    int source = N;
    int sink = N + 1;
    int total_nodes = N + 2;
    
    vector<vector<array<int, 4>>> graph(total_nodes);
    
    // Add edges from source to all officers (0 to K-1) with capacity 1
    for (int i = 0; i < K; i++) {
        addEdge(graph, source, i, 1);
    }
    
    // Add edges from all agents (K to N-1) to sink with capacity 1
    for (int i = K; i < N; i++) {
        addEdge(graph, i, sink, 1);
    }
    
    // Store compatibility edges
    vector<pair<int, int>> compatibility_edges;
    
    // Read compatibility edges and add them with capacity 1
    for (int i = 0; i < M; i++) {
        int u, v;
        cin >> u >> v;
        compatibility_edges.push_back({u, v});
        addEdge(graph, u, v, 1);
    }
    
    // Run max flow
    int max_pairs = maxFlow(graph, source, sink, total_nodes);
    
    cout << max_pairs << endl;
    
    // Extract the actual pairs from the flow
    // Check each compatibility edge to see if flow = 1
    for (int i = 0; i < compatibility_edges.size(); i++) {
        int officer = compatibility_edges[i].first;
        int agent = compatibility_edges[i].second;
        
        // Find the edge from officer to agent in graph
        for (auto& edge : graph[officer]) {
            if (edge[0] == agent && edge[1] == 1 && edge[2] == 1) {
                // This edge has flow 1, so it's a match
                cout << officer << " " << agent << endl;
                break;
            }
        }
    }
    
    return 0;
}
