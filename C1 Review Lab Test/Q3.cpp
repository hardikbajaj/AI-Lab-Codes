#include<bits/stdc++.h>
using namespace std;
typedef long long int ll;
#define pb push_back
#define ff first
#define se second
#define mp make_pair
#define M 1000000007

bool can2ahead (vector< vector<int> >g, pair<int,int>pos){
	int n =g.size();int m =g[0].size();
	if(pos.second+1 >=m-1)return 0;
	else{
		return((g[pos.first][pos.second+1] == 0) && (g[pos.first][pos.second + 2] == 0));
	}
}

bool can1ahead (vector< vector<int> >g, pair<int,int>pos){
	int n =g.size();int m =g[0].size();
	if(pos.second+1 >=m)return 0;
	else{
		return( (g[pos.first][pos.second+1] == 0) );
	}
}
bool canLeft (vector< vector<int> >g, pair<int,int>pos){
	//  i --
	int n =g.size();int m =g[0].size();
	
	int x = pos.first;
	int y = pos.second;
	if(x == 0)return 0;
	if(pos.second+1 >=m)return 0;
	return ( (g[x-1][y] == 0) && (g[x-1][y+1] == 0) && (g[x][y+1] == 0) );
}

bool canRight (vector< vector<int> >g, pair<int,int>pos){
	//  i --
	int n =g.size();int m =g[0].size();
	int x = pos.first;
	int y = pos.second;
	if(x == n-1)return 0;
	if(pos.second+1 >=m)return 0;
	return ( (g[x+1][y] == 0) && (g[x+1][y+1] == 0) && (g[x][y+1] == 0) );
}

int main()
{

	ios::sync_with_stdio(0);
    cin.tie(0);

	#ifndef ONLINE_JUDGE
	freopen("input.txt","r",stdin);
	freopen("output.txt", "w", stdout);
	#endif

	int t;cin>>t;
	while(t--){
		int m,n,k;
		cin>>m>>n>>k;
		vector<vector<vector<int>>> v (n+1);
		vector<vector<int>>g(m,vector<int>(n,0));
		v[n] = g;
		for(int i=0; i<k; i++){
			int a,b;cin>>a>>b;
			g[a][b] = 1;
		}
		int ini;cin>>ini;
		int ans = -1;

		
		v[0] = g;
		for(int k=1; k<n; k++){
			for(int i=0; i<m; i++){
				if(g[i][n-1] == 1)g[i][n-1]=0;
				for(int j=1; j<n; j++){
					if(g[i][j-1] == 1){
						g[i][j]=1;
						g[i][j-1] =0;
						j++;
					}
				}
			}
			v[k] = g;
		}
		// for(int k=0; k<n; k++){
		// 	for(int i=0; i<m; i++){
		// 		for(int j=0; j<n; j++){
		// 			cout<<v[k][i][j]<<" ";
		// 		}
		// 		cout<<"\n";
		// 	}
		// 	cout<<"\n";
		// }
		
		set<pair<pair<int,int>,pair<int,int> >> s;
		
		pair<int,int>ps = {ini,0};
		s.insert({{0,0},ps});
		while(!s.empty()){
			auto state = *s.begin();
			auto pos = state.second;
			int cost = state.first.first;
			int time= state.first.second;
			if(pos.second == n-1){
				ans=cost;break;
			}
			s.erase(s.begin());
			if(time>n)time=n;
			// 2 ahead, 1 ahead, and left or right
			if(can2ahead(v[time],pos)){
				s.insert({{cost+1,time+1}, {pos.first, pos.second+2}});
			}
			if(can1ahead(v[time],pos)){
				s.insert({{cost+1,time+1},{pos.first,pos.second+1}});
			}
			if(canLeft(v[time],pos)){
				s.insert({{cost+2,time+1},{pos.first-1,pos.second+1}});
			}
			if(canRight(v[time],pos)){
				s.insert({{cost+2,time+1},{pos.first+1,pos.second+1}});
			}

		}
		if(ans != -1)
		cout<<ans<<"\n";
		else cout<<"NIL \n";
		// state- cost, position
		
	}
}