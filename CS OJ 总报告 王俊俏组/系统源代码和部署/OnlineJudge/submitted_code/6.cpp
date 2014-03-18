/*-----this comment added by system------------------
user: zjut_DD
probID: 1001
-----------------------------------------------------*/
#include <vector>
#include <map>
#include <set>
#include <deque>
#include <stack>
#include <bitset>
#include <algorithm>
#include <functional>
#include <numeric>
#include <utility>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <cstdio>
#include <queue>
#include <cmath>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <string>

using namespace std;

//***********zjut_DD for Topcoder***********
typedef long long int64;
typedef unsigned long long uint64;

typedef pair<int,int> PII;
typedef pair<int64,int64> PLL;
typedef vector<int> VI;
typedef vector<string> VS;
typedef vector<PII> VPII;
typedef map<string,int> MSI;
typedef map<string,string> MSS;

#define PB push_back
#define ALL(v) v.begin(),v.end() 

#define clr(buf,val) memset(buf,val,sizeof(buf)) //clear memory

#define forl(i,s,t) for(int i=s;i< t;i++) //less   [s,t)
#define fore(i,s,t) for(int i=s;i<=t;i++) //equal  [s,t]
#define ford(i,t,s) for(int i=t;i>=s;i--) //down [s,t] t->s
#define forv(i,v) for(int i=0;i<(int)v.size();i++)  //vector
#define fors(i,s) for(int i=0;i<(int)s.length();i++)//string
//******************************************

#define maxn 550

char ch[maxn];
int fix[maxn][maxn];
bool vst[maxn][maxn];

int dfs(int a,int b){
	if( a>b ) return 0;
	if( vst[a][b] ) return fix[a][b];
	vst[a][b]=true;
	if( a==b ) return fix[a][b]=0;
	
	if( ch[a]==ch[b] ) return fix[a][b]=dfs(a+1,b-1);
	else return fix[a][b]=1+dfs(a+1,b-1);
}

struct DD{
	int val,last;
}dp[maxn][maxn];

PII ans[maxn];
int cnt;

void gao(int a,int b){
	if( a>b ) return;
	if( ch[a]==ch[b] ) return gao(a+1,b-1);
	else {
		ch[a]=ch[b];
		return gao(a+1,b-1);
	}
}

int main(){
	int K;
	while( scanf(" %s %d",ch+1,&K)!=EOF ){
		int len=strlen(ch+1);
		memset(vst,false,sizeof(vst));
		for(int i=1;i<=len;i++){
			for(int j=i;j<=len;j++){
				dfs(i,j);
			}
		}
		for(int i=0;i<=len;i++) for(int j=0;j<=len;j++) dp[i][j].val=1000000;
		
		dp[0][0].val=0;
		for(int i=0;i<len;i++){
			for(int k=0;k<K;k++){
				if( dp[i][k].val>=1000000 ) continue;
				for(int y=i+1;y<=len;y++){
					int x=i+1;
					int val=dp[i][k].val+fix[x][y];
					if( dp[y][k+1].val>val ){
						dp[y][k+1].val=val;
						dp[y][k+1].last=i;
					}
				}
			}
		}
		int bk, mi=1000000;
		for(int k=0;k<=K;k++){
			if( dp[len][k].val<mi ){
				mi=dp[len][k].val;
				bk=k;
			}
		}
		
		printf("%d\n",mi);
		cnt=0;
		int y=len;
		while( y ){
			ans[cnt].first=dp[y][bk].last+1;
			ans[cnt].second=y;
			//printf("first: %d second: %d\n",ans[cnt].first,ans[cnt].second);
			cnt++;
			y=dp[y][bk].last;
			bk--;
		}
		sort(ans,ans+cnt);
		for(int i=0;i<cnt;i++){
			if( i ) putchar('+');
			//printf("  first: %d second: %d\n",ans[i].first,ans[i].second);
			gao(ans[i].first,ans[i].second);
			for(int j=ans[i].first;j<=ans[i].second;j++) putchar(ch[j]);
		}
		puts("");
	}
}





