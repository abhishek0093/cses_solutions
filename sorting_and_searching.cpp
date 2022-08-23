//SORTING AND SEARCHING

//FACTORY MACHINES
//It checks whether we can make cnt number of products in mid time or not.
bool ifThis(long long mid, vector<long long> &time, long long cnt){ 
    long long made = 0;
    for(long long i : time){
        made+=(mid/i);
        if(made >= cnt){return true;}
    }
    return false;
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    long long n,cnt;
    cin>>n>>cnt;
    vector<long long> time(n);
    for(auto &i : time){cin>>i;}
    sort(time.begin(), time.end());
    long long r = 1e18;     
    long long l = 0;
    while(r>l){     //Do Binary Search
        long long mid = l+((r-l)/2);
        if(ifThis(mid,time,cnt)){
            r = mid;
        }
        else{
            l = mid+1;
        }
    }
    cout<<l<<"\n";
    return 0;
}

//Maximum Subarray Sum
int main(){
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  int n;        //Use normal Kadane's algorithm.
  cin>>n;
  long long next;
  cin>>next;
  long long best = next;            //global max subarray sum
  long long curr = next;
  for(int i = 1; i<n; ++i){
    cin>>next;
    curr = max(curr+next, next);
    best = max(best, curr);
  }
  cout<<best<<"\n";
  return 0;
}

//APARTMENTS
int main(){
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  int n,m,k;
  cin>>n>>m>>k;
  vector<int> aparts(n); vector<int> demands(m);
  for(int &i : aparts){cin>>i;}
  for(int &i : demands){cin>>i;}
  sort(aparts.begin(), aparts.end());
  sort(demands.begin(), demands.end());
  
  int i = 0; int j = 0;int satisfied = 0;
  while(i < n && j <m){
    if(abs(aparts[i]- demands[j]) <=k){
      ++i; ++j;  ++satisfied;
    }
    else if(demands[j]+k < aparts[i]){
      ++j;
    }
    else{
      ++i;
    }
  }
  cout<<satisfied<<"\n";
  return 0;
}

//FERRIS WHEEL
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int n,x;
    cin>>n>>x;
    vector<int> wts(n);
    for(int &wt : wts){cin>>wt;}
    sort(wts.begin(), wts.end());
    int gandolas = 0;
    int c1 = 0;         //child 1
    int c2 = n-1;       //child 2
    while(c2>c1){
        if(wts[c2]+wts[c1] > x){
            ++gandolas;     //we need to take c2 alone, without sharing
            --c2;
        }
        else{
            ++gandolas;     //we can send c1 and c2 in one gandola
            ++c1;
            --c2;
        }
    }
    if(c1 == c2){++gandolas;}           //we need to send this child alone
    cout<<gandolas << "\n";
    return 0;
}

//CONCERT TICKETS
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int n,m;
    cin>>n>>m;
    multiset<int> ticks;
    vector<int> price(m);
    while(n--){
        int i;
        cin>>i;
        ticks.insert(-1*i);
    }
    for(int &i : price){
        cin>>i;
        i *= -1;
    }
    for(int i : price){
        auto itr = ticks.lower_bound(i);
        if(itr == ticks.end()){
            cout<<-1<<"\n";
        }
        else{
            cout<<-1* (*itr)<<"\n";
            ticks.erase(itr);
        }
    }
    return 0;
}

//TASKS AND DEADLINES

int main(){
    ios_base::sync_with_stdio(false);               //The Idea to get the shortest duration job done first
    cin.tie(nullptr);
    cout.tie(nullptr);
    int n; cin>>n;
    vector<pair<int, int>> arr(n);
    for(auto &i : arr){cin>>i.first>>i.second;}
    sort(arr.begin(), arr.end());
    long long time = 0;
    long long reward = 0;
    for(int i = 0; i<n; ++i){
        time+=arr[i].first;
        reward+=(arr[i].second - time);
    }
    cout<<reward<<"\n";
    return 0;
}

//RESTAURANT CUSTOMERS
#include<iostream>
#include<bits/stdc++.h>
using namespace std;
//Idea : do ++cnt when a customer arrives, and --cnt when a customer leaves
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int n; cin>>n;
    int start; int end;
    set<int> enter;
    set<int> left;
    while(n--){
        int s,e; cin>>s>>e;
        enter.insert(s);
        left.insert(e);
    }
    int maxCustomer = 0;
    int presCustomer = 0;
    auto eItr = enter.begin();
    auto lItr = left.begin();
    while(eItr != enter.end() || lItr != left.end()){
        if(eItr == enter.end() || *eItr > *lItr){
            ++lItr;
            --presCustomer;
        }
        else{
            ++eItr;
            ++presCustomer;
            maxCustomer = max(presCustomer,maxCustomer);
        }

    }
    cout<<maxCustomer<<"\n";
    return 0;
}

//SUM OF TWO VALUES
#include<iostream>
#include<bits/stdc++.h>
using namespace std;

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int n,tar; cin>>n>>tar;
    vector<pair<int,int>> arr;
    for(int i = 0; i<n; ++i){
        int a; cin>>a;
        arr.push_back({a,i});
    }
    sort(arr.begin(),arr.end());
    int s = 0; 
    int e = n-1;
    while(e>s){
        int sum = arr[s].first+arr[e].first;
        if(sum == tar){
            cout<<arr[s].second+1<<" "<<arr[e].second+1<<"\n";
            return 0;
        }
        else if(sum > tar){--e;}
        else{++s;}
    }
    cout<<"IMPOSSIBLE\n";
    return 0;
}

//MOVIE FESTIVAL
//USING ARRAYS
#include<iostream>
#include<bits/stdc++.h>
using namespace std;

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int n; cin>>n;
    vector<pair<int,int>> showTimes(n);
    for(pair<int,int> &show : showTimes){
        cin>>show.second>>show.first;
    }
    sort(showTimes.begin(),showTimes.end());
    int shows = 1;
    int currTime = showTimes[0].first;
    int nextShow = 1;
    while(nextShow < n){
        if(currTime <= showTimes[nextShow].second){
            ++shows;
            currTime = showTimes[nextShow].first;
        }
        ++nextShow;
    }
    cout<<shows<<"\n";
    return 0;
}

//USING SETS
#include<iostream>
#include<bits/stdc++.h>
using namespace std;

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int n; cin>>n;
    set<pair<int,int>> showTimes;
    for(int i = 0; i<n; ++i){
        int start,end; cin>>start>>end;
        showTimes.insert({end,start});
    }
    auto itr = showTimes.begin();
    int shows = 1;
    int currTime = itr->first;
    itr++;
    while(itr != showTimes.end()){
        if(currTime <= itr->second){
            ++shows;
            currTime = itr->first;
        }
        ++itr;
    }
    cout<<shows<<"\n";
    return 0;
}

//STICK LENGTHS
//IDEA - O(N) : Use two array, lCost(leftCost) ,and rCost.lCost[i] stores cost of making all sticks left of index i equal to sticks[i](sticks = sorted). And similarly rCost, but replacing left with right.
//Then Cost of making all sticks equal to sticks[i] = lCost[i]+rCost[i].
//Another approch is that we need to make all stick lengths same as the median of the sticks.  
#include<iostream>
#include<bits/stdc++.h>
using namespace std;

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int n; cin>>n;
    vector<long long> sticks(n);
    for(long long &i : sticks){cin>>i;}
    sort(sticks.begin(),sticks.end());
    vector<long long> lCost(n);  
    vector<long long> rCost(n);
    lCost[0] = 0;
    for(int i = 1; i<n; ++i){
        long long diff = (sticks[i]-sticks[i-1])*i;
        lCost[i] = lCost[i-1]+diff;
    }
    rCost[n-1] = 0;
    for(int i = n-2; i>=0; --i){
        long long diff = (sticks[i+1]-sticks[i])*(n-1-i);
        rCost[i] = rCost[i+1]+diff;
    }
    long long minCost = 1e15;
    for(int i = 0; i<n; ++i){
        minCost = min(minCost,lCost[i]+rCost[i]);
    }
    cout<<minCost<<"\n";
    return 0;
}

//COLLECTING NUMBERS-II
#include<iostream>
#include<bits/stdc++.h>
using namespace std;
//Idea O(n)+O(m)
/*
E.g [4, 2, 1, 5, 3], Now storing it as position array we get [3,2,5,1,4], we see that here are 2 inversions(1-2 (see pos array, pos[1] > pos[2]) & 3-4). so to collect these numbers we will have to make anathor round. like ki 2 pehle aa chuka hai 1 ke, so 1 ko lene ke liye hume peeche jaana hi padega.
So total number of  rounds = 1(always 1 round required)+2(Inversions) = 3
BUT HOW TO DEAL WITH THOSE UPDATES?
OK So Cool, lets say we swap (a,b) - ELEMENTS NOT pos
Now, see carefully when we are swapping these we will only affect inversions of pair {(a,a+1),(a,a-1),(b,b+1),(b,b-1)}, and put them in set as there may be duplicates.
Now we will check that were there any inversions before caused by these 4(or less) pair, and if there were we remove them,and decrease inversion count. 
Now we will swap the elements. After swapping we will again check if our new element positions caused any inversions and if so, add to inversion count. 
And finally print InvCnt+1;
*/

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int n,m; cin>>n>>m;
    vector<int> pos(n+1);       //pos[i] denotes position of i in array
    vector<int> backPos(n+1);   //backPos[i] denotes element at position i
    for(int i = 1; i<=n; ++i){
        int num; cin>>num;
        pos[num] = i;
        backPos[i] = num;
    }
    int invCnt = 0;                 //Inversion Counts in the array (between consecutive elements only)
    for(int i = 2; i<=n; ++i){
        if(pos[i] < pos[i-1]){++invCnt;}
    }
    while(m--){
        int a,b; cin>>a>>b;
        int num1 = backPos[a];
        int num2 = backPos[b];
        set<pair<int,int>> st = {{num1-1,num1},{num1,num1+1},{num2-1,num2},{num2,num2+1}};      //Ensure .second is always greater than .first
        auto itr = st.begin();
        //check whether any of these pair had previously caused inversion,if so ignore them, as they may get removed after updation
        while(itr != st.end()){
            int num1 = itr->first;
            int num2 = itr->second;
            if(pos[num2] < pos[num1]){--invCnt;}
            ++itr;
        }
        swap(backPos[a],backPos[b]);
        pos[num1] = b;
        pos[num2] = a;
        //check if updation caused any new inversions
        itr = st.begin();
        while(itr != st.end()){
            int num1 = itr->first;
            int num2 = itr->second;
            if(pos[num2] < pos[num1]){++invCnt;}
            ++itr;
        }
        cout<<invCnt+1<<"\n";

    }
    return 0;
}

//PLAYLIST
#include<iostream>
#include<bits/stdc++.h>
using namespace std;

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    long long n ; cin>>n;
    vector<long long> arr(n);
    for(long long &i : arr){cin>>i;}
    long long s = 0; long long e = 0;
    long long maxLen = 0;
    map<long long, long long> seen;
    while(e<n && s<n){
        long long element = arr[e];
        if(!seen.count(element)){
            seen[element] = e++;
            maxLen = max(maxLen,e-s);
        }
        else{
            maxLen = max(maxLen,e-s);
            s = max(seen[element]+1,s);     //It is possible that be already ahead of mp[element], because of previous repetion of some other element
            seen[element] = e++;
        } 
    }
    cout<<maxLen<<"\n";
    return 0;
}

//INCREASING SUBSEQUENCE 
//O(N^2) - TLE
#include<iostream>
#include<bits/stdc++.h>
using namespace std;

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int n; cin>>n;
    vector<int> arr(n);
    for(auto &i : arr){cin>>i;}
    vector<int> lis(n); //lis[i] = length of longest subsequence that ends at arr[i].
    int best = 0;
    for(int i = 0; i<n; ++i){
        lis[i] = 1;
        for(int j = 0; j<n; ++j){
            if(arr[j] < arr[i] && lis[j]+1 > lis[i]){
                lis[i] = lis[j]+1;
            }
        }
        best = max(best,lis[i]);
    }
    cout<<best<<"\n";
    return 0;
}

//O(nlogn)
#include<iostream>
#include<bits/stdc++.h>
using namespace std;

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int n; cin>>n;
    vector<int> arr(n);
    for(auto &i : arr){cin>>i;}
    vector<int> lis;
    for(int i = 0; i<n; ++i){
        auto itr = lower_bound(lis.begin(),lis.end(),arr[i]);
        if(itr == lis.end()){lis.push_back(arr[i]);}
        else{
            *itr = arr[i];
        }

    }
    cout<<lis.size()<<"\n";
    return 0;
}


//JOSEPHUS PROBLEM-I
//IDEA : Every time (n/2)persons are removed, and then after each round we get the same problem, with shifted starting point. 
//If n is even, then After one round removal, start will again come back to person where it started(he will again kill the person next to him).
//But for odd n, in next round the last person would start the next round (this person will kill the person next to him)
#include<iostream>
#include<bits/stdc++.h>
using namespace std;

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int n; cin>>n;
    vector<int> seated(n);      //seated[i] - Denotes person sitting at index 'i' position
    for(int i = 0; i<n; ++i){seated[i] = i+1;}
    while(seated.size()>1){
        vector<int> survived;       //List of survivor. survived[i] = person who will be at index 'i' in the next round.
        for(int i = 0; i<seated.size(); ++i){
            if(i%2){
                cout<<seated[i]<<" ";       //Odd index person will be killed (0th will kill 1st, 2nd will kill 3rd .....)
            }
            else{
                survived.push_back(seated[i]);
            }
        }
        if(seated.size()%2){
            int last = survived.back();     //This man has survived, and now this man would be the first one in the seated array for next round. ---survived = [1,3,5,7], and 7 will start next round, so next seated will be like ---[7,1,3,5].
            survived.pop_back();
            seated.clear();
            seated.push_back(last);
            for(int z : survived){
                seated.push_back(z);
            }
        }
        else{swap(seated,survived);}

    }
    cout<<seated[0]<<"\n";
    return 0;
}

//JOSEPHUS PROBLEM - II
/*
IDEA : This is just extension of Josephus Problem 1, with more general k value. This requires direct implementation of ordered_set pbds available with gnu  compiler.
*/

#include<iostream>
#include<bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
using namespace std;
 
using ordered_set = tree<int, null_type,less<int>, rb_tree_tag, tree_order_statistics_node_update>;
 
int main(){
    ordered_set seated;
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int n,k; cin>>n>>k;
    for(int i = 1; i<=n; ++i){seated.insert(i);}
    int start = 0;  //The person at start will have sword, and with it will kill (k+1)th child
    while(seated.size()>0){
        int posOfchildToBeKilled = (start+k)%seated.size();
        auto childToBeKilled = seated.find_by_order(posOfchildToBeKilled); 
        cout<<*(childToBeKilled)<<" ";
        seated.erase(childToBeKilled);
        start = posOfchildToBeKilled;
    }
    cout<<"\n";
    return 0;
}


//MAXIMUM SUM SUBARRAY-II
/*
IDEA : This question is basically advanced version of maximum subarray sum-I question. 
We can only consider subarrays of lens (a to b). So , would not it be a nice idea to store for every possible start of a subarray , the sums that can be considered 

.......................
*/

#include<bits/stdc++.h>
using namespace std;
 
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    int n,a,b; cin>>n>>a>>b;
    vector<long long> arr(n);
    vector<long long> score(n+1);
    set<pair<long long,int>> valids;

    for(long long &i : arr){cin>>i;}
    for(int i = 1; i<=n; ++i){score[i] = score[i-1]+arr[i-1];}
    long long best = -1e18;
    int subArrStart = 1;
    int validStart = a;
    int validEnd = b;
    for(int i = validStart; i<=validEnd; ++i){valids.insert({score[i],i});}
    best = max(best,valids.rbegin()->first);
    ++subArrStart;   validEnd++; validStart++;
    while(validEnd <= n){
        valids.erase({score[validStart-1],validStart-1});
        valids.insert({score[validEnd],validEnd});
        best = max(best, (valids.rbegin()->first-score[subArrStart-1]));
        ++subArrStart; ++validEnd; ++validStart;
    }

    while(validStart < validEnd){
        valids.erase({score[validStart-1],validStart-1});
        if (valids.size()) best = max(best, (valids.rbegin()->first-score[subArrStart-1]));
        ++subArrStart; ++validStart;
    }
    cout<<best<<"\n";
    return 0;
}

//ROOM ALLOCATION 
#include<iostream>
#include<bits/stdc++.h>
using namespace std;

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int n; cin>>n; 
    multimap<pair<int,int>,int> mp;          //Multimap as 2 customers may have same {arr,dep}.first.first = arrival time ; .first.second = departure time; .second = person No.(0-indexed)
    for(int i = 0; i<n; ++i){
        int arr,dep; cin>>arr>>dep;
        mp.insert({{arr,dep},i});
    }
    vector<int> roomAlloted(n);     //roomAlloted[i] = roomAlloted to ith person
    int nextRoomToBeAlloted = 1;
    priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> pq;    //MinHeap storing occupied room ; .first = departure time; .second = room number
    auto itr = mp.begin();
    while(itr != mp.end()){
        int arrival = itr->first.first;
        int dep = itr->first.second;
        int index = itr->second;
        if(pq.size() && pq.top().first < arrival){      //We have atleast one vacant room, that was vacated earlier than the arrival of current customer, so allot that room
            roomAlloted[index] = pq.top().second;
            pq.push({dep,pq.top().second});
            pq.pop();
        }
        else{           //We don't have any utilised-vacant room, so allot a fresh room to the customer
            roomAlloted[index] = nextRoomToBeAlloted;
            pq.push({dep,nextRoomToBeAlloted++});
        }
        ++itr;
    }
    cout<<--nextRoomToBeAlloted<<"\n";
    for(int room : roomAlloted){
        cout<<room<<" ";
    }
    cout<<"\n";
    return 0;
}

//SUM OF THREE VALUES
#include<iostream>
#include<bits/stdc++.h>
using namespace std;

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int n,x; cin>>n>>x;
    vector<pair<int,int>> nums;     //.first stores number, and .second stores position at which this number was provided as input
    for(int i = 1; i<=n; ++i){
        int numb; cin>>numb;
        nums.push_back({numb,i});
    }
    sort(nums.begin(),nums.end());
    if(nums.size()<3){cout<<"IMPOSSIBLE\n"; return 0;}
    for(int i = 0; i<n-2; ++i){
        long long sumToBeMade = x-nums[i].first;        //we always take nums[i].first as 1 of the possible 3 numbers
        int s = i+1;
        int e = n-1;
        while(e>s){
            long long currSum = nums[s].first+nums[e].first;
            if(currSum == sumToBeMade){
                cout<<nums[i].second<<" "<<nums[s].second<<" "<<nums[e].second<<"\n";
                return 0;
            }
            else if(currSum < sumToBeMade){++s;}
            else{--e;}
        }
    }
    cout<<"IMPOSSIBLE\n";
    return 0;
}

//SUM OF FOUR VALUES
#include<iostream>
#include<bits/stdc++.h>
using namespace std;

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int n,x; cin>>n>>x;
    vector<pair<int,int>> nums;     //.first stores number, and .second stores position at which this number was provided as input
    for(int i = 1; i<=n; ++i){
        int numb; cin>>numb;
        nums.push_back({numb,i});
    }
    sort(nums.begin(),nums.end());
    if(nums.size()<4){cout<<"IMPOSSIBLE\n"; return 0;}
    for(int k = 0; k<n-3; ++k){
        long long threeSumToBeMade = x- nums[k].first;
        for(int i = k+1; i<n-2; ++i){
            long long sumToBeMade = threeSumToBeMade-nums[i].first;
            int s = i+1;
            int e = n-1;
            while(e>s){
                long long currSum = nums[s].first+nums[e].first;
                if(currSum == sumToBeMade){
                    cout<<nums[k].second<<" "<<nums[i].second<<" "<<nums[s].second<<" "<<nums[e].second<<"\n";
                    return 0;
                }
                else if(currSum < sumToBeMade){++s;}
                else{--e;}
            }
        }
    }
    cout<<"IMPOSSIBLE\n";
    return 0;
}

//NESTED RANGES CHECK
#include<iostream>
#include<bits/stdc++.h>
using namespace std;

bool cmp(pair<pair<int,int>,int> a, pair<pair<int,int>,int> b){
    //If both interval end at same time, put that interval first which started late 
    //(This way we can be sure that, lower interval(e.g [1,6]) would be able to contain late starter(e.g [3,6]))
    return (a.first.second == b.first.second) ? (a.first.first > b.first.first) : (a.first.second < b.first.second);
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int n; cin>>n;
    vector<pair<pair<int,int>,int>> vec;        //.first.first = start; .first.second = end; .second = index in original input
    vector<bool> contains(n);
    vector<bool> contained(n);      //if contained by some other interval

    for(int i = 0; i<n; ++i){
        int s,e; cin>>s>>e;
        vec.push_back({{s,e},i});
    }
    
    sort(vec.begin(), vec.end(), cmp);      //Sorting on the basis of end time

    //E.g after sorting - [(2,4),(3,6),(1,6),(4,8)]

    //LOGIC FOR CONTAINS : Now for any interval, if it contains any interval that must lie above it.
    //So, one way  could be to loop through all elements, but again that would be O(n^2). 
    //So, we maintain a maxLeft(maxStart) seen so far, and update as we move. If our current interval start is greater than maxLeft, we could be sure that our interval contains interval [maxLeft, end time of maxLeft]. 
    int maxLeft = INT_MIN;
    for(int i = 0; i<n; ++i){
        if(vec[i].first.first <= maxLeft){
            contains[vec[i].second] = 1;  
        }
        else{
            maxLeft = vec[i].first.first;
        }
    }



    //LOGIC FOR CONTAINED : Now for any interval, if it is contained by any interval that must lie below it(as end is smaller only at tops).
    //So, one way  could be to loop through all elements, but again that would be O(n^2). 
    //So, we maintain a minLeft(minStart) seen so far, and update as we move. If our current interval start later than our minLeft, we could be sure that our interval is contained by interval [minLeft, end time of minLeft(which will always be greater than current interval end time)]. 
    int minLeft = INT_MAX;
    for(int i = n-1; i>=0; --i){
        if(vec[i].first.first >= minLeft){
            contained[vec[i].second] = 1;  
        }
        else{
            minLeft = vec[i].first.first;
        }
    }
    for(int i : contains){
        cout<<i<<" ";
    }
    cout<<"\n"; 
    for(int i : contained){
        cout<<i<<" ";
    }
    cout<<"\n";
    return 0;
}

//SUBARRAY DIVISIBILITY
#include<iostream>
#include<bits/stdc++.h>
using namespace std;

//IDEA (O(n)) {https://www.geeksforgeeks.org/count-sub-arrays-sum-divisible-k/} : Any subarray sum can be written as (n*q+rem). 

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int n; cin>>n;
    vector<long long> score(n+1);       //score[i] = ((cumlativeSum%n)+n)%n considering only first i inputs
    score[0] = 0;
    for(int i = 1; i<=n; ++i){
        long long t; cin>>t;
        score[i] = score[i-1]+t;
        score[i]%=n;
        (score[i] += n)%=n;         //As orignial modulo can be negative, so make it positive in range [0,n-1]
    }
    long long cnt = 0;
    map<long long,long long> freq;      //To store frequency of each remainder
    freq[0] = 1;                    
    for(int i = 1; i<=n; ++i){
        long long rem1 = score[i];      //remainder considering length i inputs
        cnt+=freq[rem1]++;          //If we have seen this remainder before, so count all those subarrays.
    }
    cout<<cnt<<"\n";
    return 0;
}

//SLIDING MEDIAN
#include<iostream>
#include<bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
using namespace std;

//Using ordered (pbds) Multiset. used less_equal inplace of less(to get multiset from set). ]
//But lower_bound will start behaving as upper bound, but as we don't need lower_bound, we will continue to use it. 

using ordered_set = tree<int, null_type,less_equal<int>, rb_tree_tag, tree_order_statistics_node_update>;

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int n,k; cin>>n>>k;
    ordered_set oSet;       //It will contain k elements, i.e current window elements in sorted order 
    vector<int> arr(n);
    for(int &i : arr){cin>>i;}
    auto s = arr.begin();
    auto e = arr.begin();
    while(oSet.size()!=k){
        oSet.insert(*e);
        ++e;
    }

    //As we need median, which will lie in middle of oSet. 
    //But, also for even case, we want left one element out of two, so we take effective size of set for median calculation to be (k-1)

    cout<<*oSet.find_by_order((k-1)/2)<<" ";
    while(e!=arr.end()){
        int smalls = oSet.order_of_key(*s++);     //No. of elements strictly smaller than *s element
        //Now, as smalls elements are smaller, so *s element must have 'small' index in our oSet (0 based indexing).

        oSet.erase(oSet.find_by_order(smalls));       
        oSet.insert(*e++);      //Insert next element
        cout<<*oSet.find_by_order((k-1)/2)<<" ";
    }
    cout<<"\n";
    return 0;
}

//Array Division
/*
This involves a monotonic predicate and hence can be solved through binary search. 
A beautiful explaination and intution has been provided here for the problem - https://www.youtube.com/watch?v=nai96X4ZsJg&t=700s
*/

#include<bits/stdc++.h>
using namespace std;

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int n,k; cin>>n>>k;
    vector<long long> arr(n);
    long long low = 0;          //lowest max sum . We can be sure that it will be at Least be equal to the max element of the array. 
    for(long long &i : arr){
        cin>>i; 
        low = max(low, i);
    }
    long long high = 1e18;      
    while(low <= high){
        long long mid = (high-low)/2+low;           //We will break arr into subarrays such that in no subarray sum be greater than k. If we are able to achieve this in less than or equal to k partions then we will shift our high otherwise low.
        bool possible = false;
        long long sum = 0;
        int partitions = 1; 
        for(int i = 0; i<n; ++i){
            if(sum+arr[i] <= mid){sum+=arr[i];}
            else{
                partitions++;
                sum = arr[i];
            }
        }
        if(partitions > k){
            low = mid+1;
        }
        else{
            high = mid-1;
        }
    }
    cout<<low<<"\n";

    return 0;
}

//MOVIE FESTIVAL - II
#include<iostream>
#include<bits/stdc++.h>
using namespace std;

bool cmp(pair<int,int>a, pair<int,int>b){
    return a.second < b.second;
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int n,k; cin>>n>>k;
    vector<pair<int,int>> movieTimes(n);
    for(pair<int,int> &p : movieTimes){cin>>p.first>>p.second;}
    
    //Uncomment this Sort line
    //sort(movieTimes.begin(),movieTimes.end(), cmp);     //Sort on the basis of show ending time
    
    multiset<int> busyMembers;      //Many Members may get freed at the same time, so use multi set instead of regular set. 
    busyMembers.insert(-1*movieTimes[0].second);        //First member will always watch first show(sorted list). 
    int movieCounts = 1;

    for(int i = 1; i<n; ++i){
        //We Want to preserve very early freed ones, as they may be utilised gain to watch shows that start early, but ended very late and will be encountered ahead in movieTimes
        auto memberJustFreed = busyMembers.lower_bound(-1*movieTimes[i].first);     //Member freed time, who has just before freed.
        if(memberJustFreed == busyMembers.end() && busyMembers.size() < k){     //We have extra members doing nothing, put one to watch this show
            ++movieCounts;
            busyMembers.insert(-1*movieTimes[i].second);
        }
        else if(memberJustFreed != busyMembers.end()){
            ++movieCounts;
            busyMembers.erase(memberJustFreed);
            busyMembers.insert(-1*movieTimes[i].second);
        }
    }
    cout<<movieCounts<<"\n";
    return 0;
}

//READING BOOKS
/*
IDEA : At any situation we will atleast require sum of all reading times(netReadTime) to read all the books. 
We will start by making kotivalo to read the book that requires maximum time(here 8), and till then justiina will read the just lower reading time book( = 3hrs). 
Now by the time kotivalo finished his book, justiina would have had definately finished her book (we will always make justinna to read just lower reading time book, than kotivalo who reads all books in desending order).
Now, kotivalo will start reading book that justiina has just finished (= 3hrs), and justiina would read book just below it in reading time (= 2hrs), and so on this will continue (if we would had more elements in our example).
Now, as soon as kotivalo will want to read lowest reading time book, justiina would want to read maximum time book. They both can do this in harmony(without waiting for other), if the time required to read the most time consuming book is less than timerequired by all other books,
else justiian would have to wait for kotivalo to finish first book, while she herself would have read alll the remaining books. In this case the netReadTime would be double of time required by most heavy book (as in our example).
*/

#include<bits/stdc++.h>
using namespace std;

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int n ; cin>>n;
    long long netReadTime = 0;
    vector<int> readingTimes(n);
    for(int &readingTime : readingTimes){cin>>readingTime; netReadTime+=readingTime;}
    sort(readingTimes.begin(), readingTimes.end());
    cout<<(netReadTime-readingTimes.back() < readingTimes.back() ? 2*(readingTimes.back()) : netReadTime)<<"\n";
    return 0;
}

//NESTED RANGES COUNT
//NESTED RANGES CHECK
#include<iostream>
#include<bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
using namespace std;
 


using ordered_set = tree<pair<int,int>, null_type,less<pair<int,int>>, rb_tree_tag, tree_order_statistics_node_update>;


bool cmp(pair<pair<int,int>,int> a, pair<pair<int,int>,int> b){
    //If both interval end at same time, put that interval first which started late 
    //(This way we can be sure that, lower interval(e.g [1,6]) would be able to contain late starter(e.g [3,6]))
    return (a.first.second == b.first.second) ? (a.first.first > b.first.first) : (a.first.second < b.first.second);
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int n; cin>>n;
    vector<pair<pair<int,int>,int>> vec;        //.first.first = start; .first.second = end; .second = index in original input
    vector<int> contains(n);
    vector<int> contained(n);      //if contained by some other interval

    for(int i = 0; i<n; ++i){
        int s,e; cin>>s>>e;
        vec.push_back({{s,e},i});
    }
    
    sort(vec.begin(), vec.end(), cmp);      //Sorting on the basis of end time

    //E.g after sorting - [(2,4),(3,6),(1,6),(4,8)]

    //LOGIC FOR CONTAINS : Now for any interval, if it contains any interval that must lie above it.
    //So, one way  could be to loop through all elements, but again that would be O(n^2). 
    //So, as we will move from top to bottom, we will also maintain start time of intervals lying above to it. As we are sure that all above intervals will have end time lower than current current interval end time, so ending isn't a problem. 
    //We need a kind of data structure to tell us how many intervals lie above, which have start time greater than or equal to current interval's start time. And ordered set would be a perfect fit, given its index finding capability in the set.  
    //We can have two or more intervals that start at the same time, and set can't keep multiple entries. So, to make them unique, we will also push negative of indexes (why negative? Hint: Notice we are doing subtraction from set.size() to get all late/equal starts) of that interval into the set.
    ordered_set startTimes; 
    for(int i = 0; i<n; ++i){
        int currentStartTime = vec[i].first.first;
        int intervalsThatStartLateOrAtSameTime = startTimes.size()-startTimes.order_of_key({currentStartTime,-1*i});
        contains[vec[i].second] = intervalsThatStartLateOrAtSameTime;
        startTimes.insert({currentStartTime,-1*i});
    }

    //LOGIC FOR CONTAINED : Now for any interval, if it is contained by any interval that must lie below it(as end is smaller only at tops).
    //So, one way  could be to loop through all elements, but again that would be O(n^2). 
    //So, as we will move from bottom to top, we will also maintain start time of intervals lying below to it. As we are sure that all below intervals will have end time greater than current interval end time, so ending isn't a problem for checking contained. 
    //We need a kind of data structure to tell us how many intervals lie above, which have start time less than or equal to current interval's start time. And ordered set would be a perfect fit, given its index finding capability in the set.  
    //We can have two or more intervals that start at the same time, and set can't keep multiple entries. So, to make them unique, we will also push indexes of that interval into the set.
    //But think again for duplicate case, and pushing index as it is. E.g consider {{6,5},{6,8}}.
    //Let's assume we pushed interval index as it is. Then, while checking interval {6,5}, our ordered set would contain ({6,1}), and then we want to find out how many keys are smaller than {6,0}, So {6,1} wouldn't be counted, and we will miss one contained by interval for present case. How, to tackle this?
    //Yes, you get it right. push negative of index. 
    ordered_set startTimesAgain;
    for(int i = n-1; i>=0; --i){
        int currentStartTime = vec[i].first.first;
        int intervalsThatStartBeforeOrAtSameTime = startTimesAgain.order_of_key({currentStartTime,-1*i});
        contained[vec[i].second] = intervalsThatStartBeforeOrAtSameTime;
        startTimesAgain.insert({currentStartTime,-1*i});
    }
    for(int i : contains){
        cout<<i<<" ";
    }
    cout<<"\n"; 
    for(int i : contained){
        cout<<i<<" ";
    }
    cout<<"\n";
    return 0;
}

//TRAFFIC LIGHTS
/*
IDEA : The fact that we have to print longest non-light path after each insertion makes this question interesting. 
If we notice that each traffic light insertion(currLightPos) would disrupt the length that existed between the light next to it(nextLightPos) and the light previous to it(prevLightPos).
So the pathLen of non-traffic-light of length (nextLightPos-prevLightPos) doesn't exists anymore. That pathLen has now got divided into two smaller pathLens - (currLightPos-prevLightPos) and (nextLightPos-currLightPos). 
So if we can store all the lights position in some fashion such that we can query position of traffic light just after and before of new light insertion point, we can effectively calculate pathUpdates.
We will also need a multiset(same len path can exist between many lights), to store all valid non-traffic lights path lengths.
We will start by assuming that already traffic lights are present at pos 0 and x. 
*/


#include<bits/stdc++.h>
using namespace std;

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int n,x; cin>>x>>n;
    set<int> lightsPos;     //Positions of all traffic lights inserted so far.
    multiset<int> passagesLen;  //Lengths of all non-traffic lights paths.
    lightsPos.insert(0); lightsPos.insert(x);
    passagesLen.insert(x);
    while(n--){
        int currLightPos; cin>>currLightPos;            //Curr light position 
        int nextLightPos = *lightsPos.upper_bound(currLightPos);        //LightPos just after currLight
        int prevLightPos = *prev(lightsPos.lower_bound(currLightPos));  //LightPos just before currLight
        passagesLen.erase(passagesLen.find(nextLightPos-prevLightPos));     //PathLen between nextLightPos and prevLightPos doesn't exist anymore.

        //Update pathLens
        lightsPos.insert(currLightPos);
        passagesLen.insert(nextLightPos-currLightPos);
        passagesLen.insert(currLightPos-prevLightPos);
        cout<<*passagesLen.rbegin()<<" ";           //Longest path will be at last of multiset.
    }
    cout<<"\n";
    return 0;
}

//SUBARRAY DISTINCT VALUES
/*
IDEA : As you might have guessed, this question is somewhat mixture of sliding window and 2 pointers approach. 
We will start our window from the first element and will continue to expand until our window contains atmost k distinct elements. 
But as soon as we find an element, which will cause our distinct elements to become greater than k, we will have to shrink our window to accomodate this new element. 
So, it is clear that we need some sort of mechanism to tell us number of distinct elements in our window. Set is obvious to come into mind. But Wait, will a Set serve the purpose here? 
Think and dry run for the case (n = 5, k = 3, arr = [3,1,2,3,5], how will you deal with second 3 during addition/checking of last element 5?).
Hope you get that we can't use set here. So what else we can use ? What about using a map? 
But how a map will counter the problem faced during use of set? what about storing the frequency also, and at the time of shrinking decrease the frequency of element from where window has shifted.
And as soon as frequency of an element becomes 0, it implies that element is now nowhere present in our window. So we reduced distinct elements in our window by 1, and now we can add our new element. Hooray!! 
*/

#include<bits/stdc++.h>
using namespace std;
 
int main(){
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  int n,k; cin>>n>>k;
  vector<long long> arr(n);
  for(auto &i : arr){cin>>i;}
  int start = 0; int end = 1;           //Start denotes start of our Window. NOTE : end points to element that needs to be inspected, i.e end is not part of our window. Our window extends from (arr[start], arr[start+1],----,arr[end-1]).
  long long cnt = 1;                //arr[start] is one subarray. 
  map<long long, long long> mp;
  mp[arr[start]]++;
  while(end < n){
        if(mp.count(arr[end]) || mp.size() < k){        //If adding this element doesn't cause distinct elements(mp.size()) to beyond k, so just increase frequency of this element.
            mp[arr[end]]++;
            cnt+=(++end-start);                     //All the subarrays ending at (end). i.e [start to end],[start+1 to end], [start+2,end]-------[end to end]. SO total of (e-s+1) subarrays. 
        }
        else{                   //Now we need to shrink our window, and delete some element. Whichsoever will get first fully eliminated(its frequency in map becomes zero), we will remove that element. 
            while(mp.size() >= k){
                mp[arr[start]]--;
                if(mp[arr[start]] == 0){
                    mp.erase(arr[start]);
                }
                start++;
            }
            mp[arr[end]]++;         //Add current element.
            cnt+=(++end-start);
        }
  }
  cout<<cnt<<"\n";
  return 0;
}

//SLIDING COST
/*
IDEA : This question extends the approach used in stick lengths in an interesting way. we know that in any window we have to make all elements equal to the median, but how to handle the shifting of window?
one easy way would be to for every window, we store its elements in sorted order(so that median could be found in constant time), and then to find the cost iterate over all the elements. But as you might have guessed it will cause O(n2) complexity. We need something better. 
If we see carefully each time we are shifting we are only deleting one element(start of window, s), and adding one element (pointed by e). So, we can use ordered set to store the window elements, so that we can find median, erase and add elements effectively. 
But how to manage the changing cost?
If we notice carefully in ordered set, all the elements lying left of the median (including) will be smaller/equal to the median, while all elements lying right would be greater (lets call that median element acts as a partition. Elements lying left and including median form left partition while those strictly greater than median form right partition). 
Now, if we be knowing sum and count of all elements lying on each partition, we can easily calculate the cost of making entire set equal to "median" value as - cost = ((count of elements in left partion*median)-(left partition sum)) + ((right partition sum)-(count of elements in right partion*median)).
So, we effectively need left partion sum and right partition sum to calculate the cost. As our window size is fixed, so our count of left and right elements is also fixed, and we need to maintain it as we shift our window.
Because it may happen during window shifting that element get erased from right/left partition, but new element was inserted in left/right partition. In this case we would need to shift the elements between the partitions to (and thus adjust left/right sum) to maintain the required sizes of left and right partitions.
*/


#include<iostream>
#include<bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
using namespace std;
typedef pair<int,int> pii;
using ordered_set = tree<pii, null_type,less<pii>, rb_tree_tag, tree_order_statistics_node_update>;
 
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);  cout.tie(nullptr);
    int n,k; cin>>n>>k;
    ordered_set oSet;       //It will contain k elements, i.e current window elements in sorted order. 
    vector<int> arr(n);
    vector<int> firstKElements;     //Initial k elements of the array in sorted order, so that we can calculate lSum and rSum. 
    long long medianIndex = (k-1)/2;
    long long firstKEleSum = 0;
    long long lSum = 0;         //leftSum. It will be the sum of elements smaller than or equal to median element of our current window. 
    long long rSum = 0;             //rightSum. It will be the sum of elements greater than our median . 

    for(int &i : arr){cin>>i;}
    for(int i = 0; i<k; ++i){ firstKElements.push_back(arr[i]);}
    sort(firstKElements.begin(), firstKElements.end());         //
    //calculate lSum and rSum. 
    for(int i = 0; i<k; ++i){
        if(i<=medianIndex){lSum+=firstKElements[i];}
        firstKEleSum+=firstKElements[i];
    }
    rSum = firstKEleSum-lSum;

    for(int i = 0; i<k; ++i){oSet.insert({arr[i],i});}      //Insert first k elements in ordered set. 
    long long median = oSet.find_by_order(medianIndex)->first;
    cout<<((median*(medianIndex+1))-lSum)+(rSum-(median*((long long)oSet.size()-medianIndex-1)))<<" ";
    
    auto s = arr.begin();           //Starting element of our current window. It will be the element that will be removed as we will shift our window towards right.
    auto e = arr.begin()+k;             //Pointing to element that will be added next to our window/oSet.
    int eIndex = k;                 //Index of e and s respectively . Needed as to make same numbers unique in our oSet. We will insert indexes also . 
    int sIndex = 0;
    while(e!=arr.end()){
        int elementToBeAdded = *e;
        int elementToBeRem = *s;
        long long median = oSet.find_by_order(medianIndex)->first;          //median of our current window. 
        elementToBeAdded <= median ? lSum+=elementToBeAdded : rSum+=elementToBeAdded;           //If element to be added is smaller than/equal to median, add it to lSum otherwise add it to rightSum. 
        elementToBeRem <= median ? lSum-=elementToBeRem : rSum-=elementToBeRem;
        oSet.insert({elementToBeAdded,eIndex});
        oSet.erase({elementToBeRem, sIndex});
        if((elementToBeRem <= median && elementToBeAdded <= median) || (elementToBeRem > median && elementToBeAdded > median)){         //If both removal and addition happen on same side of median (either left or right ), our window partition would not be affected , and we can directly go ahead. 
            median = oSet.find_by_order(medianIndex)->first;            //new Median
            cout<<((median*(medianIndex+1))-lSum)+(rSum-(median*((long long)oSet.size()-medianIndex-1)))<<" ";
        }
        else if(elementToBeRem <= median && elementToBeAdded > median){         //If addition happens on right side and deletion from left side, then effectively right side size will get increased by 1 while left side size will get decreased by 1. So, we will need to shift the element at medianIndex (as it will be the smallest in right partition) to left partition, and thus effectively need to adjust lSum and rSum.
            long long elementToBeShifted = oSet.find_by_order(medianIndex)->first;
            lSum+=elementToBeShifted;
            rSum-=elementToBeShifted;
            long long median = oSet.find_by_order(medianIndex)->first;
            cout<<((median*(medianIndex+1))-lSum)+(rSum-(median*((long long)oSet.size()-medianIndex-1)))<<" ";
        }
        else{                       //If addition happens on left side and deletion from right side, then effectively leftt side size will get increased by 1 while right side size will get decreased by 1. So, we will need to shift the element at (medianIndex+1) (as it will be the highest in leftt partition) to right partition, and thus effectively need to adjust lSum and rSum.
            long long elementToBeShifted = oSet.find_by_order(medianIndex+1)->first;
            lSum-=elementToBeShifted;
            rSum+=elementToBeShifted;
            long long median = oSet.find_by_order(medianIndex)->first;          //new Median of window.
            cout<<((median*(medianIndex+1))-lSum)+(rSum-(median*((long long)oSet.size()-medianIndex-1)))<<" ";
        }
        ++e; ++s;
        ++eIndex; ++sIndex;
    }
    cout<<"\n";
    return 0;
}