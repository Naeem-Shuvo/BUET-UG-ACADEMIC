#include <bits/stdc++.h>
using namespace std;
void detectNegCycle(vector<vector<int>> &edge, int nodes)
{
    vector<int> dist(nodes + 1, 0); // nodes+1 --> 1-indexing
                                    //sob node ke possible starting point dhora
    vector<int> parent(nodes + 1, -1);
    dist[1] = 0;
    dist[0]=-1; //use hocche na
    for (int i = 0; i < nodes - 1; i++)
    {
        for (auto it : edge)
        {
            int a = it[0] ; // dist array 1 indexed
            int b = it[1] ;
            int c = it[2];
            if (dist[a] != INT_MAX && dist[a] + c < dist[b])
            {
                dist[b] = dist[a] + c;
                parent[b] = a;
            }
        }
    }
    // for (int i : dist)
    // {
    //     cout << i<< " ";
    // }
    // cout << endl;
    int negaNode=-1;
    for (auto it : edge)
        {
            int a = it[0] ; // dist array 1 indexed
            int b = it[1] ;
            int c = it[2];
            if (dist[a] != INT_MAX && dist[a] + c < dist[b])
            {
                negaNode=a;
                break;
            }
        }
        if(negaNode==-1){
            cout<<-1; //no nega cycle
            return;
        }
        int it=negaNode;
        vector<int> path;
    while(parent[it]!=negaNode){
        // cout<<it<<" ";
        path.push_back(it);
        it=parent[it];
    }
    path.push_back(it);  ///condition check kore last e ekta print na korei beroy jay tai
    reverse(path.begin(),path.end());
    for(int i:path) cout<<i<<" ";
    //    for(int i=0;i<4;i++){
    //     cout<<it<<" ";
    //     it=parent[it];
    //    }
}
int main()
{
    int n, m;
    cin >> n >> m;
    vector<vector<int>> edge(m, vector<int>(3));
    for (auto& it: edge)
    {
        for (int j = 0; j < 3; j++)
        {
            cin >> it[j];
        }
    }
    detectNegCycle(edge, n);
    // for(int i=0;i<m;i++){
    //     for(int j=0;j<3;j++){
    //         cout<<edge[i][j]<<" ";
    //     }
    //     cout<<endl;
    // }
    return 0;
}