#include <bits/stdc++.h>
using namespace std;

int main()
{
    int n, m;
    cin >> n >> m;
    vector<vector<int>> route(m, vector<int>(3));
    for (auto &it : route)
    {
        cin >> it[0] >> it[1] >> it[2];
    }
    priority_queue<vector<int>, vector<vector<int>>, greater<vector<int>>> pq;
    vector<pair<int,int>> dist(n+1,{INT_MAX,INT_MAX});
    dist[0].first=0;
    pq.push({0,route[0][0],0});
    while(!pq.empty()){
        int state=pq.top()[2];
        int cost=pq.top()[0];
        int node=pq.top()[1]; 
        pq.pop();
        if(!state){
            for(auto it:route){
                if(it[0]==node){
                    int dest=it[1];
                    int pathCost=it[2];
                    if(pathCost+cost<dist[dest].first){
                        dist[dest].first=it[2]+cost;
                        pq.push({dist[dest].first,dest,0});
                    } 
                    if(pathCost/2+cost<dist[dest].second){
                       dist[dest].second=pathCost/2+cost;
                       pq.push({dist[dest].second,dest,1});
                    }

                }
            }
        }
        else{
            for(auto it:route){
                if(it[0]==node){
                    int dest=it[1];
                    int pathCost=it[2];
                    if(pathCost+cost<dist[dest].first){
                        dist[dest].first=it[2]+cost;
                        pq.push({dist[dest].first,dest,0});
                    } 
                }
            }
        }
    }
cout<<min(dist[n].first,dist[n].second);
    return 0;
}