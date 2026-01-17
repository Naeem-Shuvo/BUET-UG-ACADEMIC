#include<bits/stdc++.h>
using namespace std;

int main(){
    for(int testCase=1; testCase<=10; testCase++){
        string inputFile = "sampleio/sampleio/input/test" + to_string(testCase) + ".txt";
        string outputFile = "primOutputs/output" + to_string(testCase) + ".txt";
        
        ifstream fin(inputFile);
        ofstream fout(outputFile);
        
        if(!fin.is_open()){
            cerr<<"Could not open "<<inputFile<<endl;
            continue;
        }
        
        int N,M;
        fin>>N>>M;
        vector<vector<pair<int,int>>> adj(N); //idx=u, {v,w} //node numbered container nisi
        for(auto i=0;i<M;i++){
            int u,v,w;
            fin>>u>>v>>w;
            adj[u].push_back({v,w});
            adj[v].push_back({u,w});
        }
        int root;
        fin>>root;
        
        if(root < 0 || root >= N){
            cerr<<"Invalid root "<<root<<" for test "<<testCase<<endl;
            continue;
        }
        
        priority_queue<vector<int>,vector<vector<int>>,greater<vector<int>>> pq;
        vector<bool> visited(N,false);
        for(auto it:adj[root]){
            pq.push({it.second,root,it.first}); //w,u,v
        }
        visited[root]=true;
        int total_cost=0;
        vector<pair<int,int>> mst_edges;
        while(!pq.empty()){
            auto curr=pq.top();
            pq.pop();
            int cost=curr[0];
            int node=curr[1];
            int dest=curr[2];
            
            if(visited[dest]) continue;//etar pore add korbo whether mst,naile cycle hoye jabe
            visited[dest]=true;
            mst_edges.push_back({node,dest});
            total_cost+=cost;
            for(auto &it:adj[dest] ){
                int next_cost=it.second;
                int next_node=it.first;
                if(!visited[next_node]){ //revisit prevent kore
                    pq.push({next_cost,dest,next_node});
                }
            }
        }
        fout<<"Total weight "<<total_cost<<endl;
        fout<<"Root node "<<root<<endl;
        for(auto it:mst_edges){
            fout<<it.first<<" "<<it.second<<endl;
        }
        
        fin.close();
        fout.close();
        
        cout<<"Test case "<<testCase<<" completed."<<endl;
    }
    return 0;
}
