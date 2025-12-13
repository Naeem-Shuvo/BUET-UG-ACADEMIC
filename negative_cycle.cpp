#include <bits/stdc++.h>
using namespace std;
void detectNegCycle(vector<vector<int>> &edge, int nodes)
{
    vector<int> dist(nodes + 1, INT_MAX); // nodes+1 --> 1-indexing
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
    for (int i : dist)
    {
        cout << i<< " ";
    }
    cout << endl;

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