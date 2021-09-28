// written by Hardik Bajaj, IIT2019039, IIITA

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
		vector<vector<int>>g(m,vector<int>(n,0));
		for(int i=0; i<k; i++){
			int a,b;cin>>a>>b;
			g[a][b] = 1;
		}
		int ini;cin>>ini;
		int ans = -1;
		set<pair<pair<int,vector<pair<int,int>>>,pair<int,int> >> s;
		vector<pair<int,int>>path = { {ini,0} };
		map<pair<int,int>,int> mp;
		
		pair<int,int>ps = {ini,0};
		
		vector<pair<int,int>>anss;
		s.insert({{0,path},ps});
		while(!s.empty()){
			auto state = *s.begin();
			auto pos = state.second;
			int cost = state.first.first;
			auto path = state.first.second;
			if(pos.second == n-1){
				if(ans == -1){ans=cost;
					anss = path;
				}
				if(ans != -1){
					if(path < anss)anss = path;
				}
			}
			if(ans!= -1 && cost > ans){
				break;
			}

			s.erase(s.begin());
			if(mp.find(pos) != mp.end()){
				continue;
			}
			else mp[pos] = cost;

			// 2 ahead, 1 ahead, and left or right
			if(can2ahead(g,pos)){
				path.push_back({pos.first, pos.second+2});
				s.insert({{cost+1,path}, {pos.first, pos.second+2}});
				path.pop_back();
			}
			if(can1ahead(g,pos) && can2ahead(g,pos)){
				path.push_back({pos.first, pos.second+1});
				s.insert({{cost+1,path},{pos.first,pos.second+1}});
				path.pop_back();
			}
			if(canLeft(g,pos)){
				path.push_back({pos.first-1, pos.second+1});
				s.insert({{cost+2,path},{pos.first-1,pos.second+1}});
				path.pop_back();
			}
			if(canRight(g,pos)){
				path.push_back({pos.first+1, pos.second+1});
				s.insert({{cost+2,path},{pos.first+1,pos.second+1}});
				path.pop_back();
			}

		}
		if(ans != -1)
		{
			//cout<<ans<<"\n";
			for(auto i: anss){
				cout<<i.first<<" "<<i.second<<"\n";
			}
		}
		else cout<<"NIL";
		cout<<"\n";
		// state- cost, position
		
	}
}
