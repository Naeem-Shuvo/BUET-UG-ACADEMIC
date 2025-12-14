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
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    vector<int> dist(n + 1, INT_MAX);
    dist[0] = -1;
    dist[1] = 0;
    pq.push({0, 1});
    while (!pq.empty())
    {
        int dis = pq.top().first;
        int node = pq.top().second;
        pq.pop();
        // node er neighbour gulo khuji whole vector e and relax them
        for (auto it : route)
        {
            if (it[0] == node && dist[node] + it[2] < dist[it[1]])
            {
                dist[it[1]] = dist[node] + it[2]; // dis==it[2],,it[1]==dest,,it[0]==node
                pq.push({dis, it[1]});
            }
        }
    }
    for(int i:dist) cout<<i<<" ";
    return 0;
}