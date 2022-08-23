
//RANGE QUERIES
//STATIC RANGE MIN QUERIES
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int n,q;
    cin>>n>>q;
    vector<int> arr(n);
    for(int &i : arr){cin>>i;}
    vector<int> rt(n);          //rt[i] stores first index j to the right if i, such that arr[j] < arr[i]
    rt[n-1] = n;
    for(int i = n-2; i>=0; --i){
        int v = i+1;
        while(v < n && arr[v] >= arr[i]){
            v = rt[v];
        }
        rt[i] = v;
    }
    while(q--){
        int i,j;
        cin>>i>>j;
        int score;
        i = i-1; j = j-1; 
        if(i ==j || rt[i] > j){
            score = arr[i];
        }
        else if(rt[i] == j){
            score = arr[j];
        }
        else{
            int prev = i;
            int cand = rt[i];
            while(cand <= j){
                prev = cand;
                cand = rt[cand]; 
            }
            score = arr[prev];
        }
        cout<<score<<"\n";
    }
    
    return 0;
}

//DYNAMIC RANGE SUM QUERIES
//Direct implementation of segment trees
#include<iostream>
#include<bits/stdc++.h>
using namespace std;

void build(vector<long long> &arr, int node, int s, int e, vector<long long> &segTree){       //node is basically denotes our position. root is 1
    if(s == e){segTree[node] = arr[s]; return;}
    int mid = s+((e-s)/2);
    build(arr, 2*node, s, mid, segTree);
    build(arr, 2*node+1, mid+1, e, segTree);

    //Modify here
    segTree[node] = segTree[2*node]+segTree[2*node+1];
}

void modify(int node, int s, int e, int pos, int newV, vector<long long> &segTree){
    if(s == e){segTree[node] = newV; return;}
    int mid = s+((e-s)/2);
    if(pos <= mid){
        modify(2*node, s, mid, pos, newV, segTree);
    }
    else{
        modify(2*node+1, mid+1, e, pos, newV, segTree);
    }

    //Modify here
    segTree[node] = segTree[2*node]+segTree[2*node+1];
}

long long query(int node, int s, int e, int qs, int qe, vector<long long> &segTree){
    if(qs<=s && e <= qe){
        return segTree[node];
    }
    if(qe < s || qs > e){return 0;}
    int mid = s+((e-s)/2);
    long long left = query(2*node, s, mid, qs, qe, segTree);
    long long right = query(2*node+1, mid+1, e, qs, qe, segTree);
    return left+right;
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int n,q; cin>>n>>q;
    vector<long long> arr(n);
    vector<long long> segTree(4*n);
    for(long long &i : arr){cin>>i;}
    build(arr,1,0,n-1, segTree);
    while(q--){
        int a,b,c; cin>>a>>b>>c;
        if(a == 1){
            modify(1,0, n-1, b-1, c, segTree);
        }
        else{
            cout<<query(1,0,n-1,b-1,c-1, segTree)<<"\n";
        }
    }
    return 0;
}

//DYNAMIC MINIMUM QUERIES
#include<iostream>
#include<bits/stdc++.h>
using namespace std;

void build(vector<int> &arr, int node, int s, int e, vector<int> &segTree){       //node is basically denotes our position. root is 1
    if(s == e){segTree[node] = arr[s]; return;}
    int mid = s+((e-s)/2);
    build(arr, 2*node, s, mid, segTree);
    build(arr, 2*node+1, mid+1, e, segTree);

    //Modify here
    segTree[node] = min(segTree[2*node],segTree[2*node+1]);
}

void modify(int node, int s, int e, int pos, int newV, vector<int> &segTree){
    if(s == e){segTree[node] = newV; return;}
    int mid = s+((e-s)/2);
    if(pos <= mid){
        modify(2*node, s, mid, pos, newV, segTree);
    }
    else{
        modify(2*node+1, mid+1, e, pos, newV, segTree);
    }

    //Modify here
    segTree[node] = min(segTree[2*node],segTree[2*node+1]);
}

int query(int node, int s, int e, int qs, int qe, vector<int> &segTree){
    if(qs<=s && e <= qe){
        return segTree[node];
    }
    if(qe < s || qs > e){return INT_MAX;}
    int mid = s+((e-s)/2);
    int left = query(2*node, s, mid, qs, qe, segTree);
    int right = query(2*node+1, mid+1, e, qs, qe, segTree);
    return min(left,right);
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int n,q; cin>>n>>q;
    vector<int> arr(n);
    vector<int> segTree(4*n);
    for(int &i : arr){cin>>i;}
    build(arr,1,0,n-1, segTree);
    while(q--){
        int a,b,c; cin>>a>>b>>c;
        if(a == 1){
            modify(1,0, n-1, b-1, c, segTree);
        }
        else{
            cout<<query(1,0,n-1,b-1,c-1, segTree)<<"\n";
        }
    }
    return 0;
}

//RANGE XOR QUERIES
#include<iostream>
#include<bits/stdc++.h>
using namespace std;

void build(vector<int> &arr, int node, int s, int e, vector<int> &segTree){       //node is basically denotes our position. root is 1
    if(s == e){segTree[node] = arr[s]; return;}
    int mid = s+((e-s)/2);
    build(arr, 2*node, s, mid, segTree);
    build(arr, 2*node+1, mid+1, e, segTree);

    //Modify here
    segTree[node] = segTree[2*node]^segTree[2*node+1];
}

int query(int node, int s, int e, int qs, int qe, vector<int> &segTree){
    if(qs<=s && e <= qe){
        return segTree[node];
    }
    if(qe < s || qs > e){return 0;}
    int mid = s+((e-s)/2);
    int left = query(2*node, s, mid, qs, qe, segTree);
    int right = query(2*node+1, mid+1, e, qs, qe, segTree);
    return left^right;
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int n,q; cin>>n>>q;
    vector<int> arr(n);
    vector<int> segTree(4*n);
    for(int &i : arr){cin>>i;}
    build(arr,1,0,n-1, segTree);
    while(q--){
        int b,c; cin>>b>>c;
        cout<<query(1,0,n-1,b-1,c-1, segTree)<<"\n";
    }
    return 0;
}


//FOREST QUERIES
#include<iostream>
#include<bits/stdc++.h>
using namespace std;

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int n,q; cin>>n>>q;
    //jungle[i][j] = No. of trees between (1,1) and (i,j)
    vector<vector<int>> tree(n, vector<int>(n)); 
    vector<vector<int>> jungle(n+1, vector<int>(n+1)); 
    for(int i = 0; i<n; ++i){
        for(int j = 0; j<n; ++j){
            char s; cin>>s;
            if(s == '*'){tree[i][j] = 1;}
        }
    }
    
    for(int i = 1; i<=n; ++i){
        for(int j = 1; j<=n; ++j){
            jungle[i][j] = jungle[i-1][j]+jungle[i][j-1]-jungle[i-1][j-1]+tree[i-1][j-1];
        }
    }
    
    while(q--){
        int x1,x2,y1,y2; 
        cin>>y1>>x1>>y2>>x2;
        //cout<<y1<<","<<x1<<" and "<<y2<<","<<x2<<"\n";
        //cout<<jungle[y2][x2]<<" "<<jungle[y1-1][x2]<<" "<<jungle[y2][x1-1]<<" "<<jungle[y1-1][x1-1]<<"\n";
        cout<<(jungle[y2][x2]-jungle[y1-1][x2]-jungle[y2][x1-1]+jungle[y1-1][x1-1])<<"\n";
    }
    return 0;
}

//LIST REMOVALS
#include<iostream>
#include<bits/stdc++.h>
using namespace std;

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int n; cin>>n;
    vector<int> arr(n);
    for(int &i : arr){cin>>i;}
    set<int> queried;
    while(n--){
        int pos; cin>>pos; --pos;
        queried.insert(pos);
        auto itr = queried.lower_bound(pos);
        cout<<"Itr at "<<*itr<<" and pos = "<<pos<<" and diff = ";
        int diff = distance(queried.end(), itr);
        cout<<diff<<"  and element is ";
        cout<<arr[diff+pos]<<"\n";
    }
    cout<<"\n";
    return 0;
}