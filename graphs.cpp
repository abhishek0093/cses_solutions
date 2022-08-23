//GRAPHS
//MESSAGE ROUTE
#include<iostream>
#include<bits/stdc++.h>
using namespace std;
 
int steps;
 
void findConnected(vector<vector<int>> &arr, vector<int> &reached){
    int n = arr.size()-1;
    steps = 1;
    queue<int> que;
    que.push(1);
    while(!que.empty()){
        int sz = que.size();
        while(sz--){
            int from = que.front();
            que.pop();
            for(int next : arr[from]){
                if(next == n){
                    reached[n] = from;
                    return;
                }
                if(reached[next] == -1){
                    reached[next] = from;
                    que.push(next);
                }
            }
        }
        ++steps;
    }
    steps = INT_MAX;        //Not possible to reach nth computer
}
 
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int n, m;
    cin>>n>>m;
    vector<vector<int>> arr(n+1);
    vector<int> reached(n+1, -1);   //reached[i] denotes computer j, from where we have reached i(optimally from comp 1)
    reached[1] = 1;
    while(m--){
        int u,v ;
        cin>>u>>v;
        arr[u].push_back(v);
        arr[v].push_back(u);
    }
    findConnected(arr, reached);
    if(steps == INT_MAX){
        cout<<"IMPOSSIBLE\n";
        return 0;
    }
    cout<<++steps<<"\n";
    vector<int> path(steps);
    path[--steps] = n;
    int point = n;
    while(steps--){
        path[steps] = reached[point];
        point = reached[point];
    }
    for(int i : path){
        cout<<i<<" ";
    }
    cout<<"\n";

    return 0;
}

//LABYRINTH
#include<iostream>
#include<bits/stdc++.h>
using namespace std;

int steps;
int di, dj,n,m;
map<pair<int, int>, char>mp;
vector<int> dirs = {0,1,0,-1,0};

void startHere(vector<vector<char>> &building, int i, int j, vector<vector<pair<int, int>>> &reached){ 
    steps = 1;
    queue<pair<int, int>> que;
    que.push({i,j});
    while(!que.empty()){
        int sz = que.size();
        while(sz--){
          int fi = que.front().first;  //from_i   
          int fj = que.front().second; //from_j
          que.pop();
          for(int k = 0; k<4; ++k){
            int r = fi+dirs[k];
            int c = fj+dirs[k+1];
            if(r == di && c == dj){
              reached[r][c] = {fi,fj};
              return;
            }
            if(r < n && r>=0 && c<m && c>=0 && building[r][c] == '.' && reached[r][c].first == -1){
              reached[r][c] = {fi,fj};
              que.push({r,c});
            }
          }
        }
        ++steps;
    }
    steps = INT_MAX;        //Not possible to reach nth computer
}
 
int main(){
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  
  cin>>n>>m;
  int si,sj;
  vector<vector<char>> building(n, vector<char>(m,'#'));
  vector<vector<pair<int, int>>> reached(n, vector<pair<int, int>>(m,{-1,-1}));

  for(int i = 0; i<n; ++i){
    string s;
    cin>>s;
    for(int j = 0; j<m; ++j){
      if(s[j] == 'A'){si = i; sj = j; building[i][j] = '.' ;}
      else if(s[j] == 'B'){di = i; dj = j; building[i][j] = '.';}
      else if(s[j] == '.'){
        building[i][j] = '.';
      }
    }
  }
  reached[si][sj] = {si,sj};
  mp[{0,1}] = 'R';
  mp[{0,-1}] = 'L';
  mp[{1,0}] = 'D';
  mp[{-1,0}] = 'U';
  startHere(building, si,sj, reached);
  if(steps == INT_MAX){
    cout<<"NO\n";
    return 0;
  }
  cout<<"YES\n";
  cout<<steps<<"\n";
  vector<char> path(steps);

  while(steps--){
    int fi = reached[di][dj].first;
    int fj = reached[di][dj].second;
    pair<int, int> move = {di-fi, dj-fj};
    path[steps] = mp[move];
    di = fi; dj = fj;
  }
  for(char i : path){
    cout<<i;
  }
  cout<<"\n";
  return 0;
}

//BUILDING TEAMS
//APPROACH : Simple IsGraphBipartite problem
#include<iostream>
#include<bits/stdc++.h>
using namespace std;

int main(){
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  int n, m; cin>>n>>m;
  vector<vector<int>> pupil(n+1);   //pupil[i] ---> list of friends of pupil i
  while(m--){
    int u,v;
    cin>>u>>v;
    pupil[u].push_back(v);
    pupil[v].push_back(u);
  }
  vector<int> visited(n+1,0);     //visited[i] = 0/1/2 --> Team to which i belongs (0 implies that not visited yet).
  for(int i = 1; i<=n; ++i){
    if(!visited[i]){
      queue<int> que;
      que.push(i);
      visited[i] = 1;
      while(!que.empty()){
        int u = que.front();
        que.pop();
        int team = visited[u];
        for(int v : pupil[u]){
          if(visited[v] == team){     //Two friends Got into same team
            cout<<"IMPOSSIBLE\n";
            return 0;
          }
          if(!visited[v]){
            visited[v] = (team == 1 ? 2 : 1);
            que.push(v);
          }
        }
      }
    }
  }
  for(int i = 1; i<=n; ++i){
    cout<<visited[i]<<" ";
  }
  cout<<"\n";
  return 0;
}

//ROUND TRIP 
/*
IDEA : This question just asks us to find presence of a cycle in a Un-directed graph.
We will use dfs for this task. We will process each node. Initially all nodes will be unvisited (i.e all have parent as -1). 
We will start by selecting a starting node(SN) and will make it parent of its own (i.e parent[SN] = SN). Now,We will explore all its neighbour nodes (v) through dfs, and there will be two possiblities:
    1) Node Not Visited Yet: In this case we will mark the node as visited (will change parent[v] from -1 to node from where we came to present node(u)), and then will call dfs for all its child nodes. 
    2) Node Already visited: There are again two possibilites:
        a) v is same as parent[u] : In this case we don't need to do anything.
        b) v is not parent[u] : This implies by joining edge (u-v) we will form a cycle. So a cycle has been detected and we can retrieve this cycle through our parent array.  
*/

#include<bits/stdc++.h>
using namespace std;

bool found = false;         //Whether we have found a cycle so far? If Yes, we don't need to explore anymore. 
int cycleStart, cycleEnd;       //Start and end of our cycle. 
vector<vector<int>> roads;
vector<int> parent;         //parent[v] = u, we came to node v through u. Initially all have parent[i] = -1, nothing visited . 

void dfs(int u,int par){            //u denotes current node into consideration, and par denotes its parent. 
    if(found){return;}
    parent[u] = par;
    for(int v : roads[u]){
        if(parent[v] == -1){
            dfs(v,u);
        }
        else if(v != par){          //CYCLE FOUND ! We will form a cycle by joining (u-v).
            if(found){return;}
            found = true;
            cycleStart = v;
            cycleEnd = u;
        }
    }
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int n, m; cin>>n>>m;
    roads.resize(n+1);
    parent.resize(n+1);
    while(m--){
        int u,v; cin>>u>>v;
        roads[u].push_back(v);
        roads[v].push_back(u);
    }
    for(int i = 0; i<=n; ++i){parent[i] = -1;}
    for(int i = 1; i<=n; ++i){
        if(parent[i] != -1){continue;}
        dfs(i,i);       //make i parent of itself.
        if(found){      //print the cycle found. 
            vector<int> cycle;
            cycle.push_back(cycleStart);
            while(cycleEnd != cycleStart){
                cycle.push_back(cycleEnd);
                cycleEnd = parent[cycleEnd];
            }
            cycle.push_back(cycleStart);
            cout<<cycle.size()<<"\n";
            for(int i : cycle){
                cout<<i<<" ";
            }
            cout<<"\n";
            return 0;
        }
    }
    cout<<"IMPOSSIBLE\n";
    return 0;
}

//SHORTEST ROUTES - I
#include<iostream>
#include<bits/stdc++.h>
using namespace std;
typedef pair<long long, long long> pll;      //first stores distance, second stores vertex
 
void dijkstra(vector<vector<pll>> &adjL, int n, int k) {
    priority_queue<pll, vector<pll>, greater<pll> > minHeap;
    
    vector<long long> timeTaken(n+1, 1e18);
    minHeap.push({0,k});     
    timeTaken[k] = 0;    
    while(!minHeap.empty()){
        long long u = minHeap.top().second;
        long long d = minHeap.top().first;
        minHeap.pop();
        if(d != timeTaken[u]){continue;}
        for(auto p : adjL[u]){        //Go to all reachable vertices from u, and check if signal can reach there in even more less time or not. If yes update the time
            long long v = p.first;
            long long wt = p.second;
            if(timeTaken[v] > timeTaken[u]+wt){
                timeTaken[v] = timeTaken[u]+wt;
                minHeap.push({timeTaken[v], v});
            }
        }
    }
    for(int i = 1; i<=n; ++i){
        cout<<timeTaken[i]<<" ";
    }              
    cout<<"\n";
    return;
}
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int n,m;
    cin>>n>>m;
    vector<vector<pll>> adjL(n+1); 
    while(m--){
        long long u,v,w;
        cin>>u>>v>>w;
        adjL[u].push_back({v, w});
    }
    dijkstra(adjL, n, 1);
 
 
    return 0;
}

//SHORTEST ROUTES-II
#include<iostream>
#include<bits/stdc++.h>
using namespace std;
const long long INF = 1e18;
 
void floydWarshall(vector<vector<long long>> &graph){
    //changes graph, if not want copy elements
    int n = graph.size();
    for (int k = 1; k < n; k++) {
        for (int i = 1; i < n; i++) {
            for (int j = 1; j < n; j++) {
                if ((graph[k][j] != INF && graph[i][k] != INF)  && graph[i][j] > (graph[i][k] + graph[k][j])){
                    graph[i][j] = graph[i][k] + graph[k][j];
                }    
            }
        }
    }    

    return ;
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int n,m,q;
    cin>>n>>m>>q;
    vector<vector<long long >> adjM(n+1, vector<long long>(n+1, INF)); 
    while(m--){
        long long u,v,w;
        cin>>u>>v>>w;
        adjM[u][v] = min(adjM[u][v], w);
        adjM[v][u] = min(adjM[u][v], w);
    }
    for(int i = 0; i<=n; ++i){adjM[i][i] = 0;}
    floydWarshall(adjM);

    while(q--){
        int i,j;
        cin>>i>>j;
        cout<<(adjM[i][j] == INF ? -1 : adjM[i][j])<<"\n";
    } 
    return 0;
}

//COURSE SCHEDULE
#include<iostream>
#include<bits/stdc++.h>
using namespace std;

void findOrder(int numC, vector<vector<int>>& adjL, vector<int> &inDegree) {
    vector<int> ans; queue<int> que;       
    
    for(int i = 1; i<=numC; ++i){        
        if(inDegree[i] == 0){que.push(i);}    
    }
    while(!que.empty()){
        int u = que.front();
        que.pop();
        ans.push_back(u);   
        for(int i : adjL[u]){   
            --inDegree[i];  
            if(inDegree[i] == 0){que.push(i);}  
        }
    }
    if(ans.size() != numC){cout<<"IMPOSSIBLE\n"; return;}
    for(int i : ans){cout<<i<<" ";}
    cout<<"\n";
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int n, m;
    cin>>n>>m;
    vector<vector<int>> adjL(n+1);
    vector<int> inDegree(n+1, 0);
    while(m--){
        int a,b;cin>>a>>b;
        adjL[a].push_back(b);
        ++inDegree[b];
    }
    findOrder(n, adjL, inDegree);
    return 0;
}

//HIGH SCORE
#include<iostream>
#include<bits/stdc++.h>
using namespace std;

const long long INF = 1e18;

bool dfs(int i, vector<vector<int>> radjL, unordered_set<int> &st, vector<bool> &visited){
    if(st.count(i)){return true;}
    if(visited[i]){return false;}
    visited[i] = true;
    for(int v : radjL[i]){
        bool value = dfs(v, radjL, st, visited);
        if(value){return true;}
    }
    return false;
    
}
void  bellManFord(vector<vector<int>> &graph, int src, int n){
    //changes original graph,if don't want make a copy of graph
    vector<long long> dist(n+1, INF);
    dist[src] = 0;
    for(int i = 0; i<n-1; ++i){     //RELAX N-1 TIMES   
        for(int j = 0; j<graph.size(); ++j){
            int u = graph[j][0];
            int v = graph[j][1];
            int w = graph[j][2];
            if(dist[u] != INF && dist[v] > dist[u]+w){
                dist[v] = dist[u]+w;
            }
        }
    }
    unordered_set<int> st;
    for(int i = 0; i<graph.size(); ++i){
        int u = graph[i][0];
        int v = graph[i][1];
        int w = graph[i][2];
        if(dist[u] != INF && dist[v] > dist[u]+w){
            st.insert(v);
        }
    }
    vector<vector<int>> radjL(n+1);
    for(auto &v : graph){
        radjL[v[1]].push_back(v[0]);
    }
    vector<bool> visited(n+1,0);
    if(dfs(n,radjL,st,visited)){cout<<-1<<"\n"; return;}
    cout<<-1*dist[n]<<"\n";
    return;
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int n,m;
    cin>>n>>m;
    vector<vector<int>> graph(m);
    for(int i = 0; i<m; ++i){
        int u,v,w;
        cin>>u>>v>>w;
        graph[i] = {u,v,-1*w};
    }
    bellManFord(graph,1,n); 
    return 0;
}

//GAME ROUTES
#include<iostream>
#include<bits/stdc++.h>
using namespace std;

int MOD = 1e9+7;
int n;
int countWays(vector<vector<int>> &graph, vector<int> &dp, int u){
    if(u == n){return 1;}
    if(dp[u] != -1){return dp[u];}
    int ways = 0;
    for(int v : graph[u]){
        ways = (ways%MOD + countWays(graph,dp,v)%MOD)%MOD;
    }
    return dp[u] = ways;

}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int m; cin>>n>>m;
    vector<vector<int>> graph(n+1);
    while(m--){
        int a,b; cin>>a>>b;
        graph[a].push_back(b);
    }
    vector<int> dp(n+1,-1);
    cout<<countWays(graph,dp,1)<<"\n";
    return 0;
}

//MONSTERS
#include<bits/stdc++.h>
using namespace std;
/*
Find for every block minimum steps that any monster will need to reach there(as minsteps are needed so, bfs would be helpful.)
If we can anyhow find a path to the boundary such that, during the entire path we reach every cell before any monster, then that path will be our required path.
*/

map<pair<int,int>,char> mp;
queue<pair<int,int>> que;
vector<int> dirs = {0,-1,0,1,0};        // OUR direction array
int n,m;
string path = "";           //Our Path to boundary

void fillMonsters(int steps,vector<vector<int>> &monsters){
    while(!que.empty()){
        int sz = que.size();
        while(sz--){ 
            pair<int,int>p = que.front(); que.pop();
            for(int k = 0; k<4; ++k){
                int r = p.first+dirs[k];
                int c = p.second+dirs[k+1];
                if(r>=0 && r<n && c>=0 && c<m && monsters[r][c] == -1){
                    monsters[r][c] = steps+1; 
                    que.push({r,c});
                }
            }    
        }
        ++steps;
    }
}

void findPath(vector<vector<int>> &monsters, int i, int j){
    if(i<0 || i>=n || j<0 || j>=m || monsters[i][j] <= path.size()){return;}
    if(i == n-1 || i == 0 || j == m-1 || j == 0){
        path.push_back('Y');        //Put a Reached symbol at back
        return;
    }
    int monsterStepsToHere = monsters[i][j];
    int tillHereSteps = path.size();
    monsters[i][j] = 0;     //To Prevent Jumping back to this cell again in future, assume monsters reached here in 0 steps(or equivalently there is a wall here).
    for(int k = 0; k<4; ++k){
        int r = i+dirs[k];
        int c = j+dirs[k+1];
        path.push_back(mp[{dirs[k],dirs[k+1]}]);
        findPath(monsters,r,c);
        if(path.size()-1 != tillHereSteps){     //In addition to above pushed element, something other was also pushed --> We had already found a path!
            return;
        }
        path.pop_back();        //We can't find path with current direction, try another direction
    }
    monsters[i][j] = monsterStepsToHere;        //Restore actual steps for this {i,j}.
}


int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    cin>>n>>m;
    vector<vector<int>> monsters(n,vector<int>(m,-1));      //mosters[i][j] - min steps required by monsters to reach ith row, and jth column (0-indexed)
    mp.insert({{0,-1},'L'}); 
    mp.insert({{0,1},'R'});
    mp.insert({{-1,0},'U'}); 
    mp.insert({{1,0},'D'});
    int si = 0;int sj=0;            //starting i, starting j

    for(int i = 0; i<n; ++i){
        string s; cin>>s;
        for(int j = 0; j<m; ++j){
            if(s[j] == '#'){monsters[i][j] = 0;}        //As it is a wall, so we can't move here in any case. It is same as saying that monster reached here in 0 steps.
            if(s[j] == 'A'){si = i; sj = j;}
            if(s[j] == 'M'){que.push({i,j});monsters[i][j] = 0;}        //monsters reached here in 0 steps, but it can also expand, so push it inside our queue
        }
    }
    //For all (i,j) calculate min steps needed by monsters to reach there - SIMPLE BFS
    fillMonsters(0,monsters);       

    //Check for any valid path
    findPath(monsters,si,sj);

    if(path.size()){
        cout<<"YES"<<"\n";
        path.pop_back();
        cout<<path.size()<<"\n";
        cout<<path<<"\n";
        return 0;
    }
    cout<<"NO\n";
    return 0;
}

//FLIGHT DISCOUNT
#include<bits/stdc++.h>
using namespace std;
/*
IDEA : The Idea is very similar to normal Dijkstra algorithm. But Here we will use 2D Array for minCost calculation
flightCost[i][status] : Min cost to reach city i, from city 1 given status of discount used as 'status'. status = 0 : Discount not used till reaching i; status = 1 : Discount has been used in reached till i.
For every edge into consideration during our priority que evaluation, either status would be 0, or 1.
If it 1, we can't use discount anymore. So,simple dijkstra.
But if status is 0, then alongwith simple dijikstra, we also have the opportunity to use our dicount ticket for current edge, and use it if it gives better results,
*/


typedef pair<long long, long long> pll;      //first stores distance, second stores vertex
typedef pair<long long, pair<long long,long long>> plll;    //.first stores distance, .second.first stores vertex, and .second.second denotes status of discount.
 
void dijkstra(vector<vector<pll>> &adjL, int n, int k) {
    priority_queue<plll, vector<plll>, greater<plll> > minHeap;
    
    vector<vector<long long>> flightCost(n+1, vector<long long>(2,1e18));
    minHeap.push({0,{k,0}});     
    minHeap.push({0,{k,1}});     
    flightCost[k][0] = 0;
    flightCost[k][1] = 0;    
    while(!minHeap.empty()){
        plll top = minHeap.top(); minHeap.pop();
        long long u = top.second.first;
        long long d = top.first;
        long long status = top.second.second;

        if(d != flightCost[u][status]){continue;}       //Discard older results.
        for(auto p : adjL[u]){        //Go to all reachable vertices from u, and check if we can reach there in even more less cost or not
            long long v = p.first;
            long long wt = p.second;
            if(status == 1 && flightCost[v][1] > flightCost[u][1]+wt){      //Discount has already been used in reaching of u, so can't use anymore.
                flightCost[v][1] = flightCost[u][1]+wt;
                minHeap.push({flightCost[v][1], {v,1}});
            }
            if(status == 0){            //Current edge u----->v at cost of wt
                if(flightCost[v][0] > flightCost[u][0]+wt){     //Don't use discount for this edge 
                    flightCost[v][0] = flightCost[u][0]+wt;
                    minHeap.push({flightCost[v][0], {v,0}});
                }
                if(flightCost[v][1] > flightCost[u][0]+wt/2){       //Use discount for this edge route
                    flightCost[v][1] = flightCost[u][0]+wt/2;
                    minHeap.push({flightCost[v][1], {v,1}});
                }
                
            }
        }
    }
    cout<<min(flightCost[n][0],flightCost[n][1])<<"\n";             
    return;
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int n,m; cin>>n>>m;
    vector<vector<pll>> adjL(n+1);
    while(m--){
        long long u,v,wt; cin>>u>>v>>wt;
        adjL[u].push_back({v,wt});
    }
    dijkstra(adjL,n,1);
    return 0;
}

//FLIGHT ROUTES
#include<bits/stdc++.h>
using namespace std;
/*
IDEA : It is single source K shortest Path(s) simple question. The Idea is very similar to normal Dijkstra algorithm. But Here we will use 2D Array for finding k-best paths.
flightCost[i][j] : (j+1)th best cost path to reach city i from src city.
we will always keep flightCost[i] sorted, so that last one is always kth best path till then.
For every edge into consideration during our priority que evaluation, we will check that if current path cost is less than our worst (kth best) deal or not.
If it is, we will update our kth best deal, and again sort the array. 
*/


typedef pair<long long, long long> pll;      //first stores distance, second stores vertex 
 
void dijkstra(vector<vector<pll>> &adjL, int n, int src, int k) {
    priority_queue<pll, vector<pll>, greater<pll> > minHeap;
    
    vector<vector<long long>> flightCost(n+1, vector<long long>(k,1e18));
    minHeap.push({0,src});
    flightCost[src][0] = 0; 
    
    while(!minHeap.empty()){
        pll top = minHeap.top(); minHeap.pop();
        long long u = top.second;
        long long d = top.first;
        if(d > flightCost[u][k-1]){continue;}       //Our Current Path to 'u' is even worst than our present kth best path. So, we ignore this path.

        for(auto p : adjL[u]){        //Go to all reachable vertices from u
            long long v = p.first;
            long long wt = p.second;
            if(flightCost[v][k-1] > d+wt){      //If present path is better than kth best path?
                flightCost[v][k-1] = d+wt;
                minHeap.push({d+wt,v});
                sort(flightCost[v].begin(),flightCost[v].end());
            }
        }
    }
    for(int i = 0; i<k; ++i){
        cout<<flightCost[n][i]<<" ";
    }
    cout<<"\n";             
    return;
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int n,m,k; cin>>n>>m>>k;
    vector<vector<pll>> adjL(n+1);
    while(m--){
        long long u,v,wt; cin>>u>>v>>wt;
        adjL[u].push_back({v,wt});
    }
    dijkstra(adjL,n,1,k);
    return 0;
}

//INVESTIGATION
#include<bits/stdc++.h>
using namespace std;
/*
IDEA : As Is visible from description it is modified dijkstra problem. We need to track of optimal paths.
Now, to reach city i, 
     flightCost[i][0] = minimum cost
     flightCost[i][1] = No. of min cost paths
     flightCost[i][2] = Min flight in minCost path
     flightCost[i][3] = Max flight in minCost path

During our priority queue evaluation, if we found that the current path isn't optimal path, we discard it.
If we find yet another instance of current optimal path, we do the changes in our vector
and if we new optimal path than the current path, we reset everything.
*/

int MOD = 1e9+7;

typedef pair<long long, long long> pll;      //first stores distance, second stores vertex 
 
void dijkstra(vector<vector<pll>> &adjL, int n, int src) {
    priority_queue<pll, vector<pll>, greater<pll> > minHeap;
    
    vector<vector<long long>> flightCost(n+1, vector<long long>(4,1e18));
    for(int i = 0; i<=n; ++i){
        flightCost[i][1] = 0;
        flightCost[i][3] = INT_MIN;
    }

    minHeap.push({0,src});
    //Do the updates for src city.
    flightCost[src][0] = 0; 
    flightCost[src][1] = 1; 
    flightCost[src][2] = 0; 
    flightCost[src][3] = 0; 
    
    while(!minHeap.empty()){
        pll top = minHeap.top(); minHeap.pop();
        long long u = top.second;
        long long d = top.first;
        
        if(d != flightCost[u][0]){continue;}        //Discard longer routes
        for(auto p : adjL[u]){        //Go to all reachable vertices from u
            long long v = p.first;
            long long wt = p.second;
            if(flightCost[v][0] == d+wt){      //Found another instance to reach v,at the same current optimal cost through u, do the updates
                flightCost[v][1] += flightCost[u][1];       //Increase by number of ways to reach 'u'
                flightCost[v][1]%=MOD;
                flightCost[v][2] = min(flightCost[u][2]+1,flightCost[v][2]);    //Either we take earlier minflight to v, or take minflight to u, and take 1 flight from u->v
                flightCost[v][3] = max(flightCost[u][3]+1,flightCost[v][3]);
                //THINK : Why not pushed {d+wt,v} in the minHeap?   
            }
            else if(flightCost[v][0] > d+wt){      //Found Another better path to reach 'v' --> reset.
                flightCost[v][0] = d+wt;
                flightCost[v][1] = flightCost[u][1];
                flightCost[v][2] = flightCost[u][2]+1;
                flightCost[v][3] = flightCost[u][3]+1;
                minHeap.push({d+wt,v});
            }
        }
    }
    cout<<flightCost[n][0]<<" "<<flightCost[n][1]<<" "<<flightCost[n][2]<<" "<<flightCost[n][3]<<"\n";             
    return;
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int n,m; cin>>n>>m;
    vector<vector<pll>> adjL(n+1);
    while(m--){
        long long u,v,wt; cin>>u>>v>>wt;
        adjL[u].push_back({v,wt});
    }
    dijkstra(adjL,n,1);
    return 0;
}  

//Road Reparation 
#include<bits/stdc++.h>
using namespace std;
 
//Edge : {wt,{src vertex, dest vertex}}
#define Edge pair<long long,pair<int,int>>
int parent[200001];
int n;
 
void makeset(){    //For 0 based start from zero til less than size
    for(int i = 1; i<=n; ++i){parent[i] = -1;}
}
 
int find(int i){
    if(parent[i] == -1){return i;}
    return parent[i] = find(parent[i]);
}
 
void unin(int x, int y){
    int a = find(x);
    int b = find(y);
    parent[a] = b;
}
 
void kruskal(vector<Edge> &input){
    sort(input.begin(), input.end());
    makeset();
    long long cnt = 0;
    long long edgesAdded = 0; 
    for(Edge ed : input){
        int sR  = find(ed.second.first);        //sR strands for representative element fro source vertex, and dR for destination
        int dR  = find(ed.second.second);
        if( sR != dR ){     //means they belong to different set and cycle not formed
            cnt+=ed.first;
            ++edgesAdded;
            unin(sR, dR);     //combine source and destination sets
        }
    }
 
    if(edgesAdded != n-1){
        cout<<"IMPOSSIBLE\n";
        return;
    }
    cout<<cnt<<"\n";
}
 
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int m; cin>>n>>m;
    vector<Edge> input(m);
    for(Edge &e : input){
        cin>>e.second.first>>e.second.second>>e.first;
    }
    kruskal(input);
    return 0;
}

//ROAD CONSTRUCTION
#include<bits/stdc++.h>
using namespace std;
/*
The idea is very similar to normal kruskal's algorithm. 
But Here in parent array we will also store size of set/component represented by our representative element.
Intially all nodes are disconnected, i.e size of every compo is 1.Whenever we will join two disconnnected components, it will result in decrease on number of connected compo by 1. 
Upon joining (two non-connected compo)the size of final representative set may become larger than our current largest compo size so we need to check that also.  
*/

//Edge : {src vertex, dest vertex}
#define Edge pair<int,int>
pair<int,int> parent[100001];       //.first represent representative city, and .second is size of connected compo represented by that city.  
int n,m;                            //Number of cities/nodes; Cnt of Roads. 

void makeset(){ 
    for(int i = 1; i<=n; ++i){ //Initially all nodes are in different sets/compo, i.e parent of their own.
        parent[i].first = -1;
        parent[i].second = 1;
    }     
}

pair<int,int> find(int i){        //Find and update representative and size of set of i 
    if(parent[i].first == -1){return {i,parent[i].second};}
    pair<int,int> ele = find(parent[i].first);
    parent[i].first = ele.first;
    parent[i].second = ele.second;
    return {parent[i].first,parent[i].second}; 
}

void unin(int x, int y){    //Merge sets represented by x, and j
    parent[x].first = y;        //y becomes representative of combined set
    parent[y].second +=parent[x].second;        //size of connected compo represented by y gets increased by set earlier represented by x.
}

void kruskal(){
    makeset();
    int cntCompo = n;
    int largestCompo = INT_MIN;
    for(int i = 0; i<m; ++i){
        int a,b; cin>>a>>b;
        pair<int,int> sR  = find(a);        //sR strands for representative element for source vertex, and dR for destination
        pair<int,int> dR  = find(b);
        if( sR.first != dR.first ){     //means they belong to different set and cycle not formed
            --cntCompo;
            unin(sR.first, dR.first);     //combine source and destination sets
            largestCompo = max(largestCompo,parent[dR.first].second);
        }
        cout<<cntCompo<<" "<<largestCompo<<"\n";
    }
}

//FLIGHT ROUTES CHECK
#include<bits/stdc++.h>
using namespace std;
/*
As you would have guessed by now, Kruskal and prims won't work here.
IDEA : If we can reach all cities from city1 , and city1 can be reached by all other cities ,
then we can say that there is a path between every pair of cities.Let's say we want to go from u->v. we can first reach city1 from u, and then from city1 we can reach v, i.e u------>city1---->v.
*/
int reached[100001];        //whether city i has been reached or not?
int graphOneCityReach = 0;  //count of cities reachable from city1

//Check how many cities are reachable from src city, and evntually from city 1.
void checkReach(int src, vector<vector<int>> &graph){
    if(reached[src]){return;}
    ++graphOneCityReach;
    reached[src] = 1;
    for(int dest : graph[src]){
        checkReach(dest,graph);
    }
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int n,m; cin>>n>>m;
    vector<vector<int>> graph(n+1);     
    vector<vector<int>> revGraph(n+1);      //reverse of original graph. u--->v becomes v--->u
    while(m--){
        int a,b; cin>>a>>b;
        graph[a].push_back(b);
        revGraph[b].push_back(a);
    }
    //check how many cities are reachable from city 1.
    checkReach(1,graph);
    if(graphOneCityReach != n){     //Not all cities are reachable.
        cout<<"NO\n";
        for(int i = 1; i<=n; ++i){
            if(!reached[i]){
                cout<<1<<" "<<i<<"\n";
                return 0;
            }
        }
    }

    //Now, we need to check that from how many cities we can reach city1 in original graph.
    //It is equivalent to saying that in revGraph how many cities we can reach from city1.
    for(int i = 1; i<=n; ++i){
        reached[i] = 0;
    }
    graphOneCityReach = 0;
    checkReach(1,revGraph);
    if(graphOneCityReach != n){
        cout<<"NO\n";
        for(int i = 1; i<=n; ++i){
            if(!reached[i]){
                cout<<i<<" "<<1<<"\n";
                return 0;
            }
        }
    }
    cout<<"YES\n";
    return 0;
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    cin>>n>>m;
    kruskal();
    return 0;
}

//PLANETS AND KINGDOMS 
/*
IDEA : We just need to find Strongly connected components in this graph. Here I'm using Tarjan's algorithm.
*/
//Code Snippet Credit to - https://www.youtube.com/watch?v=ZeDNSeilf-Y

#include<bits/stdc++.h>
using namespace std;
int n,m;                //n- Number of vertices
int SccCnt = 1;
int SCC[100001];

unordered_map<int,vector<int>> adjL;            //adjL stored in a map. adl[i] - vertices reachable from i

void DFS(int u,vector<int>& disc,vector<int>& low,stack<int>& mystack,vector<bool>& presentInStack)
{
	static int time = 0;
	disc[u] = low[u] = time;
	time+=1;
	mystack.push(u);
	presentInStack[u] = true;

	for(int v: adjL[u])
	{
		if(disc[v]==-1)	//If v is not visited
		{
			DFS(v,disc,low,mystack,presentInStack);
			low[u] = min(low[u],low[v]);
		}
		//Differentiate back-edge and cross-edge
		else if(presentInStack[v])	//Back-edge case
			low[u] = min(low[u],disc[v]);
	}

	if(low[u]==disc[u])	//If u is head node of SCC
	{
		while(mystack.top()!=u)
		{
			SCC[mystack.top()] = SccCnt;
			presentInStack[mystack.top()] = false;
			mystack.pop();
		}
		SCC[mystack.top()] = SccCnt;
		presentInStack[mystack.top()] = false;
		mystack.pop();
        ++SccCnt;
	}
}

void findSCCs_Tarjan()
{
	vector<int> disc(n+1,-1),low(n+1,-1);
	vector<bool> presentInStack(n+1,false);	//Avoids cross-edge
	stack<int> mystack;

	for(int i=1;i<=n;++i)
		if(disc[i]==-1)
			DFS(i,disc,low,mystack,presentInStack);
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    cin>>n>>m;
    while(m--){
        int a,b; cin>>a>>b;
        adjL[a].push_back(b);
    }

	findSCCs_Tarjan();
    cout<<--SccCnt<<"\n";
    for(int i = 1; i<=n; ++i){
        cout<<SCC[i]<<" ";
    }
    cout<<"\n";
	return 0;
}

//COIN COLLECTOR

#include<bits/stdc++.h>
using namespace std;
/*
IDEA : Idea is very similar to finding the SCC (see the planets and kingdom problem), but here we need some extra things to keep in mind. 
As soon as we will reach a room(room 'r'), we can collect all the coins from the rooms that lie in the same SCC as room 'r', without disturbing our flow(Why? Bcz we can again reach room 'r' after collecting all SCC coins).
So, we can collect all the coins that lie in scc of room 'r'. But can we add some more coins?
Yes, we can move to one of the adjacent SCCs (why only 1? HINT: focus on SCC defination). 
So if we can represent an entire SCC as 1 node in graph with value of coins lying in that SCC, our task will become simple - To find max collectible coins in a DAG, which we can easily do with the help of dfs.
*/

int n,m; 
long long coins[100001];		//coins[i] - coin in room i
long long SCC[100001];			//SCC[i] : ith room lies in which SCC component? 
int sccCnt = 1;					//Count of SCCs+1
long long sccCoins = 0;			//VAlue of all coins lying in a particular SCC
map<int,long long>sccReps;		//Representative of SCCs. key = SCC-number, and value = sum of coin values lying in that SCC
long long maxCoins = INT_MIN;		//maxCollectible Coins

unordered_map<int,vector<int>> adjL;     //adj-List stored in map. adjL[i]- node reachable from i
unordered_map<int,set<int>> sccAdjL;     //adj-List when entire SCC is represented as only 1 node.  sccAdjL[i]- SCCs reachable from SCC-number i.

//Tarjan's algorithm for finding SCC.
void DFS(int u,vector<int>& disc,vector<int>& low,stack<int>& mystack,vector<bool>& presentInStack){
	static int time = 0;
	disc[u] = low[u] = time;
	time+=1;
	mystack.push(u);
	presentInStack[u] = true;

	for(int v: adjL[u])
	{
		if(disc[v]==-1)	//If v is not visited
		{
			DFS(v,disc,low,mystack,presentInStack);
			low[u] = min(low[u],low[v]);
		}
		//Differentiate back-edge and cross-edge
		else if(presentInStack[v])	//Back-edge case
			low[u] = min(low[u],disc[v]);
	}

	if(low[u]==disc[u])	//If u is head node of SCC
	{
		while(mystack.top()!=u)
		{
			SCC[mystack.top()] = sccCnt;
			sccCoins+=coins[mystack.top()];
			presentInStack[mystack.top()] = false;
			mystack.pop();
		}
		SCC[mystack.top()] = sccCnt;
		sccCoins+=coins[mystack.top()];
		presentInStack[mystack.top()] = false;
		mystack.pop();
		sccReps.insert({sccCnt++,sccCoins});		//Insert value for current SCC in the map
		sccCoins = 0;							//make sccCoins = 0, to be used for counting coin values for next scc.
	}
}

void findSCCs_Tarjan(){
	vector<int> disc(n+1,-1),low(n+1,-1);
	vector<bool> presentInStack(n+1,false);	//Avoids cross-edge
	stack<int> mystack;

	for(int i=1;i<=n;++i){
		if(disc[i]==-1){
			DFS(i,disc,low,mystack,presentInStack);
		}
	}			
}

long long dfs(vector<long long> &finalSccCoins, int i){
	if(i > sccCnt){return 0;}
	if(finalSccCoins[i] != -1){return finalSccCoins[i];}
	long long adjCoins = 0;
	for(int v : sccAdjL[i]){
		adjCoins = max(adjCoins,dfs(finalSccCoins,v));
	}
	return finalSccCoins[i] = sccReps[i]+adjCoins;
}

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);
	cin>>n>>m;
	for(int i =1; i<=n; ++i){cin>>coins[i];}
	while(m--){
		int a,b; cin>>a>>b;
		adjL[a].push_back(b);
	}
	findSCCs_Tarjan();--sccCnt;
	//Now we need to construct a graph where an entire SCC is represented as 1 node. (So there will be in total of sccCnt nodes in graph, i.e 1,2,3,4,---sccCnt)
	for(auto p : adjL){
		for(int v : p.second){
			if(SCC[p.first] != SCC[v]){
				sccAdjL[SCC[p.first]].insert(SCC[v]);
			}
		}
	}

	vector<long long>finalSccCoins(sccCnt+1, -1);			//finalSccCoins[i] = maxCoins Collectible if we start at SCC number i. 
	for(int i = 1; i<=sccCnt; ++i){
		maxCoins = max(maxCoins, dfs(finalSccCoins, i));
	}
	cout<<maxCoins<<"\n";
	return 0;
}

// GIANT PIZZA
#include<bits/stdc++.h>
using namespace std;
/*
IDEA : Highly Reccomended --> Read page 192 of the book given in the introduction part of the cses, otherwise understanding solution would be very difficult. (competitive programmer's handbook)
*/
 
int n,m; 
long long SCC[200005];			//SCC[i] : ith index (or (-m+i)th topping) lies in which SCC component? 
int sccCnt = 1;					//Count of SCCs
map<int, vector<int>>sccs;		//sccs[i] - list of all the toppings(remember topping can be negative as well, read the book to get more) lying in ith SCC.
long long toppingPresent[100001];			//Status of abs(ith) toppping in final pizza. -1 will denote that we are not yet sure. 
 
unordered_map<int,vector<int>> adjL;     //adj-List stored in map. adjL[i]- list of indexes j(or equivalently j-m th toppings) reachable from i
unordered_map<int,set<int>> sccAdjL;     //adj-List when entire SCC is represented as only 1 node.  sccAdjL[i]- SCCs reachable from SCC-number i.
 
//Tarjan's algorithm for finding SCC.
void DFS(int u,vector<int>& disc,vector<int>& low,stack<int>& mystack,vector<bool>& presentInStack){
	static int time = 0;
	disc[u] = low[u] = time;
	time+=1;
	mystack.push(u);
	presentInStack[u] = true;
 
	for(int v: adjL[u])
	{
		if(disc[v]==-1)	//If v is not visited
		{
			DFS(v,disc,low,mystack,presentInStack);
			low[u] = min(low[u],low[v]);
		}
		//Differentiate back-edge and cross-edge
		else if(presentInStack[v])	//Back-edge case
			low[u] = min(low[u],disc[v]);
	}
 
	if(low[u]==disc[u])	//If u is head node of SCC
	{
		while(mystack.top()!=u)
		{
			SCC[mystack.top()] = sccCnt;
			sccs[sccCnt].push_back(mystack.top()-m);
			presentInStack[mystack.top()] = false;
			mystack.pop();
		}
		SCC[mystack.top()] = sccCnt;
		sccs[sccCnt].push_back(mystack.top()-m);
		presentInStack[mystack.top()] = false;
		mystack.pop();
		++sccCnt;
	}
}
 
void findSCCs_Tarjan(){
	vector<int> disc(2*m+1,-1),low(2*m+1,-1);
	vector<bool> presentInStack(2*m+1,false);	//Avoids cross-edge
	stack<int> mystack;
 
	for(int i=0;i<=2*m;++i){
		if(disc[i]==-1){
			DFS(i,disc,low,mystack,presentInStack);
		}
	}			
}

//Traverse Connected SCCs in reverse topological order. 
void findOrder(vector<int> &outDegree, vector<vector<int>> &revList) {       
    queue<int> que;   
 
    for(int i = 1; i<=sccCnt; ++i){        
        if(outDegree[i] == 0){que.push(i);}    
    }
    
    while(!que.empty()){
        int u = que.front();
        que.pop();
		for(int v : sccs[u]){
			if(toppingPresent[abs(v)] == -1){
				v<0 ? toppingPresent[abs(v)] = 0 : toppingPresent[abs(v)] = 1;
			}
		}
        for(int v : revList[u]){   
            --outDegree[v];  
            if(outDegree[v] == 0){que.push(v);}  
        }
    }
 
    return ;
}
 
 
int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);
	cin>>n>>m;
	while(n--){
		char s1,s2; int a,b; cin>>s1>>a>>s2>>b;
		if(s1 == '-'){a = -1*a;}
		if(s2 == '-'){b = -1*b;}
		adjL[m-a].push_back(m+b);
		adjL[m-b].push_back(m+a);
	}
 
	findSCCs_Tarjan();--sccCnt;
	for(int i = 0; i<m; ++i){
		if(SCC[i] == SCC[2*m-i]){
			cout<<"IMPOSSIBLE\n";
			return 0;
		}
	}
	vector<int> outDegree(sccCnt+1,0); 
	vector<vector<int>> revList(sccCnt+1);
 
	//Now we need to construct a graph where an entire SCC is represented as 1 node. (So there will be in total of sccCnt nodes in graph, i.e 1,2,3,4,---sccCnt)
	for(auto p : adjL){
		for(int v : p.second){
			if(SCC[p.first] != SCC[v]){
				sccAdjL[SCC[p.first]].insert(SCC[v]);
				outDegree[SCC[p.first]]++;
				revList[SCC[v]].push_back(SCC[p.first]);
			}
		}
	}
 
	for(int i = 0; i<=m; ++i){
		toppingPresent[i] = -1;
	}
	findOrder(outDegree, revList);
	for(int i = 1; i<=m; ++i){
		cout<<(toppingPresent[i] == 0 ? "-" : "+")<<" ";
	}
	cout<<"\n";
	return 0;
}

//PLANET QUERIES-I
/*
IDEA : (treat using teleport as making a jump). 
One of the naive ways would be to construct the graph and then simulate the queries.
But as you guessed it right , it would lead to TLE!. Can we do something better? 
Can we preprocess the data so that we can answer the queries faster?
Is the fact that any number can be represented as some combination of power of 2 relatable here?(53 = 32+16+4+1).
What if we know already know for query(x,k), what will be destination if we make nearest 2's exponent jumps. Let y pe planet reached, and k' (2's max power less than k) be the jumps made. 
Then our new task has been reduced to answer the query (y,k-k'), and if k-k' == 0, we are done! y will be the destination.
So as we can see that we are able to reduce a subquery, we can get idea that it is some combination of graph and dp.   
if we can store that from planet x,making all 2's power jumps what will be the planet reached, then we can answer any query efficiently.
SO, let's dp[i][j] = planet reached if we start from planet i, and make (2^j) jumps.  

To calculate dp[i][j], we can take help of dp[i][j-1](let = prevPos).
Now, we were able to reach prevPos from i, making 2^(j-1) or (2^j / 2) jumps. Now to make j jumps, we still have to make 2^(j-1) more jumps. So, now treating prevPos as our starting point we can get destination after 2^(j-1) jumps from our dp array.
*/

#include<bits/stdc++.h>
using namespace std;

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);
	int n,q; cin>>n>>q;
	int dp[n+1][32];			//dp[i][j] = planet reached if we start from planet i, and make (2^j) jumps. k is atMax 1e9, so max(j) = 30 will work.
	for(int i = 1; i<=n; ++i){cin>>dp[i][0];}		//dp[i][0] will be destination of direct teleport. 
	for(int j = 1; j<=30; ++j){
		for(int i = 1; i<=n; ++i){
			int prevPos = dp[i][j-1];
			dp[i][j] = dp[prevPos][j-1];
		}
	}
	while(q--){
		int x,k; cin>>x>>k;
		while(k!=0){
			int nearest2Power = int(log2(k));
			x = dp[x][nearest2Power];		//Update x (start planet) 
			k -=(1<<nearest2Power);		//Remaining jumps
		}
		cout<<x<<"\n";
	}
	return 0;
}

//DOWNLOAD SPEED
//Snippet taken from geeksForGeeks, so kudos to them !
#include<bits/stdc++.h>
using namespace std;
 
// Number of vertices in given graph
int n;
long long rGraph[501][501];
int parent[501];
bool visited[501];
 
/* Returns true if there is a path from source 's' to sink
  't' in residual graph. Also fills parent[] to store the
  path */
bool bfs(int s, int t){
	memset(visited, false, sizeof(visited));
 
	queue<int> Q; Q.push(s); visited[s]=1;
 
	while(!Q.empty()) {
		int i=Q.front(); Q.pop();
		for(int j = 1; j<=n; ++j) {
			if (rGraph[i][j] && !visited[j]){
				visited[j]=1, parent[j]=i, Q.push(j);
			}	
		}
	}
 
	return visited[n];
}
 
// Returns the maximum flow from s to t in the given graph
long long fordFulkerson(int s, int t){
    int u, v;
 
    long long max_flow = 0; // There is no flow initially	
    // Augment the flow while there is path from source to
    // sink
    while (bfs(s, t)) {
        // Find minimum residual capacity of the edges along
        // the path filled by BFS. Or we can say find the
        // maximum flow through the path found.
        long long path_flow = 1e18;
        for (v = t; v != s; v = parent[v]) {
            u = parent[v];
            path_flow = min(path_flow, rGraph[u][v]);
        }
 
        // update residual capacities of the edges and
        // reverse edges along the path
        for (v = t; v != s; v = parent[v]) {
            u = parent[v];
            rGraph[u][v] -= path_flow;
            rGraph[v][u] += path_flow;
        }
 
        // Add path flow to overall flow
        max_flow += path_flow;
    }
    // Return the overall flow
    return max_flow;
}
 
 
int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);
	int m; cin>>n>>m;
	while (m--){
		long long a,b,c; cin>>a>>b>>c;
		rGraph[a][b] += c;
	}
	cout<<fordFulkerson(1,n)<<"\n";
	return 0;
}

//POLICE CHASE
/*
IDEA : This question requires knowledge of minimum cut. 
As it is an unweighed graph,  so what we can do is we can put a weight of 1 on each road. In that case, our sum of wts to be removed will be equal to the number of roads to be removed.
We can then just resuse the code used in "network speed", to find the minimum number of roads to be removed. 
To find and print the roads which are to be removed we will use our rGraph (the residual graph after running ford-fulkerson algo).
We will find set (call it A) of all nodes reachable from our src Vertex in residual graph. 
Now, We need to find the edges a->b in original graph, such that a is present in A(reachable from src vertex in rGraph), but b isn't present.
Then edge (a-b) is the edge that needs to be removed.  

Code Snippet taken from GeeksForGeeks. So, kudos to them. 
*/

#include<bits/stdc++.h>
using namespace std;
 
// Number of vertices in given graph
int n;
long long graph[501][501];              //Our original graph
long long rGraph[501][501];             //residual graph
int parent[501];                //parent array for ford-fulkerson method
bool visited[501];          //visited array. whether crossing i has been visited or not. 

 
/* Returns true if there is a path from source 's' to sink
  't' in residual graph. Also fills parent[] to store the
  path */
bool bfs(int s, int t){
	memset(visited, false, sizeof(visited));
 
	queue<int> Q; Q.push(s); visited[s]=1;
 
	while(!Q.empty()) {
		int i=Q.front(); Q.pop();
		for(int j = 1; j<=n; ++j) {
			if (rGraph[i][j] && !visited[j]){
				visited[j]=1, parent[j]=i, Q.push(j);
			}	
		}
	}
 
	return visited[n];
}
 
// Returns the maximum flow from s to t in the given graph
long long fordFulkerson(int s, int t){
    int u, v;
 
    long long removalsCnt = 0; // No road to be removed initially. 
    while (bfs(s, t)) {
        // Find minimum residual capacity of the edges along
        // the path filled by BFS. Or we can say a path to harbour. 
        long long path = 1e18;
        for (v = t; v != s; v = parent[v]) {
            u = parent[v];
            path = min(path, rGraph[u][v]);
        }
 
        // update residual capacities of the edges and
        // reverse edges along the path
        for (v = t; v != s; v = parent[v]) {
            u = parent[v];
            rGraph[u][v] -= path;
            rGraph[v][u] += path;
        }
 
        // we need to remove this path. 
        removalsCnt += path;
    }
    // Return the overall removals.
    return removalsCnt;
}

void doBfs(int i){
    if(visited[i]){return;}
    visited[i] = 1;
    for(int j = 1; j<=n; ++j){
        if(rGraph[i][j]){doBfs(j);}
    }
} 
 
int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);
	int m; cin>>n>>m;
	while (m--){
		long long a,b; cin>>a>>b;
		rGraph[a][b] += 1;
        rGraph[b][a] += 1 ;
        graph[a][b] += 1;
        graph[b][a] += 1 ;
	}
    int removed = fordFulkerson(1,n);
	cout<<removed<<"\n";
    doBfs(1);
    for(int i = 1; i<=n; ++i){
        if(!visited[i]){
            for(int j = 1; j<=n; ++j){
                if(visited[j] && graph[i][j]){
                    cout<<i<<" "<<j<<"\n";
                    removed--;
                    if(!removed){return 0;}
                }
            }
        }
    }
    
	return 0;
}