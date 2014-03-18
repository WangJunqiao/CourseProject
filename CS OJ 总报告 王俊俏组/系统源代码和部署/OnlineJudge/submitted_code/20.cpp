/*-----this comment added by system------------------
user: 111
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
#define Clear(buf,val) memset(buf,val,sizeof(buf)) //clear memory
#define Forl(i,s,t) for(int i=s;i< t;i++) //less   [s,t)
#define Fore(i,s,t) for(int i=s;i<=t;i++) //equal  [s,t]
#define Ford(i,t,s) for(int i=t;i>=s;i--) //down [s,t] t->s
#define Forv(i,v) for(int i=0;i<(int)v.size();i++)  //vector
#define Fors(i,s) for(int i=0;i<(int)s.length();i++)//string
//******************************************




int pa[55000];
int find(int u){
	return pa[u]==u?u:pa[u]=find(pa[u]);
}
void createTreeEdge(int n){
	for(int i=0;i<n;i++) pa[i]=i;
	for(int i=1;i<n;i++){
		int a,b;
		do{
			a=rand()*rand()%n;
			b=rand()*rand()%n;
		}while( find(a)==find(b) );
		printf("%d %d\n",a+1,b+1);
		pa[find(a)]=find(b);
	}
}


int64 getInt64(int len){
	int64 ret=rand()%9+1;
	for(int i=1;i<len;i++){
		ret=10*ret+rand()%10;
	}
	return ret;
}

int x[55000];

void create(int n){
	int sum=0;
	for(int i=0;i<=n;i++){
			x[i]=rand();
			sum+=x[i];
		}
	printf("%d\n",n);
	for(int i=0;i<=n;i++) printf("%.8lf\n",x[i]/(double)sum);
}

int main(){
	freopen("in.txt","w",stdout);
	
	srand(time(NULL)); //每次运行都不
	
	for(int i=0;i<=20;i++) create(i);
	int cas=4;
	//cout<<cas<<endl;
	while( cas-- ){
		create(rand()%20000+1);
		puts("");
	}
	create(50000);
	//system("notepad in.txt");
}





















