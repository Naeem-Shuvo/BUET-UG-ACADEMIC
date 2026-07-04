#include<bits/stdc++.h>
using namespace std;

int main(){
    int n;
    cin>>n;
    vector<string> currency(n);
    for(int i=0;i<n;i++){
        cin>>currency[i];
    }
    vector<vector<float>> arbitrage(n,vector<float>(n,0));
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            if(i==j) arbitrage[i][j]=1;
        }
    }
    int m;
    cin>>m;
    for(int i=0;i<m;i++){
        string from,to;
        float rate;
        cin>>from>>rate>>to;
        int u,v;
        for(int i=0;i<n;i++){
            if(currency[i].compare(from)==0) u=i;
            if(currency[i].compare(to)==0) v=i;
        }
        arbitrage[u][v]=rate;
    }
    //output okay
    // for(auto it:arbitrage){
    //     for(auto jt:it){
    //         cout<<jt<<" ";
    //     }
    //     cout<<endl;
    // }

    for(int k=0;k<n;k++){
        for(int i=0;i<n;i++){
            for(int j=0;j<n;j++){
                if(arbitrage[i][k]*arbitrage[k][j]>arbitrage[i][j]){
                    arbitrage[i][j]=arbitrage[i][k]*arbitrage[k][j];
                    if(i==j && arbitrage[i][j]>1.0){
                        cout<<"Yes"<<endl;
                        return 0;
                }
            }
        }
    }
}
    cout<<"No"<<endl;
    return 0;
}