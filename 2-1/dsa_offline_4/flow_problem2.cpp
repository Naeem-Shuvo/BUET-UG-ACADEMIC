#include<bits/stdc++.h>
using namespace std;

bool bfs(int s, int t,vector<vector<array<int,4>>> &graph, vector<int> &parent) {
    queue<int> q;
    vector<bool> vis(graph.size(),false);
    q.push(s);
    parent[s]=s;
    vis[s]=true;
    while(!q.empty()){
        int u=q.front();
        q.pop();
        for(auto &it:graph[u]){
            int v=it[0];
            int capacity=it[1];
            int idx=it[3];
            if(!vis[v] && capacity>0){
                vis[v]=true;
                parent[v]=u;
                q.push(v);
                if(v==t){
                    return true;
                }
            }
        }
    }
    return false;
}

// int bottleneck(int s, int t, vector<vector<array<int,4>>> &graph, vector<int> &parent) {
//     int curr=t;
//     int flow=INT_MAX;
//     while(parent[curr]!=curr){
//         int prev=parent[curr];
//         for(auto &it:graph[prev])
//         {
//             if(it[0]==curr){
//                 flow=min(flow,it[1]);
//             }
//         }
//         curr=prev;
//     }
// return flow;
// }

void augment(int s, int t, vector<vector<array<int,4>>> &graph, vector<int> &parent, int flow) {
    int curr=t;
    while(parent[curr]!=curr){
        int prev=parent[curr];
        for(auto &it:graph[prev]){
           if(it[0]==curr){
            it[1]-=flow;
            int rev_idx=it[2];
            graph[curr][rev_idx][1]+=flow;
           }
        }
        curr=prev;
    }
}

int main() {
    int N,K,M;
    cin >> N >> K >> M;
    cout << "N: " << N << ", K: " << K << ", M: " << M << endl;
    //vector<tuple<int,int,int,int>> edges;
    vector<vector<array<int,4>>> graph(N+2);
    for(int i=0;i<M;i++){
        int u,v,c;
        cin>>u>>v;
        //edges.push_back({u,v,1,graph[u].size()});
        graph[u].push_back({v,1,(int)graph[v].size()});
        graph[v].push_back({u,0,(int)graph[u].size()-1});
    }
    for(int i=0;i<K;i++){
        graph[N].push_back({i,1,(int)graph[i].size()});
        graph[i].push_back({N,0,(int)graph[N].size()-1});
    }
    for(int i=K;i<N;i++){
        graph[i].push_back({N+1,1,(int)graph[N+1].size()});
        graph[N+1].push_back({i,0,(int)graph[i].size()-1});
    }
    int s=N; int t=N+1;
    vector<int> parent(N+2,-1);
    int totalConnections = 0;
    while(bfs(s,t,graph,parent)){
        int botNeck= 1;
        augment(s,t,graph,parent,1);
        fill(parent.begin(),parent.end(),-1);
        totalConnections++;
    }
    
    cout << totalConnections << endl;
    for(int i=0;i<K;i++){
        for(auto &it:graph[i]){
            if(it[0]>=K && it[0]<N && it[1]==0){
                cout<<i<<" "<<it[0]<<endl;
            }
        }
    }
    return 0;
}