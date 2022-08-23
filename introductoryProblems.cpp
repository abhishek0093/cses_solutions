#include<iostream>
#include<bits/stdc++.h>
using namespace std;


//INTRODUCTORY Problems

//CREATING STRINGS
#include<iostream>
#include<bits/stdc++.h>
using namespace std;

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    string s;
    cin>>s;
    map<char, int>mp;
    for(char c : s){++mp[c];}
    int deno = 0;
    for(auto p : mp){
        int freq = p.second;
        if(freq == 1){continue;}
        int add = 1;
        while(freq != 1){
            add*=freq;
            --freq;
        }
        deno+=add;
    }
    if(deno == 0){deno = 1;}
    int num = 1;
    int sSize = s.size();
    while(sSize != 1){
        num*=sSize;
        --sSize;
    }
    cout<<num/deno<<"\n";
    sort(s.begin(), s.end());
    cout<<s<<"\n";
    while(next_permutation(s.begin(), s.end())){
        cout<<s<<"\n";
    }
    return 0;
}

//Q-> NUMBER SPIRAL
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int t;
    cin>>t;
    while(t--){
        long long r,c;
        cin>>r>>c;      //row and column
        long long curr = (max(r,c)*max(r,c))-max(r,c)+1;        //curr = nth diagonal term. Differences of diagonal term is in AP, so will be of the form an2+bn+c, and here a = 1, b= -1, c =1;
        if(r >= c){     //For odd rows, number decreases on moving left, while it increases for even number rows.
            if(r%2){
                cout<<curr-(r-c)<<"\n";
            }
            else{
                cout<<curr+(r-c)<<"\n";
            }
        }
        else{           //For even columns, number decreases on moving up, while it increases for odd row case.
            if(c%2 == 0){
                cout<<curr-(c-r)<<"\n";
            }
            else{
                cout<<curr+(c-r)<<"\n";
            }
        }
    }
    return 0;
}


//TWO SETS
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    long long n ;
    cin>>n;
    long long sum = (n*(n+1))/2;
    if(sum & 1){            //If Summation(n) is odd --> Not possile.
        cout<<"NO\n";
        return 0;
    }
    long long tar = sum/2;  //Target Sum for each set
    vector<int> A, B;
    cout<<"YES\n";
    for(int i = n; i>=1; --i){
        if(i<=tar){
            A.push_back(i);
            tar-=i;
        }
        else{
            B.push_back(i);
        }
    }
    cout<<A.size()<<"\n";
    for(int i : A){cout<<i<<" ";}
    cout<<"\n";
    cout<<B.size()<<"\n";
    for(int i : B){cout<<i<<" ";}
    cout<<"\n";
    return 0;
}


//TRAILING ZEROS
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int n;
    cin>>n;
    int fives = 0;
    while(n){           //In first round all 5's multiple taken into account, in 2nd 25's multiple, then 125..625.......
        fives+=n/5;
        n/=5;
    }
    cout<<fives<<"\n";
    return 0;
}


//TOWER OF HANOI
vector<pair<int, int>> arr;

void towerofHanoi(int n,int s, int m, int d){
    if(n >  0){
        towerofHanoi(n-1,s,d,m);            //shift first n-1 (from top on source stack) into middle tower(use dest towwer as helping)
        arr.push_back({s,d});               //shift bottommost into the destination 
        towerofHanoi(n-1,m,s,d);               //shift n-1 that in Middle tower to the dest tower (using source tower as intermediate)
    }
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int n;
    cin>>n;
    towerofHanoi(n, 1, 2 ,3);
    cout<<arr.size()<<"\n";
    for(auto i : arr){
        cout<<i.first<<" "<<i.second<<"\n";
    }
    return 0;
}

//PERMUTATIONS
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int n;
    cin>>n;
    vector<int> arr(n);
    if(n==2 || n == 3){
        cout<<"NO SOLUTION\n";
        return 0;
    }
    for(int i = 2; i<=n; i+=2){
        cout<<i<<" ";
    }
    for(int i = 1; i<=n; i+=2){
        cout<<i<<" ";
    }
    cout<<"\n";
    return 0;
}

//TWO KNIGHTS
#include<iostream>
#include<bits/stdc++.h>
using namespace std;

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    long long n;cin>>n;
    for(long long k = 1; k<=n; ++k){
        long long totalPossWays = ((k*k)*((k*k)-1))/2;     //(k^2)C1 for 1st knight, and (k^2-1)C1 and both knights are identical
        long long twoByThreeRecs = (k-2)*(k-1);
        cout<<(totalPossWays-(2*2*twoByThreeRecs))<<" ";
    }
    cout<<"\n";

    return 0;
}

//BIT STRINGS
#include<iostream>
#include<bits/stdc++.h>
using namespace std;

int MOD = 1e9+7; 

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int n; cin>>n;
    int ans = 1;
    while(n--){
        ans = (ans<<1)%MOD;
    }
    cout<<ans<<"\n";
    return 0;
}

//COIN PILES
#include<iostream>
#include<bits/stdc++.h>
using namespace std;

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int t; cin>>t;
    while(t--){
        int left,right; cin>>left>>right;
        long long sum = left+right;
        if(sum % 3 == 0 && max(left,right) <= 2*min(left,right)){cout<<"YES\n";}
        else{cout<<"NO\n";}
    }
    return 0;
}

//PALINDROME REORDER
#include<iostream>
#include<bits/stdc++.h>
using namespace std;

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    vector<int> freq(26,0);
    string s; cin>>s;
    int n = s.size();
    vector<char> reserve;
    for(char c : s){++freq[c-'A'];}
    int pos = 0;
    int i = 0;
    while(i < n/2 && pos < 26){
        if(n%2 == 0 && freq[pos]%2){
            cout<<"NO SOLUTION\n";
            return 0;
        }
        int times = freq[pos]/2;
        while(times--){
            s[i] = char(pos+'A');
            s[n-1-i] = char(pos+'A');
            freq[pos]-=2;
            i++;
        }
        if(freq[pos]){
            reserve.push_back(char(pos+'A'));
            --freq[pos];
        }
        if(reserve.size()>1){
            cout<<"NO SOLUTION\n";
            return 0;
        }
        ++pos;
    }
    if(n%2){
        s[n/2] = reserve.size() ? reserve[0] : char(pos+'A');
    }
    cout<<s<<"\n";

    return 0;
}

//DIGIT QUERIES
#include<iostream>
#include<bits/stdc++.h>
using namespace std;

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int q; cin>>q;
    while(q--){ //SEE PATTERN : 1digit - 9, 2digit- 90, 3digit-900, ----and so on...
        long long k; cin>>k;
        long long curr = 9;
        long long zeros = 0;  
        while(k-(curr*(zeros+1)) >= 0){     //Find the number of digits in the number that lies at the kth place, let it be n digit number   
            k-=(curr*(zeros+1));
            curr*=10;
            ++zeros;
        }
        long long complete = k/(zeros+1);       //These are the count of complete n digits number that can be formed
        long long partial = k%(zeros+1);
        string base(zeros+1,'0');
        base[0] = '1';          //Now base is the number that is the first number of digit == n
        long long number = stoll(base)+complete-1;
        if(partial == 0){
            string ans = to_string(number);
            cout<<ans.back()<<"\n";
        }
        else{
            string ans = to_string(number+1);
            cout<<ans[partial-1]<<"\n";
        }

    }
    return 0;
}

//APPLE DIVISION
#include<iostream>
#include<bits/stdc++.h>
using namespace std;

long long calculateMin(int index, long long sA, long long sB, vector<long long>&wts){
    if(index >= wts.size()){return abs(sA-sB);}
    return min(calculateMin(index+1,sA+wts[index],sB,wts),calculateMin(index+1,sA,sB+wts[index],wts));
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int n; cin>>n;
    vector<long long> wts(n);
    for(long long &i : wts){cin>>i;}
    long long sA = wts[0];
    if(wts.size() == 1){cout<<wts[0]<<"\n"; return 0;}
    long long sB = 0;
    cout<<calculateMin(1,sA,sB,wts)<<"\n";
    return 0;
}

//GRAY CODES
/*
IDEA : The key idea here is to understand the pattern followed. 
See for n = 3, we observe following : 
000    001       011     010    110		111		101		100.
Now if you observe that as soon as we complete some 2^k numbers of gray code out of total 2^n graycodes, we will have to invert bit at index (n-k-1) from 0 to 1, to continue to find new codes (as all codes of length k have exhausted).
Now if you observe carefully, from the previous number , we are only changing 1 bit at (n-k-1)th position, so it will be continuation of previous grayCode.
Also if we go in reverse direction in grayCodes found so far and keep inverting bit at (n-k-1) position, we will observe that we keep forming new grayCodes.
000 --> (2^0) gCs found, so we need to flip (n-1-k = 2th) index bit, to get next grayCode. We need to do this for all grayCodes found so far, but traversing in reverse direction.
{000,001} ---> (2^1) gCs found, so we need to flip (n-1-k = 1st) index bit, to get next grayCode.We need to do this for all grayCodes found so far, but traversing in reverse direction.
{000,001,011,010}, again repeat here k = 2, so we need to flip bits at index 0.
{000, 001,011,010,110,111,101,100}. 
*/

#include<bits/stdc++.h>
using namespace std;

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);
	int n; cin>>n;
	vector<string> grayCode;		//gCs found so far.
	string s = string(n,'0');
	grayCode.push_back(s);
	int pos = n-1;		//Position where bit needs to be flipped from 0 to 1.
	for(int i = 0; i<n; ++i){
		//Traverse the gCs in reverse direction, and flip the bits at pos index.
		for(int j = grayCode.size()-1; j>=0; --j){
			string s = grayCode[j];
			s[pos] = '1';
			grayCode.push_back(s); 
		}
		--pos;
	}
	for(string code : grayCode){cout<<code<<"\n";}
	return 0;
}

//GRID PATHS
/*
IDEA : This question deals with optimazations in backtracking. 
This question has been very beautifully explained at pageN0.52 of this book. Please have a look - https://cses.fi/book/book.pdf
But you will notice that even after applying all these optimazations your code will give TLE in 2 test cases, and that because we need even one more optimazation. 
I would encourage you to please go through this video  from 12:00 to 15:00 see the need for this optimazation. 
And as you get the crux of the optimazations writing code is fairly simple. 
*/

#include<bits/stdc++.h>
using namespace std;
string path;
vector<int> dirs = {0,1,0,-1,0};		//Our direction array to help us move L,R,U,D. 
map<char, pair<int,int>> mp;			//mp stores direction (U,L,R,D) as key, and their corresponding mathematical notation as pairs. E.g to move downwards means increasing row by 1, and remaining in same column. so, mp['D'] = {1,0}. 
long long  matches = 0;				//Count of paths matching description.
bool visited[7][7];				//Our visited array

void matchPaths(int i, int r, int c){		//i is current index(our movement position) in path string, (r/c) is row/column index where we are standing.
	if(r>=7 || c >=7 || r<0 || c<0 || visited[r][c] || (i!=48 && r == 6 && c == 0)){return;}			//check validity and optimization 2 of book.
	if(i == 48 && r == 6 && c == 0){++matches; return;}			//We Found a matching path!

	//Optimization 3 and 4 of book
	if( ( r == 0 || ((r-1) < 7 && (r-1) >=0 && visited[r-1][c])) && (r == 6 || ((r+1) < 7 && (r+1) >=0 && visited[r+1][c])) && ((c-1)>=0 && (c-1)<7 && !visited[r][c-1]) && ((c+1)>=0 && (c+1)<7 && !visited[r][c+1])){return;}		//Both Up and down have been visited, but both left and right sides are unvisited.
	if(( c == 0 || ((c-1) < 7 && (c-1) >=0 && visited[r][c-1])) && ( c == 6 || ((c+1) < 7 && (c+1) >=0 && visited[r][c+1])) && (r-1)>=0 && (r-1)<7 && !visited[r-1][c] && (r+1)>=0 && (r+1)<7 && !visited[r+1][c]){return;}			////Both left and right have been visited, but both up and down sides are unvisited.

	//Additional optimization, explained in video. 
	if(((r-1) >= 0 && (r-1) < 7 && (c-1) >= 0 && (c-1)<7 && visited[r-1][c-1]) && (!visited[r-1][c]) && (!visited[r][c-1])){return;}
	if(((r-1) >= 0 && (r-1) < 7 && (c+1) >= 0 && (c+1)<7 && visited[r-1][c+1]) && (!visited[r-1][c]) && (!visited[r][c+1])){return;}
	if(((r+1) >= 0 && (r+1) < 7 && (c+1) >= 0 && (c+1)<7 && visited[r+1][c+1]) && (!visited[r+1][c]) && (!visited[r][c+1])){return;}
	if(((r+1) >= 0 && (r+1) < 7 && (c-1) >= 0 && (c-1)<7 && visited[r+1][c-1]) && (!visited[r+1][c]) && (!visited[r][c-1])){return;}

	visited[r][c] = true;

	//We have direction defined by given string, so move in that direction only. Else, we will explore all the four possible directions .
	if(path[i] != '?'){matchPaths(i+1,r+mp[path[i]].first,c+mp[path[i]].second);}
	else{	
		for(int j = 0; j<4; ++j){
			int row = r+dirs[j];
			int col = c+dirs[j+1];
			matchPaths(i+1,row,col);	
		}
	}
	//Backtrack.
	visited[r][c] = false;
}

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);
	cin>>path;
	mp['R'] = {0,1};
	mp['L'] = {0,-1};
	mp['U'] = {-1,0};
	mp['D'] = {1,0};
	matchPaths(0,0,0);
	cout<<matches<<"\n";
	return 0;
}