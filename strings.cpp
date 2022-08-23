//STRING ALGORITHM 
//STRING MATCHING 
/*
This is an classic example problem of Z algorithm. We can also use other algorithm such as hashing.  
*/
#include<bits/stdc++.h>
using namespace std;

int matchCount = 0;
int m;
vector<int> calculateZArray(string str){
	int n = str.size();
	vector<int> zArray(n);
	int L = 0, R = 0;
	for (int i = 1; i < n; i++) {
	  if (i > R) {
	    L = R = i;
	    while (R < n && str[R-L] == str[R]) R++;
	    zArray[i] = R-L; R--;
	  }
	  else{
	    int k = i-L;
	    if (zArray[k] < R-i+1) zArray[i] = zArray[k];
	    else {
	      L = i;
	      while (R < n && str[R-L] == str[R]) R++;
	      zArray[i] = R-L; R--;
	    }
	  }
	  if(zArray[i] == m){++matchCount;}
	}
	return zArray;
}

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);
	string str, patt ; cin>>str>>patt;
	m = patt.size();
	string final = patt+"$"+str;
	calculateZArray(final);
	cout<<matchCount<<"\n";
	return 0;
}


//FINDING BORDERS
/*
IDEA : Idea is very simple. A substr starting at k is a border exactly when zArray[k] + k = n. WHY?It is simple to infer.
We don't need to bother about prefix border, as by definition of zArray it will be taken care of.
Now, we want our zArray[k] to always end(i.e our matching pattern consisting of str[k]....str[n-1]) at array's end as then only it will be counted as a suffix-border.
So, we want our ,
zArray[k] = (n-k), to end with array's end. ===> zArray[k]+k = n.
*/

#include<bits/stdc++.h>
using namespace std;
 
bool borders[1000001];
int n;
void calculateZArray(string str){
	vector<int> zArray(n);
	int L = 0, R = 0;
	for (int i = 1; i < n; i++) {
	  if (i > R) {
	    L = R = i;
	    while (R < n && str[R-L] == str[R]) R++;
	    zArray[i] = R-L; R--;
	  }
	  else{
	    int k = i-L;
	    if (zArray[k] < R-i+1) zArray[i] = zArray[k];
	    else {
	      L = i;
	      while (R < n && str[R-L] == str[R]) R++;
	      zArray[i] = R-L; R--;
	    }
	  }
	  if(zArray[i]+i == n){borders[i] = 1;}			//Condition for a suffix (str[i],...,str[n-1]) to be a border. 
	}
}
 
int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);
	string str; cin>>str;
	n = str.size();
	calculateZArray(str);
	for(int i = n-1; i>=0; --i){
		if(borders[i]){cout<<n-i<<" ";}
	}
	cout<<"\n";
	return 0;
}


//Finding Periods
/*
IDEA :
i will be period of string str if and only if zArray[i]+i >=n.
*/

#include<bits/stdc++.h>
using namespace std;
 
vector<int> zArray(1000001,0);
int n;
void calculateZArray(string str){
	int L = 0, R = 0;
	for (int i = 1; i < n; i++) {
	  if (i > R) {
	    L = R = i;
	    while (R < n && str[R-L] == str[R]) R++;
	    zArray[i] = R-L; R--;
	  }
	  else{
	    int k = i-L;
	    if (zArray[k] < R-i+1) zArray[i] = zArray[k];
	    else {
	      L = i;
	      while (R < n && str[R-L] == str[R]) R++;
	      zArray[i] = R-L; R--;
	    }
	  }
	}
}
 
int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);
	string str; cin>>str;
	n = str.size();
	calculateZArray(str);
	for(int i = 0; i<=n; ++i){
		if(i+zArray[i] == n){cout<<i<<" ";}
	}
	cout<<"\n";
	return 0;
}


//ADDITIONAL PROBLEMS
//COUNTING BITS
/*
Idea : Very Good approach shown here . https://www.youtube.com/watch?v=g6OxU-hRGtY   (Sorry, if you don't know hindi :( Maybe, reading code may help you to get  the idea.)
But, here I have used the same idea, but instead of recursion have used dp and iterative approach.
*/

#include<bits/stdc++.h>
using namespace std;

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);
	long long n; cin>>n;
    long long dp[50];		//dp[i] = count of set bits int numbers 0,1,2,3----,(2^i)-1. i.e, dp[3] = count of set bits in (0,1,2,3,4,5,6,7, i.e first 2^3 whole numbers).
    dp[0] = 0;
    for (int i = 1; i < 50; i++){ dp[i] = i*(1LL<<(i-1));}
	long long ans = 0;
	//We will use the fact that any number n, can be written as some combination of 2's exponents (e.g 19 = 2^4+2^1+2^0).
	while(n!=0){
		long long nearest2Expo = (long long) log2(n);		//exponent in number which is just smaller number(or equal) than n and is some power of 2.(For n = 11, it will be 3 (2^3 = 8)).
		long long nearest2powerNum = 1LL<<nearest2Expo;		//Number just smaller/equal to n, which is also some power of 2.

		ans+=(dp[nearest2Expo]+(n-nearest2powerNum+1));		//First term comes from dp's defination, while second term is count of all MSB 1(s), in numbers (nearest2Num,nearest2Num+1...,n). See Video for details. 
		n = n-nearest2powerNum;
	} 
	cout<<ans<<"\n";
	return 0;
}

//ADVERTISEMENT
/*
IDEA : One of the naive approach would be to go to every advertisement board and treat its height(h0) as the height of our rectangle, R0 having area A0.
Now to calculate the area of the rectangle R0, we also need to know the width . We can extend the width to either side of current board as long as height of the board continues to be greater than/or equal to the h0.
But as you guessed it, it would be O(n^2) complexity. Can we do something better?
What if beforehand know that for any index i(board position), what is the max index upto which we can extend the current board width. Then our task to calculate the area would become constant for any given h0, and we can process all heights in O(n) time.
But how to get this width?
To get extensible width to the left of index i, we can create a leftViolate array, such that leftViolate[i] contains  index j, such that j is the first index to the left where hts[j]<hts[i], i.e we can't extend our h0 height rectagle there.
And similarily to get RHS width extension length we can use another rightViolate array.
And use previous results to calculate left(/right)Violate[i] faster. 
Let's assume i = 9, and hts[9] = 35. Now we will assume that index j is the first where hts[j] < hts[i]. We start by assuming j to be index just before i(j=8). If it is the case, we have found the leftViolate[i].
But if ht[j] >=hts[i] and leftViolate[j] = k (let's say hts[8] = 89 and leftViolate[8] = 3), then we can be sure that our nextViolateIndex can't be (k+1,k+2,----j), so we will shift our next potential j's index to be k. (In our example we don't need to check index 4,5,6,7,8, as leftViolate[8] = 3, this means at index = 3, we have for first time number less than 89, so midway number at any cost are greater than our hts[i](=35)).
I know it has become a little messy, but reading the code will help.  
*/

#include<bits/stdc++.h>
using namespace std;

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);
	int n; cin>>n;
	vector<long long> hts(n);
	for(long long &i : hts){cin>>i;}
	vector<int> leftViolate(n);		//leftViolate[i] contains  index j, such that j is the first index to the left of i where hts[j]<hts[i]
	vector<int> rightViolate(n);	//rightViolate[i] contains  index j, such that j is the first index to the right of i where hts[j]<hts[i]
	rightViolate[n-1] = n;			//There is nothing on the right of last index. 	
	leftViolate[0] = -1;			//Nothing in left of first board.

	//Calculate leftViolate array. 
	for(int i = 1; i<n; ++i){
		int potentialIndex = i-1;
		while(potentialIndex >= 0 && hts[potentialIndex] >= hts[i]){
			potentialIndex = leftViolate[potentialIndex];
		}
		leftViolate[i] = potentialIndex;
	}

	//Calculate rightViolate array
	for(int i = n-2; i>=0; --i){
		int potentialIndex = i+1;
		while(potentialIndex < n && hts[potentialIndex] >= hts[i]){
			potentialIndex = rightViolate[potentialIndex];
		}
		rightViolate[i] = potentialIndex;
	}
	long long maxArea = 0;
	for(int i = 0; i<n; ++i){
		long long area = hts[i]*(rightViolate[i]-leftViolate[i]-1);		//Treat hts[i] to be the height of the current rectnagle into consideration. 
		maxArea = max(maxArea,area);
	}
	cout<<maxArea<<"\n";
	return 0;
}


//MISSING COIN SUM
/*
One of the obvious approach would be to generate all the possible sum
and, then check which minimum isn't possible. But ofCourse given time 
and space , it will not pass all the testCases. 
Sorting of the array will give us a direction to move. 
Let's say we are at index i, and considering all the indices upto (i-1)
we can make all the sum in the range (1-K) such that (k+1) is our candidate 
for smallest non-possible sum. 

Now two cases arises : 
1) arr[i] <= (k+1), then we can make all the sum upto (arr[i]+k+1), why? 
K+1 can be made using arr[i]+(1=< (K+1-arr[i]) <=k) and so on. 
Now see, if arr[i] > (k+1), then we can't make (k+1) using any combination. why? 
Because max sum we were able to make was K, and arr[i](and all later elements as well) > k+1, hence there is no way to make sum of k+1. 
*/
#include<iostream>
#include<bits/stdc++.h>
using namespace std;
 
int main(){
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  long long n;
  cin>>n;
  vector<long long> arr(n);
  for(auto &i : arr){cin>>i;}
  sort(arr.begin(), arr.end());
  long long nposs = 1;
  for(long long i : arr){
      if(i <= nposs){
          nposs+=i;
      }
      else{
          break;
      }
  }
  cout<<nposs<<"\n";
  return 0;
}