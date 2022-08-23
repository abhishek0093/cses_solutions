//TREES ALGORITHM
//SUBORDINATES
#include<iostream>
#include<bits/stdc++.h>
using namespace std;

int countSubs(vector<int> &subs, vector<vector<int>> &tree, int i){
    if(subs[i] != -1){return subs[i];}
    int ans = tree[i].size();
    for(int j : tree[i]){
        ans+=countSubs(subs,tree,j);
    }
    subs[i] = ans;
    return ans;
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int n;cin>>n;
    vector<vector<int>> tree(n+1);
    for(int i = 2; i<=n; ++i){
        int boss;
        cin>>boss;
        tree[boss].push_back(i);
    }
    vector<int> subs(n+1, -1);
    for(int i = 1; i<=n; ++i){
        cout<<countSubs(subs,tree, i)<<"\n";
    }
    return 0;
}

//TREE DIAMETER
#include<iostream>
#include<bits/stdc++.h>
using namespace std;

void calculateHts(int parent, int i, vector<vector<int>> &tree, vector<int> &hts){
    int ht = 1;
    for(int j : tree[i]){
        if(j == parent){continue;}
        calculateHts(i,j,tree,hts);
        ht = max(ht, 1+hts[j]);
    }
    hts[i] = ht;
}

void calculateDia(int pare, vector<vector<int>> &tree, int node, vector<int> &hts, vector<int> &diameter){
    int dia = 0;
    vector<int> childhts;
    for(int j : tree[node]){
        if(j == pare){continue;}
        calculateDia(node,tree,j,hts,diameter);
        childhts.push_back(hts[j]);
        dia = max(dia, diameter[j]);   
    }
    sort(childhts.begin(), childhts.end(), greater<int>());
    if(childhts.size() == 0){
        diameter[node] = 0;
    }
    else if(childhts.size() == 1){
        diameter[node] = childhts[0];
    }
    else{
        diameter[node] =  childhts[0]+childhts[1];
    }
    diameter[node] = max(diameter[node], dia);
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int n; cin>>n;
    vector<vector<int>> tree(n+1);
    vector<int> diameter(n+1);
    vector<int> hts(n+1,-1);
    int t = n-1;
    while(t--){
        int a,b; cin>>a>>b;
        tree[a].push_back(b);
        tree[b].push_back(a);
    }
    calculateHts(0,1,tree, hts);
    calculateDia(0,tree,1,hts,diameter);
    cout<<diameter[1]<<"\n";
    return 0;
}