#include<bits/stdc++.h>
using namespace std;

class DisjointSet{
    vector<int> parent,rank;
    public:
    DisjointSet(int n){
        parent.resize(n);
        rank.resize(n,0);
        for(int i=0;i<n;i++){
            parent[i]=i;
        }
    }
    int findUPar(int node){
        if(node==parent[node]) return node;
        return parent[node]=findUPar(parent[node]);
    }
    void unionByRank(int u,int v){
        int ulp_u=findUPar(u);
        int ulp_v=findUPar(v);
        if(ulp_u==ulp_v) return;

        if(rank[ulp_u]<rank[ulp_v]){
            parent[ulp_u]=ulp_v;
        }
        else if(rank[ulp_v]<rank[ulp_u]){
            parent[ulp_v]=ulp_u;
        }
        else{
            parent[ulp_v]=ulp_u;
            rank[ulp_u]++;
        }
    }
};
int main(){
   for(int testCase=1;testCase<=10;testCase++){
    string inputfile="sampleio/sampleio/input/test"+to_string(testCase)+".txt";
    string outputfile="kruskalOutputs/output"+to_string(testCase)+".txt";
    ifstream fin(inputfile);
    ofstream fout(outputfile);
    
    if(!fin.is_open()){
        cerr<<"Could not open "<<inputfile<<endl;
        continue;
    }
    int N,M; //nodes ar edges
    fin>>N>>M;
    DisjointSet ds(N);
    vector<vector<pair<int,int>>> adj(N); //idx=u, {v,w}
    priority_queue<vector<int>,vector<vector<int>>,greater<vector<int>>> pq; //w,u,v
    for(int i=0;i<M;i++){
        int u,v,w;
        fin>>u>>v>>w;
        //**kruskal e adj list lage na ,cz pq e push kore randomly lightest edge nitesi */
        // adj[u].push_back({v,w});
        // adj[v].push_back({u,w});
        pq.push({w,u,v});
    }
    vector<vector<int>> mst_edges;
    int total_cost=0;
    while(!pq.empty()){
        auto curr=pq.top();
        pq.pop();
        int weight=curr[0];
        int u=curr[1];
        int v=curr[2];
        if(ds.findUPar(u)!=ds.findUPar(v)){
            ds.unionByRank(u,v);
            total_cost+=weight;
            mst_edges.push_back({u,v});
        }
    }
    fout<<"Total weight "<<total_cost<<endl;
    for(auto it:mst_edges){
        fout<<it[0]<<" "<<it[1]<<endl;
    }
    fin.close();
    fout.close();
    cout<<"Test case "<<testCase<<" completed."<<endl;
   }
    return 0;
}