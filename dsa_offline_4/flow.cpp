#include<bits/stdc++.h>
using namespace std;

bool bfs(int s,int t, vector<vector<vector<int>>> &graph,vector<int> &parent){
   queue<int> q;
   vector<bool> visited(graph.size(),false);
    q.push(s);
    visited[s]=true;
    parent[s]=s;
    while(!q.empty()){
        int u=q.front();
        q.pop();
        for(auto it:graph[u]){
            int v=it[0];
            int capacity=it[1];
            if(!visited[v] && capacity>0){
                visited[v]=true;
                q.push(v);
                parent[v]=u;
                if(v==t){
                    return true;
                }
            }
        }
    }
    return false;
}

int bottleneck(int s,int t,vector<vector<vector<int>>> &graph,vector<int> &parent){
    int path_flow =INT_MAX;
    int curr=t;

    while(curr!=s){
        int prev=parent[curr];
        for(auto &it:graph[prev]){
            if(it[0]==curr){
                path_flow=min(path_flow,it[1]);
            }
        }
        curr=prev;
    }

    //augment the flow
    curr=t;

    while(curr!=s){
        int prev=parent[curr];
        for(auto &it:graph[prev]){
            if(it[0]==curr){
                it[1]-=path_flow;
                int rev_idx=it[2];
                graph[curr][rev_idx][1]+=path_flow;
            }
        }
        curr=prev;
    }
    return path_flow;
}

int main(){
    int N,M;
    cin>>N>>M;
    vector<vector<vector<int>>> graph(N);
    
    // Store original edges: {u, v, capacity, index_in_graph[u]}
    vector<tuple<int,int,int,int>> edges;
    
    for(int i=0;i<M;i++){
        int u,v,c;
        cin>>u>>v>>c;
        //idx and (int)graph[v].size()
        //this thing's purpose is completely different
        int idx = graph[u].size();
        edges.push_back({u, v, c, idx});
        graph[u].push_back({v,c,(int)graph[v].size()});
        graph[v].push_back({u,0,(int)graph[u].size()-1});
    }
    int s,t;
    cin>>s>>t;
    vector<int> parent(graph.size(), -1);
    int max_flow=0;
    while(bfs(s,t,graph,parent)){
        
        max_flow+=bottleneck(s,t,graph,parent);
        fill(parent.begin(),parent.end(),-1);

    }
    cout<<max_flow<<endl;
    
    // Print flow through each edge
    for(auto& edge : edges){
        int u = get<0>(edge);
        int v = get<1>(edge);
        int original_cap = get<2>(edge);
        int idx = get<3>(edge);
        
        // Flow = original_capacity - residual_capacity
        int residual_cap = graph[u][idx][1];
        int flow = original_cap - residual_cap;
        
        cout << u << " " << v << " " << flow << "/" << original_cap << endl;
    }
    
    return 0;
}