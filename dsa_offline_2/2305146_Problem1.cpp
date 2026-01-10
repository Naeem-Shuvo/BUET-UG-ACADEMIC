#include<bits/stdc++.h>
using namespace std;

int main(){
    int n,m,query;
    cin>>n>>m>>query;
    vector<pair<int,int>> queries(query);
    vector<vector<int>> edges(m,vector<int>(3));
    vector<vector<int>> adj(n+1,vector<int>(n+1,INT_MAX));

    for(auto &edge:edges){
        cin>>edge[0]>>edge[1]>>edge[2];
        adj[edge[0]][edge[1]]=edge[2];
        adj[edge[1]][edge[0]]=edge[2];
    }
    for(auto &q:queries){
        cin>>q.first>>q.second;
    }
     for(int i=0;i<=n;i++){
            for(int j=0;j<=n;j++){
                if(i==j) adj[i][j]=0;
            }
        }
    for(int i=0;i<=n;i++){
        for(int j=0;j<=n;j++){  
            cout<<adj[i][j]<<" ";
        }
        cout<<endl;
    }    cout<<endl<<endl;
    for(int k=1;k<=n;k++){
        for(int i=1;i<=n;i++){
            for(int j=1;j<=n;j++){
                if(adj[i][k]!=INT_MAX && adj[k][j]!=INT_MAX){
                    adj[i][j]=min(adj[i][j],adj[i][k]+adj[k][j]);
                }
            }
        }
    }
    for(int i=0;i<=n;i++){
        for(int j=0;j<=n;j++){  
            cout<<adj[i][j]<<" ";
        }
        cout<<endl;
    }    cout<<endl<<endl;
    for(auto q:queries){
        if(adj[q.first][q.second]==INT_MAX){
            cout<<"-1\n";
        }else{
            cout<<adj[q.first][q.second]<<"\n";
        }
    }
    return 0;
}