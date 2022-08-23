//Dynamic Programming
//Memoization Approach
#include<iostream>
#include<bits/stdc++.h>
using namespace std;
 
int minSteps(int i , vector<int> &fromHere){
    if(fromHere[i] != -1){return fromHere[i];}
    if(i <= 9){return  1;}
    string num = to_string(i);
    int startHere = INT_MAX;
    for(char c : num){
        if(c == '0'){continue;}
        startHere = min({startHere, 1+minSteps(i-(c-'0'), fromHere)});
    }
    return fromHere[i] = startHere;
}
 
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int n;
    cin>>n;
    //fromHere[i] represents minimum steps needed to transform  digit i to 0;
    vector<int> fromHere(n+1, -1);
    fromHere[0]  =  0;
    cout<<minSteps(n, fromHere)<<"\n";
    return 0;
}

//Iterative Approach
#include<iostream>
#include<bits/stdc++.h>
using namespace std;

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int n;
    cin>>n;
    //fromHere[i] represents minimum steps needed to transform  digit i to 0;
    vector<int> fromHere(n+1, 1000001);
    fromHere[0]  =  0;
    for(int i = 1; i<=n; ++i){
        string num = to_string(i);
        for(char c : num){
            if(c == '0'){continue;}
            fromHere[i] = min(fromHere[i], 1+fromHere[i-(c-'0')]);
        }
    }
    cout<<fromHere[n]<<"\n";
    return 0;
}

//MONEY SUMS
#include<iostream>
#include<bits/stdc++.h>
using namespace std;

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int n; cin>>n; 
    vector<int> coins(n);
    int maxi  = 0;
    int cnt = 0;
    for(int &i : coins){
        cin>>i;
        if(i > maxi){maxi = i;}
    }
    //isPossible[i][j] denotes possiblity of making sum of i using only first j coins of coins array
    vector<vector<bool>> isPossible(maxi*n+2, vector<bool>(n+1, 1));
    for(int i = 1; i<=maxi*n; ++i){
        for(int j = 0; j<=n; ++j){
            isPossible[i][j] = 0;
            if(j == 0){continue;}
            if(i >= coins[j-1]){
                isPossible[i][j] = (isPossible[i][j] || isPossible[i-coins[j-1]][j-1]);
            }
            isPossible[i][j] = (isPossible[i][j] || isPossible[i][j-1]);
        }
        if(isPossible[i][n]){
            ++cnt;
        }        
    }    
    cout<<cnt<<"\n";
    for(int i = 1; i<=maxi*n; ++i){
        if(isPossible[i][n]){
            cout<<i<<" ";
        }
    }
    cout<<"\n";
    return 0;
}

//GRID PATHS
//MEMOIZATION --> CONSUMES A LOT OF SPACE, SO GIVES RUNTIME ERROR
#include<iostream>
#include<bits/stdc++.h>
using namespace std;
int MOD = 1e9+7;

int countPaths(int i, int j, vector<vector<char>> grid, vector<vector<int>> &visited){
    if(i >= grid.size() || i< 0 || j >= grid.size() || j<0){return 0;}
    if(visited[i][j] != -1){return visited[i][j];}
    visited[i][j] = (((countPaths(i,j+1,grid,visited)%MOD)+(countPaths(i+1,j,grid,visited)%MOD))%MOD);
    return visited[i][j]%MOD;
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int n;
    cin>>n;
    vector<vector<char>> grid(n, vector<char>(n, '.'));
    //visited[i][j] = cnt of paths from (i,j) cell to bottom-right corner
    vector<vector<int>> visited(n, vector<int>(n, -1));
    visited[n-1][n-1] = 1;
    for(int i = 0; i<n; ++i){
        for(int j = 0; j<n; ++j){
            char c;
            cin>>c;
            if(c == '*'){grid[i][j] = c; visited[i][j] = 0;}
        }
    }
    cout<<countPaths(0,0,grid, visited)<<"\n";

    return 0;
}

//ITERATIVE APPROACH
#include<iostream>
#include<bits/stdc++.h>
using namespace std;
int MOD = 1e9+7;

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int n;
    cin>>n;
    vector<vector<char>> grid(n, vector<char>(n, '.'));
    //visited[i][j] = cnt of paths from (i,j) cell to bottom-right corner
    vector<vector<int>> visited(n, vector<int>(n, 0));
    visited[n-1][n-1] = 1;
    for(int i = 0; i<n; ++i){
        for(int j = 0; j<n; ++j){
            char c;
            cin>>c;
            if(c == '*'){grid[i][j] = c; visited[i][j] = -1;}
        }
    }

    for(int i = n-1; i>=0; --i){
        for(int j = n-1; j>=0; --j){
            if(grid[i][j] == '*'){continue;}
            if(i - 1 >=0  && grid[i-1][j] != '*'){
                (visited[i-1][j] +=visited[i][j])%=MOD;
            }
            if(j - 1 >=0  && grid[i][j-1] != '*'){
                (visited[i][j-1] +=visited[i][j])%=MOD;
            }
        }
    }
    cout<<(visited[0][0] == -1 ? 0 : visited[0][0])<<"\n";

    return 0;
}

//BOOK SHOP
#include<iostream>
#include<bits/stdc++.h>
using namespace std;

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int n,k;
    cin>>n>>k;
    vector<int> price(n);
    vector<int> page(n);
    for(int & i : price){cin>>i;}
    for(int & i : page){cin>>i;}
    //dp[i][j] refers to max pages we can buy if we had first i books, and i total money.
    vector<vector<int>> dp(n+1, vector<int>(k+1,0));
    for(int i = 1; i<=n; ++i){
        for(int j = 1; j<=k; ++j){
            if(j>=price[i-1]){
                dp[i][j] = page[i-1]+dp[i-1][j-price[i-1]];
            }
            dp[i][j] = max(dp[i][j], dp[i-1][j]);
        }
    }
    cout<<dp[n][k]<<"\n";
    return 0;
}

//EDIT DISTANCE
#include<iostream>
#include<bits/stdc++.h>
using namespace std;

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    string s1,s2;
    cin>>s1>>s2;
    int n = s1.size();
    int m = s2.size();
    //dp[i][j] represents minimum steps to make s1 == s2, considering i len of s1 and j len of s2
    vector<vector<int>> dp(n+1, vector<int>(m+1, 5000001));
    for(int i = 0; i<=n; ++i){
        for(int j = 0; j<=m; ++j){
            if(!i || !j){dp[i][j] = (i == 0 ? j : i);}
            else if(s1[i-1] == s2[j-1]){
                dp[i][j] = dp[i-1][j-1];
            }
            else{
                dp[i][j] = 1+min({dp[i-1][j] , dp[i-1][j-1], dp[i][j-1]});
            }
        }
    }
    cout<<dp[n][m]<<"\n";
    return 0;
}

//ARRAY DESCRIPTION
#include<iostream>
#include<bits/stdc++.h>
using namespace std;
 
int MOD = 1e9+7; 
 
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int n,m; cin>>n>>m;
    vector<int> arr(n);
    for(int &i : arr){cin>>i;}
    //dp[i][j] = required ans if we consider array upto index i and last element as j
    vector<vector<int>> dp(n,vector<int>(m+1,0));
    if(arr[0]){dp[0][arr[0]] = 1;}
    else{
        for(int i = 1; i<=m; ++i){dp[0][i] = 1;}        //We can fill any number in range [1,m]
    }
    for(int i = 1; i<n; ++i){
        int e = arr[i];     //current element
        if(e != 0){     //Current element being 'e' implies that previous its previous element must have been either of {e-1,e,e+1}
            for(int k : {e-1,e,e+1}){
                if(k>=1 && k<=m){(dp[i][e] += dp[i-1][k])%= MOD;}
            }
        }
        else{           //current element i 0, so we can fill any of the number in range[1,m] restricted to the element at previous index of the array
            for(int j = 1; j<=m; ++j){
                for(int k : {j-1,j,j+1}){       //If element at 'i' index supposed be 'j', then at index 'i-1' it must have been either of {j-1,j,j+1}.
                    if(k>=1 && k<=m){(dp[i][j] += dp[i-1][k])%= MOD;}
                }
            }
        }
    }
    if(arr[n-1] != 0){cout<<dp[n-1][arr[n-1]]<<"\n";}
    else{
        int sum = 0;
        for(int i = 1; i<=m; ++i){
            (sum+=dp[n-1][i])%=MOD;
        }
        cout<<sum<<"\n";
    }
 
    return 0;
}

//COIN COMBINATIONS
/*
IDEA : The point to be specially noted here is that we need "ordered" combinations.
This means we can't use coin of value 2, after using 3 to make up the sum.
If we look at value of n=100,and x = 10^6, this hints that time complexity needed is somewhat O(n.x).
What we can do is go through all coins, and all possible sums. There will be two cases:
1- We can't use coin to make up the sum. In this case ways to make up the sum remain unchanged.
2- We can use coin. So number of ways to make up the sum will get increased by number of ways to make up total of (sum-coinVal).

After processing all ways we get desired answer
*/

#include <bits/stdc++.h>
using namespace std;   
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int n, k;
    cin>>n>>k;
    vector<int> coins(n);
    for(int &i : coins){cin>>i;}
    int MOD = 1e9+7;
    sort(coins.begin(),coins.end());
    vector<int> ways(k+1);
    ways[0] = 1;
    for(int i = 0; i<n; ++i){
        int coinVal = coins[i];
        for(int sum = 0; sum<=k; ++sum){
            ways[sum]+=(sum-coinVal >= 0 ? ways[sum-coinVal] : 0);
            ways[sum]%=MOD;
        }
    }
    cout<<ways[k]<<"\n";
    return 0;           
}

//COUNTING TOWERS
#include<iostream>
#include<bits/stdc++.h>
using namespace std;
//Increasing layers(bottom to top) : Representation (**)-> two closed one, (..)-> two open one, (^) ->one open, (!) -> one but closed 
int MOD = 1e9+7;
long long arr[1000001][2];      //arr[i][0] - No. of ways to make tower of height i, given that at (i-1)th height there were two dis-united tiles of width 1 each
                                //arr[i][1] - No. of ways to make tower of height i, given that at (i-1)th height there was 1 united tile of width 2
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int t; cin>>t;
    long long arr[1000001][2];      //Ignore this line
    arr[1][0] = 1;
    arr[1][1] = 1;
    for(int i = 2; i<=1000000; ++i){
        arr[i][0] = (2*arr[i-1][0])%MOD;    
        (arr[i][0] += arr[i-1][1] )%=MOD; 
        arr[i][1] = (4*arr[i-1][1])%MOD;
        (arr[i][1] += arr[i-1][0] )%=MOD;
    }
    while(t--){
        int n; cin>>n;
        cout<<(arr[n][0]+arr[n][1])%MOD<<"\n";
    }
    return 0;
}


//RECTANGLE CUTTING
#include<iostream>
#include<bits/stdc++.h>
using namespace std;

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int n,m; cin>>n>>m;
    vector<vector<int>> dp(n+1,vector<int>(m+1,100000001));        //dp[i][j] = Min cuts required if rectangle be of height i, and j column
    for(int i = 0; i<=min(m,n); ++i){dp[i][i] = 0;}     //It is already a square, so no cut needed
    for(int i = 1; i<=n; ++i){
        for(int j = 1; j<=m; ++j){
            //Cut Along the Row, such that below the cut has height k.
            //Now, we have divided into two rectangles of same columns but lower height, which we have already calculated.
            for(int k = 1; k<i; ++k){
                dp[i][j] = min(dp[i][j],dp[k][j]+dp[i-k][j]+1);
            }

            //Cut Along the Column, such that left of the cut has width k.
            //Now, we have divided into two rectangles of same height but width, which we have already calculated.
            for(int k = 1; k<j; ++k){
                dp[i][j] = min(dp[i][j],dp[i][k]+dp[i][j-k]+1);
            }
        }
    }
    cout<<dp[n][m]<<"\n";
    return 0;
}


//REMOVAL GAME
#include<bits/stdc++.h>
using namespace std;
/*
IDEA O(n^2): At each point of time we can choose only 1st or last element of the array.Lets say 1st player choose one element of the two, 
then now, we are left with a subarray of orginal array to choose from, and 2nd player to start with. 
E.g arr = [4,5,1,3]. 
If 1st player choose first, then - left [5,1,3](subarray - A), with 2nd player starting, or if
1st player chooses last , then - left with [4,5,1](subarray - B) with 2nd player turn to choose.
Now, if we had somehow known that for subarray A and B, what is the maximum score that a player can get by starting first, our task would become very easy(Lets call that posible score as maxSubarrScore coming through subarray A).
Now, if we will give subarray A to player2 to startwith, he will endup with score of maxSubarrScore, and we(1st player) will gain (Sum of all elements in subarrayA - maxSubarrScore) as a whole from subarray A.
So, our optimal strategy should be to choose either first or last element such that (first/last element)+(gain from the subarray) is maximum. 
Now, As we will be relying on past results, so DP comes into picture.

dp[i][j] = maxScore that a player can get, if that player starts first and array into consideration is {arr[i],arr[i+1],---,arr[j]}.
score[i] = score[i] = Running Sum of all arr elements till(including) ith index. i.e sum(arr[0]+arr[1]+----+arr[i])

Now, for dp[i][j], we can only choose either arr[i](first), or arr[j](last), and so, our dp relation will look something like:
dp[i][j] = max((arr[i]+(score[j]-score[i]-dp[i+1][j])),  (arr[j]+(score[j-1]-score[i-1]-dp[i][j-1]))
*/

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);
	int n; cin>>n;
	vector<long long>arr(n);
	vector<long long>score(n);		
	vector<vector<long long>> dp(n,vector<long long>(n));
	cin>>arr[0];
	dp[0][0] = arr[0];
	score[0] = arr[0];
	for(int i = 1; i<n; ++i){
		cin>>arr[i];
		dp[i][i] = arr[i];		//only element will be arr[i]. 
		score[i] = score[i-1]+arr[i];
	}
	for(int i = n-2; i>=0; --i){
		for(int j = i+1; j<n; ++j){
			long long first = arr[i]+(score[j]-score[i]-dp[i+1][j]);
			long long last = arr[j]+(score[j-1]-(i == 0 ? 0 : score[i-1])-dp[i][j-1]);
			dp[i][j] = max(first,last);		//choose from where max score is possible.
		}
	}
	cout<<dp[0][n-1]<<"\n";
	return 0;
}


//PROJECTS
#include<bits/stdc++.h>
using namespace std;
/*
IDEA(O(nlogn)) : We will first sort the elements as per their ending time (why ending time ? ). 
Now projects will start coming in their end-time sorted order. For each project we have two choices - either do the project or don't do the project.
1- IF WE DO THE PROJECT : 
Then the last project that we must have done must had end time smaller than the current project's start day. So we need a good mechanism to find that.
There can be two easy ways do find that last project : 
a) Use array and binary search to get the last project .
b) Use a map and then use lower_bound to get the last project. I have used this optiion , but you can definately go with 1st approach as it will be little faster.

2- IF WE IGNORE THE PROJECT : 
In this case we will only get the reward that we were getting considering only previous projects.
*/


//Sort on the basis of end time. WHY?
bool cmp(vector<int> a, vector<int> b){return a[1] < b[1];}

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);
	int n; cin>>n;
	vector<vector<int>> projects(n, vector<int>(3));
	map<int , long long> reward; //reward - {key : end day, value : maxReward possible considering projects having deadline/end day <=key} 
	reward[0] = 0;
	long long maxReward = 0;			//maxReward that can be earned so far. 

	for(auto &project : projects){cin>>project[0]>>project[1]>>project[2];}
	sort(projects.begin(), projects.end(), cmp);	//Sort by the ending time of the projects.

	for(auto &project : projects){
		int start = project[0];
		int end = project[1];
		int money = project[2];
		auto itr = reward.lower_bound(start); --itr; 	//We need to do --itr, to get to the ending day that is strictly smaller than the start.
		long long takeThisProject = itr->second+money; 
		long long notTake = maxReward;
		reward[end] = max(takeThisProject, notTake);
		maxReward = reward[end];
	}
	cout<<maxReward<<"\n";
	return 0;
}

//COUNTING NUMBERS
/*
Nss = number of digits such that no adjancent digits are same. 
This problem is very good to solve and very good explaination has been provided here. https://www.youtube.com/watch?v=TN0qGN0YqDQ
Now let, solve(n) = Nss between 0 and n(including). 
So,our answer would be simply = solve(b)-solve(a-1).
But wait , how to actually solve the "solve"?
You guessed it right , dp comes to our rescue. 
dp[i] = Nss for all i digit number. = (9x9x9---i times) = (9^i) {we can always fill jth (<=i) place in 9 ways}. 
Now for any digit "c", we can always form words summation(dp[i]), where i < c
The main problem lies in finding exact "c" letter words that satisfy the conditiions, and we can again do that using our dp and small maths. 
*/
 
#include<bits/stdc++.h>
using namespace std;
long long dp[19];			//dp[i] - No. of ways to make Nss of i digits.

long long countNssDigit(string num, int index){
	if(index == num.size()){return 0;}
	int numAtIndex = num[index]-'0';
	long long waystoFillIndexPos = numAtIndex;
	if(num[index-1]-'0' < numAtIndex){--waystoFillIndexPos;}
	if(num[index-1]-'0' == numAtIndex){
		return (waystoFillIndexPos*dp[num.size()-1-index]);
	}
	return (waystoFillIndexPos*dp[num.size()-1-index])+countNssDigit(num, index+1);
}
 
//It return number of Nss lying between [a,0].
long long solve(long long a){
	if(a == -1){return 0;}		//As inputs can be 0 as well and we are also passing (input-1), so we need to handle this case. 
	long long Nss = 0;			//Our Nss count. 
	string num = to_string(a);
	for(int i = 0; i<num.size(); ++i){Nss+=dp[i];}		//Count all Nss having digits less than "a".

	//Now we need to count Nss for digits exactly equal to that of "a".
	//We can always choose number smaller than current MSB-most significant bit(here number) (1st digit from left), and then make subsequent(right afterwards) places fill through our dp.
	Nss+=((num[0]-'0'-1)*(dp[num.size()-1]));	//NSs having same digit count as "a", but starting with lower number , than original "a"'s MSB.	
	Nss+=countNssDigit(num,1);	//Similarly go for other indexes as well		
	++Nss;			//Assume Original number doesn't have any consecutive same numbers.
	char s = num[0];
	for(int i = 1; i<num.size(); ++i){
		if(num[i] == s){--Nss; break;}			//Assumption was wrong, so decrease the count. 
		s = num[i];
	}
	return Nss;
}
 
int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);
	long long a,b; cin>>a>>b;
	long long ways = 0;
	dp[0] = 1;
	for(int i = 1 ; i<=18; ++i){dp[i] = 9*dp[i-1];}
	cout<<solve(b)-solve(a-1)<<"\n";
	return 0;
}